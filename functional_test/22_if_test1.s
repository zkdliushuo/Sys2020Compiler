@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
	 @ icmp Instruction %2: 12
	 @ load Instruction %3: 16
	 @ mul Instruction %4: 20
	 @ load Instruction %5: 24
@ After Enter EntryBB
	 @ call Instruction %0: 4
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	ifElse
	.arch armv8-a
	.type	ifElse, %function
ifElse: 
	@frame_size = 6
	@alloc = 24
	push	{r4, lr}
	sub	sp, sp, #24
	mov	r1, #5
	add	r2, sp, #20
	str	r1, [r2]
	add	r1, sp, #20
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	mov	r2, #5
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #12]
	beq	then_bb0
	b	else_bb1
then_bb0: 
	mov	r1, #25
	add	r2, sp, #20
	str	r1, [r2]
	b	if_next_bb2
else_bb1: 
	add	r1, sp, #20
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #2
	mul	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #20
	str	r1, [r2]
	b	if_next_bb2
if_next_bb2: 
	add	r1, sp, #20
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	ifElse_retbb
ifElse_retbb:
	mov	r0, r3
	add	sp, sp, #24
	pop	{r4, lr}
	bx	lr
ifElse_alignbb:
	.align	2
	.size	ifElse, .-ifElse
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
	bl	ifElse
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
