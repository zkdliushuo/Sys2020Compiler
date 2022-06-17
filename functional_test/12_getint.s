@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ call Instruction %1: 8
	 @ load Instruction %2: 12
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 3
	@alloc = 12
	push	{r4, lr}
	sub	sp, sp, #12
	bl	getint
	str	r0, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #8
	str	r1, [r2]
	add	r1, sp, #8
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #12
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
