@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ load Instruction %3: 16
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ load Instruction %7: 32
	 @ load Instruction %8: 36
	 @ getelementptr inbounds Instruction %9: 40
	 @ load Instruction %10: 44
	 @ alloca Instruction %11 alloc space: [44 , 48]
	 @ load Instruction %12: 52
	 @ sub Instruction %13: 56
	 @ load Instruction %14: 60
	 @ icmp Instruction %15: 64
	 @ load Instruction %16: 68
	 @ add Instruction %17: 72
	 @ load Instruction %18: 76
	 @ getelementptr inbounds Instruction %19: 80
	 @ load Instruction %20: 84
	 @ load Instruction %21: 88
	 @ getelementptr inbounds Instruction %22: 92
	 @ load Instruction %23: 96
	 @ load Instruction %24: 100
	 @ sub Instruction %25: 104
	 @ load Instruction %26: 108
	 @ add Instruction %27: 112
	 @ load Instruction %28: 116
	 @ getelementptr inbounds Instruction %29: 120
	 @ load Instruction %30: 124
	 @ load Instruction %31: 128
	 @ add Instruction %32: 132
	 @ load Instruction %33: 136
	 @ load Instruction %34: 140
	 @ load Instruction %35: 144
	 @ getelementptr inbounds Instruction %36: 148
	 @ load Instruction %37: 152
	 @ icmp Instruction %38: 156
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 40]
	 @ getelementptr inbounds Instruction %1: 44
	 @ getelementptr inbounds Instruction %2: 48
	 @ getelementptr inbounds Instruction %3: 52
	 @ getelementptr inbounds Instruction %4: 56
	 @ getelementptr inbounds Instruction %5: 60
	 @ getelementptr inbounds Instruction %6: 64
	 @ getelementptr inbounds Instruction %7: 68
	 @ getelementptr inbounds Instruction %8: 72
	 @ getelementptr inbounds Instruction %9: 76
	 @ getelementptr inbounds Instruction %10: 80
	 @ alloca Instruction %11 alloc space: [80 , 84]
	 @ getelementptr inbounds Instruction %12: 88
	 @ call Instruction %13: 92
	 @ load Instruction %14: 96
	 @ load Instruction %15: 100
	 @ icmp Instruction %16: 104
	 @ alloca Instruction %17 alloc space: [104 , 108]
	 @ load Instruction %18: 112
	 @ getelementptr inbounds Instruction %19: 116
	 @ load Instruction %20: 120
	 @ load Instruction %21: 124
	 @ load Instruction %22: 128
	 @ load Instruction %23: 132
	 @ add Instruction %24: 136
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global n 
	.data
	.align	2
	.type	n, %object
	.size	n, 4 
n:
	.word	0
	.text
	.align	2
	.global	insertsort
	.arch armv8-a
	.type	insertsort, %function
insertsort: 
	@frame_size = 39
	@alloc = 156
	push	{r4, lr}
	movw	r4, #156
	sub	sp, sp, r4
	movw	r4, #152
	str	r0, [sp, r4]
	movw	r1, #152
	ldr	r1, [sp, r1]
	movw	r2, #148
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #1
	movw	r2, #144
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_block0: 
	movw	r1, #144
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #140
	str	r3, [sp, r4]
	adrl	r1, insertsort_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	movw	r4, #136
	str	r3, [sp, r4]
	movw	r1, #140
	ldr	r1, [sp, r1]
	movw	r2, #136
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #132
	str	r3, [sp, r4]
	blt	while_body1
	b	while_next2
