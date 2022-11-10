#include "led.h"
#include "clocks.h"
#include "uart.h"

int main(){
  clocks_init();
  uart_init();
  
  // checksum();
  uart_echo();
 
  return 0;
}
