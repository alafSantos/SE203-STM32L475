#include "memfuncs.h"

void *memcpy(void *dest, const void *src, size_t n){
    uint8_t *pDest = (uint8_t*) dest;
    uint8_t *pSrc = (uint8_t*) src;
    int intN = (int)n;

    const int8_t overlap = (pSrc + intN-1 >= pDest) || (pDest + intN-1 >= pSrc);

    if (overlap)
        return memmove(dest, src, n);

    for (int i = 0; i < intN; i++)
        pDest[i] = pSrc[i];
    return dest; 
}

void *memmove(void *dest, const void *src, size_t n) {
    uint8_t *pDest = (uint8_t *) dest;
    uint8_t *pSrc = (uint8_t *) src;
    int intN = (int)n;

    if (pSrc + intN-1 >= pDest) {
        for (int i = intN-1; 0 <= i; i--)
            pDest[i] = pSrc[i];
    }

    if (pDest + intN-1 >= pSrc) {
        for (int i = 0; i < intN; i++)
            pDest[i] = pSrc[i];
    }

    return dest;
}

void *memset(void *s, int c, size_t n){
    uint8_t *p = (uint8_t*) s;

    for (size_t i = 0; i < n; i++)
        p[i] = (uint8_t) c;
    
    return s;
}

int memcmp(const void* s1, const void* s2, size_t n)
{
    const uint8_t *pS1 = s1;
    const uint8_t *pS2 = s2;

    while(n){
        if(*pS1 != *pS2){
            int8_t diff = *pS1 - *pS2;
            if(diff < 0)
                return -1;
            else return 1;
        }
        else{
            pS1++;
            pS2++;
        }
        n--;
    }
    return 0;
}