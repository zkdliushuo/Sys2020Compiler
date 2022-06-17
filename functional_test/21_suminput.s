@ After Enter EntryBB
	 @ call Instruction %0: 4
	 @ load Instruction %1: 8
	 @ icmp Instruction %2: 12
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ load Instruction %7: 32
	 @ icmp Instruction %8: 36
	 @ load Instruction %9: 40
	 @ getelementptr inbounds Instruction %10: 44
	 @ call Instruction %11: 48
	 @ load Instruction %12: 52
	 @ load Instruction %13: 56
	 @ getelementptr inbounds Instruction %14: 60
	 @ load Instruction %15: 64
	 @ add Instruction %16: 68
	 @ load Instruction %17: 72
	 @ add Instruction %18: 76
	 @ load Instruction %19: 80
	 @ alloca Instruction %20 alloc space: [80 , 84]
	 @ load Instruction %21: 88
	 @ load Instruction %22: 92
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global n 
	.data
	.align	2
	.type	n, %object
	.size	n, 4 
n:
	.word	0
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 40 
a:
	.space	40
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 23
	@alloc = 92
	push	{r4, lr}
	sub	sp, sp, #92
	bl	getint
	str	r0, [sp, #88]
	ldr	r1, [sp, #88]
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #84]
	ldr	r1, [sp, #84]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #80]
	bgt	then_bb0
	b	if_next_bb2
then_bb0: 
	mov	r3, #1
	b	main_retbb
if_next_bb2: 
	mov	r1, #0
	add	r2, sp, #72
	str	r1, [r2]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	add	r2, sp, #76
	str	r1, [r2]
	b	while_block3
while_block3: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #64]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #64]
	ldr	r2, [sp, #60]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #56]
	blt	while_body4
	b	while_next5
while_body4: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #52]
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r2, [sp, #52]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #48]
	bl	getint
	str	r0, [sp, #44]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #48]
	str	r1, [r2]
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #40]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #36]
	adrl	r1, main_gvbb+4
	ldr	r1, [r1]
	ldr	r2, [sp, #36]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #40]
	ldr	r2, [sp, #28]
	add	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	add	r2, sp, #76
	str	r1, [r2]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #72
	str	r1, [r2]
	b	while_block3
while_next5: 
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r0, [sp, #12]
	bl	putint
	mov	r1, #10
	add	r2, sp, #8
	str	r1, [r2]
	add	r1, sp, #8
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r0, [sp, #4]
	bl	putch
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #92
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	n
	.word	a
	.size	main, .-main
