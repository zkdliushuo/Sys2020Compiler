@ After Enter EntryBB
	 @ call Instruction %0: 4
	 @ call Instruction %1: 8
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
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
	@frame_size = 6
	@alloc = 24
	push	{r4, lr}
	sub	sp, sp, #24
	bl	getint
	str	r0, [sp, #20]
	ldr	r1, [sp, #20]
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	bl	getint
	str	r0, [sp, #16]
	ldr	r1, [sp, #16]
	adrl	r2, main_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #8]
	bne	next_and_bb3
	b	else_bb1
then_bb0: 
	mov	r3, #1
	b	main_retbb
else_bb1: 
	mov	r3, #0
	b	main_retbb
next_and_bb3: 
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #0]
	bne	then_bb0
	b	else_bb1
main_retbb:
	mov	r0, r3
	add	sp, sp, #24
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.word	b
	.size	main, .-main
