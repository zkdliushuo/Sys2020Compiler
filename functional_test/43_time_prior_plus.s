@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ mul Instruction %7: 32
	 @ add Instruction %8: 36
	 @ load Instruction %9: 40
	 @ load Instruction %10: 44
	 @ load Instruction %11: 48
	 @ add Instruction %12: 52
	 @ srem Instruction %13: 56
	 @ load Instruction %14: 60
	 @ sdiv Instruction %15: 64
	 @ sub Instruction %16: 68
	 @ load Instruction %17: 72
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
	@frame_size = 18
	@alloc = 72
	push	{r4, lr}
	sub	sp, sp, #72
	mov	r1, #20
	add	r2, sp, #68
	str	r1, [r2]
	mov	r1, #5
	add	r2, sp, #64
	str	r1, [r2]
	mov	r1, #6
	add	r2, sp, #60
	str	r1, [r2]
	mov	r1, #-4
	add	r2, sp, #56
	str	r1, [r2]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #52]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #48]
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #48]
	ldr	r2, [sp, #44]
	mul	r3, r1, r2
	str	r3, [sp, #40]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #40]
	add	r3, r1, r2
	str	r3, [sp, #36]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #32]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #28]
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #28]
	ldr	r2, [sp, #24]
	add	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r0, [sp, #32]
	ldr	r1, [sp, #20]
	bl	__aeabi_idivmod
	str	r1, [sp, #16]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r0, [sp, #16]
	ldr	r1, [sp, #12]
	bl	__aeabi_idiv
	str	r0, [sp, #8]
	ldr	r1, [sp, #36]
	ldr	r2, [sp, #8]
	sub	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #68
	str	r1, [r2]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #72
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
