@ After Enter EntryBB
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ getelementptr inbounds Instruction %7: 32
	 @ load Instruction %8: 36
	 @ icmp Instruction %9: 40
	 @ load Instruction %10: 44
	 @ add Instruction %11: 48
	 @ load Instruction %12: 52
	 @ load Instruction %13: 56
	 @ getelementptr inbounds Instruction %14: 60
	 @ load Instruction %15: 64
	 @ icmp Instruction %16: 68
	 @ load Instruction %17: 72
	 @ load Instruction %18: 76
	 @ getelementptr inbounds Instruction %19: 80
	 @ load Instruction %20: 84
	 @ icmp Instruction %21: 88
	 @ load Instruction %22: 92
	 @ load Instruction %23: 96
	 @ getelementptr inbounds Instruction %24: 100
	 @ load Instruction %25: 104
	 @ icmp Instruction %26: 108
	 @ load Instruction %27: 112
	 @ load Instruction %28: 116
	 @ getelementptr inbounds Instruction %29: 120
	 @ load Instruction %30: 124
	 @ icmp Instruction %31: 128
	 @ load Instruction %32: 132
	 @ add Instruction %33: 136
	 @ load Instruction %34: 140
	 @ load Instruction %35: 144
	 @ load Instruction %36: 148
	 @ getelementptr inbounds Instruction %37: 152
	 @ load Instruction %38: 156
	 @ icmp Instruction %39: 160
	 @ load Instruction %40: 164
	 @ load Instruction %41: 168
	 @ getelementptr inbounds Instruction %42: 172
	 @ load Instruction %43: 176
	 @ icmp Instruction %44: 180
	 @ load Instruction %45: 184
	 @ mul Instruction %46: 188
	 @ load Instruction %47: 192
	 @ load Instruction %48: 196
	 @ getelementptr inbounds Instruction %49: 200
	 @ load Instruction %50: 204
	 @ add Instruction %51: 208
	 @ sub Instruction %52: 212
	 @ load Instruction %53: 216
	 @ add Instruction %54: 220
	 @ load Instruction %55: 224
	 @ load Instruction %56: 228
	 @ mul Instruction %57: 232
	 @ load Instruction %58: 236
	 @ load Instruction %59: 240
	 @ getelementptr inbounds Instruction %60: 244
	 @ load Instruction %61: 248
	 @ icmp Instruction %62: 252
	 @ load Instruction %63: 256
	 @ load Instruction %64: 260
	 @ getelementptr inbounds Instruction %65: 264
	 @ load Instruction %66: 268
	 @ icmp Instruction %67: 272
	 @ Arg %0 Alloc : 4
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 2000]
	 @ alloca Instruction %1 alloc space: [2000 , 2004]
	 @ alloca Instruction %2 alloc space: [2004 , 2008]
	 @ load Instruction %3: 2012
	 @ icmp Instruction %4: 2016
	 @ call Instruction %5: 2020
	 @ load Instruction %6: 2024
	 @ getelementptr inbounds Instruction %7: 2028
	 @ load Instruction %8: 2032
	 @ load Instruction %9: 2036
	 @ add Instruction %10: 2040
	 @ load Instruction %11: 2044
	 @ getelementptr inbounds Instruction %12: 2048
	 @ getelementptr inbounds Instruction %13: 2052
	 @ call Instruction %14: 2056
	 @ load Instruction %15: 2060
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	atoi_
	.arch armv8-a
	.type	atoi_, %function
atoi_: 
	@frame_size = 68
	@alloc = 272
	push	{r4, lr}
	movw	r4, #272
	sub	sp, sp, r4
	movw	r4, #268
	str	r0, [sp, r4]
	movw	r1, #268
	ldr	r1, [sp, r1]
	movw	r2, #264
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #0
	movw	r2, #260
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #1
	movw	r2, #256
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #0
	movw	r2, #252
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_block0: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #248
	str	r3, [sp, r4]
	movw	r1, #264
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #244
	str	r3, [sp, r4]
	movw	r1, #244
	ldr	r1, [sp, r1]
	movw	r2, #248
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #240
	str	r3, [sp, r4]
	movw	r1, #240
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #236
	str	r3, [sp, r4]
	movw	r1, #236
	ldr	r1, [sp, r1]
	mov	r2, #32
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	movw	r4, #232
	str	r3, [sp, r4]
	beq	while_body1
	b	while_next2
while_body1: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #228
	str	r3, [sp, r4]
	movw	r1, #228
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #224
	str	r3, [sp, r4]
	movw	r1, #224
	ldr	r1, [sp, r1]
	movw	r2, #252
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_next2: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #220
	str	r3, [sp, r4]
	movw	r1, #264
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #216
	str	r3, [sp, r4]
	movw	r1, #216
	ldr	r1, [sp, r1]
	movw	r2, #220
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #212
	str	r3, [sp, r4]
	movw	r1, #212
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #208
	str	r3, [sp, r4]
	movw	r1, #208
	ldr	r1, [sp, r1]
	mov	r2, #43
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	movw	r4, #204
	str	r3, [sp, r4]
	beq	then_bb3
	b	next_or_bb6
