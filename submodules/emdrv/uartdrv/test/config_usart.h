/**
 * UARTDRV test configuration for USART<->USART test
 */


/**
 * Interface 0 pin config
 */
#if defined( _USART_ROUTELOC0_MASK ) // Platform 2
  #define TEST_UART_I0_DEVICE    (USART0)
  #define TEST_UART_I0_LOC       (_USART_ROUTELOC0_TXLOC_LOC1) , (_USART_ROUTELOC0_RXLOC_LOC31)
  #define TEST_UART_I0_CTS_PORT  (gpioPortA)     /* CTS port number */
  #define TEST_UART_I0_CTS_PIN   (3)             /* CTS pin number  */
  #define TEST_UART_I0_CTS_LOC   (_USART_ROUTELOC1_CTSLOC_LOC31)  /* CTS location #31 => PA3 */
  #define TEST_UART_I0_RTS_PORT  (gpioPortA)     /* RTS port number */
  #define TEST_UART_I0_RTS_PIN   (4)             /* RTS pin number  */
  #define TEST_UART_I0_RTS_LOC   (_USART_ROUTELOC1_RTSLOC_LOC31)  /* RTS location #31 => PA4 */
#else // Platform 1
  #if defined (_EZR32_LEOPARD_FAMILY) || defined (_EZR32_WONDER_FAMILY)
    #define TEST_UART_I0_DEVICE    (USART2)
    #define TEST_UART_I0_LOC       (_USART_ROUTE_LOCATION_LOC1)
    #define TEST_UART_I0_CTS_PORT  (GPIO_Port_TypeDef)AF_USART2_CS_PORT(_USART_ROUTE_LOCATION_LOC1)  /* CTS port number */
    #define TEST_UART_I0_CTS_PIN   AF_USART2_CS_PIN(_USART_ROUTE_LOCATION_LOC1)                      /* CTS pin number  */
    #define TEST_UART_I0_RTS_PORT  (GPIO_Port_TypeDef)AF_USART2_CLK_PORT(_USART_ROUTE_LOCATION_LOC1) /* RTS port number */
    #define TEST_UART_I0_RTS_PIN   AF_USART2_CLK_PIN(_USART_ROUTE_LOCATION_LOC1)                     /* RTS pin number  */
  #elif defined(_EZR32_HAPPY_FAMILY)
    // USART0 Location 0, (TX=PE10, RX=PE11, CTS=PE13, RTS=PE12)
    #define TEST_UART_I0_DEVICE    (USART0)
    #define TEST_UART_I0_LOC       (_USART_ROUTE_LOCATION_LOC0)
    #define TEST_UART_I0_CTS_PORT  (GPIO_Port_TypeDef)AF_USART0_CS_PORT(_USART_ROUTE_LOCATION_LOC0)
    #define TEST_UART_I0_CTS_PIN   AF_USART0_CS_PIN(_USART_ROUTE_LOCATION_LOC0)
    #define TEST_UART_I0_RTS_PORT  (GPIO_Port_TypeDef)AF_USART0_CLK_PORT(_USART_ROUTE_LOCATION_LOC0)
    #define TEST_UART_I0_RTS_PIN   AF_USART0_CLK_PIN(_USART_ROUTE_LOCATION_LOC0)
  #elif defined(_EFM32_ZERO_FAMILY)
    #define TEST_UART_I0_DEVICE    (USART1)
    #define TEST_UART_I0_LOC       (_USART_ROUTE_LOCATION_LOC3)
    #define TEST_UART_I0_CTS_PORT  (gpioPortC)     /* CTS port number */
    #define TEST_UART_I0_CTS_PIN   (15)            /* CTS pin number  */
    #define TEST_UART_I0_RTS_PORT  (gpioPortC)     /* RTS port number */
    #define TEST_UART_I0_RTS_PIN   (14)            /* RTS pin number  */
  #elif defined(_EFM32_HAPPY_FAMILY)
    #define TEST_UART_I0_DEVICE    (USART1)
    #define TEST_UART_I0_LOC       (_USART_ROUTE_LOCATION_LOC0)
    #define TEST_UART_I0_CTS_PORT  (gpioPortC)     /* CTS port number */
    #define TEST_UART_I0_CTS_PIN   (2)             /* CTS pin number  */
    #define TEST_UART_I0_RTS_PORT  (gpioPortA)     /* RTS port number */
    #define TEST_UART_I0_RTS_PIN   (2)             /* RTS pin number  */
  #else
    #define TEST_UART_I0_DEVICE    (USART0)
    #define TEST_UART_I0_LOC       (_USART_ROUTE_LOCATION_LOC1) /* USART pins location number   */
    #define TEST_UART_I0_CTS_PORT  ((GPIO_Port_TypeDef)AF_USART0_CS_PORT(_USART_ROUTE_LOCATION_LOC1)) /* CTS port number */
    #define TEST_UART_I0_CTS_PIN   ((GPIO_Port_TypeDef)AF_USART0_CS_PIN(_USART_ROUTE_LOCATION_LOC1))  /* CTS pin number  */
    #define TEST_UART_I0_RTS_PORT  ((GPIO_Port_TypeDef)AF_USART0_CLK_PORT(_USART_ROUTE_LOCATION_LOC1)) /* RTS port number */
    #define TEST_UART_I0_RTS_PIN   ((GPIO_Port_TypeDef)AF_USART0_CLK_PIN(_USART_ROUTE_LOCATION_LOC1)) /* RTS pin number */
  #endif
