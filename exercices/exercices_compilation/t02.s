	.cpu arm7tdmi
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 4
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"t02.c"
	.text
	.align	2
	.global	f
	.arch armv4t
	.syntax unified
	.arm
	.fpu softvfp
	.type	f, %function
f:
	@ Function supports interworking.
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	ldr	r3, .L2
	ldr	r2, [r3]
	ldr	r3, .L2+4
	ldr	r1, [r3]
	ldr	r3, [r2]
	ldr	r0, [r1]
	add	r3, r3, r0
	str	r3, [r2]
	ldr	r3, .L2+8
	ldr	r2, [r3]
	ldr	r1, [r1]
	ldr	r3, [r2]
	add	r3, r3, r1
	str	r3, [r2]
.L3:
	.align	2
.L2:
	.word	a
	.word	c
	.word	b
	.size	f, .-f
	.comm	c,4,4
	.comm	b,4,4
	.comm	a,4,4
	.ident	"GCC: (15:9-2019-q4-0ubuntu1) 9.2.1 20191025 (release) [ARM/arm-9-branch revision 277599]"
