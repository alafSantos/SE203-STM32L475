extern char _bstart, _bend;

void init_bss(){
    char* dst = &_bstart;
    for (dst = &_bstart; dst < &_bend; dst++)
        *dst = 0;
}