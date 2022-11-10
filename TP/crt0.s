.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start

@ read only object code for first text section (still rom)
.section .textFLASH, "ax", %progbits

.thumb_func
_start:
    ldr sp, =_stackStart /* initialiser le pointeur pile, 0x10008000 32K (0x8000) */
    bl init_text /* text : LMA to VMA */
    bl init_data /* data : LMA to VMA */
    bl init_IRQ /* IRQ : LMA to VMA */
    bl init_bss /* Création et initialisation à 0 de la bss en C */
    bl main /* main en C */

_exit:
    b _exit
    