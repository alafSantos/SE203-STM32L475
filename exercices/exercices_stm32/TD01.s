@ Alaf do Nascimento Santos
@ 19/09/2022
@ Exercice 1 : Initialisation d’une zone mémoire

.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:

/* ldr est une pseudo-instruction */
ldr r0, =0xdeadbeef
ldr r1, =0x10000000 /* on peut pas utiliser ce adress dans la carte */

ldr r2, =0x10000000
ldr r3, =0x100
add r2, r2, r3

loop :
    str r0, [r1]
    add r1, r1, #4
    cmp r1, r2
    bne loop

end : b end

/* .word 0xdeadbeef */

/* arm-none-eabi-as -c toto.s -o toto.o */
/* arm-none-eabi-objdump -d toto */

/* https://perso.telecom-paristech.fr/graba/ */