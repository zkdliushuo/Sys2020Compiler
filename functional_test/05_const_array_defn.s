@ After Enter EntryBB
	 @ getelementptr inbounds Instruction %0: 4
	 @ load Instruction %1: 8
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.section	.rodata
	.align	2
	.type	a, %object
	.size	a, 20 
a:

	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 2
	@alloc = 8
	push	{r4, lr}
	sub	sp, sp, #8
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #16
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #8
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.size	main, .-main
