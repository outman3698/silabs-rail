/***************************************************************************//**
 * @file debug_ci.c
 * @brief This file implements the debug commands for RAIL test applications.
 * @copyright Copyright 2015 Silicon Laboratories, Inc. http://www.silabs.com
 ******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "bsp.h"
#include "command_interpreter.h"
#include "response_print.h"
#include "rail_types.h"

#include "rail.h"
#include "app_common.h"

/*
 * setFrequency
 *
 * Allows the user to set an arbitrary frequency if
 * the frequency override debug mode is enabled.
 */
void setFrequency(int argc, char **argv)
{
  uint32_t newFrequency = ciGetUnsigned(argv[1]);

  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0]))
  {
    return;
  }

  if ((RAIL_DebugModeGet() & RAIL_DEBUG_MODE_FREQ_OVERRIDE) == RAIL_DEBUG_MODE_FREQ_OVERRIDE)
  {
    if (!RAIL_DebugFrequencyOverride(newFrequency)) {
      responsePrint(argv[0], "New Frequency:%u", newFrequency);
    } else {
      // This won't take effect until we parse divider ranges.
      responsePrintError(argv[0], 0x14, "%u Hz is out of range and cannot be "
          "set as the frequency", newFrequency);
    }
  } else {
    responsePrintError(argv[0], 0x13, "Not currently in frequency override debug mode.");
  }
}

char * lookupDebugModeString(uint32_t debugMode)
{
  if (debugMode == 0)
  {
    return "Disabled";
  }
  if (debugMode & RAIL_DEBUG_MODE_FREQ_OVERRIDE)
  {
    return "Frequency Override";
  }

  return "NULL";
}
/*
 * setDebugMode()
 *
 * Configure RAIL into a debug mode.
 *
 * Current debug modes:
 * RAIL_DEBUG_MODE_FREQ_OVERRIDE - Disable RAIL's channel scheme and
 *  uses a specific frequency defined by the user.
 */
void setDebugMode(int argc, char **argv)
{
  uint32_t debugMode;

  debugMode = ciGetUnsigned(argv[1]);
  if (!RAIL_DebugModeSet(debugMode))
  {
    responsePrint (argv[0], "DebugMode:%s", lookupDebugModeString(debugMode));
  }
  else
  {
    responsePrintError(argv[0], 0x15, "%d is an invalid debug mode!", debugMode);
  }
}

void getMemWord(int argc, char **argv)
{
  uint32_t *address = (uint32_t*)ciGetUnsigned(argv[1]);
  uint32_t count = 1;
  uint32_t value;

  // If there was a length given then read it out
  if (argc > 2)
  {
    count = ciGetUnsigned(argv[2]);
  }

  // Check for alignment
  if (((uint32_t)address % 4) != 0)
  {
    responsePrintError(argv[0], 0xFF, "Address 0x%.8X is not 32bit aligned", address);
    return;
  }

  responsePrintHeader(argv[0], "address:0x%.8x,value:0x%.8x");
  for (uint32_t i = 0; i < count; i++)
  {
    value = address[i];
    responsePrintMulti("address:0x%.8x,value:0x%.8x", address+i, value);
  }
}

void setMemWord(int argc, char **argv)
{
  uint32_t *address = (uint32_t*)ciGetUnsigned(argv[1]);
  int count = 0;
  char lengthStr[10];

  // Check for alignment
  if (((uint32_t)address % 4) != 0)
  {
    responsePrintError(argv[0], 0xFF, "Address 0x%.8X is not 32bit aligned", address);
    return;
  }

  // Write each word given sequentially
  for (int i = 2; i < argc; i++)
  {
    address[count] = ciGetUnsigned(argv[i]);
    count++;
  }

  // Make getMemWord print out everything we just wrote to
  sprintf(lengthStr, "%d", count);
  argv[2] = lengthStr;
  getMemWord(3, argv);
}

void setTxUnderflow(int argc, char **argv)
{
  bool enable = !!ciGetUnsigned(argv[1]);
  enableAppMode(TX_UNDERFLOW, enable, argv[0]);
}

