@ Alaf do Nascimento Santos
@ 19/09/2022
@ Exercice 4 : Manipulation d’une chaine de caractère

.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb
.global _start

.data
    .EQU destin, 0x10000000
    .EQU combienDefois, 5
    chaine1: .ascii "Bonjour le monde !\0"
    chaine2: .asciz "Bonjour le monde !"
    chaine3: .string "Bonjour le monde !"

.text
_start:
main:
    ldr r0, =destin /* destin */
    ldr r1, =chaine1 /* store address of start of string to r1 */
    ldr r3, =combienDefois

boucle:
    bl copy
    ldr r1, =chaine1
    subs r3, #1 
    bne boucle

end: b end

copy:
    ldrb r2, [r1]
    strb r2, [r0]
    add r0, r0, #1
    add r1, r1, #1
    cmp r2, #0
    bne copy
    bx lr