@ After Enter EntryBB
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ alloca Instruction %5 alloc space: [20 , 24]
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ load Instruction %7: 32
	 @ load Instruction %8: 36
	 @ sub Instruction %9: 40
	 @ icmp Instruction %10: 44
	 @ load Instruction %11: 48
	 @ load Instruction %12: 52
	 @ add Instruction %13: 56
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ icmp Instruction %16: 68
	 @ load Instruction %17: 72
	 @ load Instruction %18: 76
	 @ getelementptr inbounds Instruction %19: 80
	 @ load Instruction %20: 84
	 @ load Instruction %21: 88
	 @ load Instruction %22: 92
	 @ getelementptr inbounds Instruction %23: 96
	 @ load Instruction %24: 100
	 @ icmp Instruction %25: 104
	 @ load Instruction %26: 108
	 @ load Instruction %27: 112
	 @ icmp Instruction %28: 116
	 @ load Instruction %29: 120
	 @ load Instruction %30: 124
	 @ add Instruction %31: 128
	 @ alloca Instruction %32 alloc space: [128 , 132]
	 @ load Instruction %33: 136
	 @ load Instruction %34: 140
	 @ getelementptr inbounds Instruction %35: 144
	 @ load Instruction %36: 148
	 @ load Instruction %37: 152
	 @ load Instruction %38: 156
	 @ getelementptr inbounds Instruction %39: 160
	 @ load Instruction %40: 164
	 @ load Instruction %41: 168
	 @ getelementptr inbounds Instruction %42: 172
	 @ load Instruction %43: 176
	 @ load Instruction %44: 180
	 @ load Instruction %45: 184
	 @ getelementptr inbounds Instruction %46: 188
	 @ load Instruction %47: 192
	 @ load Instruction %48: 196
	 @ add Instruction %49: 200
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
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
	 @ load Instruction %13: 92
	 @ call Instruction %14: 96
	 @ load Instruction %15: 100
	 @ load Instruction %16: 104
	 @ icmp Instruction %17: 108
	 @ alloca Instruction %18 alloc space: [108 , 112]
	 @ load Instruction %19: 116
	 @ getelementptr inbounds Instruction %20: 120
	 @ load Instruction %21: 124
	 @ load Instruction %22: 128
	 @ load Instruction %23: 132
	 @ load Instruction %24: 136
	 @ add Instruction %25: 140
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
	.global	select_sort
	.arch armv8-a
	.type	select_sort, %function
select_sort: 
	@frame_size = 50
	@alloc = 200
	push	{r4, lr}
	movw	r4, #200
	sub	sp, sp, r4
	movw	r4, #196
	str	r0, [sp, r4]
	movw	r4, #192
	str	r1, [sp, r4]
	movw	r1, #196
	ldr	r1, [sp, r1]
	movw	r2, #188
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #192
	ldr	r1, [sp, r1]
	movw	r2, #184
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #0
	movw	r2, #180
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_block0: 
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #168
	str	r3, [sp, r4]
	movw	r1, #184
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #164
	str	r3, [sp, r4]
	movw	r1, #164
	ldr	r1, [sp, r1]
	mov	r2, #1
	sub	r3, r1, r2
	movw	r4, #160
	str	r3, [sp, r4]
	movw	r1, #168
	ldr	r1, [sp, r1]
	movw	r2, #160
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #156
	str	r3, [sp, r4]
	blt	while_body1
	b	while_next2
while_body1: 
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #152
	str	r3, [sp, r4]
	movw	r1, #152
	ldr	r1, [sp, r1]
	movw	r2, #172
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #148
	str	r3, [sp, r4]
	movw	r1, #148
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #144
	str	r3, [sp, r4]
	movw	r1, #144
	ldr	r1, [sp, r1]
	movw	r2, #176
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
while_next2: 
	mov	r3, #0
	b	select_sort_retbb
