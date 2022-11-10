#include <stdint.h>
extern uint8_t _bstart, _bend;
extern uint8_t _tstart, _tend;
extern uint8_t _dstart, _dend;
extern uint8_t _istart, _iend;
extern uint8_t dataAddr_LMA, textAddr_LMA, IRQAddr_LMA;

void __attribute__((section(".textFLASH"))) init_text(){
    uint8_t *src = &textAddr_LMA;
    for(uint8_t *dst = &_tstart; dst < &_tend; dst++)
        *dst = *src++;
};

void init_data(){
    uint8_t *src = &dataAddr_LMA;
    for (uint8_t *dst = &_dstart; dst < &_dend; dst++)
        *dst = *src++;
}

void init_IRQ(){
    uint8_t *src = &IRQAddr_LMA;
    for (uint8_t *dst = &_istart; dst < &_iend; dst++)
        *dst = *src++;
}

void init_bss(){
    for (uint8_t *dst = &_bstart; dst < &_bend; dst++)
        *dst = 0;
}