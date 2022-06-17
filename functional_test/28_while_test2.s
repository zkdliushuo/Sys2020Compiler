@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
	 @ load Instruction %6: 28
	 @ add Instruction %7: 32
	 @ load Instruction %8: 36
	 @ load Instruction %9: 40
	 @ load Instruction %10: 44
	 @ add Instruction %11: 48
	 @ add Instruction %12: 52
	 @ load Instruction %13: 56
	 @ add Instruction %14: 60
	 @ load Instruction %15: 64
	 @ icmp Instruction %16: 68
	 @ load Instruction %17: 72
	 @ add Instruction %18: 76
	 @ load Instruction %19: 80
	 @ sub Instruction %20: 84
	 @ load Instruction %21: 88
	 @ icmp Instruction %22: 92
	 @ load Instruction %23: 96
	 @ sub Instruction %24: 100
	 @ load Instruction %25: 104
	 @ add Instruction %26: 108
	 @ load Instruction %27: 112
	 @ icmp Instruction %28: 116
	 @ load Instruction %29: 120
	 @ add Instruction %30: 124
	 @ load Instruction %31: 128
	 @ sub Instruction %32: 132
@ After Enter EntryBB
	 @ call Instruction %0: 4
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	FourWhile
	.arch armv8-a
	.type	FourWhile, %function
FourWhile: 
	@frame_size = 33
	@alloc = 132
	push	{r4, lr}
	movw	r4, #132
	sub	sp, sp, r4
	mov	r1, #5
	movw	r2, #128
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #6
	add	r2, sp, #124
	str	r1, [r2]
	mov	r1, #7
	add	r2, sp, #120
	str	r1, [r2]
	mov	r1, #10
	add	r2, sp, #116
	str	r1, [r2]
	b	while_block0
while_block0: 
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #112]
	ldr	r1, [sp, #112]
	mov	r2, #20
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #108]
	blt	while_body1
	b	while_next2
while_body1: 
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #104]
	ldr	r1, [sp, #104]
	mov	r2, #3
	add	r3, r1, r2
	str	r3, [sp, #100]
	ldr	r1, [sp, #100]
	movw	r2, #128
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
while_next2: 
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #96]
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #92]
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #88]
	ldr	r1, [sp, #92]
	ldr	r2, [sp, #88]
	add	r3, r1, r2
	str	r3, [sp, #84]
	ldr	r1, [sp, #96]
	ldr	r2, [sp, #84]
	add	r3, r1, r2
	str	r3, [sp, #80]
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #76]
	ldr	r1, [sp, #80]
	ldr	r2, [sp, #76]
	add	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r3, [sp, #72]
	b	FourWhile_retbb
while_block3: 
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #64]
	blt	while_body4
	b	while_next5
while_body4: 
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	add	r2, sp, #124
	str	r1, [r2]
	b	while_block6
while_next5: 
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	mov	r2, #2
	sub	r3, r1, r2
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	add	r2, sp, #124
	str	r1, [r2]
	b	while_block0
while_block6: 
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	mov	r2, #7
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #40]
	beq	while_body7
	b	while_next8
while_body7: 
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	add	r2, sp, #120
	str	r1, [r2]
	b	while_block9
while_next8: 
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	add	r2, sp, #120
	str	r1, [r2]
	b	while_block3
while_block9: 
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #20
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #16]
	blt	while_body10
	b	while_next11
while_body10: 
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #3
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	add	r2, sp, #116
	str	r1, [r2]
	b	while_block9
while_next11: 
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #116
	str	r1, [r2]
	b	while_block6
FourWhile_retbb:
	movw	r4, #132
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
FourWhile_alignbb:
	.align	2
	.size	FourWhile, .-FourWhile
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 1
	@alloc = 4
	push	{r4, lr}
	sub	sp, sp, #4
	bl	FourWhile
	str	r0, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
