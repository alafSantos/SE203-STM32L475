.data
.word a

.text
ldr r2, =a /* global variable a */
mov r3, #0 /* i = 0 */

startLoop:
	cmp r3, r2 	/* to compare a and i */
	bgt endLoop /* BRANCH GREATER THAN */
	bl g		/* g(); */
	add r3, r3, #1  /* i++; */
	b startLoop /* next iteration */
endLoop:

g:
	bx	lr /* return to the function call point */
