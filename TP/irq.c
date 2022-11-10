#include "irq.h"

/*
    désactiver toutes les interruptions
    faire une boucle sans fin 
*/
#define MAKE_DEFAULT_HANDLER(handler) \
    void __attribute__((weak)) handler(){\
        __disable_irq();\
        while(1);\
    }

MAKE_DEFAULT_HANDLER(NMI_Handler)
MAKE_DEFAULT_HANDLER(HardFault_Handler)
MAKE_DEFAULT_HANDLER(MemManage_Handler)
MAKE_DEFAULT_HANDLER(BusFault_Handler)
MAKE_DEFAULT_HANDLER(UsageFault_Handler)
MAKE_DEFAULT_HANDLER(SVC_Handler)
MAKE_DEFAULT_HANDLER(PendSV_Handler)
MAKE_DEFAULT_HANDLER(SysTick_Handler)
MAKE_DEFAULT_HANDLER(WWDG_IRQHandler)
MAKE_DEFAULT_HANDLER(PVD_PVM_IRQHandler)
MAKE_DEFAULT_HANDLER(RTC_TAMP_STAMP_IRQHandler)
MAKE_DEFAULT_HANDLER(RTC_WKUP_IRQHandler)
MAKE_DEFAULT_HANDLER(FLASH_IRQHandler)
MAKE_DEFAULT_HANDLER(RCC_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI0_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI1_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI2_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI3_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_CH1_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_CH2_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_CH3_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_CH4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_CH5_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_CH6_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA1_CH7_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC1_2_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_TX_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_RX0_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_RX1_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN1_SCE_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI9_5_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_BRK_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_UP_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_TRG_COM_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM1_CC_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM2_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM3_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM4_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C1_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C1_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C2_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C2_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI1_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI2_IRQHandler)
MAKE_DEFAULT_HANDLER(USART1_IRQHandler)
MAKE_DEFAULT_HANDLER(USART2_IRQHandler)
MAKE_DEFAULT_HANDLER(USART3_IRQHandler)
MAKE_DEFAULT_HANDLER(EXTI15_10_IRQHandler)
MAKE_DEFAULT_HANDLER(RTC_ALARM_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT3_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_BRK_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_UP_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_TRG_COM_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM8_CC_IRQHandler)
MAKE_DEFAULT_HANDLER(ADC3_IRQHandler)
MAKE_DEFAULT_HANDLER(FMC_IRQHandler)
MAKE_DEFAULT_HANDLER(SDMMC1_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM5_IRQHandler)
MAKE_DEFAULT_HANDLER(SPI3_IRQHandler)
MAKE_DEFAULT_HANDLER(UART4_IRQHandler)
MAKE_DEFAULT_HANDLER(UART5_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM6_DACUNDER_IRQHandler)
MAKE_DEFAULT_HANDLER(TIM7_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_CH1_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_CH2_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_CH3_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_CH4_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_CH5_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT0_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT1_IRQHandler)
MAKE_DEFAULT_HANDLER(DFSDM1_FLT2_IRQHandler)
MAKE_DEFAULT_HANDLER(COMP_IRQHandler)
MAKE_DEFAULT_HANDLER(LPTIM1_IRQHandler)
MAKE_DEFAULT_HANDLER(LPTIM2_IRQHandler)
MAKE_DEFAULT_HANDLER(OTG_FS_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_CH6_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2_CH7_IRQHandler)
MAKE_DEFAULT_HANDLER(LPUART1_IRQHandler)
MAKE_DEFAULT_HANDLER(QUADSPI_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C3_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C3_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(SAI1_IRQHandler)
MAKE_DEFAULT_HANDLER(SAI2_IRQHandler)
MAKE_DEFAULT_HANDLER(SWPMI1_IRQHandler)
MAKE_DEFAULT_HANDLER(TSC_IRQHandler)
MAKE_DEFAULT_HANDLER(LCD_IRQHandler)
MAKE_DEFAULT_HANDLER(AES_IRQHandler)
MAKE_DEFAULT_HANDLER(RNG_IRQHandler)
MAKE_DEFAULT_HANDLER(FPU_IRQHandler)
MAKE_DEFAULT_HANDLER(HASH_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C4_EV_IRQHandler)
MAKE_DEFAULT_HANDLER(I2C4_ER_IRQHandler)
MAKE_DEFAULT_HANDLER(DCMI_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN2_TX_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN2_RX0_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN2_RX1_IRQHandler)
MAKE_DEFAULT_HANDLER(CAN2_SCE_IRQHandler)
MAKE_DEFAULT_HANDLER(DMA2D_IRQHandler)

extern uint8_t _start, _stackStart;

/*
  On relogera la table des vecteurs d'interruption en RAM, 
  de façon à donner à l'utilisateur la possibilité de mettre en place ses propres handlers d'IRQ.
*/
void __attribute__((section(".IRQFLASH"))) *vector_table_flash[] = {
  &_stackStart,
  &_start,  
  // ARM internal exceptions
  NMI_Handler,        /* NMI handler */
  HardFault_Handler,  /* Hard Fault handler */
  MemManage_Handler, /* Memory management */
  BusFault_Handler, /* Pre-fetch fault, memory access fault */
  UsageFault_Handler, /* Undefined instruction or illegal state */
  0,                  /* Reserved */
  0,                  /* Reserved */
  0,                  /* Reserved */
  0,                  /* Reserved */
  SVC_Handler,        /* SVC handler */
  0,                  /* Reserved */
  0,                  /* Reserved */
  PendSV_Handler,     /* Pending SVC handler */
  SysTick_Handler    /* SysTick hanlder */
};

/* Interrupt and exception vectors - pages 396 - 399 (stm32l475xx_rm.pdf) */
void __attribute__((section(".IRQ"))) *vector_table[] = {
  // Stack and Reset Handler
  &_stackStart,            /* Top of stack */
  &_start,             /* Reset handler */

  // ARM internal exceptions
  NMI_Handler,        /* NMI handler */
  HardFault_Handler,  /* Hard Fault handler */
  MemManage_Handler, /* Memory management */
  BusFault_Handler, /* Pre-fetch fault, memory access fault */
  UsageFault_Handler, /* Undefined instruction or illegal state */
  0,                  /* Reserved */
  0,                  /* Reserved */
  0,                  /* Reserved */
  0,                  /* Reserved */
  SVC_Handler,        /* SVC handler */
  0,                  /* Reserved */
  0,                  /* Reserved */
  PendSV_Handler,     /* Pending SVC handler */
  SysTick_Handler,    /* SysTick hanlder */

  // STM32L475 External interrupts
  WWDG_IRQHandler, /* Watchdog IRQ */
  PVD_PVM_IRQHandler, /* PVD/PVM1/PVM2/PVM3/PVM4  */
  RTC_TAMP_STAMP_IRQHandler, /* RTC Tamper or TimeStamp /CSS on LSE  */
  RTC_WKUP_IRQHandler, /* RTC Wakeup timer through EXTI line 20 */
  FLASH_IRQHandler, /* Flash global interrupt */
  RCC_IRQHandler, /* RCC global interrupt */
  EXTI0_IRQHandler, /* EXTI Line0 interrupt */
  EXTI1_IRQHandler, /* EXTI Line1 interrupt */
  EXTI2_IRQHandler, /* EXTI Line2 interrupt */
  EXTI3_IRQHandler, /* EXTI Line3 interrupt */
  EXTI4_IRQHandler, /* EXTI Line4 interrupt */
  DMA1_CH1_IRQHandler, /* DMA1 channel 1 interrupt */
  DMA1_CH2_IRQHandler, /* DMA1 channel 2 interrupt */
  DMA1_CH3_IRQHandler, /* DMA1 channel 3 interrupt */
  DMA1_CH4_IRQHandler, /* DMA1 channel 4 interrupt */
  DMA1_CH5_IRQHandler, /* DMA1 channel 5 interrupt */
  DMA1_CH6_IRQHandler, /* DMA1 channel 6 interrupt */
  DMA1_CH7_IRQHandler, /* DMA1 channel 7 interrupt */
  ADC1_2_IRQHandler, /* ADC1 and ADC2 global interrupt */
  CAN1_TX_IRQHandler, /* CAN1_TX interrupts */
  CAN1_RX0_IRQHandler, /* CAN1_RX0 interrupts */
  CAN1_RX1_IRQHandler, /*  CAN1_RX1 interrupt */
  CAN1_SCE_IRQHandler, /* CAN1_SCE interrupt */
  EXTI9_5_IRQHandler, /* EXTI Line[9:5] interrupts */
  TIM1_BRK_IRQHandler, /* TIM1 Break/TIM15 global interrupts  */
  TIM1_UP_IRQHandler, /* TIM1 Update/TIM16 global interrupts  */
  TIM1_TRG_COM_IRQHandler, /* TIM1 trigger and commutation/TIM17 interrupts */
  TIM1_CC_IRQHandler, /* TIM1 capture compare interrupt */
  TIM2_IRQHandler, /* TIM2 global interrupt */
  TIM3_IRQHandler, /* TIM3 global interrupt */
  TIM4_IRQHandler, /* TIM4 global interrupt */
  I2C1_EV_IRQHandler, /* I2C1 event interrupt */
  I2C1_ER_IRQHandler, /* I2C1 error interrupt */
  I2C2_EV_IRQHandler, /* I2C2 event interrupt */
  I2C2_ER_IRQHandler, /* I2C2 error interrupt */
  SPI1_IRQHandler, /* SPI1 global interrupt */
  SPI2_IRQHandler, /* SPI2 global interrupt */
  USART1_IRQHandler, /* USART1 global interrupt */
  USART2_IRQHandler, /* USART2 global interrupt */
  USART3_IRQHandler, /* USART3 global interrupt */
  EXTI15_10_IRQHandler, /* EXTI Line[15:10] interrupts */
  RTC_ALARM_IRQHandler, /*  RTC alarms through EXTI line 18 interrupts */
  DFSDM1_FLT3_IRQHandler, /* DFSDM1_FLT3 global interrupt */
  TIM8_BRK_IRQHandler, /* TIM8 Break interrupt */
  TIM8_UP_IRQHandler, /* TIM8 Update interrupt */
  TIM8_TRG_COM_IRQHandler, /* TIM8 trigger and commutation interrupt */
  TIM8_CC_IRQHandler, /* TIM8 capture compare interrupt */
  ADC3_IRQHandler, /* ADC3 global interrupt */
  FMC_IRQHandler, /* FMC global interrupt */
  SDMMC1_IRQHandler, /* SDMMC1 global interrupt */
  TIM5_IRQHandler, /* TIM5 global interrupt */
  SPI3_IRQHandler, /* SPI3 global interrupt */
  UART4_IRQHandler, /* UART4 global interrupt */
  UART5_IRQHandler, /* UART5 global interrupt */
  TIM6_DACUNDER_IRQHandler, /* TIM6 global and DAC1 underrun interrupts */
  TIM7_IRQHandler, /* TIM7 global interrupt */
  DMA2_CH1_IRQHandler, /* DMA2 channel 1 interrupt */
  DMA2_CH2_IRQHandler, /* DMA2 channel 2 interrupt */
  DMA2_CH3_IRQHandler, /* DMA2 channel 3 interrupt */
  DMA2_CH4_IRQHandler, /* DMA2 channel 4 interrupt */
  DMA2_CH5_IRQHandler, /* DMA2 channel 5 interrupt */
  DFSDM1_FLT0_IRQHandler, /* DFSDM1_FLT0 global interrupt */
  DFSDM1_FLT1_IRQHandler, /* DFSDM1_FLT1 global interrupt */
  DFSDM1_FLT2_IRQHandler, /* DFSDM1_FLT2 global interrupt */
  COMP_IRQHandler, /* COMP1/COMP2 through EXTI lines 21/22 interrupts */
  LPTIM1_IRQHandler, /* LPTIM1 global interrupt */
  LPTIM2_IRQHandler, /* LPTIM2 global interrupt */
  OTG_FS_IRQHandler, /* OTG_FS global interrupt  */
  DMA2_CH6_IRQHandler, /* DMA2 channel 6 interrupt */
  DMA2_CH7_IRQHandler, /* DMA2 channel 7 interrupt */
  LPUART1_IRQHandler, /* LPUART1 global interrupt */
  QUADSPI_IRQHandler, /* QUADSPI global interrupt */
  I2C3_EV_IRQHandler, /* I2C3 event interrupt */
  I2C3_ER_IRQHandler, /* I2C3 error interrupt */
  SAI1_IRQHandler, /* SAI1 global interrupt */
  SAI2_IRQHandler, /* SAI2 global interrupt */
  SWPMI1_IRQHandler, /* SWPMI1 global interrupt */
  TSC_IRQHandler, /* TSC global interrupt */
  LCD_IRQHandler, /* LCD global interrupt */
  AES_IRQHandler, /* AES global interrupt */
  RNG_IRQHandler, /* RNG global interrupt */
  FPU_IRQHandler, /* Floating point interrupt */

  // STM32L496xx/4A6xx devices
  HASH_IRQHandler, /* HASH and CRS interrupt */
  I2C4_EV_IRQHandler, /* I2C4 event interrupt */
  I2C4_ER_IRQHandler, /* I2C4 error interrupt */
  DCMI_IRQHandler, /* DCMI global interrupt */
  CAN2_TX_IRQHandler, /* textAN2 TX interrupt */
  CAN2_RX0_IRQHandler, /* CAN2 RX0 interrupt */
  CAN2_RX1_IRQHandler, /* CAN2 RX1 interrupt */
  CAN2_SCE_IRQHandler, /* CAN SCE interrupt */
  DMA2D_IRQHandler /* DMA2D global interrupt */
};

void irq_init(void) {
  SCB->VTOR = (uint32_t) vector_table;
}