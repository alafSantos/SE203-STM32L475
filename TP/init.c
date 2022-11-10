#include <stdint.h>
extern uint8_t _bstart, _bend;

void init_bss(){
    for (uint8_t *dst = &_bstart; dst < &_bend; dst++)
        *dst = 0;
}