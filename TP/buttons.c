#include "buttons.h"
#include "led.h"
#include "uart.h"
#include "irq.h"

static void clock_enable(){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
}

static void pinMode(){
    GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;
}

static void sourceIRQ(){ // page page 403
    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13_Msk;
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
}

static void hardwareInterruptSelection(){ // page 402, section 14.3.4
    EXTI->IMR1 |= EXTI_IMR1_IM13_Msk; // Configure the corresponding mask bit in the EXTI_IMR register.

    // EXTI_RTSR and EXTI_FTSR - detection de borde
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13_Msk; // rising
    EXTI->FTSR1 |= EXTI_FTSR1_FT13_Msk; // falling

    NVIC_EnableIRQ(40); //  EXTI Line[15:10] interrupts, so that an interrupt coming from one of the EXTI lines can be correctly acknowledged
}

void button_init(void){
    led_init(); //pour utiliser led_g_toggle après
    clock_enable(); // active l'horloge du port C
    pinMode(); // configure la broche PC13 en GPIO et en entrée
    sourceIRQ(); // sélectionne la broche PC13 comme source d'IRQ pour EXTI13
    hardwareInterruptSelection(); // configure l'EXTI selon la procédure décrite en 14.3.4.
}

void EXTI15_10_IRQHandler(void){
    EXTI->PR1 |= EXTI_PR1_PIF13_Msk; //acquittement de l'interruption dans l'EXTI
    led_g_toggle(); //toggle de la LED verte
}
