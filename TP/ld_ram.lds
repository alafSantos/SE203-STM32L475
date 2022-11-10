MEMORY {
 flash (rx)  : ORIGIN = 0x08000000, LENGTH = 1M
 sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
 sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}

SECTIONS {
    .IRQ : {
        *(.IRQ)
    } > sram1

    .text : {
        *(.text)
    } > sram1

    .rodata : {
        *(.rodata)
    } > sram1
    
    .data : {
        *(.data)
    } > sram1
    
    .bss : {
        _bstart = .;
        *(.bss) *(COMMON)
        _bend = .;
    } > sram1
}

_stackStart = ORIGIN(sram2) + LENGTH(sram2);
ENTRY(_start)
