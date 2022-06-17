@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ load Instruction %7: 32
	 @ sub Instruction %8: 36
	 @ alloca Instruction %9 alloc space: [36 , 40]
	 @ load Instruction %10: 44
	 @ sub Instruction %11: 48
	 @ load Instruction %12: 52
	 @ call Instruction %13: 56
	 @ load Instruction %14: 60
	 @ call Instruction %15: 64
	 @ add Instruction %16: 68
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
	.global	fib
	.arch armv8-a
	.type	fib, %function
fib: 
	@frame_size = 17
	@alloc = 68
	push	{r4, lr}
	sub	sp, sp, #68
	str	r0, [sp, #64]
	ldr	r1, [sp, #64]
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #52]
	beq	then_bb0
	b	if_next_bb2
then_bb0: 
	mov	r3, #0
	b	fib_retbb
if_next_bb2: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	mov	r2, #1
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	str	r3, [sp, #44]
	beq	then_bb3
	b	if_next_bb5
then_bb3: 
	mov	r3, #1
	b	fib_retbb
if_next_bb5: 
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	add	r2, sp, #40
	str	r1, [r2]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	mov	r2, #2
	sub	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	add	r2, sp, #28
	str	r1, [r2]
	add	r1, sp, #40
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r0, [sp, #16]
	bl	fib
	str	r0, [sp, #12]
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r0, [sp, #8]
	bl	fib
	str	r0, [sp, #4]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #4]
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	fib_retbb
fib_retbb:
	mov	r0, r3
	add	sp, sp, #68
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
	@frame_size = 3
	@alloc = 12
	push	{r4, lr}
	sub	sp, sp, #12
	mov	r1, #10
	add	r2, sp, #8
	str	r1, [r2]
	add	r1, sp, #8
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r0, [sp, #4]
	bl	fib
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
