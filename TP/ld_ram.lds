MEMORY {
 flash (rx)  : ORIGIN = 0x08000000, LENGTH = 1M
 sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
 sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}

SECTIONS {
    .IRQ : {
        *(.IRQ)
    } > flash

    .text : {
        *(.text)
    } > flash

    .data : {
        _dstart = .;
        *(.data)
        _dend = .;
    } > sram1 AT>flash

    .rodata : {
        *(.rodata)
    } > flash
    
    .bss : {
        _bstart = .;
        *(.bss) *(COMMON)
        _bend = .;
    } > sram1
}

_stackStart = ORIGIN(sram2) + LENGTH(sram2);

/* renvoie la LMA d'une section (debut) */
dataAddr_LMA = LOADADDR(.data);

ENTRY(_start)

