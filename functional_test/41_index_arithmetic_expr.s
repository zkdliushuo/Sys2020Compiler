@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 20]
	 @ getelementptr inbounds Instruction %3: 24
	 @ getelementptr inbounds Instruction %4: 28
	 @ getelementptr inbounds Instruction %5: 32
	 @ alloca Instruction %6 alloc space: [32 , 36]
	 @ load Instruction %7: 40
	 @ load Instruction %8: 44
	 @ srem Instruction %9: 48
	 @ load Instruction %10: 52
	 @ add Instruction %11: 56
	 @ sdiv Instruction %12: 60
	 @ sub Instruction %13: 64
	 @ getelementptr inbounds Instruction %14: 68
	 @ load Instruction %15: 72
	 @ load Instruction %16: 76
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
	@frame_size = 19
	@alloc = 76
	push	{r4, lr}
	sub	sp, sp, #76
	mov	r1, #56
	add	r2, sp, #72
	str	r1, [r2]
	mov	r1, #12
	add	r2, sp, #68
	str	r1, [r2]
	add	r1, sp, #56
	add	r1, r1, #0
	str	r1, [sp, #52]
	mov	r1, #1
	ldr	r2, [sp, #52]
	str	r1, [r2]
	add	r1, sp, #56
	add	r1, r1, #4
	str	r1, [sp, #48]
	mov	r1, #2
	ldr	r2, [sp, #48]
	str	r1, [r2]
	add	r1, sp, #56
	add	r1, r1, #8
	str	r1, [sp, #44]
	mov	r1, #3
	ldr	r2, [sp, #44]
	str	r1, [r2]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #36]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r0, [sp, #36]
	ldr	r1, [sp, #32]
	bl	__aeabi_idivmod
	str	r1, [sp, #28]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #28]
	ldr	r2, [sp, #24]
	add	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r0, [sp, #20]
	mov	r1, #5
	bl	__aeabi_idiv
	str	r0, [sp, #16]
	ldr	r1, [sp, #16]
	mov	r2, #2
	sub	r3, r1, r2
	str	r3, [sp, #12]
	add	r1, sp, #56
	ldr	r2, [sp, #12]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #40
	str	r1, [r2]
	add	r1, sp, #40
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #76
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
