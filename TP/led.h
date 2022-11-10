#ifndef LED_H
#define LED_H

#include<stdint.h>
#define TIME 100000

typedef enum
{
    LED_OFF,
    LED_GREEN,
    LED_YELLOW,
    LED_BLUE
} state;

void clock_disable(void);
void clock_enable(void);

void led_init(void);

void led_g_on(void);
void led_g_off(void);
void led(state);

void delay(int n);

#endif