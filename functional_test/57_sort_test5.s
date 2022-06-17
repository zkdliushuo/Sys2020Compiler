@ After Enter EntryBB
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ alloca Instruction %5 alloc space: [20 , 24]
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ load Instruction %7: 32
	 @ load Instruction %8: 36
	 @ getelementptr inbounds Instruction %9: 40
	 @ load Instruction %10: 44
	 @ load Instruction %11: 48
	 @ load Instruction %12: 52
	 @ getelementptr inbounds Instruction %13: 56
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ getelementptr inbounds Instruction %16: 68
	 @ load Instruction %17: 72
	 @ load Instruction %18: 76
	 @ load Instruction %19: 80
	 @ getelementptr inbounds Instruction %20: 84
	 @ load Instruction %21: 88
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
	 @ Arg %2 Alloc : 12
@ After Enter EntryBB
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ alloca Instruction %5 alloc space: [20 , 24]
	 @ alloca Instruction %6 alloc space: [24 , 28]
	 @ load Instruction %7: 32
	 @ alloca Instruction %8 alloc space: [32 , 36]
	 @ load Instruction %9: 40
	 @ mul Instruction %10: 44
	 @ add Instruction %11: 48
	 @ load Instruction %12: 52
	 @ load Instruction %13: 56
	 @ add Instruction %14: 60
	 @ icmp Instruction %15: 64
	 @ load Instruction %16: 68
	 @ load Instruction %17: 72
	 @ icmp Instruction %18: 76
	 @ load Instruction %19: 80
	 @ add Instruction %20: 84
	 @ load Instruction %21: 88
	 @ load Instruction %22: 92
	 @ getelementptr inbounds Instruction %23: 96
	 @ load Instruction %24: 100
	 @ load Instruction %25: 104
	 @ load Instruction %26: 108
	 @ getelementptr inbounds Instruction %27: 112
	 @ load Instruction %28: 116
	 @ icmp Instruction %29: 120
	 @ load Instruction %30: 124
	 @ load Instruction %31: 128
	 @ getelementptr inbounds Instruction %32: 132
	 @ load Instruction %33: 136
	 @ load Instruction %34: 140
	 @ add Instruction %35: 144
	 @ load Instruction %36: 148
	 @ getelementptr inbounds Instruction %37: 152
	 @ load Instruction %38: 156
	 @ icmp Instruction %39: 160
	 @ load Instruction %40: 164
	 @ getelementptr inbounds Instruction %41: 168
	 @ load Instruction %42: 172
	 @ load Instruction %43: 176
	 @ call Instruction %44: 180
	 @ load Instruction %45: 184
	 @ load Instruction %46: 188
	 @ mul Instruction %47: 192
	 @ add Instruction %48: 196
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
	 @ Arg %2 Alloc : 12
@ After Enter EntryBB
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ alloca Instruction %5 alloc space: [20 , 24]
	 @ load Instruction %6: 28
	 @ sdiv Instruction %7: 32
	 @ sub Instruction %8: 36
	 @ load Instruction %9: 40
	 @ icmp Instruction %10: 44
	 @ load Instruction %11: 48
	 @ sub Instruction %12: 52
	 @ load Instruction %13: 56
	 @ getelementptr inbounds Instruction %14: 60
	 @ load Instruction %15: 64
	 @ load Instruction %16: 68
	 @ call Instruction %17: 72
	 @ load Instruction %18: 76
	 @ sub Instruction %19: 80
	 @ load Instruction %20: 84
	 @ sub Instruction %21: 88
	 @ load Instruction %22: 92
	 @ icmp Instruction %23: 96
	 @ alloca Instruction %24 alloc space: [96 , 100]
	 @ load Instruction %25: 104
	 @ getelementptr inbounds Instruction %26: 108
	 @ load Instruction %27: 112
	 @ load Instruction %28: 116
	 @ call Instruction %29: 120
	 @ load Instruction %30: 124
	 @ sub Instruction %31: 128
	 @ load Instruction %32: 132
	 @ getelementptr inbounds Instruction %33: 136
	 @ load Instruction %34: 140
	 @ load Instruction %35: 144
	 @ call Instruction %36: 148
	 @ load Instruction %37: 152
	 @ sub Instruction %38: 156
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
	.global	swap
	.arch armv8-a
	.type	swap, %function
