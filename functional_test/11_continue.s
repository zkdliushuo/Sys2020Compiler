@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
	 @ icmp Instruction %2: 12
	 @ load Instruction %3: 16
	 @ icmp Instruction %4: 20
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ sub Instruction %7: 32
	 @ load Instruction %8: 36
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 9
	@alloc = 36
	push	{r4, lr}
	sub	sp, sp, #36
	mov	r1, #10
	add	r2, sp, #32
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #24]
	bgt	while_body1
	b	while_next2
while_body1: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #5
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #16]
	bgt	then_bb3
	b	if_next_bb5
while_next2: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r3, [sp, #12]
	b	main_retbb
then_bb3: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #32
	str	r1, [r2]
	b	while_block0
if_next_bb5: 
	add	r1, sp, #32
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
	b	while_block0
main_retbb:
	mov	r0, r3
	add	sp, sp, #36
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