void setRxOverflow(int argc, char **argv)
{
  bool enable = !!ciGetUnsigned(argv[1]);
  enableAppMode(RX_OVERFLOW, enable, argv[0]);
}

void setCalibrations(int argc, char **argv)
{
  bool enable = !!ciGetUnsigned(argv[1]);
  skipCalibrations = !enable;
  responsePrint(argv[0], "Calibrations:%s", enable ? "Enabled": "Disabled");
}

void txCancel(int argc, char **argv)
{
  int32_t delay = ciGetSigned(argv[1]);
  txCancelDelay = delay;

  enableAppMode(TX_CANCEL, delay != 0, argv[0]);
  if ((txCancelDelay > 0) && (currentAppMode() == TX_CANCEL))
  {
    txCount = 1;
    pendPacketTx();
  }
}

void getLogLevels(int argc, char **argv)
{
  responsePrint(argv[0], "Peripherals:%s,Notifications:%s",
                ((logLevel & PERIPHERAL_ENABLE) ? "Enabled" : "Disabled"),
                ((logLevel & ASYNC_RESPONSE) ? "Enabled" : "Disabled"));
}

void setPeripheralEnable(int argc, char **argv)
{
  bool enable = !!ciGetUnsigned(argv[1]);
  logLevel = enable ? (logLevel | PERIPHERAL_ENABLE)
                    : (logLevel & ~(PERIPHERAL_ENABLE));
  getLogLevels(1, argv);
}

void setNotifications(int argc, char **argv)
{
  bool enable = !!ciGetUnsigned(argv[1]);
  logLevel = enable ? (logLevel | ASYNC_RESPONSE)
                    : (logLevel & ~(ASYNC_RESPONSE));
  getLogLevels(1, argv);
}

void resetChip(int argc, char **argv)
{
  // Wait for any serial traffic to be done before resetting so we don't
  // output garbage characters
  serialWaitForTxIdle();

  // Use the NVIC to reset the chip
  NVIC_SystemReset();
}

void printDataRates(int argc, char **argv)
{
  responsePrint(argv[0],
                "Symbolrate:%d,Bitrate:%d",
                RAIL_SymbolRateGet(),
                RAIL_BitRateGet());
}

#define MAX_RANDOM_BYTES (1024)
#define MAX_PRINTABLE_RANDOM_BYTES (200)
static char randomPrintBuffer[2 * MAX_PRINTABLE_RANDOM_BYTES + 2];
static uint8_t randomDataBuffer[MAX_RANDOM_BYTES];

void getRandom(int argc, char **argv)
{
  uint16_t length = ciGetUnsigned(argv[1]);
  bool hidden = false;
  uint16_t result, offset = 0;
  int i;

  // Read out the hidden option if specified
  if (argc > 2)
  {
    hidden = !!ciGetUnsigned(argv[2]);
  }

  if (length > MAX_RANDOM_BYTES)
  {
    responsePrintError(argv[0], 0x10,
                       "Cannot collect more than %d random bytes.",
                       MAX_RANDOM_BYTES);
    return;
  }

  // Collect the random data
  result = RAIL_GetRadioEntropy(randomDataBuffer, length);
  if (result != length)
  {
    responsePrintError(argv[0], 0x11, "Error collecting random data.");
  }

  if (!hidden)
  {
    for (i = 0; i < length; i++)
    {
      int n = snprintf(randomPrintBuffer + offset,
                       sizeof(randomPrintBuffer) - offset,
                       "%.2x",
                       randomDataBuffer[i]);
      if (n < 0)
      {
        responsePrintError(argv[0], 0x12, "Error printing random data.");
        return;
      }
      offset += n;

      // Make sure we don't try to print too much data
      if (offset >= sizeof(randomPrintBuffer))
      {
        break;
      }
    }

    responsePrint(argv[0], "Length:%u,Data:%s", result, randomPrintBuffer);
  }
  else
  {
    responsePrint(argv[0],
                  "Length:%u,DataPtr:0x%.8x",
                  result,
                  &randomDataBuffer);
  }
}
