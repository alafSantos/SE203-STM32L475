.syntax unified
.arch armv7-m
.cpu cortex-m4

.thumb

.global _start

_start:

ldr r0, =#0x22222222
ldr r1, =#0x22222222
ldr r2, =#0x22222222
ldr r3, =#0x22222222
ldr r4, =#0x22222222

end : b end
