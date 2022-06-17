@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
	 @ load Instruction %2: 12
	 @ add Instruction %3: 16
	 @ load Instruction %4: 20
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 4 
a:
	.word	0
	.global b 
	.data
	.align	2
	.type	b, %object
	.size	b, 4 
b:
	.word	0
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 5
	@alloc = 20
	push	{r4, lr}
	sub	sp, sp, #20
	mov	r1, #10
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	mov	r1, #20
	adrl	r2, main_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #12]
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #8]
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #16
	str	r1, [r2]
	add	r1, sp, #16
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #20
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.word	b
	.size	main, .-main
