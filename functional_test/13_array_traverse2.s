@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
	 @ load Instruction %6: 28
	 @ icmp Instruction %7: 32
	 @ load Instruction %8: 36
	 @ add Instruction %9: 40
	 @ load Instruction %10: 44
	 @ icmp Instruction %11: 48
	 @ load Instruction %12: 52
	 @ load Instruction %13: 56
	 @ load Instruction %14: 60
	 @ mul Instruction %15: 64
	 @ add Instruction %16: 68
	 @ mul Instruction %17: 72
	 @ add Instruction %18: 76
	 @ getelementptr inbounds Instruction %19: 80
	 @ load Instruction %20: 84
	 @ load Instruction %21: 88
	 @ add Instruction %22: 92
	 @ load Instruction %23: 96
	 @ add Instruction %24: 100
	 @ load Instruction %25: 104
	 @ add Instruction %26: 108
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 108 
a:
	.space	108
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 27
	@alloc = 108
	push	{r4, lr}
	sub	sp, sp, #108
	mov	r1, #0
	add	r2, sp, #104
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #100
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #96
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #92
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #104
	ldr	r3, [r1]
	str	r3, [sp, #88]
	ldr	r1, [sp, #88]
	mov	r2, #3
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #84]
	blt	while_body1
	b	while_next2
while_body1: 
	b	while_block3
while_next2: 
	mov	r3, #0
	b	main_retbb
while_block3: 
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #80]
	ldr	r1, [sp, #80]
	mov	r2, #3
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #76]
	blt	while_body4
	b	while_next5
while_body4: 
	b	while_block6
while_next5: 
	add	r1, sp, #104
	ldr	r3, [r1]
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	add	r2, sp, #104
	str	r1, [r2]
	b	while_block0
while_block6: 
	add	r1, sp, #96
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	mov	r2, #3
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #60]
	blt	while_body7
	b	while_next8
while_body7: 
	add	r1, sp, #104
	ldr	r3, [r1]
	str	r3, [sp, #56]
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #52]
	add	r1, sp, #96
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #56]
	mov	r2, #3
	mul	r3, r1, r2
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #52]
	add	r3, r1, r2
	str	r3, [sp, #40]
	ldr	r1, [sp, #40]
	mov	r2, #3
	mul	r3, r1, r2
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	ldr	r2, [sp, #48]
	add	r3, r1, r2
	str	r3, [sp, #32]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r2, [sp, #32]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #28]
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #28]
	str	r1, [r2]
	add	r1, sp, #92
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #92
	str	r1, [r2]
	add	r1, sp, #96
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	add	r2, sp, #96
	str	r1, [r2]
	b	while_block6
while_next8: 
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #100
	str	r1, [r2]
	b	while_block3
main_retbb:
	mov	r0, r3
	add	sp, sp, #108
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.size	main, .-main
