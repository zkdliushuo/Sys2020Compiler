@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ icmp Instruction %6: 28
	 @ load Instruction %7: 32
	 @ load Instruction %8: 36
	 @ icmp Instruction %9: 40
	 @ load Instruction %10: 44
	 @ load Instruction %11: 48
	 @ load Instruction %12: 52
	 @ mul Instruction %13: 56
	 @ add Instruction %14: 60
	 @ load Instruction %15: 64
	 @ getelementptr inbounds Instruction %16: 68
	 @ load Instruction %17: 72
	 @ add Instruction %18: 76
	 @ load Instruction %19: 80
	 @ add Instruction %20: 84
	 @ load Instruction %21: 88
	 @ add Instruction %22: 92
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ getelementptr inbounds Instruction %0: 4
	 @ call Instruction %1: 8
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 100 
a:
	.word	1
	.word	2
	.word	3
	.word	4
	.word	5
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.text
	.align	2
	.global	func
	.arch armv8-a
	.type	func, %function
func: 
	@frame_size = 23
	@alloc = 92
	push	{r4, lr}
	sub	sp, sp, #92
	str	r0, [sp, #88]
	ldr	r1, [sp, #88]
	add	r2, sp, #84
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #80
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #76
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #72
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #80
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	mov	r2, #5
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #64]
	blt	while_body1
	b	while_next2
while_body1: 
	b	while_block3
while_next2: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r3, [sp, #60]
	b	func_retbb
while_block3: 
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #5
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #52]
	blt	while_body4
	b	while_next5
while_body4: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #48]
	add	r1, sp, #80
	ldr	r3, [r1]
	str	r3, [sp, #44]
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #44]
	mov	r2, #5
	mul	r3, r1, r2
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	ldr	r2, [sp, #40]
	add	r3, r1, r2
	str	r3, [sp, #32]
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	ldr	r2, [sp, #32]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #48]
	ldr	r2, [sp, #20]
	add	r3, r1, r2
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #72
	str	r1, [r2]
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	add	r2, sp, #76
	str	r1, [r2]
	b	while_block3
while_next5: 
	add	r1, sp, #80
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #80
	str	r1, [r2]
	b	while_block0
func_retbb:
	mov	r0, r3
	add	sp, sp, #92
	pop	{r4, lr}
	bx	lr
func_alignbb:
	.align	2
	.size	func, .-func
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 2
	@alloc = 8
	push	{r4, lr}
	sub	sp, sp, #8
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #0
	str	r1, [sp, #4]
	ldr	r0, [sp, #4]
	bl	func
	str	r0, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #8
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.size	main, .-main
