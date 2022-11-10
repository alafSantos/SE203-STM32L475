#include "clocks.h"
#include "irq.h"
#include "buttons.h"
#include "matrix.h"
#include "uart.h"

/* Définissez un objet global qui contiendra la trame affichée. Il sera modifé par le handler d'IRQ du port série, et lu par la tâche d'affichage */
volatile rgb_color frames[64];

int main(){
  clocks_init();
  matrix_init();
  irq_init();
  button_init();
  uart_init(38400);

  while(1)
    display_image((rgb_color *)frames);

  return 0;
}
