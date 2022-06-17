@ After Enter EntryBB
	 @ load Instruction %0: 4
	 @ icmp Instruction %1: 8
	 @ load Instruction %2: 12
	 @ load Instruction %3: 16
	 @ add Instruction %4: 20
	 @ load Instruction %5: 24
	 @ sub Instruction %6: 28
	 @ load Instruction %7: 32
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
	@frame_size = 8
	@alloc = 32
	push	{r4, lr}
	sub	sp, sp, #32
	mov	r1, #0
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	mov	r1, #3
	adrl	r2, main_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block0
while_block0: 
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #24]
	bgt	while_body1
	b	while_next2
while_body1: 
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #20]
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #20]
	ldr	r2, [sp, #16]
	add	r3, r1, r2
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	adrl	r2, main_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block0
while_next2: 
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #32
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	b
	.word	a
	.size	main, .-main
