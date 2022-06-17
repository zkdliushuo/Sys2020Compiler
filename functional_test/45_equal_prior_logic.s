@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ add Instruction %7: 32
	 @ load Instruction %8: 36
	 @ icmp Instruction %9: 40
	 @ load Instruction %10: 44
	 @ load Instruction %11: 48
	 @ load Instruction %12: 52
	 @ sdiv Instruction %13: 56
	 @ mul Instruction %14: 60
	 @ add Instruction %15: 64
	 @ load Instruction %16: 68
	 @ load Instruction %17: 72
	 @ icmp Instruction %18: 76
	 @ load Instruction %19: 80
	 @ load Instruction %20: 84
	 @ sdiv Instruction %21: 88
	 @ icmp Instruction %22: 92
	 @ load Instruction %23: 96
	 @ load Instruction %24: 100
	 @ load Instruction %25: 104
	 @ sub Instruction %26: 108
	 @ load Instruction %27: 112
	 @ icmp Instruction %28: 116
	 @ load Instruction %29: 120
	 @ load Instruction %30: 124
	 @ mul Instruction %31: 128
	 @ icmp Instruction %32: 132
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
	@frame_size = 33
	@alloc = 132
	push	{r4, lr}
	movw	r4, #132
	sub	sp, sp, r4
	mov	r1, #10
	movw	r2, #128
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #6
	add	r2, sp, #124
	str	r1, [r2]
	mov	r1, #4
	add	r2, sp, #120
	str	r1, [r2]
	mov	r1, #5
	add	r2, sp, #116
	str	r1, [r2]
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #108]
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #104]
	ldr	r1, [sp, #108]
	ldr	r2, [sp, #104]
	add	r3, r1, r2
	str	r3, [sp, #100]
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #96]
	ldr	r1, [sp, #100]
	ldr	r2, [sp, #96]
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #92]
	beq	next_and_bb3
	b	if_next_bb2
then_bb0: 
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #88]
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #84]
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #80]
	ldr	r0, [sp, #84]
	ldr	r1, [sp, #80]
	bl	__aeabi_idiv
	str	r0, [sp, #76]
	ldr	r1, [sp, #76]
	mov	r2, #2
	mul	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r1, [sp, #88]
	ldr	r2, [sp, #72]
	add	r3, r1, r2
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	add	r2, sp, #112
	str	r1, [r2]
	add	r1, sp, #112
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r0, [sp, #64]
	bl	putint
	b	if_next_bb2
if_next_bb2: 
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #56]
	blt	then_bb4
	b	next_or_bb7
next_and_bb3: 
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #52]
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r0, [sp, #48]
	mov	r1, #2
	bl	__aeabi_idiv
	str	r0, [sp, #44]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #44]
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #40]
	bne	then_bb0
	b	if_next_bb2
then_bb4: 
	mov	r1, #1
	add	r2, sp, #112
	str	r1, [r2]
	add	r1, sp, #112
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r0, [sp, #36]
	bl	putint
	b	if_next_bb6
if_next_bb6: 
	mov	r3, #0
	b	main_retbb
next_or_bb7: 
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #32]
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #28]
	sub	r3, r1, r2
	str	r3, [sp, #24]
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #20]
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #16]
	beq	next_and_bb8
	b	if_next_bb6
next_and_bb8: 
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #12]
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #2
	mul	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #4]
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #0]
	bne	then_bb4
	b	if_next_bb6
main_retbb:
	movw	r4, #132
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
