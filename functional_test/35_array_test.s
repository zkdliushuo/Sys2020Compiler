@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ getelementptr inbounds Instruction %2: 12
	 @ load Instruction %3: 16
	 @ sub Instruction %4: 20
	 @ load Instruction %5: 24
	 @ getelementptr inbounds Instruction %6: 28
	 @ load Instruction %7: 32
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 16]
	 @ alloca Instruction %2 alloc space: [16 , 20]
	 @ getelementptr inbounds Instruction %3: 24
	 @ getelementptr inbounds Instruction %4: 28
	 @ getelementptr inbounds Instruction %5: 32
	 @ getelementptr inbounds Instruction %6: 36
	 @ getelementptr inbounds Instruction %7: 40
	 @ load Instruction %8: 44
	 @ sub Instruction %9: 48
	 @ getelementptr inbounds Instruction %10: 52
	 @ load Instruction %11: 56
	 @ getelementptr inbounds Instruction %12: 60
	 @ getelementptr inbounds Instruction %13: 64
	 @ call Instruction %14: 68
	 @ add Instruction %15: 72
	 @ load Instruction %16: 76
	 @ add Instruction %17: 80
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global field 
	.data
	.align	2
	.type	field, %object
	.size	field, 8 
field:
	.space	8
	.text
	.align	2
	.global	func
	.arch armv8-a
	.type	func, %function
func: 
	@frame_size = 8
	@alloc = 32
	push	{r4, lr}
	sub	sp, sp, #32
	str	r0, [sp, #28]
	ldr	r1, [sp, #28]
	add	r2, sp, #24
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
	add	r1, sp, #24
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
	add	sp, sp, #32
	pop	{r4, lr}
	bx	lr
func_alignbb:
	.align	2
func_gvbb:
	.word	field
	.size	func, .-func
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 20
	@alloc = 80
	push	{r4, lr}
	sub	sp, sp, #80
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #0
	str	r1, [sp, #56]
	mov	r1, #1
	ldr	r2, [sp, #56]
	str	r1, [r2]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	add	r1, r1, #4
	str	r1, [sp, #52]
	mov	r1, #2
	ldr	r2, [sp, #52]
	str	r1, [r2]
	add	r1, sp, #64
	add	r1, r1, #0
	str	r1, [sp, #48]
	mov	r1, #-1
	ldr	r2, [sp, #48]
	str	r1, [r2]
	add	r1, sp, #64
	add	r1, r1, #4
	str	r1, [sp, #44]
	add	r1, sp, #64
	add	r1, r1, #0
	str	r1, [sp, #40]
	ldr	r1, [sp, #40]
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #2
	sub	r3, r1, r2
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #44]
	str	r1, [r2]
	add	r1, sp, #64
	add	r1, r1, #4
	str	r1, [sp, #28]
	ldr	r1, [sp, #28]
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #64
	add	r1, r1, #8
	str	r1, [sp, #20]
	mov	r1, #16
	ldr	r2, [sp, #20]
	str	r1, [r2]
	add	r1, sp, #64
	add	r1, r1, #0
	str	r1, [sp, #16]
	ldr	r0, [sp, #16]
	bl	func
	str	r0, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #2
	add	r3, r1, r2
	str	r3, [sp, #8]
	add	r1, sp, #60
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
	add	sp, sp, #80
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	field
	.size	main, .-main
