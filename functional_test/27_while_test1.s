@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ load Instruction %4: 20
	 @ add Instruction %5: 24
	 @ load Instruction %6: 28
	 @ load Instruction %7: 32
	 @ icmp Instruction %8: 36
	 @ load Instruction %9: 40
	 @ add Instruction %10: 44
	 @ load Instruction %11: 48
	 @ sub Instruction %12: 52
@ After Enter EntryBB
	 @ call Instruction %0: 4
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	doubleWhile
	.arch armv8-a
	.type	doubleWhile, %function
doubleWhile: 
	@frame_size = 13
	@alloc = 52
	push	{r4, lr}
	sub	sp, sp, #52
	mov	r1, #5
	add	r2, sp, #48
	str	r1, [r2]
	mov	r1, #7
	add	r2, sp, #44
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #48
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #40]
	mov	r2, #100
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #36]
	blt	while_body1
	b	while_next2
while_body1: 
	add	r1, sp, #48
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	mov	r2, #30
	add	r3, r1, r2
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	add	r2, sp, #48
	str	r1, [r2]
	b	while_block3
while_next2: 
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r3, [sp, #24]
	b	doubleWhile_retbb
while_block3: 
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #100
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #16]
	blt	while_body4
	b	while_next5
while_body4: 
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #6
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	add	r2, sp, #44
	str	r1, [r2]
	b	while_block3
while_next5: 
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #100
	sub	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #44
	str	r1, [r2]
	b	while_block0
doubleWhile_retbb:
	mov	r0, r3
	add	sp, sp, #52
	pop	{r4, lr}
	bx	lr
doubleWhile_alignbb:
	.align	2
	.size	doubleWhile, .-doubleWhile
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
	bl	doubleWhile
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
