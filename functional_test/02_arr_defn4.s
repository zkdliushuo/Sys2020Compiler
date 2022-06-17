@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 32]
	 @ getelementptr inbounds Instruction %1: 36
	 @ getelementptr inbounds Instruction %2: 40
	 @ getelementptr inbounds Instruction %3: 44
	 @ getelementptr inbounds Instruction %4: 48
	 @ getelementptr inbounds Instruction %5: 52
	 @ getelementptr inbounds Instruction %6: 56
	 @ getelementptr inbounds Instruction %7: 60
	 @ getelementptr inbounds Instruction %8: 64
	 @ alloca Instruction %9 alloc space: [64 , 96]
	 @ getelementptr inbounds Instruction %10: 100
	 @ load Instruction %11: 104
	 @ getelementptr inbounds Instruction %12: 108
	 @ load Instruction %13: 112
	 @ getelementptr inbounds Instruction %14: 116
	 @ getelementptr inbounds Instruction %15: 120
	 @ getelementptr inbounds Instruction %16: 124
	 @ getelementptr inbounds Instruction %17: 128
	 @ getelementptr inbounds Instruction %18: 132
	 @ getelementptr inbounds Instruction %19: 136
	 @ getelementptr inbounds Instruction %20: 140
	 @ getelementptr inbounds Instruction %21: 144
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
	@frame_size = 36
	@alloc = 144
	push	{r4, lr}
	movw	r4, #144
	sub	sp, sp, r4
	add	r1, sp, #112
	add	r1, r1, #0
	str	r1, [sp, #108]
	mov	r1, #1
	ldr	r2, [sp, #108]
	str	r1, [r2]
	add	r1, sp, #112
	add	r1, r1, #4
	str	r1, [sp, #104]
	mov	r1, #2
	ldr	r2, [sp, #104]
	str	r1, [r2]
	add	r1, sp, #112
	add	r1, r1, #8
	str	r1, [sp, #100]
	mov	r1, #3
	ldr	r2, [sp, #100]
	str	r1, [r2]
	add	r1, sp, #112
	add	r1, r1, #12
	str	r1, [sp, #96]
	mov	r1, #4
	ldr	r2, [sp, #96]
	str	r1, [r2]
	add	r1, sp, #112
	add	r1, r1, #16
	str	r1, [sp, #92]
	mov	r1, #5
	ldr	r2, [sp, #92]
	str	r1, [r2]
	add	r1, sp, #112
	add	r1, r1, #20
	str	r1, [sp, #88]
	mov	r1, #6
	ldr	r2, [sp, #88]
	str	r1, [r2]
	add	r1, sp, #112
	add	r1, r1, #24
	str	r1, [sp, #84]
	mov	r1, #7
	ldr	r2, [sp, #84]
	str	r1, [r2]
	add	r1, sp, #112
	add	r1, r1, #28
	str	r1, [sp, #80]
	mov	r1, #8
	ldr	r2, [sp, #80]
	str	r1, [r2]
	add	r1, sp, #112
	add	r1, r1, #0
	str	r1, [sp, #44]
	ldr	r1, [sp, #44]
	ldr	r3, [r1]
	str	r3, [sp, #40]
	add	r1, sp, #112
	add	r1, r1, #4
	str	r1, [sp, #36]
	ldr	r1, [sp, #36]
	ldr	r3, [r1]
	str	r3, [sp, #32]
	add	r1, sp, #48
	add	r1, r1, #0
	str	r1, [sp, #28]
	ldr	r1, [sp, #40]
	ldr	r2, [sp, #28]
	str	r1, [r2]
	add	r1, sp, #48
	add	r1, r1, #4
	str	r1, [sp, #24]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #24]
	str	r1, [r2]
	add	r1, sp, #48
	add	r1, r1, #8
	str	r1, [sp, #20]
	mov	r1, #3
	ldr	r2, [sp, #20]
	str	r1, [r2]
	add	r1, sp, #48
	add	r1, r1, #12
	str	r1, [sp, #16]
	mov	r1, #4
	ldr	r2, [sp, #16]
	str	r1, [r2]
	add	r1, sp, #48
	add	r1, r1, #16
	str	r1, [sp, #12]
	mov	r1, #5
	ldr	r2, [sp, #12]
	str	r1, [r2]
	add	r1, sp, #48
	add	r1, r1, #20
	str	r1, [sp, #8]
	mov	r1, #6
	ldr	r2, [sp, #8]
	str	r1, [r2]
	add	r1, sp, #48
	add	r1, r1, #24
	str	r1, [sp, #4]
	mov	r1, #7
	ldr	r2, [sp, #4]
	str	r1, [r2]
	add	r1, sp, #48
	add	r1, r1, #28
	str	r1, [sp, #0]
	mov	r1, #8
	ldr	r2, [sp, #0]
	str	r1, [r2]
	mov	r3, #0
	b	main_retbb
main_retbb:
	movw	r4, #144
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
