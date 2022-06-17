@ After Enter EntryBB
	 @ call Instruction %0: 4
	 @ call Instruction %1: 8
	 @ call Instruction %2: 12
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ mul Instruction %7: 32
	 @ add Instruction %8: 36
	 @ load Instruction %9: 40
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
	.global c 
	.data
	.align	2
	.type	c, %object
	.size	c, 4 
c:
	.word	0
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 10
	@alloc = 40
	push	{r4, lr}
	sub	sp, sp, #40
	bl	getint
	str	r0, [sp, #36]
	ldr	r1, [sp, #36]
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	bl	getint
	str	r0, [sp, #32]
	ldr	r1, [sp, #32]
	adrl	r2, main_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	bl	getint
	str	r0, [sp, #28]
	ldr	r1, [sp, #28]
	adrl	r2, main_gvbb+8
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #20]
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #16]
	adrl	r1, main_gvbb+8
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #16]
	ldr	r2, [sp, #12]
	mul	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #20]
	ldr	r2, [sp, #8]
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #24
	str	r1, [r2]
	add	r1, sp, #24
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #40
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.word	b
	.word	c
	.size	main, .-main
