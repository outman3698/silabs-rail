/***************************************************************************//**
 * @file hal_efr.c
 * @brief This file contains EFR32 specific HAL code to handle chip startup.
 * @copyright Copyright 2015 Silicon Laboratories, Inc. http://www.silabs.com
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>

#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "bsp.h"
#include "em_chip.h"
#include "pti.h"
#include "pa.h"

#include "rail_config.h"

uint8_t radioPtiDclkRouteLoc = 6;
uint8_t radioPtiDoutRouteLoc = 6;

static void boardDisableSpiFlash(void);
static void boardLowPowerInit(void);
static void usecDelay(uint32_t usecs);

void halInitChipSpecific(void)
{
  EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_WSTK_DEFAULT;
  CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_WSTK_DEFAULT;
  RADIO_PTIInit_t ptiInit = RADIO_PTI_INIT;
  RADIO_PAInit_t paInit;

  // Init DCDC regulator and HFXO with WSTK radio board specific parameters
  // from s025_sw\kits\SLWSTK6100A_EFR32MG\config\bspconfig.h
  EMU_DCDCInit(&dcdcInit);
  CMU_HFXOInit(&hfxoInit);

  // Initialize the Packet Trace Interface (PTI) to match the configuration in
  // the board header
  RADIO_PTI_Init(&ptiInit);

  /* Switch HFCLK to HFXO and disable HFRCO */
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
  CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

  // Initialize the PA now that the HFXO is up and the timing is correct
  #if (RADIO_CONFIG_BASE_FREQUENCY < 1000000000UL)
    paInit = (RADIO_PAInit_t) RADIO_PA_SUBGIG_INIT;
  #else
    paInit = (RADIO_PAInit_t) RADIO_PA_2P4_INIT;
  #endif

  RADIO_PA_Init(&paInit);

  // Initialize other chip clocks
  CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFRCO);
  CMU_ClockEnable(cmuClock_CORELE, true);

  // Disable any unusd peripherals to ensure we enter a low power mode
  boardLowPowerInit();
}

static void boardLowPowerInit(void)
{
  boardDisableSpiFlash();  
}

#define CMD_POWER_DOWN                      (0xB9)
#define CMD_POWER_UP                        (0xAB)

/** Synchronous mode init structure. */
static const USART_InitSync_TypeDef usartInit = 
{
  /** Specifies whether TX and/or RX shall be enabled when init completed. */
  //USART_Enable_TypeDef    enable;
  usartEnable,

  /**
   * USART/UART reference clock assumed when configuring baudrate setup. Set
   * it to 0 if currently configurated reference clock shall be used.
   */
  //uint32_t                refFreq;
  38400000U,

  /** Desired baudrate. */
  //uint32_t                baudrate;
  12000000U,

  /** Number of databits in frame. */
  //USART_Databits_TypeDef  databits;
  usartDatabits8,

  /** Select if to operate in master or slave mode. */
  //bool                    master;
  true,

  /** Select if to send most or least significant bit first. */
  //bool                    msbf;
  true,

  /** Clock polarity/phase mode. */
  //USART_ClockMode_TypeDef clockMode;
  usartClockMode0,

  /** Enable USART Rx via PRS. */
  //bool                    prsRxEnable;
  false,

  /** Select PRS channel for USART Rx. (Only valid if prsRxEnable is true). */
  //USART_PrsRxCh_TypeDef   prsRxCh;
  usartPrsRxCh0,

  /** Enable AUTOTX mode. Transmits as long as RX is not full.
   *  If TX is empty, underflows are generated. */
  //bool                    autoTx;
  false,

  /** Auto CS enabling */
  //bool autoCsEnable;
  false,

  /** Auto CS hold time in baud cycles */
  //uint8_t autoCsHold;
  0,

  /** Auto CS setup time in baud cycles */
  //uint8_t autoCsSetup;
  0,

} ;

static void boardDisableSpiFlash(void)
{
  // Enable clocks needed for using the USART
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_USART1, true);

  USART_InitSync(USART1, &usartInit);

  USART1->ROUTEPEN  =   USART_ROUTEPEN_TXPEN
                      | USART_ROUTEPEN_RXPEN
                      | USART_ROUTEPEN_CLKPEN;

  USART1->ROUTELOC0 =   USART_ROUTELOC0_TXLOC_LOC11
                      | USART_ROUTELOC0_RXLOC_LOC11
                      | USART_ROUTELOC0_CLKLOC_LOC11 ;

  // MOSI
  GPIO_PinModeSet(gpioPortC, 6, gpioModePushPull,  0);
  // MISO
  GPIO_PinModeSet(gpioPortC, 7, gpioModeInputPull, 0);
  // CLK
  GPIO_PinModeSet(gpioPortC, 8, gpioModePushPull,  0);
  // CS#
  GPIO_PinModeSet(gpioPortA, 4, gpioModePushPull,  1);

  // Delay for 10ms to wait for the part to be ready to talk to
  usecDelay(10000);

  // Send the power on command so we can talk to it
  GPIO_PinOutClear(gpioPortA, 4);
  USART_Tx(USART1, CMD_POWER_UP);
  USART_Rx(USART1);
  GPIO_PinOutSet(gpioPortA, 4);

  // Delay for 30 usecs to make sure it's awake
  usecDelay(30);

  // Finally, send the power down command to put it in low power mode
  GPIO_PinOutClear(gpioPortA, 4);
  USART_Tx(USART1, CMD_POWER_DOWN);
  USART_Rx(USART1);
  GPIO_PinOutSet(gpioPortA, 4);
}

// Simple microsecond delay routine that has been calibrated for an EFR32
// running at 38.4MHz. This code should be moved to a more clean location
// along with all board initialization in the future.
static const uint32_t iterations_per_microsecond = 3;
static void usecDelay(uint32_t usecs)
{
  volatile uint64_t iterations = iterations_per_microsecond * usecs;

  while(iterations--);
}
