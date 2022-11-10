#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>
#include "stm32l475xx.h"

#define SYSCLK 80000000

void uart_init();
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);
void uart_echo();
void checksum();


#endif