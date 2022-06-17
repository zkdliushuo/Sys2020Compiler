@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ alloca Instruction %7 alloc space: [28 , 32]
	 @ load Instruction %8: 36
	 @ sub Instruction %9: 40
	 @ load Instruction %10: 44
	 @ sub Instruction %11: 48
	 @ alloca Instruction %12 alloc space: [48 , 52]
	 @ load Instruction %13: 56
	 @ call Instruction %14: 60
	 @ load Instruction %15: 64
	 @ call Instruction %16: 68
	 @ add Instruction %17: 72
	 @ load Instruction %18: 76
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ call Instruction %0: 4
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ load Instruction %3: 16
	 @ call Instruction %4: 20
	 @ load Instruction %5: 24
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ load Instruction %7: 32
	 @ load Instruction %8: 36
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global n 
	.data
	.align	2
	.type	n, %object
	.size	n, 4 
n:
	.word	0
	.text
	.align	2
	.global	f
	.arch armv8-a
	.type	f, %function
f: 
	@frame_size = 19
	@alloc = 76
	push	{r4, lr}
	sub	sp, sp, #76
	str	r0, [sp, #72]
	ldr	r1, [sp, #72]
	add	r2, sp, #68
	str	r1, [r2]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	mov	r2, #1
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #60]
	beq	then_bb0
	b	if_next_bb2
then_bb0: 
	mov	r3, #1
	b	f_retbb
if_next_bb2: 
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #2
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #52]
	beq	then_bb3
	b	if_next_bb5
then_bb3: 
	mov	r3, #1
	b	f_retbb
if_next_bb5: 
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #40]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	add	r2, sp, #48
	str	r1, [r2]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	mov	r2, #2
	sub	r3, r1, r2
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	add	r2, sp, #44
	str	r1, [r2]
	add	r1, sp, #48
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r0, [sp, #20]
	bl	f
	str	r0, [sp, #16]
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r0, [sp, #12]
	bl	f
	str	r0, [sp, #8]
	ldr	r1, [sp, #16]
	ldr	r2, [sp, #8]
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #24
	str	r1, [r2]
	add	r1, sp, #24
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	f_retbb
f_retbb:
	mov	r0, r3
	add	sp, sp, #76
	pop	{r4, lr}
	bx	lr
f_alignbb:
	.align	2
	.size	f, .-f
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
	bl	getint
	str	r0, [sp, #32]
	ldr	r1, [sp, #32]
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r0, [sp, #20]
	bl	f
	str	r0, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #28
	str	r1, [r2]
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r0, [sp, #12]
	bl	putint
	mov	r1, #10
	add	r2, sp, #8
	str	r1, [r2]
	add	r1, sp, #8
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r0, [sp, #4]
	bl	putch
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #36
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	n
	.size	main, .-main
