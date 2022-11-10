#include<stdint.h>
uint32_t a; // global variable

void g();

__attribute__((naked)) void f() {
 for (uint8_t i=0; i<=a; i++)
    g();
}


void g(){

}