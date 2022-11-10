#include "led.h"

static void clock_enable(){
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN;
}

void led_init(void){
    clock_enable();
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;
    GPIOC->MODER = GPIOC->MODER & ~GPIO_MODER_MODE9_Msk;
}

static uint8_t led_g_etat = 0; //une variable static pour la fonction led_g_toggle

/* il faut lire la page 306/1881 du manuel */
void led_g_on(void){
    GPIOB->BSRR = GPIO_BSRR_BS14_Msk;
    led_g_etat = 1;
}

void led_g_off(void){
    GPIOB->BSRR = GPIO_BSRR_BR14_Msk;
    led_g_etat = 0;
}

void led_g_toggle(void){
    if(led_g_etat)
        led_g_off();
    else led_g_on ();
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
