@ After Enter EntryBB
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ load Instruction %5: 24
	 @ add Instruction %6: 28
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
@ After Enter EntryBB
	 @ load Instruction %0: 4
	 @ load Instruction %1: 8
	 @ load Instruction %2: 12
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
	.global	add
	.arch armv8-a
	.type	add, %function
add: 
	@frame_size = 7
	@alloc = 28
	push	{r4, lr}
	sub	sp, sp, #28
	str	r0, [sp, #24]
	str	r1, [sp, #20]
	ldr	r1, [sp, #24]
	add	r2, sp, #16
	str	r1, [r2]
	ldr	r1, [sp, #20]
	add	r2, sp, #12
	str	r1, [r2]
	add	r1, sp, #16
	ldr	r3, [r1]
	str	r3, [sp, #8]
	add	r1, sp, #12
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #4]
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	adrl	r2, add_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	b	add_retbb
add_retbb:
	mov	r0, r3
	add	sp, sp, #28
	pop	{r4, lr}
	bx	lr
add_alignbb:
	.align	2
add_gvbb:
	.word	c
	.size	add, .-add
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
	mov	r1, #3
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	mov	r1, #2
	adrl	r2, main_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #8]
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r0, [sp, #8]
	ldr	r1, [sp, #4]
	bl	add
	adrl	r1, main_gvbb+8
	ldr	r1, [r1]
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
main_gvbb:
	.word	a
	.word	b
	.word	c
	.size	main, .-main
