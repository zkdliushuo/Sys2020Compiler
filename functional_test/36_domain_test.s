@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ getelementptr inbounds Instruction %2: 12
	 @ getelementptr inbounds Instruction %3: 16
	 @ load Instruction %4: 20
	 @ sub Instruction %5: 24
	 @ load Instruction %6: 28
	 @ getelementptr inbounds Instruction %7: 32
	 @ load Instruction %8: 36
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 16]
	 @ getelementptr inbounds Instruction %2: 20
	 @ getelementptr inbounds Instruction %3: 24
	 @ getelementptr inbounds Instruction %4: 28
	 @ getelementptr inbounds Instruction %5: 32
	 @ call Instruction %6: 36
	 @ load Instruction %7: 40
	 @ getelementptr inbounds Instruction %8: 44
	 @ load Instruction %9: 48
	 @ add Instruction %10: 52
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global a 
	.data
	.align	2
	.type	a, %object
	.size	a, 8 
a:
	.space	8
	.text
	.align	2
	.global	func
	.arch armv8-a
	.type	func, %function
func: 
	@frame_size = 9
	@alloc = 36
	push	{r4, lr}
	sub	sp, sp, #36
	str	r0, [sp, #32]
	ldr	r1, [sp, #32]
	add	r2, sp, #28
	str	r1, [r2]
	adrl	r1, func_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #0
	str	r1, [sp, #24]
	mov	r1, #1
	ldr	r2, [sp, #24]
	str	r1, [r2]
	adrl	r1, func_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #0
	str	r1, [sp, #20]
	ldr	r1, [sp, #20]
	ldr	r3, [r1]
	str	r3, [sp, #16]
	mov	r1, #3
	ldr	r2, [sp, #16]
	sub	r3, r1, r2
	str	r3, [sp, #12]
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #12]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	func_retbb
func_retbb:
	mov	r0, r3
	add	sp, sp, #36
	pop	{r4, lr}
	bx	lr
func_alignbb:
	.align	2
func_gvbb:
	.word	a
	.size	func, .-func
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 13
	@alloc = 52
	push	{r4, lr}
	sub	sp, sp, #52
	add	r1, sp, #36
	add	r1, r1, #0
	str	r1, [sp, #32]
	mov	r1, #-1
	ldr	r2, [sp, #32]
	str	r1, [r2]
	add	r1, sp, #36
	add	r1, r1, #4
	str	r1, [sp, #28]
	mov	r1, #4
	ldr	r2, [sp, #28]
	str	r1, [r2]
	add	r1, sp, #36
	add	r1, r1, #8
	str	r1, [sp, #24]
	mov	r1, #8
	ldr	r2, [sp, #24]
	str	r1, [r2]
	add	r1, sp, #36
	add	r1, r1, #0
	str	r1, [sp, #20]
	ldr	r0, [sp, #20]
	bl	func
	str	r0, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #48
	str	r1, [r2]
	add	r1, sp, #48
	ldr	r3, [r1]
	str	r3, [sp, #12]
	add	r1, sp, #36
	add	r1, r1, #4
	str	r1, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #4]
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #52
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