while_block3: 
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #140
	str	r3, [sp, r4]
	movw	r1, #184
	add	r1, sp, r1
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
	blt	while_body4
	b	while_next5
while_body4: 
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #128
	str	r3, [sp, r4]
	movw	r1, #188
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #124]
	ldr	r1, [sp, #124]
	movw	r2, #128
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #120]
	ldr	r1, [sp, #120]
	ldr	r3, [r1]
	str	r3, [sp, #116]
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #112]
	movw	r1, #188
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #108]
	ldr	r1, [sp, #108]
	ldr	r2, [sp, #112]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #104]
	ldr	r1, [sp, #104]
	ldr	r3, [r1]
	str	r3, [sp, #100]
	ldr	r1, [sp, #116]
	ldr	r2, [sp, #100]
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #96]
	bgt	then_bb6
	b	if_next_bb8
while_next5: 
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #92]
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #88]
	ldr	r1, [sp, #92]
	ldr	r2, [sp, #88]
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #84]
	bne	then_bb9
	b	if_next_bb11
then_bb6: 
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #80]
	ldr	r1, [sp, #80]
	movw	r2, #172
	add	r2, sp, r2
	str	r1, [r2]
	b	if_next_bb8
if_next_bb8: 
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #76]
	ldr	r1, [sp, #76]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	movw	r2, #176
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
then_bb9: 
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #64]
	movw	r1, #188
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	ldr	r2, [sp, #64]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	ldr	r3, [r1]
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	add	r2, sp, #68
	str	r1, [r2]
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #48]
	movw	r1, #188
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #48]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #40]
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #36]
	movw	r1, #188
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
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #20]
	movw	r1, #188
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	ldr	r2, [sp, #20]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #12]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #12]
	str	r1, [r2]
	b	if_next_bb11
if_next_bb11: 
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	movw	r2, #180
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
select_sort_retbb:
	movw	r4, #200
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
select_sort_alignbb:
	.align	2
	.size	select_sort, .-select_sort
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 35
	@alloc = 140
	push	{r4, lr}
	movw	r4, #140
	sub	sp, sp, r4
	mov	r1, #10
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #0
	str	r1, [sp, #96]
	mov	r1, #4
	ldr	r2, [sp, #96]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #4
	str	r1, [sp, #92]
	mov	r1, #3
	ldr	r2, [sp, #92]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #8
	str	r1, [sp, #88]
	mov	r1, #9
	ldr	r2, [sp, #88]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #12
	str	r1, [sp, #84]
	mov	r1, #2
	ldr	r2, [sp, #84]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #16
	str	r1, [sp, #80]
	mov	r1, #0
	ldr	r2, [sp, #80]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #20
	str	r1, [sp, #76]
	mov	r1, #1
	ldr	r2, [sp, #76]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #24
	str	r1, [sp, #72]
	mov	r1, #6
	ldr	r2, [sp, #72]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #28
	str	r1, [sp, #68]
	mov	r1, #5
	ldr	r2, [sp, #68]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #32
	str	r1, [sp, #64]
	mov	r1, #7
	ldr	r2, [sp, #64]
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #36
	str	r1, [sp, #60]
	mov	r1, #8
	ldr	r2, [sp, #60]
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #56
	str	r1, [r2]
	add	r1, sp, #100
	add	r1, r1, #0
	str	r1, [sp, #52]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r0, [sp, #52]
	ldr	r1, [sp, #48]
	bl	select_sort
	str	r0, [sp, #44]
	ldr	r1, [sp, #44]
	add	r2, sp, #56
	str	r1, [r2]
	b	while_block12
while_block12: 
	add	r1, sp, #56
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
	blt	while_body13
	b	while_next14
while_body13: 
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #24]
	add	r1, sp, #100
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
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #56
	str	r1, [r2]
	b	while_block12
while_next14: 
	mov	r3, #0
	b	main_retbb
main_retbb:
	movw	r4, #140
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	n
	.size	main, .-main
