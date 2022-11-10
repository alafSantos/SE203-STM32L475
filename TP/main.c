#include "led.h"

int main(){
  led_init();

  while (1){
    led(LED_OFF);
    led(LED_GREEN);
    delay(2*TIME);

    led(LED_OFF);
    led(LED_YELLOW);
    delay(2*TIME);

    led(LED_OFF);
    led(LED_BLUE);
    delay(2*TIME);
  }
  
  return 0;
}
