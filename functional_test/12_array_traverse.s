@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ icmp Instruction %7: 32
	 @ load Instruction %8: 36
	 @ icmp Instruction %9: 40
	 @ load Instruction %10: 44
	 @ add Instruction %11: 48
	 @ load Instruction %12: 52
	 @ load Instruction %13: 56
	 @ sub Instruction %14: 60
	 @ load Instruction %15: 64
	 @ mul Instruction %16: 68
	 @ add Instruction %17: 72
	 @ getelementptr inbounds Instruction %18: 76
	 @ load Instruction %19: 80
	 @ load Instruction %20: 84
	 @ sub Instruction %21: 88
	 @ load Instruction %22: 92
	 @ load Instruction %23: 96
	 @ sub Instruction %24: 100
	 @ icmp Instruction %25: 104
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 48 
a:
	.space	48
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 26
	@alloc = 104
	push	{r4, lr}
	sub	sp, sp, #104
	mov	r1, #0
	add	r2, sp, #100
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #96
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #92]
	ldr	r1, [sp, #92]
	mov	r2, #5
	cmp	r1, r2
	mov	r3, #0
	movle	r3, #1
	str	r3, [sp, #88]
	ble	while_body1
	b	while_next2
while_body1: 
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #80]
	ldr	r1, [sp, #80]
	add	r2, sp, #84
	str	r1, [r2]
	b	while_block3
while_next2: 
	mov	r3, #0
	b	main_retbb
while_block3: 
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #76]
	ldr	r1, [sp, #76]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movge	r3, #1
	str	r3, [sp, #72]
	bge	while_body4
	b	while_next5
while_body4: 
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	mov	r2, #4
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #64]
	blt	next_and_bb9
	b	if_next_bb8
while_next5: 
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	add	r2, sp, #100
	str	r1, [r2]
	b	while_block0
then_bb6: 
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #52]
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #48]
	sub	r3, r1, r2
	str	r3, [sp, #44]
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #44]
	mov	r2, #4
	mul	r3, r1, r2
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	ldr	r2, [sp, #40]
	add	r3, r1, r2
	str	r3, [sp, #32]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r2, [sp, #32]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #28]
	add	r1, sp, #96
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #28]
	str	r1, [r2]
	mov	r1, #1
	add	r2, sp, #96
	str	r1, [r2]
	b	if_next_bb8
if_next_bb8: 
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #84
	str	r1, [r2]
	b	while_block3
next_and_bb9: 
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #12]
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #8]
	sub	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #3
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #0]
	blt	then_bb6
	b	if_next_bb8
main_retbb:
	mov	r0, r3
	add	sp, sp, #104
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.size	main, .-main
