@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ mul Instruction %6: 28
	 @ sdiv Instruction %7: 32
	 @ load Instruction %8: 36
	 @ load Instruction %9: 40
	 @ sub Instruction %10: 44
	 @ add Instruction %11: 48
	 @ load Instruction %12: 52
	 @ add Instruction %13: 56
	 @ sub Instruction %14: 60
	 @ srem Instruction %15: 64
	 @ sub Instruction %16: 68
	 @ load Instruction %17: 72
	 @ load Instruction %18: 76
	 @ srem Instruction %19: 80
	 @ add Instruction %20: 84
	 @ load Instruction %21: 88
	 @ load Instruction %22: 92
	 @ sub Instruction %23: 96
	 @ sub Instruction %24: 100
	 @ add Instruction %25: 104
	 @ load Instruction %26: 108
	 @ add Instruction %27: 112
	 @ srem Instruction %28: 116
	 @ sub Instruction %29: 120
	 @ sub Instruction %30: 124
	 @ load Instruction %31: 128
	 @ add Instruction %32: 132
	 @ load Instruction %33: 136
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
	@frame_size = 34
	@alloc = 136
	push	{r4, lr}
	movw	r4, #136
	sub	sp, sp, r4
	mov	r1, #5
	movw	r2, #132
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #5
	movw	r2, #128
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #1
	add	r2, sp, #124
	str	r1, [r2]
	mov	r1, #-2
	add	r2, sp, #120
	str	r1, [r2]
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #112]
	ldr	r1, [sp, #112]
	mov	r2, #1
	mul	r3, r1, r2
	str	r3, [sp, #108]
	ldr	r0, [sp, #108]
	mov	r1, #2
	bl	__aeabi_idiv
	str	r0, [sp, #104]
	movw	r1, #132
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #100]
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #96]
	ldr	r1, [sp, #100]
	ldr	r2, [sp, #96]
	sub	r3, r1, r2
	str	r3, [sp, #92]
	ldr	r1, [sp, #104]
	ldr	r2, [sp, #92]
	add	r3, r1, r2
	str	r3, [sp, #88]
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #84]
	ldr	r1, [sp, #84]
	mov	r2, #3
	add	r3, r1, r2
	str	r3, [sp, #80]
	mov	r1, #0
	ldr	r2, [sp, #80]
	sub	r3, r1, r2
	str	r3, [sp, #76]
	ldr	r0, [sp, #76]
	mov	r1, #2
	bl	__aeabi_idivmod
	str	r1, [sp, #72]
	ldr	r1, [sp, #88]
	ldr	r2, [sp, #72]
	sub	r3, r1, r2
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	add	r2, sp, #116
	str	r1, [r2]
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r0, [sp, #64]
	bl	putint
	add	r1, sp, #120
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r0, [sp, #60]
	mov	r1, #2
	bl	__aeabi_idivmod
	str	r1, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #67
	add	r3, r1, r2
	str	r3, [sp, #52]
	movw	r1, #132
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #48]
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #48]
	ldr	r2, [sp, #44]
	sub	r3, r1, r2
	str	r3, [sp, #40]
	mov	r1, #0
	ldr	r2, [sp, #40]
	sub	r3, r1, r2
	str	r3, [sp, #36]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #36]
	add	r3, r1, r2
	str	r3, [sp, #32]
	add	r1, sp, #124
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #2
	add	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r0, [sp, #24]
	mov	r1, #2
	bl	__aeabi_idivmod
	str	r1, [sp, #20]
	mov	r1, #0
	ldr	r2, [sp, #20]
	sub	r3, r1, r2
	str	r3, [sp, #16]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #16]
	sub	r3, r1, r2
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	add	r2, sp, #116
	str	r1, [r2]
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #3
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #116
	str	r1, [r2]
	add	r1, sp, #116
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	movw	r4, #136
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