while_body1: 
	movw	r1, #144
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #124]
	movw	r1, #148
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #120]
	ldr	r1, [sp, #120]
	ldr	r2, [sp, #124]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #116]
	ldr	r1, [sp, #116]
	ldr	r3, [r1]
	str	r3, [sp, #112]
	ldr	r1, [sp, #112]
	movw	r2, #128
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #104]
	ldr	r1, [sp, #104]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #100]
	ldr	r1, [sp, #100]
	add	r2, sp, #108
	str	r1, [r2]
	b	while_block3
while_next2: 
	mov	r3, #0
	b	insertsort_retbb
while_block3: 
	add	r1, sp, #108
	ldr	r3, [r1]
	str	r3, [sp, #96]
	ldr	r1, [sp, #96]
	mov	r2, #-1
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #92]
	bgt	next_and_bb6
	b	while_next5
while_body4: 
	add	r1, sp, #108
	ldr	r3, [r1]
	str	r3, [sp, #88]
	ldr	r1, [sp, #88]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #84]
	movw	r1, #148
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #80]
	ldr	r1, [sp, #80]
	ldr	r2, [sp, #84]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #76]
	add	r1, sp, #108
	ldr	r3, [r1]
	str	r3, [sp, #72]
	movw	r1, #148
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	ldr	r2, [sp, #72]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	ldr	r2, [sp, #76]
	str	r1, [r2]
	add	r1, sp, #108
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	add	r2, sp, #108
	str	r1, [r2]
	b	while_block3
while_next5: 
	add	r1, sp, #108
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #44]
	movw	r1, #148
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #40]
	ldr	r2, [sp, #44]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #36]
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #36]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	movw	r2, #144
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
next_and_bb6: 
	movw	r1, #128
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #20]
	add	r1, sp, #108
	ldr	r3, [r1]
	str	r3, [sp, #16]
	movw	r1, #148
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #16]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #20]
	ldr	r2, [sp, #4]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #0]
	blt	while_body4
	b	while_next5
insertsort_retbb:
	movw	r4, #156
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
insertsort_alignbb:
	.align	2
insertsort_gvbb:
	.word	n
	.size	insertsort, .-insertsort
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
	mov	r1, #10
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #0
	str	r1, [sp, #92]
	mov	r1, #4
	ldr	r2, [sp, #92]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #4
	str	r1, [sp, #88]
	mov	r1, #3
	ldr	r2, [sp, #88]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #8
	str	r1, [sp, #84]
	mov	r1, #9
	ldr	r2, [sp, #84]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #12
	str	r1, [sp, #80]
	mov	r1, #2
	ldr	r2, [sp, #80]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #16
	str	r1, [sp, #76]
	mov	r1, #0
	ldr	r2, [sp, #76]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #20
	str	r1, [sp, #72]
	mov	r1, #1
	ldr	r2, [sp, #72]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #24
	str	r1, [sp, #68]
	mov	r1, #6
	ldr	r2, [sp, #68]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #28
	str	r1, [sp, #64]
	mov	r1, #5
	ldr	r2, [sp, #64]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #32
	str	r1, [sp, #60]
	mov	r1, #7
	ldr	r2, [sp, #60]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #36
	str	r1, [sp, #56]
	mov	r1, #8
	ldr	r2, [sp, #56]
	str	r1, [r2]
	add	r1, sp, #96
	add	r1, r1, #0
	str	r1, [sp, #48]
	ldr	r0, [sp, #48]
	bl	insertsort
	str	r0, [sp, #44]
	ldr	r1, [sp, #44]
	add	r2, sp, #52
	str	r1, [r2]
	b	while_block7
while_block7: 
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #40]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #40]
	ldr	r2, [sp, #36]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #32]
	blt	while_body8
	b	while_next9
while_body8: 
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #24]
	add	r1, sp, #96
	ldr	r2, [sp, #24]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	add	r2, sp, #28
	str	r1, [r2]
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r0, [sp, #12]
	bl	putint
	mov	r1, #10
	add	r2, sp, #28
	str	r1, [r2]
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r0, [sp, #8]
	bl	putch
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #52
	str	r1, [r2]
	b	while_block7
while_next9: 
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
main_gvbb:
	.word	n
	.size	main, .-main
