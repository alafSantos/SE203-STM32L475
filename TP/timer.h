#ifndef TIMER_H
#define TIMER_H

#include<stdint.h>
#include "stm32l475xx.h"

#define SYSCLK 80000000
#define SECOND 1000000

void timer_init(int max_us);

#endif