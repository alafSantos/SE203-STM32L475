#include "led.h"

#define RCC_base_adress 0x40021000
#define RCC_AHB2ENR_offset 0x4C
#define RCC_AHB2ENR (*(volatile uint32_t *) (RCC_base_adress + RCC_AHB2ENR_offset))

#define AHB2_BUS_GPIOB_adress 0x48000400
#define AHB2_BUS_GPIOC_adress 0x48000800

#define AHB2_BUS_GPIOB_offset 0x00 
#define AHB2_BUS_GPIOC_offset 0x00 

#define GPIOB_PORT_MODE  (*(volatile uint32_t *) (AHB2_BUS_GPIOB_adress + AHB2_BUS_GPIOB_offset))
#define GPIOC_PORT_MODE (*(volatile uint32_t *) (AHB2_BUS_GPIOC_adress + AHB2_BUS_GPIOC_offset))

#define GPIOx_BSRR_offset 0x18
#define GPIOB_MODER (*(volatile uint32_t *) (AHB2_BUS_GPIOB_adress + GPIOx_BSRR_offset))
#define GPIOC_MODER (*(volatile uint32_t *) (AHB2_BUS_GPIOC_adress + GPIOx_BSRR_offset))

#define INPUT_B  0xCFFFFFFF //11001111111111111111111111111111
#define OUTPUT_B 0xDFFFFFFF //11011111111111111111111111111111

#define INPUT_C  0xFFF3FFFF //11111111111100111111111111111111
#define OUTPUT_C 0xFFF7FFFF //11111111111101111111111111111111

#define BITSET(registre, valeur, position) ((registre & (~(0b11 << position))) | (valeur << position))

void clock_disable(){
    RCC_AHB2ENR &= ~2; // 11111111111111111111111111111101 - disable B
    RCC_AHB2ENR &= ~4; // 11111111111111111111111111111011 - disable C
}

void clock_enable(){
    RCC_AHB2ENR |= 2; // 00000000000000000000000000000010 - enable B
    RCC_AHB2ENR |= 4; // 00000000000000000000000000000100 - enable C
}

void led_init(){
    clock_enable();
    GPIOB_PORT_MODE = OUTPUT_B;
    GPIOC_PORT_MODE = OUTPUT_C;
}

/* il faut lire la page 306/1881 du manuel */
void led_g_on(){
    GPIOB_MODER = BITSET(GPIOB_MODER, 0b01, 14); // MODE14
}

void led_g_off(){
    GPIOB_MODER = BITSET(GPIOB_MODER, 0b01, 30); // MODE14
}

void led(state s){
    switch (s)
    {
        case LED_OFF:
            led_g_off();
            GPIOC_PORT_MODE = INPUT_C; // ENTRÉE = haute impédance = turn off
            break;

        case LED_GREEN:
            led_g_on();
            break;

        case LED_YELLOW:
            GPIOC_PORT_MODE = OUTPUT_C; // Sortie encore une fois
            GPIOC_MODER = BITSET(GPIOB_MODER, 0b01, 9);//0x00000200; //00000000000000000000001000000000
            break;

        case LED_BLUE:
            GPIOC_PORT_MODE = OUTPUT_C; // Sortie encore une fois
            GPIOC_MODER = BITSET(GPIOB_MODER, 0b01, 25); //00000010000000000000000000000000
            break;

    }
}

void delay(int n){
  for(int i = 0; i < n; i++)
    asm volatile("nop");
}
