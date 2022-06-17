@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ load Instruction %7: 32
	 @ sub Instruction %8: 36
	 @ srem Instruction %9: 40
	 @ icmp Instruction %10: 44
	 @ load Instruction %11: 48
	 @ load Instruction %12: 52
	 @ add Instruction %13: 56
	 @ load Instruction %14: 60
	 @ sub Instruction %15: 64
	 @ sub Instruction %16: 68
	 @ load Instruction %17: 72
	 @ load Instruction %18: 76
	 @ srem Instruction %19: 80
	 @ icmp Instruction %20: 84
	 @ load Instruction %21: 88
	 @ icmp Instruction %22: 92
	 @ load Instruction %23: 96
	 @ icmp Instruction %24: 100
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
	@frame_size = 25
	@alloc = 100
	push	{r4, lr}
	sub	sp, sp, #100
	mov	r1, #3
	add	r2, sp, #96
	str	r1, [r2]
	mov	r1, #8
	add	r2, sp, #92
	str	r1, [r2]
	mov	r1, #-4
	add	r2, sp, #88
	str	r1, [r2]
	mov	r1, #15
	add	r2, sp, #84
	str	r1, [r2]
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #76]
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #72]
	add	r1, sp, #96
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #72]
	ldr	r2, [sp, #68]
	sub	r3, r1, r2
	str	r3, [sp, #64]
	ldr	r0, [sp, #76]
	ldr	r1, [sp, #64]
	bl	__aeabi_idivmod
	str	r1, [sp, #60]
	ldr	r1, [sp, #60]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #56]
	bne	next_and_bb4
	b	next_or_bb3
then_bb0: 
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #52]
	add	r1, sp, #88
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #48]
	add	r3, r1, r2
	str	r3, [sp, #44]
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #40]
	mov	r1, #0
	ldr	r2, [sp, #40]
	sub	r3, r1, r2
	str	r3, [sp, #36]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #36]
	sub	r3, r1, r2
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	add	r2, sp, #80
	str	r1, [r2]
	add	r1, sp, #80
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r0, [sp, #28]
	bl	putint
	b	if_next_bb2
if_next_bb2: 
	mov	r3, #0
	b	main_retbb
next_or_bb3: 
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r0, [sp, #24]
	mov	r1, #3
	bl	__aeabi_idivmod
	str	r1, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #16]
	beq	next_and_bb5
	b	if_next_bb2
next_and_bb4: 
	add	r1, sp, #96
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #8]
	bgt	then_bb0
	b	next_or_bb3
next_and_bb5: 
	add	r1, sp, #88
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #0]
	bgt	then_bb0
	b	if_next_bb2
main_retbb:
	mov	r0, r3
	add	sp, sp, #100
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
