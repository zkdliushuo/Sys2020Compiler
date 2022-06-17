@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ load Instruction %5: 24
	 @ add Instruction %6: 28
	 @ load Instruction %7: 32
	 @ icmp Instruction %8: 36
	 @ load Instruction %9: 40
	 @ load Instruction %10: 44
	 @ sub Instruction %11: 48
	 @ srem Instruction %12: 52
	 @ load Instruction %13: 56
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ sub Instruction %16: 68
	 @ load Instruction %17: 72
	 @ icmp Instruction %18: 76
	 @ load Instruction %19: 80
	 @ load Instruction %20: 84
	 @ srem Instruction %21: 88
	 @ load Instruction %22: 92
	 @ add Instruction %23: 96
	 @ load Instruction %24: 100
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
	mov	r1, #1
	add	r2, sp, #96
	str	r1, [r2]
	mov	r1, #4
	add	r2, sp, #92
	str	r1, [r2]
	mov	r1, #28
	add	r2, sp, #88
	str	r1, [r2]
	add	r1, sp, #88
	ldr	r3, [r1]
	str	r3, [sp, #80]
	add	r1, sp, #96
	ldr	r3, [r1]
	str	r3, [sp, #76]
	ldr	r1, [sp, #80]
	ldr	r2, [sp, #76]
	add	r3, r1, r2
	str	r3, [sp, #72]
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #72]
	ldr	r2, [sp, #68]
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #64]
	bne	then_bb0
	b	if_next_bb2
then_bb0: 
	add	r1, sp, #88
	ldr	r3, [r1]
	str	r3, [sp, #60]
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #56]
	mov	r1, #0
	ldr	r2, [sp, #56]
	sub	r3, r1, r2
	str	r3, [sp, #52]
	ldr	r0, [sp, #60]
	ldr	r1, [sp, #52]
	bl	__aeabi_idivmod
	str	r1, [sp, #48]
	ldr	r1, [sp, #48]
	add	r2, sp, #84
	str	r1, [r2]
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r0, [sp, #44]
	bl	putint
	b	if_next_bb2
if_next_bb2: 
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #40]
	add	r1, sp, #88
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #40]
	ldr	r2, [sp, #36]
	sub	r3, r1, r2
	str	r3, [sp, #32]
	add	r1, sp, #96
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #28]
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #24]
	beq	then_bb3
	b	if_next_bb5
then_bb3: 
	add	r1, sp, #88
	ldr	r3, [r1]
	str	r3, [sp, #20]
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r0, [sp, #20]
	ldr	r1, [sp, #16]
	bl	__aeabi_idivmod
	str	r1, [sp, #12]
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #8]
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #84
	str	r1, [r2]
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	b	if_next_bb5
if_next_bb5: 
	mov	r3, #0
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #100
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
