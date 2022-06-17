@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ sub Instruction %6: 28
	 @ load Instruction %7: 32
	 @ load Instruction %8: 36
	 @ call Instruction %9: 40
	 @ mul Instruction %10: 44
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
	 @ call Instruction %2: 12
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	fact
	.arch armv8-a
	.type	fact, %function
fact: 
	@frame_size = 11
	@alloc = 44
	push	{r4, lr}
	sub	sp, sp, #44
	str	r0, [sp, #40]
	ldr	r1, [sp, #40]
	add	r2, sp, #36
	str	r1, [r2]
	add	r1, sp, #36
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #28]
	beq	then_bb0
	b	if_next_bb2
then_bb0: 
	mov	r3, #1
	b	fact_retbb
if_next_bb2: 
	add	r1, sp, #36
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #24
	str	r1, [r2]
	add	r1, sp, #36
	ldr	r3, [r1]
	str	r3, [sp, #12]
	add	r1, sp, #24
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r0, [sp, #8]
	bl	fact
	str	r0, [sp, #4]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #4]
	mul	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	fact_retbb
fact_retbb:
	mov	r0, r3
	add	sp, sp, #44
	pop	{r4, lr}
	bx	lr
fact_alignbb:
	.align	2
	.size	fact, .-fact
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 3
	@alloc = 12
	push	{r4, lr}
	sub	sp, sp, #12
	mov	r1, #4
	add	r2, sp, #8
	str	r1, [r2]
	add	r1, sp, #8
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r0, [sp, #4]
	bl	fact
	str	r0, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #12
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
