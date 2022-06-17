@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ icmp Instruction %3: 16
	 @ load Instruction %4: 20
	 @ sub Instruction %5: 24
	 @ load Instruction %6: 28
	 @ call Instruction %7: 32
	 @ load Instruction %8: 36
	 @ load Instruction %9: 40
	 @ mul Instruction %10: 44
	 @ load Instruction %11: 48
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
	 @ call Instruction %2: 12
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
	.global r 
	.data
	.align	2
	.type	r, %object
	.size	r, 4 
r:
	.word	0
	.text
	.align	2
	.global	fac
	.arch armv8-a
	.type	fac, %function
fac: 
	@frame_size = 12
	@alloc = 48
	push	{r4, lr}
	sub	sp, sp, #48
	str	r0, [sp, #44]
	ldr	r1, [sp, #44]
	add	r2, sp, #40
	str	r1, [r2]
	add	r1, sp, #40
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #2
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #32]
	blt	then_bb0
	b	if_next_bb2
then_bb0: 
	mov	r3, #1
	b	fac_retbb
if_next_bb2: 
	add	r1, sp, #40
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	adrl	r2, fac_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, fac_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r0, [sp, #20]
	bl	fac
	str	r0, [sp, #16]
	ldr	r1, [sp, #16]
	adrl	r2, fac_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	add	r1, sp, #40
	ldr	r3, [r1]
	str	r3, [sp, #12]
	adrl	r1, fac_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #8]
	mul	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	adrl	r2, fac_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, fac_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	fac_retbb
fac_retbb:
	mov	r0, r3
	add	sp, sp, #48
	pop	{r4, lr}
	bx	lr
fac_alignbb:
	.align	2
fac_gvbb:
	.word	a
	.word	r
	.size	fac, .-fac
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
	mov	r1, #5
	add	r2, sp, #8
	str	r1, [r2]
	add	r1, sp, #8
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r0, [sp, #4]
	bl	fac
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
