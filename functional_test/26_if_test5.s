@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
	 @ load Instruction %6: 28
	 @ add Instruction %7: 32
	 @ load Instruction %8: 36
@ After Enter EntryBB
	 @ call Instruction %0: 4
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	if_if_Else
	.arch armv8-a
	.type	if_if_Else, %function
if_if_Else: 
	@frame_size = 9
	@alloc = 36
	push	{r4, lr}
	sub	sp, sp, #36
	mov	r1, #5
	add	r2, sp, #32
	str	r1, [r2]
	mov	r1, #10
	add	r2, sp, #28
	str	r1, [r2]
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	mov	r2, #5
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #20]
	beq	then_bb0
	b	else_bb1
then_bb0: 
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #12]
	beq	then_bb3
	b	if_next_bb5
else_bb1: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #15
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #32
	str	r1, [r2]
	b	if_next_bb2
if_next_bb2: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	if_if_Else_retbb
then_bb3: 
	mov	r1, #25
	add	r2, sp, #32
	str	r1, [r2]
	b	if_next_bb5
if_next_bb5: 
	b	if_next_bb2
if_if_Else_retbb:
	mov	r0, r3
	add	sp, sp, #36
	pop	{r4, lr}
	bx	lr
if_if_Else_alignbb:
	.align	2
	.size	if_if_Else, .-if_if_Else
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
	bl	if_if_Else
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
