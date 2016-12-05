/***************************************************************************//**
 * @file app_ci.h
 * @brief This is the header file for common RAIL test application commands.
 * @copyright Copyright 2015 Silicon Laboratories, Inc. http://www.silabs.com
 ******************************************************************************/

#ifndef __APP_CI_H__
#define __APP_CI_H__

/******************************************************************************
 * Application commands.
 *****************************************************************************/
// Base set of Command Interface commands
// <command> <args> <help text>
// u=uint8, v=uint16, w=uint32, s=int32, b=string, ?=Anything, *=0 or more of previous
#define APP_CI_COMMANDS \
  COMMAND_SEPARATOR("Application Configuration"), \
  COMMAND_ENTRY("listConfigs", "", listConfigs, "List all available configs and their indices"), \
  COMMAND_ENTRY("setConfig", "v", setConfig, "[index] Set the radio config to the one at index in the config list."), \
  COMMAND_ENTRY("getConfig", "", getConfig, "Get the index of the current radio config"), \
  COMMAND_ENTRY("printDataRates", "", printDataRates, "Print the data rates of the current PHY"), \
  COMMAND_ENTRY("resetCounters", "", resetCounters, "Resets the Tx and Rx counters"), \
  COMMAND_ENTRY("setPeripheralEnable", "u", setPeripheralEnable, "[enable] Enable(1) or Disable(0) LEDs and LCD peripherals"), \
  COMMAND_ENTRY("setNotifications", "u", setNotifications, "[enable] Enable(1) or Disable(0) status prints that happen asynchronously (rxPacket, txEnd, txError)"), \
  COMMAND_ENTRY("getLogLevels", "", getLogLevels, "Get whether notifications are set or peripherals are enabled"), \
  COMMAND_ENTRY("getVersion", "", getVersion, "Get version information."), \
  COMMAND_ENTRY("getVersionVerbose", "", getVersionVerbose, "Get verbose version information."), \
  COMMAND_SEPARATOR("Receive and Transmit"), \
  COMMAND_ENTRY("rx",         "w", rx,           "[enable] Enable(1) or Disable(0) receive mode"), \
  COMMAND_ENTRY("tx",         "w", tx,           "[n] Transmit n packets. If n is 0 transmit infinitely"), \
  COMMAND_ENTRY("txAt",       "w", txAtTime,     "[time] Transmit a packet at the time specified in the RAIL timebase"), \
  COMMAND_ENTRY("txAfterRx", "w", txAfterRx, "[time] Schedule a TX for a delay in us after each receive. 0 to disable"), \
  COMMAND_ENTRY("setchannel", "u", setChannel,   "[channel] Set the current radio channel"), \
  COMMAND_ENTRY("getchannel",  "", getChannel,   "Get the current radio channel"), \
  COMMAND_ENTRY("setPower", "s", setPower, "[power] Set the current transmit power in deci dBm"), \
  COMMAND_ENTRY("getPower", "", getPower, "Get the current transmit power in deci dBm"), \
  COMMAND_ENTRY("getRssi", "", getRssi, "Get RSSI in dBm if the receiver is turned on."), \
  COMMAND_ENTRY("setTxTone",  "w", setTxTone, "[enable] Enable(1) or Disable(0) a tone from the radio"), \
  COMMAND_ENTRY("setTxStream", "w", setTxStream, "[enable] Enable(1) or Disable(0) a PN9 stream from the radio"), \
  COMMAND_ENTRY("status",      "", getStatus,  "Print the current status counters"), \
  COMMAND_ENTRY("setTxDelay", "w", setTxDelay, "[delay] Set the inter-packet delay in milliseconds for repeated Tx"), \
  COMMAND_ENTRY("getTxDelay", "", getTxDelay, "Get the inter-packet delay in milliseconds for repeated Tx"), \
  COMMAND_ENTRY("setTxPayload","vu*", setTxPayload, "[offset byte0 byte1 ...] Set the packet bytes to be sent"), \
  COMMAND_ENTRY("setTxLength", "v", setTxLength,  "[length] Set the number of bytes to transmit for fixed length packets"), \
  COMMAND_ENTRY("printTxPacket", "", printTxPacket, "Print the current Tx data and length"), \
  COMMAND_ENTRY("getTime", "", getTime, "Get the current time from the RAIL timebase in microseconds"), \
  COMMAND_ENTRY("setTime", "w", setTime, "Set the current time in the RAIL timebase in microseconds"), \
  COMMAND_SEPARATOR("Energy Modes and RF Sense"), \
  COMMAND_ENTRY("sleep", "bw*", sleep, "[EM# [RfSenseUs RfBand]] Sleep in EM# with RFSenseUs on RfBand (0=none,1=2.4GHz,2=SubGHz,3=both) (and UART input)"), \
  COMMAND_ENTRY("rfsense", "ww", rfSense, "[RfSenseUs RfBand] Start RfSensing with RSenseUs on RfBand"), \
  COMMAND_SEPARATOR("Address Filtering"), \
  COMMAND_ENTRY("configAddressFilter", "wu*", setAddressFilterConfig, "[matchTable offset0 size0 offset1 size1] Configure the addresss filter."), \
  COMMAND_ENTRY("addressFilterByFrame", "u", addressFilterByFrame, "[validFrames] Set interaction of address filtering and frame type length decoding. Must be called after 'configAddressFilter'"), \
  COMMAND_ENTRY("setAddressFiltering", "u", setAddressFilter, "[enable] Enable(1) or Disable(0) address filtering."), \
  COMMAND_ENTRY("getAddressFiltering", "", getAddressFilter, "Print the current state of address filtering."), \
  COMMAND_ENTRY("printAddresses", "", printAddresses, "Print the current address filtering addresses."), \
  COMMAND_ENTRY("setAddress", "uuu*", setAddress, "[field index value...] Set the address value at (field, index) to value."), \
  COMMAND_ENTRY("setAddressEnable", "uuu", enableAddress, "[field index enable] Enable address filtering for the given address."), \
  COMMAND_SEPARATOR("Error Rate Testing"), \
  COMMAND_ENTRY("perRx", "ww", startPerMode, "[packets delayUs] Start a Packet Error Rate test. 'perRx 0 0' will disable ongoing test."), \
  COMMAND_ENTRY("perStatus", "", getPerStats, "Output the results of the PER test. Also see 'status' command"), \
  COMMAND_ENTRY("setBerConfig", "w", berConfigSet, "[number bytes] Set number of bytes to receive in BER mode; 536870911 = max number of bytes to test; 0 = set max number of bytes to test"), \
  COMMAND_ENTRY("berRx", "w", berRx, "[enable] Enable(1) or Disable(0) BER receive mode"), \
  COMMAND_ENTRY("berStatus", "", berStatusGet, "Get status of last BER test or of current running test; status information is reset for commands setBerConfig and berRx enable"), \
  COMMAND_SEPARATOR("Listen Before Talk (LBT)"), \
  COMMAND_ENTRY("setLbtMode", "b*", setLbtMode, "[modeStr] Set LBT mode off, csma, lbt"), \
  COMMAND_ENTRY("getLbtParams", "", getLbtParams, "Get the current LBT parameters"),\
  COMMAND_ENTRY("setLbtParams", "uuusvvw", setLbtParams, "[minBo maxBo tries thresh backoff duration timeout] Set LBT parameters"),\
  COMMAND_SEPARATOR("RAIL Timer"), \
  COMMAND_ENTRY("setTimer", "wb", setTimer, "[timeout mode] Set the RAIL timer timeout. You can use either an absolute (abs) or relative (rel) timer mode."), \
  COMMAND_ENTRY("timerCancel", "", timerCancel, "Cancel the RAIL timer if it's active."), \
  COMMAND_ENTRY("printTimerStats", "", printTimerStats, "Print current timer configuration."), \
  COMMAND_SEPARATOR("Diagnostic and Test"), \
  COMMAND_ENTRY("getmemw", "ww*", getMemWord, "[address count] Read count 32bit words starting at address"), \
  COMMAND_ENTRY("setmemw", "ww*", setMemWord, "[address value...] Write as many 32bit values as specified starting at address"), \
  COMMAND_ENTRY("setCtune", "v", setCtune, "[ctune] Set the value of CTUNE in the CMU->HFXOSTEADYSTATECTRL register"), \
  COMMAND_ENTRY("getCtune",  "", getCtune, "Get the value of CTUNE in the CMU->HFXOSTEADYSTATECTRL register"), \
  COMMAND_ENTRY("setPaCtune", "uu", setPaCtune, "[txPaCtune] [rxPaCtune] Set the value of PACTUNE for TX and RX mode"), \
  COMMAND_ENTRY("setDebugMode","w", setDebugMode, "[mode] 1 = Frequency Override. 0 = Disable debug mode"), \
  COMMAND_ENTRY("freqOverride","w", setFrequency, "[freq] Change to freq specified in Hz. Requires debug mode to be enabled. Only small frequency deviations from the current configuration are supported."), \
  COMMAND_ENTRY("directMode", "u", setDirectMode, "[enable] Enable(1) or Disable(0) direct mode"), \
  COMMAND_ENTRY("directTx", "u", setDirectTx, "[enable] Enable(1) or Disable(0) TX in direct mode"), \
  COMMAND_ENTRY("txCancel", "s", txCancel, "[delay] Set the time in microseconds after which we should cancel a tx (a negative value disables this)"), \
  COMMAND_ENTRY("getRandom", "vu*", getRandom, "[len hidden] Get len bytes of random data from the radio. Only print them to the screen if hidden is 0 (default)."), \
  COMMAND_ENTRY("setTxUnderflow", "w", setTxUnderflow, "[enable] Enable(1) or Disable(0) TX underflows"), \
  COMMAND_ENTRY("setRxOverflow", "w", setRxOverflow, "[enable] Enable(1) or Disable(0) RX overflows"), \
  COMMAND_ENTRY("setCalibrations", "w", setCalibrations, "[enable] Enable(1) or Disable(0) RAIL calibrations"), \
  COMMAND_ENTRY("setTxTransitions", "bb", setTxTransitions, "[txSuccess txError] Set each RAIL TX state transition value to r(x) or i(dle)"), \
  COMMAND_ENTRY("setRxTransitions", "bbu", setRxTransitions, "[rxSuccess rxError ignoreErrors] Set each RAIL RX state transition value to t(x), r(x), or i(dle), and set error events bitfield"), \
  COMMAND_ENTRY("setTimings", "vvvv", setTimings, "[idleToRx txToRx idleToTx rxToTx] Set RAIL state transition timings in microseconds"), \
  COMMAND_ENTRY("reset", "", resetChip, "Perform a reboot of the chip")


