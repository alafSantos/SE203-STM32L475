#include "clocks.h"
#include "irq.h"
#include "buttons.h"
#include "matrix.h"
#include "uart.h"
#include "timer.h"
#include "led.h"
#include "stm32l475xx.h"
#include "core_cm4.h"

/* Définissez un objet global qui contiendra la trame affichée. Il sera modifé par le handler d'IRQ du port série, et lu par la tâche d'affichage */
volatile rgb_color frames[64];

int main(){
  clocks_init();
  irq_init();
  led_init();
  matrix_init();
  uart_init(38400);
  timer_init((int)((SECOND/60) - 1)/8); // affichage de l'image courante au moins 60 fois par seconde, /8 parce que je fais ligne par ligne
  button_init();
  
  while(1);

  return 0;
}
