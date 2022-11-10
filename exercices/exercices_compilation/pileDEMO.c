#include<stdio.h>
#include<stdint.h>

uint32_t * pos[2];

void h(){
    int c;
    printf("%x, %x, %x\n", pos[0], pos[1], &c);
}

void g(){
    int b;
    pos[1] = &b;
    h();
}

void f(){
    int a;
    pos[0] = &a;
    g();
}

int main(){
    f();
    return 0;
}