/******************************************************************************
 * Externed Prototypes
 *****************************************************************************/
// Command callback function prototypes
// trx_ci
void rx(int argc, char **argv);
void tx(int argc, char **argv);
void txAtTime(int argc, char **argv);
void txAfterRx(int argc, char **argv);
void setTxTone(int argc, char **argv);
void setTxStream(int argc, char **argv);
void setDirectMode(int argc, char **argv);
void setDirectTx(int argc, char **argv);
void sleep(int argc, char **argv);
void rfSense(int argc, char **argv);

//lbt_ci
void setLbtMode(int argc, char **argv);
void getLbtParams(int argc, char **argv);
void setLbtParams(int argc, char **argv);

//packet_ci
void setTxPayload(int argc, char **argv);
void setTxLength(int argc, char **argv);
void printTxPacket(int argc, char **argv);

//parameter_ci
void setChannel(int argc, char **argv);
void getChannel(int argc, char **argv);
void setDirectMode(int argc, char **argv);
void setDirectTx(int argc, char **argv);
void getMemWord(int argc, char **argv);
void setMemWord(int argc, char **argv);

void getPower(int argc, char **argv);
void setPower(int argc, char **argv);
void getTxDelay(int argc, char **argv);
void setTxDelay(int argc, char **argv);
void setTxTransitions(int argc, char **argv);
void setRxTransitions(int argc, char **argv);
void setTimings(int argc, char **argv);

