@ After Enter EntryBB
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ alloca Instruction %5 alloc space: [20 , 24]
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ load Instruction %7: 32
	 @ load Instruction %8: 36
	 @ icmp Instruction %9: 40
	 @ load Instruction %10: 44
	 @ load Instruction %11: 48
	 @ getelementptr inbounds Instruction %12: 52
	 @ load Instruction %13: 56
	 @ icmp Instruction %14: 60
	 @ load Instruction %15: 64
	 @ load Instruction %16: 68
	 @ icmp Instruction %17: 72
	 @ load Instruction %18: 76
	 @ add Instruction %19: 80
	 @ load Instruction %20: 84
	 @ add Instruction %21: 88
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 2000]
	 @ alloca Instruction %1 alloc space: [2000 , 2004]
	 @ alloca Instruction %2 alloc space: [2004 , 2008]
	 @ load Instruction %3: 2012
	 @ icmp Instruction %4: 2016
	 @ call Instruction %5: 2020
	 @ load Instruction %6: 2024
	 @ getelementptr inbounds Instruction %7: 2028
	 @ load Instruction %8: 2032
	 @ load Instruction %9: 2036
	 @ add Instruction %10: 2040
	 @ getelementptr inbounds Instruction %11: 2044
	 @ load Instruction %12: 2048
	 @ call Instruction %13: 2052
	 @ load Instruction %14: 2056
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	wc
	.arch armv8-a
	.type	wc, %function
wc: 
	@frame_size = 22
	@alloc = 88
	push	{r4, lr}
	sub	sp, sp, #88
	str	r0, [sp, #84]
	str	r1, [sp, #80]
	ldr	r1, [sp, #84]
	add	r2, sp, #76
	str	r1, [r2]
	ldr	r1, [sp, #80]
	add	r2, sp, #72
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #64
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #68
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #60
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #56]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #52]
	ldr	r1, [sp, #56]
	ldr	r2, [sp, #52]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #48]
	blt	while_body1
	b	while_next2
while_body1: 
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #44]
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #40]
	ldr	r2, [sp, #44]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	mov	r2, #32
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #28]
	bne	then_bb3
	b	else_bb4
while_next2: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r3, [sp, #24]
	b	wc_retbb
then_bb3: 
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #16]
	beq	then_bb6
	b	if_next_bb8
else_bb4: 
	mov	r1, #0
	add	r2, sp, #68
	str	r1, [r2]
	b	if_next_bb5
if_next_bb5: 
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	add	r2, sp, #64
	str	r1, [r2]
	b	while_block0
then_bb6: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #60
	str	r1, [r2]
	mov	r1, #1
	add	r2, sp, #68
	str	r1, [r2]
	b	if_next_bb8
if_next_bb8: 
	b	if_next_bb5
wc_retbb:
	mov	r0, r3
	add	sp, sp, #88
	pop	{r4, lr}
	bx	lr
wc_alignbb:
	.align	2
	.size	wc, .-wc
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 514
	@alloc = 2056
	push	{r4, lr}
	movw	r4, #2056
	sub	sp, sp, r4
	mov	r1, #0
	add	r2, sp, #48
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #52
	str	r1, [r2]
	b	while_block9
while_block9: 
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #40]
	bne	while_body10
	b	while_next11
while_body10: 
	bl	getch
	str	r0, [sp, #36]
	ldr	r1, [sp, #36]
	add	r2, sp, #52
	str	r1, [r2]
	add	r1, sp, #48
	ldr	r3, [r1]
	str	r3, [sp, #32]
	add	r1, sp, #56
	ldr	r2, [sp, #32]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #28]
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #28]
	str	r1, [r2]
	add	r1, sp, #48
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #48
	str	r1, [r2]
	b	while_block9
while_next11: 
	add	r1, sp, #56
	add	r1, r1, #0
	str	r1, [sp, #12]
	add	r1, sp, #48
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r0, [sp, #12]
	ldr	r1, [sp, #8]
	bl	wc
	str	r0, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #52
	str	r1, [r2]
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	movw	r4, #2056
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
