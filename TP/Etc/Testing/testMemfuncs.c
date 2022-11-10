#include "memfuncs.h"
int main()
{
    // uint32_t a= 0x44332211;
    // uint8_t *p = (uint32_t *) &a;
    // printf("premier octet de a = %x\n"
    // , *p);
    // return 0;

    uint32_t n = 20;
    const uint32_t c = 33;
    int *s;

    memset(s, c, n);
    return 0;
}
