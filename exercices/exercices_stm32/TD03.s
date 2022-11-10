@ Alaf do Nascimento Santos
@ 19/09/2022
@ Exercice 3 : Procédures réutilisables

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

/*----------origine, destin, taille-----------*/
ldr r0, =0x10000000
ldr r1, =0x10000300 
ldr r2, =0x00000100 

bl copy

end : b end

copy :
    loop2:
        ldr r3, [r0]
        str r3, [r1]
        add r0, #0  /* la position source ne change pas */
        add r1, #4  /* position destin */
        subs r2, #4 /* counter */
        bne loop2
    bx lr
