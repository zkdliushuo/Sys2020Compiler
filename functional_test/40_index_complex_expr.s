@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 36]
	 @ getelementptr inbounds Instruction %5: 40
	 @ getelementptr inbounds Instruction %6: 44
	 @ getelementptr inbounds Instruction %7: 48
	 @ getelementptr inbounds Instruction %8: 52
	 @ getelementptr inbounds Instruction %9: 56
	 @ alloca Instruction %10 alloc space: [56 , 60]
	 @ load Instruction %11: 64
	 @ mul Instruction %12: 68
	 @ sdiv Instruction %13: 72
	 @ add Instruction %14: 76
	 @ load Instruction %15: 80
	 @ load Instruction %16: 84
	 @ sub Instruction %17: 88
	 @ add Instruction %18: 92
	 @ load Instruction %19: 96
	 @ add Instruction %20: 100
	 @ sub Instruction %21: 104
	 @ srem Instruction %22: 108
	 @ sub Instruction %23: 112
	 @ srem Instruction %24: 116
	 @ getelementptr inbounds Instruction %25: 120
	 @ load Instruction %26: 124
	 @ load Instruction %27: 128
	 @ load Instruction %28: 132
	 @ srem Instruction %29: 136
	 @ add Instruction %30: 140
	 @ load Instruction %31: 144
	 @ add Instruction %32: 148
	 @ load Instruction %33: 152
	 @ sub Instruction %34: 156
	 @ load Instruction %35: 160
	 @ add Instruction %36: 164
	 @ srem Instruction %37: 168
	 @ sub Instruction %38: 172
	 @ sub Instruction %39: 176
	 @ srem Instruction %40: 180
	 @ getelementptr inbounds Instruction %41: 184
	 @ load Instruction %42: 188
	 @ load Instruction %43: 192
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
	@frame_size = 48
	@alloc = 192
	push	{r4, lr}
	movw	r4, #192
	sub	sp, sp, r4
	mov	r1, #5
	movw	r2, #188
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #5
	movw	r2, #184
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #1
	movw	r2, #180
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #-2
	movw	r2, #176
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #156
	add	r1, sp, r1
	add	r1, r1, #0
	movw	r4, #152
	str	r1, [sp, r4]
	mov	r1, #1
	movw	r2, #152
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #156
	add	r1, sp, r1
	add	r1, r1, #4
	movw	r4, #148
	str	r1, [sp, r4]
	mov	r1, #2
	movw	r2, #148
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #156
	add	r1, sp, r1
	add	r1, r1, #8
	movw	r4, #144
	str	r1, [sp, r4]
	mov	r1, #3
	movw	r2, #144
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #156
	add	r1, sp, r1
	add	r1, r1, #12
	movw	r4, #140
	str	r1, [sp, r4]
	mov	r1, #4
	movw	r2, #140
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #156
	add	r1, sp, r1
	add	r1, r1, #16
	movw	r4, #136
	str	r1, [sp, r4]
	mov	r1, #5
	movw	r2, #136
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #128
	str	r3, [sp, r4]
	movw	r1, #128
	ldr	r1, [sp, r1]
	mov	r2, #1
	mul	r3, r1, r2
	str	r3, [sp, #124]
	ldr	r0, [sp, #124]
	mov	r1, #2
	bl	__aeabi_idiv
	str	r0, [sp, #120]
	ldr	r1, [sp, #120]
	mov	r2, #4
	add	r3, r1, r2
	str	r3, [sp, #116]
	movw	r1, #188
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #112]
	movw	r1, #184
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #108]
	ldr	r1, [sp, #112]
	ldr	r2, [sp, #108]
	sub	r3, r1, r2
	str	r3, [sp, #104]
	ldr	r1, [sp, #116]
	ldr	r2, [sp, #104]
	add	r3, r1, r2
	str	r3, [sp, #100]
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #96]
	ldr	r1, [sp, #96]
	mov	r2, #3
	add	r3, r1, r2
	str	r3, [sp, #92]
	mov	r1, #0
	ldr	r2, [sp, #92]
	sub	r3, r1, r2
	str	r3, [sp, #88]
	ldr	r0, [sp, #88]
	mov	r1, #2
	bl	__aeabi_idivmod
	str	r1, [sp, #84]
	ldr	r1, [sp, #100]
	ldr	r2, [sp, #84]
	sub	r3, r1, r2
	str	r3, [sp, #80]
	ldr	r0, [sp, #80]
	mov	r1, #5
	bl	__aeabi_idivmod
	str	r1, [sp, #76]
	movw	r1, #156
	add	r1, sp, r1
	ldr	r2, [sp, #76]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	movw	r2, #132
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #132
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r0, [sp, #64]
	bl	putint
	movw	r1, #180
	add	r1, sp, r1
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
	movw	r1, #188
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #48]
	add	r3, r1, r2
	str	r3, [sp, #44]
	movw	r1, #184
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #40]
	sub	r3, r1, r2
	str	r3, [sp, #36]
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	mov	r2, #2
	add	r3, r1, r2
	str	r3, [sp, #28]
	ldr	r0, [sp, #28]
	mov	r1, #2
	bl	__aeabi_idivmod
	str	r1, [sp, #24]
	mov	r1, #0
	ldr	r2, [sp, #24]
	sub	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r1, [sp, #36]
	ldr	r2, [sp, #20]
	sub	r3, r1, r2
	str	r3, [sp, #16]
	ldr	r0, [sp, #16]
	mov	r1, #5
	bl	__aeabi_idivmod
	str	r1, [sp, #12]
	movw	r1, #156
	add	r1, sp, r1
	ldr	r2, [sp, #12]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	movw	r2, #132
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #132
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	movw	r4, #192
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
