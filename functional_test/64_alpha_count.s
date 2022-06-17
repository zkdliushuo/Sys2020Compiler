@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 2000]
	 @ alloca Instruction %1 alloc space: [2000 , 2004]
	 @ alloca Instruction %2 alloc space: [2004 , 2008]
	 @ alloca Instruction %3 alloc space: [2008 , 2012]
	 @ load Instruction %4: 2016
	 @ icmp Instruction %5: 2020
	 @ call Instruction %6: 2024
	 @ load Instruction %7: 2028
	 @ icmp Instruction %8: 2032
	 @ load Instruction %9: 2036
	 @ load Instruction %10: 2040
	 @ add Instruction %11: 2044
	 @ load Instruction %12: 2048
	 @ add Instruction %13: 2052
	 @ load Instruction %14: 2056
	 @ icmp Instruction %15: 2060
	 @ load Instruction %16: 2064
	 @ icmp Instruction %17: 2068
	 @ load Instruction %18: 2072
	 @ icmp Instruction %19: 2076
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
	@frame_size = 519
	@alloc = 2076
	push	{r4, lr}
	movw	r4, #2076
	sub	sp, sp, r4
	mov	r1, #0
	add	r2, sp, #64
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #68
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #72
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #56]
	bne	while_body1
	b	while_next2
while_body1: 
	bl	getch
	str	r0, [sp, #52]
	ldr	r1, [sp, #52]
	add	r2, sp, #72
	str	r1, [r2]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	mov	r2, #40
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #44]
	bgt	next_and_bb7
	b	next_or_bb6
while_next2: 
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r0, [sp, #40]
	bl	putint
	mov	r3, #0
	b	main_retbb
then_bb3: 
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	add	r2, sp, #64
	str	r1, [r2]
	b	if_next_bb5
if_next_bb5: 
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	add	r2, sp, #68
	str	r1, [r2]
	b	while_block0
next_or_bb6: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #96
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #16]
	bgt	next_and_bb8
	b	if_next_bb5
next_and_bb7: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #91
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #8]
	blt	then_bb3
	b	next_or_bb6
next_and_bb8: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #123
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #0]
	blt	then_bb3
	b	if_next_bb5
main_retbb:
	movw	r4, #2076
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
