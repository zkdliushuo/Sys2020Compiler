@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ icmp Instruction %6: 28
	 @ load Instruction %7: 32
	 @ icmp Instruction %8: 36
	 @ load Instruction %9: 40
	 @ icmp Instruction %10: 44
	 @ load Instruction %11: 48
	 @ load Instruction %12: 52
	 @ add Instruction %13: 56
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ load Instruction %16: 68
	 @ sub Instruction %17: 72
	 @ load Instruction %18: 76
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ call Instruction %0: 4
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ call Instruction %3: 16
	 @ load Instruction %4: 20
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
	.global	fib
	.arch armv8-a
	.type	fib, %function
fib: 
	@frame_size = 19
	@alloc = 76
	push	{r4, lr}
	sub	sp, sp, #76
	str	r0, [sp, #72]
	ldr	r1, [sp, #72]
	add	r2, sp, #68
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #64
	str	r1, [r2]
	mov	r1, #1
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #48]
	beq	then_bb0
	b	if_next_bb2
then_bb0: 
	mov	r3, #0
	b	fib_retbb
if_next_bb2: 
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	mov	r2, #1
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #40]
	beq	then_bb3
	b	if_next_bb5
then_bb3: 
	mov	r3, #1
	b	fib_retbb
if_next_bb5: 
	b	while_block6
while_block6: 
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #1
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #32]
	bgt	while_body7
	b	while_next8
while_body7: 
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #28]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #28]
	ldr	r2, [sp, #24]
	add	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	add	r2, sp, #56
	str	r1, [r2]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #64
	str	r1, [r2]
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #68
	str	r1, [r2]
	b	while_block6
while_next8: 
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	fib_retbb
fib_retbb:
	mov	r0, r3
	add	sp, sp, #76
	pop	{r4, lr}
	bx	lr
fib_alignbb:
	.align	2
	.size	fib, .-fib
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 5
	@alloc = 20
	push	{r4, lr}
	sub	sp, sp, #20
	bl	getint
	str	r0, [sp, #16]
	ldr	r1, [sp, #16]
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r0, [sp, #8]
	bl	fib
	str	r0, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #12
	str	r1, [r2]
	add	r1, sp, #12
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #20
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	n
	.size	main, .-main
