MEMORY {
 flash (rx) : ORIGIN = 0x08000000, LENGTH = 1M
 sram1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K
 sram2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K
}

SECTIONS {
    .IRQFLASH : {
        *(.IRQFLASH)
    } > flash

    .textFLASH : {
        *(.textFLASH)
    } > flash

    .IRQ : {
        _istart = .;
        *(.IRQ)
        _iend = .;
    } > sram1 AT>flash

    .text : {
        _tstart = .;
        *(.text)
        _tend = .;
    } > sram1 AT>flash

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
textAddr_LMA = LOADADDR(.text);
IRQAddr_LMA =  LOADADDR(.IRQ);

ENTRY(_start)