void setConfig(int argc, char **argv);
void getConfig(int argc, char **argv);
void listConfigs(int argc, char **argv);

void setCtune(int argc, char **argv);
void getCtune(int argc, char **argv);

void setPaCtune(int argc, char **argv);

//info_ci
void getStatus(int argc, char **argv);
void getVersion(int argc, char **argv);
void getVersionVerbose(int argc, char **argv);
void getRssi(int argc, char **argv);
void resetCounters(int argc, char **argv);
void getTime(int argc, char **argv);
void setTime(int argc, char **argv);

//debug_ci
void setFrequency(int argc, char **argv);
void setDebugMode(int argc, char **argv);
void getMemWord(int argc, char **argv);
void setMemWord(int argc, char **argv);
void setTxUnderflow(int argc, char **argv);
void setRxOverflow(int argc, char **argv);
void setCalibrations(int argc, char **argv);
void getLogLevels(int argc, char **argv);
void setPeripheralEnable(int argc, char **argv);
void setNotifications(int argc, char **argv);
void resetChip(int argc, char **argv);
void printDataRates(int argc, char **argv);
void txCancel(int argc, char **argv);
void getRandom(int argc, char **argv);

//address_filter_ci
void setAddressFilterConfig(int argc, char **argv);
void addressFilterByFrame(int argc, char **argv);
void setAddressFilter(int argc, char **argv);
void getAddressFilter(int argc, char **argv);
void printAddresses(int argc, char **argv);
void setAddress(int argc, char **argv);
void enableAddress(int argc, char **argv);

//error_rate_ci
void startPerMode(int argc, char **argv);
void getPerStats(int argc, char **argv);
void berConfigSet(int argc, char **argv);
void berRx(int argc, char **argv);
void berStatusGet(int argc, char **argv);

//timer_ci
void setTimer(int argc, char **argv);
void printTimerStats(int argc, char **argv);
void timerCancel(int argc, char** argv);

#endif // __APP_CI_H__