then_bb3: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #200
	str	r3, [sp, r4]
	movw	r1, #264
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #196
	str	r3, [sp, r4]
	movw	r1, #196
	ldr	r1, [sp, r1]
	movw	r2, #200
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #192
	str	r3, [sp, r4]
	movw	r1, #192
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #188
	str	r3, [sp, r4]
	movw	r1, #188
	ldr	r1, [sp, r1]
	mov	r2, #45
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	movw	r4, #184
	str	r3, [sp, r4]
	beq	then_bb7
	b	if_next_bb9
else_bb4: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #180
	str	r3, [sp, r4]
	movw	r1, #264
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #176
	str	r3, [sp, r4]
	movw	r1, #176
	ldr	r1, [sp, r1]
	movw	r2, #180
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #172
	str	r3, [sp, r4]
	movw	r1, #172
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #168
	str	r3, [sp, r4]
	movw	r1, #168
	ldr	r1, [sp, r1]
	mov	r2, #48
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #164
	str	r3, [sp, r4]
	blt	then_bb10
	b	next_or_bb13
if_next_bb5: 
	b	while_block14
next_or_bb6: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #160
	str	r3, [sp, r4]
	movw	r1, #264
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #156
	str	r3, [sp, r4]
	movw	r1, #156
	ldr	r1, [sp, r1]
	movw	r2, #160
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #152
	str	r3, [sp, r4]
	movw	r1, #152
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #148
	str	r3, [sp, r4]
	movw	r1, #148
	ldr	r1, [sp, r1]
	mov	r2, #45
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	movw	r4, #144
	str	r3, [sp, r4]
	beq	then_bb3
	b	else_bb4
then_bb7: 
	mov	r1, #-1
	movw	r2, #256
	add	r2, sp, r2
	str	r1, [r2]
	b	if_next_bb9
if_next_bb9: 
	movw	r1, #252
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
	movw	r1, #136
	ldr	r1, [sp, r1]
	movw	r2, #252
	add	r2, sp, r2
	str	r1, [r2]
	b	if_next_bb5
then_bb10: 
	movw	r1, #65535
	movt	r1, #32767
	mov	r1, r1
	movw	r2, #260
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #260
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #132
	str	r3, [sp, r4]
	movw	r3, #132
	ldr	r3, [sp, r3]
	b	atoi__retbb
if_next_bb12: 
	b	if_next_bb5
next_or_bb13: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #128
	str	r3, [sp, r4]
	movw	r1, #264
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
	ldr	r1, [sp, #116]
	mov	r2, #57
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #112]
	bgt	then_bb10
	b	if_next_bb12
while_block14: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #108]
	movw	r1, #264
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
	ldr	r1, [sp, #96]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #92]
	bne	next_and_bb18
	b	while_next16
while_body15: 
	movw	r1, #260
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #88]
	ldr	r1, [sp, #88]
	mov	r2, #10
	mul	r3, r1, r2
	str	r3, [sp, #84]
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #80]
	movw	r1, #264
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #76]
	ldr	r1, [sp, #76]
	ldr	r2, [sp, #80]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #84]
	ldr	r2, [sp, #68]
	add	r3, r1, r2
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	mov	r2, #48
	sub	r3, r1, r2
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	movw	r2, #260
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	movw	r2, #252
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block14
while_next16: 
	movw	r1, #260
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #48]
	movw	r1, #256
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #48]
	ldr	r2, [sp, #44]
	mul	r3, r1, r2
	str	r3, [sp, #40]
	ldr	r3, [sp, #40]
	b	atoi__retbb
next_and_bb17: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #36]
	movw	r1, #264
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
	mov	r2, #58
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #20]
	blt	while_body15
	b	while_next16
next_and_bb18: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #16]
	movw	r1, #264
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
	ldr	r1, [sp, #4]
	mov	r2, #47
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #0]
	bgt	next_and_bb17
	b	while_next16
atoi__retbb:
	movw	r4, #272
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
atoi__alignbb:
	.align	2
	.size	atoi_, .-atoi_
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 515
	@alloc = 2060
	push	{r4, lr}
	movw	r4, #2060
	sub	sp, sp, r4
	mov	r1, #0
	add	r2, sp, #56
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #52
	str	r1, [r2]
	b	while_block19
while_block19: 
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movne	r3, #1
	str	r3, [sp, #44]
	bne	while_body20
	b	while_next21
while_body20: 
	bl	getch
	str	r0, [sp, #40]
	ldr	r1, [sp, #40]
	add	r2, sp, #56
	str	r1, [r2]
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #36]
	add	r1, sp, #60
	ldr	r2, [sp, #36]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #32]
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	ldr	r2, [sp, #32]
	str	r1, [r2]
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	add	r2, sp, #52
	str	r1, [r2]
	b	while_block19
while_next21: 
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #16]
	add	r1, sp, #60
	ldr	r2, [sp, #16]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #12]
	mov	r1, #0
	ldr	r2, [sp, #12]
	str	r1, [r2]
	add	r1, sp, #60
	add	r1, r1, #0
	str	r1, [sp, #8]
	ldr	r0, [sp, #8]
	bl	atoi_
	str	r0, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #52
	str	r1, [r2]
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	movw	r4, #2060
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
