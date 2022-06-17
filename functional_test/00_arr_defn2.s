@ After Enter EntryBB
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 400 
a:
	.space	400
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 0
	@alloc = 0
	push	{r4, lr}
	sub	sp, sp, #0
	mov	r3, #0
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #0
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