swap: 
	@frame_size = 22
	@alloc = 88
	push	{r4, lr}
	sub	sp, sp, #88
	str	r0, [sp, #84]
	str	r1, [sp, #80]
	str	r2, [sp, #76]
	ldr	r1, [sp, #84]
	add	r2, sp, #72
	str	r1, [r2]
	ldr	r1, [sp, #80]
	add	r2, sp, #68
	str	r1, [r2]
	ldr	r1, [sp, #76]
	add	r2, sp, #64
	str	r1, [r2]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #56]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #56]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #40]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	ldr	r2, [sp, #40]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #32]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #28]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #28]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	ldr	r2, [sp, #32]
	str	r1, [r2]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #12]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #12]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #4]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	ldr	r2, [sp, #4]
	str	r1, [r2]
	mov	r3, #0
	b	swap_retbb
swap_retbb:
	mov	r0, r3
	add	sp, sp, #88
	pop	{r4, lr}
	bx	lr
swap_alignbb:
	.align	2
	.size	swap, .-swap
	.text
	.align	2
	.global	heap_ajust
	.arch armv8-a
	.type	heap_ajust, %function
heap_ajust: 
	@frame_size = 49
	@alloc = 196
	push	{r4, lr}
	movw	r4, #196
	sub	sp, sp, r4
	movw	r4, #192
	str	r0, [sp, r4]
	movw	r4, #188
	str	r1, [sp, r4]
	movw	r4, #184
	str	r2, [sp, r4]
	movw	r1, #192
	ldr	r1, [sp, r1]
	movw	r2, #180
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #188
	ldr	r1, [sp, r1]
	movw	r2, #176
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #184
	ldr	r1, [sp, r1]
	movw	r2, #172
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #176
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #164
	str	r3, [sp, r4]
	movw	r1, #164
	ldr	r1, [sp, r1]
	movw	r2, #168
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #156
	str	r3, [sp, r4]
	movw	r1, #156
	ldr	r1, [sp, r1]
	mov	r2, #2
	mul	r3, r1, r2
	movw	r4, #152
	str	r3, [sp, r4]
	movw	r1, #152
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #148
	str	r3, [sp, r4]
	movw	r1, #148
	ldr	r1, [sp, r1]
	movw	r2, #160
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_block0: 
	movw	r1, #160
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #144
	str	r3, [sp, r4]
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #140
	str	r3, [sp, r4]
	movw	r1, #140
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #136
	str	r3, [sp, r4]
	movw	r1, #144
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
	movw	r1, #160
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #128
	str	r3, [sp, r4]
	movw	r1, #172
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #124]
	movw	r1, #128
	ldr	r1, [sp, r1]
	ldr	r2, [sp, #124]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #120]
	blt	next_and_bb6
	b	if_next_bb5
while_next2: 
	mov	r3, #0
	b	heap_ajust_retbb
then_bb3: 
	movw	r1, #160
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #116]
	ldr	r1, [sp, #116]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #112]
	ldr	r1, [sp, #112]
	movw	r2, #160
	add	r2, sp, r2
	str	r1, [r2]
	b	if_next_bb5
if_next_bb5: 
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #108]
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #104]
	ldr	r1, [sp, #104]
	ldr	r2, [sp, #108]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #100]
	ldr	r1, [sp, #100]
	ldr	r3, [r1]
	str	r3, [sp, #96]
	movw	r1, #160
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #92]
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #88]
	ldr	r1, [sp, #88]
	ldr	r2, [sp, #92]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #84]
	ldr	r1, [sp, #84]
	ldr	r3, [r1]
	str	r3, [sp, #80]
	ldr	r1, [sp, #96]
	ldr	r2, [sp, #80]
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #76]
	bgt	then_bb7
	b	else_bb8
next_and_bb6: 
	movw	r1, #160
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #72]
	movw	r1, #180
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
	movw	r1, #160
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #52]
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	ldr	r2, [sp, #52]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #60]
	ldr	r2, [sp, #40]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #36]
	blt	then_bb3
	b	if_next_bb5
then_bb7: 
	mov	r3, #0
	b	heap_ajust_retbb
else_bb8: 
	movw	r1, #180
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	add	r1, r1, #0
	str	r1, [sp, #28]
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #24]
	movw	r1, #160
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r0, [sp, #28]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #20]
	bl	swap
	str	r0, [sp, #16]
	ldr	r1, [sp, #16]
	movw	r2, #168
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #160
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	movw	r2, #168
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #168
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	mov	r2, #2
	mul	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	movw	r2, #160
	add	r2, sp, r2
	str	r1, [r2]
	b	if_next_bb9
if_next_bb9: 
	b	while_block0
heap_ajust_retbb:
	movw	r4, #196
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
heap_ajust_alignbb:
	.align	2
	.size	heap_ajust, .-heap_ajust
	.text
	.align	2
	.global	heap_sort
	.arch armv8-a
	.type	heap_sort, %function
heap_sort: 
	@frame_size = 39
	@alloc = 156
	push	{r4, lr}
	movw	r4, #156
	sub	sp, sp, r4
	movw	r4, #152
	str	r0, [sp, r4]
	movw	r4, #148
	str	r1, [sp, r4]
	movw	r1, #152
	ldr	r1, [sp, r1]
	movw	r2, #144
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #148
	ldr	r1, [sp, r1]
	movw	r2, #140
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #140
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #128
	str	r3, [sp, r4]
	movw	r0, #128
	ldr	r0, [sp, r0]
	mov	r1, #2
	bl	__aeabi_idiv
	str	r0, [sp, #124]
	ldr	r1, [sp, #124]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #120]
	ldr	r1, [sp, #120]
	movw	r2, #136
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block10
while_block10: 
	movw	r1, #136
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #116]
	ldr	r1, [sp, #116]
	mov	r2, #-1
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #112]
	bgt	while_body11
	b	while_next12
while_body11: 
	movw	r1, #140
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #108]
	ldr	r1, [sp, #108]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #104]
	ldr	r1, [sp, #104]
	movw	r2, #132
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #100]
	ldr	r1, [sp, #100]
	add	r1, r1, #0
	str	r1, [sp, #96]
	movw	r1, #136
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #92]
	movw	r1, #132
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #88]
	ldr	r0, [sp, #96]
	ldr	r1, [sp, #92]
	ldr	r2, [sp, #88]
	bl	heap_ajust
	str	r0, [sp, #84]
	ldr	r1, [sp, #84]
	movw	r2, #132
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #136
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #80]
	ldr	r1, [sp, #80]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #76]
	ldr	r1, [sp, #76]
	movw	r2, #136
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block10
while_next12: 
	movw	r1, #140
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	movw	r2, #136
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block13
while_block13: 
	movw	r1, #136
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #60]
	bgt	while_body14
	b	while_next15
while_body14: 
	mov	r1, #0
	add	r2, sp, #56
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	add	r1, r1, #0
	str	r1, [sp, #48]
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #44]
	movw	r1, #136
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r0, [sp, #48]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #40]
	bl	swap
	str	r0, [sp, #36]
	ldr	r1, [sp, #36]
	movw	r2, #132
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #136
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	movw	r2, #132
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	add	r1, r1, #0
	str	r1, [sp, #20]
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #16]
	movw	r1, #132
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r0, [sp, #20]
	ldr	r1, [sp, #16]
	ldr	r2, [sp, #12]
	bl	heap_ajust
	str	r0, [sp, #8]
	ldr	r1, [sp, #8]
	movw	r2, #132
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #136
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	movw	r2, #136
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block13
while_next15: 
	mov	r3, #0
	b	heap_sort_retbb
heap_sort_retbb:
	movw	r4, #156
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
heap_sort_alignbb:
	.align	2
	.size	heap_sort, .-heap_sort
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
	bl	heap_sort
	str	r0, [sp, #44]
	ldr	r1, [sp, #44]
	add	r2, sp, #56
	str	r1, [r2]
	b	while_block16
while_block16: 
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
	blt	while_body17
	b	while_next18
while_body17: 
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
	b	while_block16
while_next18: 
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
