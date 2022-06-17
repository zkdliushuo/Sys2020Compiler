@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ load Instruction %3: 16
	 @ sub Instruction %4: 20
	 @ sub Instruction %5: 24
	 @ load Instruction %6: 28
	 @ load Instruction %7: 32
	 @ add Instruction %8: 36
	 @ sub Instruction %9: 40
	 @ load Instruction %10: 44
	 @ load Instruction %11: 48
	 @ sub Instruction %12: 52
	 @ sub Instruction %13: 56
	 @ srem Instruction %14: 60
	 @ add Instruction %15: 64
	 @ load Instruction %16: 68
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
	@frame_size = 17
	@alloc = 68
	push	{r4, lr}
	sub	sp, sp, #68
	mov	r1, #-2
	add	r2, sp, #64
	str	r1, [r2]
	mov	r1, #1
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #56]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #52]
	mov	r1, #0
	ldr	r2, [sp, #52]
	sub	r3, r1, r2
	str	r3, [sp, #48]
	ldr	r1, [sp, #56]
	ldr	r2, [sp, #48]
	sub	r3, r1, r2
	str	r3, [sp, #44]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #40]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #40]
	ldr	r2, [sp, #36]
	add	r3, r1, r2
	str	r3, [sp, #32]
	mov	r1, #0
	ldr	r2, [sp, #32]
	sub	r3, r1, r2
	str	r3, [sp, #28]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #24]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #20]
	sub	r3, r1, r2
	str	r3, [sp, #16]
	mov	r1, #0
	ldr	r2, [sp, #16]
	sub	r3, r1, r2
	str	r3, [sp, #12]
	ldr	r0, [sp, #28]
	ldr	r1, [sp, #12]
	bl	__aeabi_idivmod
	str	r1, [sp, #8]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #8]
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #64
	str	r1, [r2]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #68
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
