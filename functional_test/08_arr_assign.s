@ After Enter EntryBB
	 @ getelementptr inbounds Instruction %0: 4
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 40 
a:
	.space	40
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
	add	r1, r1, #0
	str	r1, [sp, #0]
	mov	r1, #1
	ldr	r2, [sp, #0]
	str	r1, [r2]
	mov	r3, #0
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.size	main, .-main
