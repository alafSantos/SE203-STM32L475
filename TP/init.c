#include <stdint.h>
extern uint8_t _bstart, _bend;
extern uint8_t _dstart, _dend, dataAddr_LMA;

void init_bss(){
    for (uint8_t *dst = &_bstart; dst < &_bend; dst++)
        *dst = 0;
}

void init_data(){
    uint8_t *src = &dataAddr_LMA;
    for (uint8_t *dst = &_dstart; dst < &_dend; dst++)
        *dst = *src++;
}
