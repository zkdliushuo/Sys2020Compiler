@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
	 @ getelementptr inbounds Instruction %2: 12
	 @ load Instruction %3: 16
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
	 @ load Instruction %6: 28
	 @ add Instruction %7: 32
	 @ load Instruction %8: 36
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
	.word	5
	.global s 
	.data
	.align	2
	.type	s, %object
	.size	s, 40 
s:
	.word	0
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	6
	.word	7
	.word	8
	.word	9
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 9
	@alloc = 36
	push	{r4, lr}
	sub	sp, sp, #36
	mov	r1, #0
	add	r2, sp, #32
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #28]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r2, [sp, #28]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	ldr	r3, [r1]
	str	r3, [sp, #20]
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #20]
	ldr	r2, [sp, #16]
	cmp	r1, r2
	mov	r3, #0
	movle	r3, #1
	str	r3, [sp, #12]
	ble	while_body1
	b	while_next2
while_body1: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #32
	str	r1, [r2]
	b	while_block0
while_next2: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #36
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	s
	.word	a
	.size	main, .-main
