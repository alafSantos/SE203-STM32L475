@ Alaf do Nascimento Santos
@ 19/09/2022
@ Exercice 2 : Copie du contenu d’une zone mémoire

.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:

ldr r0, =0xdeadbeef
ldr r1, =0x10000000

ldr r2, =0x10000000
ldr r3, =0x100
add r2, r2, r3

loop :
    str r0, [r1]
    add r1, r1, #4
    cmp r1, r2
    bne loop

/*---------------------*/
ldr r0, =0x10000000
ldr r1, =0x10000100
ldr r3, =0x00000100 

loop2 :
    ldr r2, [r0]
    str r2, [r1]
    add r0, #4  /* position source */
    add r1, #4  /* position destin */
    subs r3, #4 /* counter */
    bne loop2

end : b end
