@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ load Instruction %5: 24
	 @ sub Instruction %6: 28
	 @ icmp Instruction %7: 32
	 @ load Instruction %8: 36
	 @ load Instruction %9: 40
	 @ load Instruction %10: 44
	 @ sub Instruction %11: 48
	 @ sub Instruction %12: 52
	 @ icmp Instruction %13: 56
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ getelementptr inbounds Instruction %16: 68
	 @ load Instruction %17: 72
	 @ load Instruction %18: 76
	 @ add Instruction %19: 80
	 @ load Instruction %20: 84
	 @ getelementptr inbounds Instruction %21: 88
	 @ load Instruction %22: 92
	 @ icmp Instruction %23: 96
	 @ load Instruction %24: 100
	 @ add Instruction %25: 104
	 @ alloca Instruction %26 alloc space: [104 , 108]
	 @ load Instruction %27: 112
	 @ add Instruction %28: 116
	 @ load Instruction %29: 120
	 @ getelementptr inbounds Instruction %30: 124
	 @ load Instruction %31: 128
	 @ load Instruction %32: 132
	 @ add Instruction %33: 136
	 @ load Instruction %34: 140
	 @ getelementptr inbounds Instruction %35: 144
	 @ load Instruction %36: 148
	 @ load Instruction %37: 152
	 @ getelementptr inbounds Instruction %38: 156
	 @ load Instruction %39: 160
	 @ load Instruction %40: 164
	 @ load Instruction %41: 168
	 @ getelementptr inbounds Instruction %42: 172
	 @ load Instruction %43: 176
	 @ load Instruction %44: 180
	 @ add Instruction %45: 184
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
	.global	bubblesort
	.arch armv8-a
	.type	bubblesort, %function
bubblesort: 
	@frame_size = 46
	@alloc = 184
	push	{r4, lr}
	movw	r4, #184
	sub	sp, sp, r4
	movw	r4, #180
	str	r0, [sp, r4]
	movw	r1, #180
	ldr	r1, [sp, r1]
	movw	r2, #176
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #0
	movw	r2, #172
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_block0: 
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #164
	str	r3, [sp, r4]
	adrl	r1, bubblesort_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	movw	r4, #160
	str	r3, [sp, r4]
	movw	r1, #160
	ldr	r1, [sp, r1]
	mov	r2, #1
	sub	r3, r1, r2
	movw	r4, #156
	str	r3, [sp, r4]
	movw	r1, #164
	ldr	r1, [sp, r1]
	movw	r2, #156
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #152
	str	r3, [sp, r4]
	blt	while_body1
	b	while_next2
while_body1: 
	mov	r1, #0
	movw	r2, #168
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
while_next2: 
	mov	r3, #0
	b	bubblesort_retbb
while_block3: 
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #148
	str	r3, [sp, r4]
	adrl	r1, bubblesort_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	movw	r4, #144
	str	r3, [sp, r4]
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #140
	str	r3, [sp, r4]
	movw	r1, #144
	ldr	r1, [sp, r1]
	movw	r2, #140
	ldr	r2, [sp, r2]
	sub	r3, r1, r2
	movw	r4, #136
	str	r3, [sp, r4]
	movw	r1, #136
	ldr	r1, [sp, r1]
	mov	r2, #1
	sub	r3, r1, r2
	movw	r4, #132
	str	r3, [sp, r4]
	movw	r1, #148
	ldr	r1, [sp, r1]
	movw	r2, #132
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #128
	str	r3, [sp, r4]
	blt	while_body4
	b	while_next5
while_body4: 
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #124]
	movw	r1, #176
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
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #108]
	ldr	r1, [sp, #108]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #104]
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #100]
	ldr	r1, [sp, #100]
	ldr	r2, [sp, #104]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #96]
	ldr	r1, [sp, #96]
	ldr	r3, [r1]
	str	r3, [sp, #92]
	ldr	r1, [sp, #112]
	ldr	r2, [sp, #92]
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #88]
	bgt	then_bb6
	b	if_next_bb8
while_next5: 
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #84]
	ldr	r1, [sp, #84]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #80]
	ldr	r1, [sp, #80]
	movw	r2, #172
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
then_bb6: 
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #68]
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	ldr	r2, [sp, #68]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	add	r2, sp, #76
	str	r1, [r2]
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #48]
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #48]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #40]
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #36]
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #36]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #40]
	str	r1, [r2]
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #20]
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	ldr	r2, [sp, #20]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #12]
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #12]
	str	r1, [r2]
	b	if_next_bb8
if_next_bb8: 
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	movw	r2, #168
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
bubblesort_retbb:
	movw	r4, #184
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
bubblesort_alignbb:
	.align	2
bubblesort_gvbb:
	.word	n
	.size	bubblesort, .-bubblesort
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
	bl	bubblesort
	str	r0, [sp, #44]
	ldr	r1, [sp, #44]
	add	r2, sp, #52
	str	r1, [r2]
	b	while_block9
while_block9: 
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
	blt	while_body10
	b	while_next11
while_body10: 
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
	b	while_block9
while_next11: 
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