#endif

/**
 * Interface 1 pin config
 */
#if defined( _USART_ROUTELOC0_MASK )
  // P2 STK: 2 USARTs availabe on expansion header
  #define TEST_UART_I1_DEVICE    (USART1)
  #define TEST_UART_I1_LOC       (_USART_ROUTELOC0_TXLOC_LOC11) , (_USART_ROUTELOC0_RXLOC_LOC11)
  #define TEST_UART_I1_CTS_PORT  (gpioPortC)     /* CTS port number */
  #define TEST_UART_I1_CTS_PIN   (9)             /* CTS pin number  */
  #define TEST_UART_I1_CTS_LOC   (_USART_ROUTELOC1_CTSLOC_LOC10) /* CTS location #10 => PC9 */
  #define TEST_UART_I1_RTS_PORT  (gpioPortC)     /* RTS port number */
  #define TEST_UART_I1_RTS_PIN   (8)             /* RTS pin number  */
  #define TEST_UART_I1_RTS_LOC   (_USART_ROUTELOC1_RTSLOC_LOC8) /* RTS location #8 => PC8 */
#elif defined(EFM32GG_DK3750) || defined(EFM32LG_DK3650) || defined(EFM32WG_DK3850) || defined(EFM32_GXXX_DK)
  // DK: Can connect 2nd USART on protoboard
  #define TEST_UART_I1_DEVICE    (USART1)
  #define TEST_UART_I1_LOC       (_USART_ROUTE_LOCATION_LOC1)
  #define TEST_UART_I1_CTS_PORT  ((GPIO_Port_TypeDef)AF_USART1_CS_PORT(_USART_ROUTE_LOCATION_LOC1))  /* CTS port number */
  #define TEST_UART_I1_CTS_PIN   ((GPIO_Port_TypeDef)AF_USART1_CS_PIN(_USART_ROUTE_LOCATION_LOC1))   /* CTS pin number  */
  #define TEST_UART_I1_RTS_PORT  ((GPIO_Port_TypeDef)AF_USART1_CLK_PORT(_USART_ROUTE_LOCATION_LOC1)) /* RTS port number */
  #define TEST_UART_I1_RTS_PIN   ((GPIO_Port_TypeDef)AF_USART1_CLK_PIN(_USART_ROUTE_LOCATION_LOC1))  /* RTS pin number  */
#else
  // P1 STK: Cannot connect 2 USARTs with 4 pins
  // TODO: Maybe solder headers on kits in regression test?
  #undef TEST_UART_I1_DEVICE
#endif

/**
 * Interface 0 config
 */
#if defined(_USART_ROUTELOC0_MASK)
/**
 * Platform 2
 */
