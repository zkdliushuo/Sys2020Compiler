@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ sub Instruction %3: 16
	 @ load Instruction %4: 20
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
	 @ call Instruction %2: 12
	 @ load Instruction %3: 16
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
	.global	func
	.arch armv8-a
	.type	func, %function
func: 
	@frame_size = 5
	@alloc = 20
	push	{r4, lr}
	sub	sp, sp, #20
	str	r0, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #12
	str	r1, [r2]
	add	r1, sp, #12
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #12
	str	r1, [r2]
	add	r1, sp, #12
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	func_retbb
func_retbb:
	mov	r0, r3
	add	sp, sp, #20
	pop	{r4, lr}
	bx	lr
func_alignbb:
	.align	2
	.size	func, .-func
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 4
	@alloc = 16
	push	{r4, lr}
	sub	sp, sp, #16
	mov	r1, #10
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r0, [sp, #8]
	bl	func
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
	add	sp, sp, #16
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	a
	.size	main, .-main
