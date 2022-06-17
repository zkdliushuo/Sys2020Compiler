@ After Enter EntryBB
	 @ load Instruction %0: 4
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global x 
	.section	.rodata
	.align	2
	.type	x, %object
	.size	x, 4 
x:

	.word	4
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 1
	@alloc = 4
	push	{r4, lr}
	sub	sp, sp, #4
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	x
	.size	main, .-main