#define TEST_UART_I0                                                                                         \
{                                                                                                               \
  TEST_UART_I0_DEVICE,                                               /* USART port                   */      \
  115200,                                                               /* Baud rate                    */      \
  TEST_UART_I0_LOC,                                                  /* USART location number        */      \
  (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */      \
  (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */      \
  (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */      \
  false,                                                                /* Majority vote disable        */      \
  uartdrvFlowControlHw,                                                 /* Flow control                 */      \
  TEST_UART_I0_CTS_PORT,                                             /* CTS port number              */      \
  TEST_UART_I0_CTS_PIN,                                              /* CTS pin number               */      \
  TEST_UART_I0_RTS_PORT,                                             /* RTS port number              */      \
  TEST_UART_I0_RTS_PIN,                                              /* RTS pin number               */      \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueueI0,                       /* RX operation queue           */      \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueueI0,                       /* TX operation queue           */      \
  TEST_UART_I0_CTS_LOC,                                              /* CTS location                 */      \
  TEST_UART_I0_RTS_LOC                                               /* RTS location                 */      \
}
#elif defined(USART_CTRL_MVDIS)
/**
 * Platform 1 (GG)
 */
#define TEST_UART_I0                                                                                         \
{                                                                                                               \
  TEST_UART_I0_DEVICE,                                               /* USART port                   */      \
  115200,                                                               /* Baud rate                    */      \
  TEST_UART_I0_LOC,                                                  /* USART location number        */      \
  (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */      \
  (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */      \
  (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */      \
  false,                                                                /* Majority vote disable        */      \
  uartdrvFlowControlHw,                                                 /* Flow control                 */      \
  TEST_UART_I0_CTS_PORT,                                             /* CTS port number              */      \
  TEST_UART_I0_CTS_PIN,                                              /* CTS pin number               */      \
  TEST_UART_I0_RTS_PORT,                                             /* RTS port number              */      \
  TEST_UART_I0_RTS_PIN,                                              /* RTS pin number               */      \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueueI0,                       /* RX operation queue           */      \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueueI0,                       /* TX operation queue           */      \
}
#else
/**
 * Platform 1 (G)
 */
#define TEST_UART_I0                                                                                         \
{                                                                                                               \
  TEST_UART_I0_DEVICE,                                               /* USART port                   */      \
  115200,                                                               /* Baud rate                    */      \
  TEST_UART_I0_LOC,                                                  /* USART location number        */      \
  (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */      \
  (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */      \
  (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */      \
  uartdrvFlowControlHw,                                                 /* Flow control                 */      \
  TEST_UART_I0_CTS_PORT,                                             /* CTS port number              */      \
  TEST_UART_I0_CTS_PIN,                                              /* CTS pin number               */      \
  TEST_UART_I0_RTS_PORT,                                             /* RTS port number              */      \
  TEST_UART_I0_RTS_PIN,                                              /* RTS pin number               */      \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueueI0,                       /* RX operation queue           */      \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueueI0                        /* TX operation queue           */      \
}
#endif

#if defined( TEST_UART_I1_DEVICE )
/**
 * Interface 1 config
 */
#if defined(_USART_ROUTELOC0_MASK)
/**
 * Platform 2
 */
#define TEST_UART_I1                                                                                         \
{                                                                                                               \
  TEST_UART_I1_DEVICE,                                               /* USART port                   */      \
  115200,                                                               /* Baud rate                    */      \
  TEST_UART_I1_LOC,                                                  /* USART location number        */      \
  (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */      \
  (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */      \
  (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */      \
  false,                                                                /* Majority vote disable        */      \
  uartdrvFlowControlHw,                                                 /* Flow control                 */      \
  TEST_UART_I1_CTS_PORT,                                             /* CTS port number              */      \
  TEST_UART_I1_CTS_PIN,                                              /* CTS pin number               */      \
  TEST_UART_I1_RTS_PORT,                                             /* RTS port number              */      \
  TEST_UART_I1_RTS_PIN,                                              /* RTS pin number               */      \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueueI1,                       /* RX operation queue           */      \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueueI1,                       /* TX operation queue           */      \
  TEST_UART_I1_CTS_LOC,                                              /* CTS location                 */      \
  TEST_UART_I1_RTS_LOC                                               /* RTS location                 */      \
}
#elif defined(USART_CTRL_MVDIS)
/**
 * Platform 1 (GG)
 */
#define TEST_UART_I1                                                                                         \
{                                                                                                               \
  TEST_UART_I1_DEVICE,                                               /* USART port                   */      \
  115200,                                                               /* Baud rate                    */      \
  TEST_UART_I1_LOC,                                                  /* USART location number        */      \
  (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */      \
  (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */      \
  (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */      \
  false,                                                                /* Majority vote disable        */      \
  uartdrvFlowControlHw,                                                 /* Flow control                 */      \
  TEST_UART_I1_CTS_PORT,                                             /* CTS port number              */      \
  TEST_UART_I1_CTS_PIN,                                              /* CTS pin number               */      \
  TEST_UART_I1_RTS_PORT,                                             /* RTS port number              */      \
  TEST_UART_I1_RTS_PIN,                                              /* RTS pin number               */      \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueueI1,                       /* RX operation queue           */      \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueueI1,                       /* TX operation queue           */      \
}
#else
/**
 * Platform 1 (G)
 */
#define TEST_UART_I1                                                                                         \
{                                                                                                               \
  TEST_UART_I1_DEVICE,                                               /* USART port                   */      \
  115200,                                                               /* Baud rate                    */      \
  TEST_UART_I1_LOC,                                                  /* USART location number        */      \
  (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */      \
  (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */      \
  (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */      \
  uartdrvFlowControlHw,                                                 /* Flow control                 */      \
  TEST_UART_I1_CTS_PORT,                                             /* CTS port number              */      \
  TEST_UART_I1_CTS_PIN,                                              /* CTS pin number               */      \
  TEST_UART_I1_RTS_PORT,                                             /* RTS port number              */      \
  TEST_UART_I1_RTS_PIN,                                              /* RTS pin number               */      \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueueI1,                       /* RX operation queue           */      \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueueI1                        /* TX operation queue           */      \
}
#endif
#endif
