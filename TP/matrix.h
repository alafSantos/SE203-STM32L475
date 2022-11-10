#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include "stm32l475xx.h"

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

void matrix_init();
void pulse_SCK();
void pulse_LAT();
void deactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val, int bank);
void mat_set_row(int row, const rgb_color *val);
void init_bank0();
void test_pixels();

#endif