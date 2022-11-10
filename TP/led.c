#include "led.h"

static void clock_enable(){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;
}

void led_init(){
    clock_enable();
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;
    GPIOC->MODER = GPIOC->MODER & ~GPIO_MODER_MODE9_Msk;
}

/* il faut lire la page 306/1881 du manuel */
void led_g_on(){
    GPIOB->BSRR = GPIO_BSRR_BS14_Msk;
}

void led_g_off(){
    GPIOB->BSRR = GPIO_BSRR_BR14_Msk;
}

void led(state s){
    switch (s)
    {
        case LED_OFF:
            led_g_off();
            GPIOC->MODER = GPIOC->MODER & ~GPIO_MODER_MODE9_Msk;
            break;

        case LED_GREEN:
            led_g_on();
            break;

        case LED_YELLOW:
            GPIOC->MODER = (GPIOC->MODER &~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0;
            GPIOC->BSRR = GPIO_BSRR_BS9_Msk;
            break;

        case LED_BLUE:
            GPIOC->MODER = (GPIOC->MODER &~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0;
            GPIOC->BSRR  = GPIO_BSRR_BR9_Msk;
            break;

    }
}

void delay(int n){
  for(int i = 0; i < n; i++)
    asm volatile("nop");
}
