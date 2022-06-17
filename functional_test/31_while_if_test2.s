@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ load Instruction %4: 20
	 @ load Instruction %5: 24
	 @ icmp Instruction %6: 28
	 @ load Instruction %7: 32
	 @ add Instruction %8: 36
	 @ load Instruction %9: 40
	 @ add Instruction %10: 44
	 @ load Instruction %11: 48
	 @ icmp Instruction %12: 52
	 @ load Instruction %13: 56
	 @ mul Instruction %14: 60
	 @ load Instruction %15: 64
	 @ add Instruction %16: 68
@ After Enter EntryBB
	 @ call Instruction %0: 4
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	ifWhile
	.arch armv8-a
	.type	ifWhile, %function
ifWhile: 
	@frame_size = 17
	@alloc = 68
	push	{r4, lr}
	sub	sp, sp, #68
	mov	r1, #0
	add	r2, sp, #64
	str	r1, [r2]
	mov	r1, #3
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #5
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #52]
	beq	then_bb0
	b	else_bb1
then_bb0: 
	b	while_block3
else_bb1: 
	b	while_block6
if_next_bb2: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r3, [sp, #48]
	b	ifWhile_retbb
while_block3: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	mov	r2, #2
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #40]
	beq	while_body4
	b	while_next5
while_body4: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #2
	add	r3, r1, r2
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	add	r2, sp, #60
	str	r1, [r2]
	b	while_block3
while_next5: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #25
	add	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	add	r2, sp, #60
	str	r1, [r2]
	b	if_next_bb2
while_block6: 
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #5
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #16]
	blt	while_body7
	b	while_next8
while_body7: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #2
	mul	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #64
	str	r1, [r2]
	b	while_block6
while_next8: 
	b	if_next_bb2
ifWhile_retbb:
	mov	r0, r3
	add	sp, sp, #68
	pop	{r4, lr}
	bx	lr
ifWhile_alignbb:
	.align	2
	.size	ifWhile, .-ifWhile
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
	bl	ifWhile
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
