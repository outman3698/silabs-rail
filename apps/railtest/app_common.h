/***************************************************************************//**
 * @file app_common.h
 * @brief This header file defines variables to be shared between the main
 * test application and customer specific sections.
 * @copyright Copyright 2015 Silicon Laboratories, Inc. http://www.silabs.com
 ******************************************************************************/

#ifndef __APPS_COMMON_H__
#define __APPS_COMMON_H__

#include "em_gpio.h" // For ButtonArray definition
#ifdef CONFIGURATION_HEADER
#include CONFIGURATION_HEADER
#endif

/******************************************************************************
 * Constants
 *****************************************************************************/
#define COUNTOF(a) (sizeof(a)/sizeof(a[0]))
#define TX_CONTINUOUS_COUNT (0xFFFFFFFF)

/******************************************************************************
 * Variable Export
 *****************************************************************************/
#define PER_PORT (gpioPortC)
#define PER_PIN  (7)

typedef struct ButtonArray
{
  GPIO_Port_TypeDef   port;
  unsigned int        pin;
} ButtonArray_t;

typedef struct Stats
{
  uint32_t samples;
  int32_t min;
  int32_t max;
  float mean;
  float varianceTimesSamples;
} Stats_t;

typedef struct Counters
{
  uint32_t transmit;
  uint32_t receive;
  uint32_t syncDetect;
  uint32_t preambleDetect;
  uint32_t frameError;
  uint32_t rxOfEvent;
  uint32_t txAbort;
  uint32_t txChannelBusy;
  uint32_t addrFilterEvent;
  uint32_t calibrations;
  uint32_t noRxBuffer;
  uint32_t rfSensedEvent;
  uint32_t perTriggers;
  Stats_t rssi;
} Counters_t;

extern Counters_t counters;
extern int currentConfig;
extern bool receiveModeEnabled;
extern bool transmitting;
extern bool txParameterChanged;
extern uint16_t channel;
extern uint32_t continuousTransferPeriod;
extern int32_t txCount;
extern uint32_t txAfterRxDelay;
extern int32_t txCancelDelay;
extern RAIL_ChannelConfigEntry_t channels[];
extern const RAIL_ChannelConfig_t channelConfig;
extern bool redrawDisplay;
extern bool skipCalibrations;
extern volatile bool serEvent;
extern uint32_t perCount;
extern uint32_t perDelay;

#define PERIPHERAL_ENABLE (0x01)
#define ASYNC_RESPONSE (0x02)
extern uint8_t logLevel;
extern uint8_t txData[APP_MAX_PACKET_LENGTH];
extern RAIL_TxData_t transmitPayload;

extern RAIL_PreTxOp_t txPreTxOp;
extern void* txPreTxOpArgs;

/**
 * @enum AppMode
 * @brief Enumeration of RailTest transmit states.
 */
typedef enum AppMode
{
  NONE=0,         /**< RAILtest is not doing anything special */
  TX_STREAM=1,    /**< Send a stream of pseudo-random bits */
  TX_TONE=2,      /**< Send a tone at the carrier frequency */
  TX_CONTINUOUS=3,/**< Send an unending stream of packets*/
  DIRECT=4,       /**< Send data to and from a GPIO, without any packet handling */
  TX_N_PACKETS=5, /**< Send a specific number of packets */
  TX_SCHEDULED=6, /**< Send one packet scheduled in the future */
  SCHTX_AFTER_RX=7, /**< Schedule a TX for a fixed delay after receiving a packet */
  RX_OVERFLOW=8,  /**< Cause overflow on receive */
  TX_UNDERFLOW=9, /**< Cause underflows on the next TX sequence */
  TX_CANCEL=10,   /**< Cancel a single packet transmit to force an error callback */
  RF_SENSE=11,    /**< Sense RF energy to wake the radio */
  PER=12,         /**< Packet Error Rate test mode */
  BER=13,         /**< Bit Error Rate test mode */
} AppMode_t;


AppMode_t previousAppMode(void);
AppMode_t currentAppMode(void);
void enableAppMode(AppMode_t appMode, bool enable, char *command);
bool enableAppModeSync(AppMode_t appMode, bool enable, char *command);
void setNextAppMode(AppMode_t appMode, char *command);
void changeAppModeIfPending();
char *appModeNames(AppMode_t appMode);
bool inAppMode(AppMode_t appMode, char *command);
bool inRadioState(RAIL_RadioState_t state, char *command);

void updateStats(int32_t newValue, Stats_t *stats);
void rfSensedCheck(void);
void updateDisplay(void);

void changeChannel(uint32_t i);
void pendPacketTx(void);
void pendFinishTxSequence(void);
void setNextPacketTime(uint32_t absTime);
void radioTransmit(uint32_t iterations, char *command);
void configureTxAfterRx(uint32_t delay, bool enable, char *command);
void scheduleNextTx(void);
void changeRadioConfig(int newConfig);
void printPacket(char *cmdName,
                 uint8_t *data,
                 uint16_t dataLength,
                 RAIL_RxPacketInfo_t *packetInfo);

void appHalInit(void);
void LedSet(int led);
void LedToggle(int led);
void PeripheralDisable(void);
void PeripheralEnable(void);
void usDelay(uint32_t microseconds);
void serialWaitForTxIdle(void);
#endif // __APPS_COMMON_H__
