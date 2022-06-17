@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ mul Instruction %6: 28
	 @ sdiv Instruction %7: 32
	 @ icmp Instruction %8: 36
	 @ load Instruction %9: 40
	 @ load Instruction %10: 44
	 @ srem Instruction %11: 48
	 @ add Instruction %12: 52
	 @ icmp Instruction %13: 56
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ sub Instruction %16: 68
	 @ icmp Instruction %17: 72
	 @ load Instruction %18: 76
	 @ add Instruction %19: 80
	 @ srem Instruction %20: 84
	 @ icmp Instruction %21: 88
	 @ load Instruction %22: 92
	 @ load Instruction %23: 96
	 @ load Instruction %24: 100
	 @ sub Instruction %25: 104
	 @ icmp Instruction %26: 108
	 @ load Instruction %27: 112
	 @ add Instruction %28: 116
	 @ srem Instruction %29: 120
	 @ icmp Instruction %30: 124
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
	@frame_size = 31
	@alloc = 124
	push	{r4, lr}
	sub	sp, sp, #124
	mov	r1, #5
	add	r2, sp, #120
	str	r1, [r2]
	mov	r1, #5
	add	r2, sp, #116
	str	r1, [r2]
	mov	r1, #1
	add	r2, sp, #112
	str	r1, [r2]
	mov	r1, #-2
	add	r2, sp, #108
	str	r1, [r2]
	mov	r1, #2
	add	r2, sp, #104
	str	r1, [r2]
	add	r1, sp, #108
	ldr	r3, [r1]
	str	r3, [sp, #100]
	ldr	r1, [sp, #100]
	mov	r2, #1
	mul	r3, r1, r2
	str	r3, [sp, #96]
	ldr	r0, [sp, #96]
	mov	r1, #2
	bl	__aeabi_idiv
	str	r0, [sp, #92]
	ldr	r1, [sp, #92]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #88]
	blt	then_bb0
	b	next_or_bb3
then_bb0: 
	add	r1, sp, #104
	ldr	r3, [r1]
	str	r3, [sp, #84]
	ldr	r0, [sp, #84]
	bl	putint
	b	if_next_bb2
if_next_bb2: 
	add	r1, sp, #108
	ldr	r3, [r1]
	str	r3, [sp, #80]
	ldr	r0, [sp, #80]
	mov	r1, #2
	bl	__aeabi_idivmod
	str	r1, [sp, #76]
	ldr	r1, [sp, #76]
	mov	r2, #67
	add	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #68]
	blt	then_bb5
	b	next_or_bb8
next_or_bb3: 
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #64]
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #64]
	ldr	r2, [sp, #60]
	sub	r3, r1, r2
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #52]
	bne	next_and_bb4
	b	if_next_bb2
next_and_bb4: 
	add	r1, sp, #112
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	mov	r2, #3
	add	r3, r1, r2
	str	r3, [sp, #44]
	ldr	r0, [sp, #44]
	mov	r1, #2
	bl	__aeabi_idivmod
	str	r1, [sp, #40]
	ldr	r1, [sp, #40]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #36]
	bne	then_bb0
	b	if_next_bb2
then_bb5: 
	mov	r1, #4
	add	r2, sp, #104
	str	r1, [r2]
	add	r1, sp, #104
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r0, [sp, #32]
	bl	putint
	b	if_next_bb7
if_next_bb7: 
	mov	r3, #0
	b	main_retbb
next_or_bb8: 
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #28]
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #28]
	ldr	r2, [sp, #24]
	sub	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #16]
	bne	next_and_bb9
	b	if_next_bb7
next_and_bb9: 
	add	r1, sp, #112
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #2
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r0, [sp, #8]
	mov	r1, #2
	bl	__aeabi_idivmod
	str	r1, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #0]
	bne	then_bb5
	b	if_next_bb7
main_retbb:
	mov	r0, r3
	add	sp, sp, #124
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
