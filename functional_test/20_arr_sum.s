@ After Enter EntryBB
	 @ getelementptr inbounds Instruction %0: 4
	 @ call Instruction %1: 8
	 @ getelementptr inbounds Instruction %2: 12
	 @ call Instruction %3: 16
	 @ getelementptr inbounds Instruction %4: 20
	 @ call Instruction %5: 24
	 @ getelementptr inbounds Instruction %6: 28
	 @ call Instruction %7: 32
	 @ getelementptr inbounds Instruction %8: 36
	 @ call Instruction %9: 40
	 @ alloca Instruction %10 alloc space: [40 , 44]
	 @ alloca Instruction %11 alloc space: [44 , 48]
	 @ load Instruction %12: 52
	 @ icmp Instruction %13: 56
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ getelementptr inbounds Instruction %16: 68
	 @ load Instruction %17: 72
	 @ add Instruction %18: 76
	 @ load Instruction %19: 80
	 @ sub Instruction %20: 84
	 @ load Instruction %21: 88
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 20 
a:
	.space	20
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 22
	@alloc = 88
	push	{r4, lr}
	sub	sp, sp, #88
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #0
	str	r1, [sp, #84]
	bl	getint
	str	r0, [sp, #80]
	ldr	r1, [sp, #80]
	ldr	r2, [sp, #84]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #4
	str	r1, [sp, #76]
	bl	getint
	str	r0, [sp, #72]
	ldr	r1, [sp, #72]
	ldr	r2, [sp, #76]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #8
	str	r1, [sp, #68]
	bl	getint
	str	r0, [sp, #64]
	ldr	r1, [sp, #64]
	ldr	r2, [sp, #68]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #12
	str	r1, [sp, #60]
	bl	getint
	str	r0, [sp, #56]
	ldr	r1, [sp, #56]
	ldr	r2, [sp, #60]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #16
	str	r1, [sp, #52]
	bl	getint
	str	r0, [sp, #48]
	ldr	r1, [sp, #48]
	ldr	r2, [sp, #52]
	str	r1, [r2]
	mov	r1, #4
	add	r2, sp, #44
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #40
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #1
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #32]
	bgt	while_body1
	b	while_next2
while_body1: 
	add	r1, sp, #40
	ldr	r3, [r1]
	str	r3, [sp, #28]
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #24]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r2, [sp, #24]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #28]
	ldr	r2, [sp, #16]
	add	r3, r1, r2
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	add	r2, sp, #40
	str	r1, [r2]
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #44
	str	r1, [r2]
	b	while_block0
while_next2: 
	add	r1, sp, #40
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #88
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.size	main, .-main
