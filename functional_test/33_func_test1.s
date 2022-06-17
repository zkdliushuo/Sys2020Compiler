@ After Enter EntryBB
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ alloca Instruction %5 alloc space: [20 , 24]
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ load Instruction %7: 32
	 @ icmp Instruction %8: 36
	 @ load Instruction %9: 40
	 @ icmp Instruction %10: 44
	 @ load Instruction %11: 48
	 @ sub Instruction %12: 52
	 @ load Instruction %13: 56
	 @ load Instruction %14: 60
	 @ add Instruction %15: 64
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
	 @ Arg %2 Alloc : 12
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ call Instruction %1: 8
	 @ load Instruction %2: 12
	 @ load Instruction %3: 16
	 @ add Instruction %4: 20
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 4 
a:
	.word	0
	.text
	.align	2
	.global	myFunc
	.arch armv8-a
	.type	myFunc, %function
myFunc: 
	@frame_size = 16
	@alloc = 64
	push	{r4, lr}
	sub	sp, sp, #64
	str	r0, [sp, #60]
	str	r1, [sp, #56]
	str	r2, [sp, #52]
	ldr	r1, [sp, #60]
	add	r2, sp, #48
	str	r1, [r2]
	ldr	r1, [sp, #56]
	add	r2, sp, #44
	str	r1, [r2]
	ldr	r1, [sp, #52]
	add	r2, sp, #40
	str	r1, [r2]
	mov	r1, #2
	add	r2, sp, #48
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #36
	str	r1, [r2]
	add	r1, sp, #36
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #28]
	bne	then_bb0
	b	if_next_bb2
then_bb0: 
	mov	r3, #0
	b	myFunc_retbb
if_next_bb2: 
	b	while_block3
while_block3: 
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #20]
	bgt	while_body4
	b	while_next5
while_body4: 
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	add	r2, sp, #44
	str	r1, [r2]
	b	while_block3
while_next5: 
	add	r1, sp, #48
	ldr	r3, [r1]
	str	r3, [sp, #8]
	add	r1, sp, #44
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #4]
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	myFunc_retbb
myFunc_retbb:
	mov	r0, r3
	add	sp, sp, #64
	pop	{r4, lr}
	bx	lr
myFunc_alignbb:
	.align	2
	.size	myFunc, .-myFunc
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
	mov	r1, #3
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	mov	r0, #1
	mov	r1, #2
	mov	r2, #1
	bl	myFunc
	str	r0, [sp, #12]
	ldr	r1, [sp, #12]
	add	r2, sp, #16
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #8]
	add	r1, sp, #16
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #4]
	add	r3, r1, r2
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
	.word	a
	.size	main, .-main
