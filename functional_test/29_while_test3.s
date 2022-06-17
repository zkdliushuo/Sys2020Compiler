@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ icmp Instruction %5: 24
	 @ load Instruction %6: 28
	 @ add Instruction %7: 32
	 @ load Instruction %8: 36
	 @ load Instruction %9: 40
	 @ load Instruction %10: 44
	 @ add Instruction %11: 48
	 @ add Instruction %12: 52
	 @ load Instruction %13: 56
	 @ add Instruction %14: 60
	 @ load Instruction %15: 64
	 @ load Instruction %16: 68
	 @ add Instruction %17: 72
	 @ load Instruction %18: 76
	 @ sub Instruction %19: 80
	 @ load Instruction %20: 84
	 @ add Instruction %21: 88
	 @ sub Instruction %22: 92
	 @ load Instruction %23: 96
	 @ icmp Instruction %24: 100
	 @ load Instruction %25: 104
	 @ add Instruction %26: 108
	 @ load Instruction %27: 112
	 @ sub Instruction %28: 116
	 @ load Instruction %29: 120
	 @ icmp Instruction %30: 124
	 @ load Instruction %31: 128
	 @ sub Instruction %32: 132
	 @ load Instruction %33: 136
	 @ add Instruction %34: 140
	 @ load Instruction %35: 144
	 @ icmp Instruction %36: 148
	 @ load Instruction %37: 152
	 @ add Instruction %38: 156
	 @ load Instruction %39: 160
	 @ sub Instruction %40: 164
	 @ load Instruction %41: 168
	 @ icmp Instruction %42: 172
	 @ load Instruction %43: 176
	 @ sub Instruction %44: 180
	 @ load Instruction %45: 184
	 @ add Instruction %46: 188
	 @ load Instruction %47: 192
	 @ icmp Instruction %48: 196
	 @ load Instruction %49: 200
	 @ sub Instruction %50: 204
	 @ load Instruction %51: 208
	 @ add Instruction %52: 212
	 @ load Instruction %53: 216
	 @ icmp Instruction %54: 220
	 @ load Instruction %55: 224
	 @ add Instruction %56: 228
	 @ load Instruction %57: 232
	 @ sub Instruction %58: 236
	 @ load Instruction %59: 240
	 @ icmp Instruction %60: 244
	 @ load Instruction %61: 248
	 @ add Instruction %62: 252
	 @ load Instruction %63: 256
	 @ sub Instruction %64: 260
@ After Enter EntryBB
	 @ call Instruction %0: 4
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.global g 
	.data
	.align	2
	.type	g, %object
	.size	g, 4 
g:
	.word	0
	.global h 
	.data
	.align	2
	.type	h, %object
	.size	h, 4 
h:
	.word	0
	.global f 
	.data
	.align	2
	.type	f, %object
	.size	f, 4 
f:
	.word	0
	.global e 
	.data
	.align	2
	.type	e, %object
	.size	e, 4 
e:
	.word	0
	.text
	.align	2
	.global	EightWhile
	.arch armv8-a
	.type	EightWhile, %function
EightWhile: 
	@frame_size = 65
	@alloc = 260
	push	{r4, lr}
	movw	r4, #260
	sub	sp, sp, r4
	mov	r1, #5
	movw	r2, #256
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #6
	movw	r2, #252
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #7
	movw	r2, #248
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #10
	movw	r2, #244
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_block0: 
	movw	r1, #256
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #240
	str	r3, [sp, r4]
	movw	r1, #240
	ldr	r1, [sp, r1]
	mov	r2, #20
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #236
	str	r3, [sp, r4]
	blt	while_body1
	b	while_next2
while_body1: 
	movw	r1, #256
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #232
	str	r3, [sp, r4]
	movw	r1, #232
	ldr	r1, [sp, r1]
	mov	r2, #3
	add	r3, r1, r2
	movw	r4, #228
	str	r3, [sp, r4]
	movw	r1, #228
	ldr	r1, [sp, r1]
	movw	r2, #256
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
while_next2: 
	movw	r1, #256
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #224
	str	r3, [sp, r4]
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #220
	str	r3, [sp, r4]
	movw	r1, #244
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #216
	str	r3, [sp, r4]
	movw	r1, #220
	ldr	r1, [sp, r1]
	movw	r2, #216
	ldr	r2, [sp, r2]
	add	r3, r1, r2
	movw	r4, #212
	str	r3, [sp, r4]
	movw	r1, #224
	ldr	r1, [sp, r1]
	movw	r2, #212
	ldr	r2, [sp, r2]
	add	r3, r1, r2
	movw	r4, #208
	str	r3, [sp, r4]
	movw	r1, #248
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #204
	str	r3, [sp, r4]
	movw	r1, #208
	ldr	r1, [sp, r1]
	movw	r2, #204
	ldr	r2, [sp, r2]
	add	r3, r1, r2
	movw	r4, #200
	str	r3, [sp, r4]
	adrl	r1, EightWhile_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	movw	r4, #196
	str	r3, [sp, r4]
	movw	r1, #244
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #192
	str	r3, [sp, r4]
	movw	r1, #196
	ldr	r1, [sp, r1]
	movw	r2, #192
	ldr	r2, [sp, r2]
	add	r3, r1, r2
	movw	r4, #188
	str	r3, [sp, r4]
	adrl	r1, EightWhile_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	movw	r4, #184
	str	r3, [sp, r4]
	movw	r1, #188
	ldr	r1, [sp, r1]
	movw	r2, #184
	ldr	r2, [sp, r2]
	sub	r3, r1, r2
	movw	r4, #180
	str	r3, [sp, r4]
	adrl	r1, EightWhile_gvbb+8
	ldr	r1, [r1]
	ldr	r3, [r1]
	movw	r4, #176
	str	r3, [sp, r4]
	movw	r1, #180
	ldr	r1, [sp, r1]
	movw	r2, #176
	ldr	r2, [sp, r2]
	add	r3, r1, r2
	movw	r4, #172
	str	r3, [sp, r4]
	movw	r1, #200
	ldr	r1, [sp, r1]
	movw	r2, #172
	ldr	r2, [sp, r2]
	sub	r3, r1, r2
	movw	r4, #168
	str	r3, [sp, r4]
	movw	r3, #168
	ldr	r3, [sp, r3]
	b	EightWhile_retbb
while_block3: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #164
	str	r3, [sp, r4]
	movw	r1, #164
	ldr	r1, [sp, r1]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #160
	str	r3, [sp, r4]
	blt	while_body4
	b	while_next5
while_body4: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #156
	str	r3, [sp, r4]
	movw	r1, #156
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #152
	str	r3, [sp, r4]
	movw	r1, #152
	ldr	r1, [sp, r1]
	movw	r2, #252
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block6
while_next5: 
	movw	r1, #252
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #148
	str	r3, [sp, r4]
	movw	r1, #148
	ldr	r1, [sp, r1]
	mov	r2, #2
	sub	r3, r1, r2
	movw	r4, #144
	str	r3, [sp, r4]
	movw	r1, #144
	ldr	r1, [sp, r1]
	movw	r2, #252
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_block6: 
	movw	r1, #248
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #140
	str	r3, [sp, r4]
	movw	r1, #140
	ldr	r1, [sp, r1]
	mov	r2, #7
	cmp	r1, r2
	mov	r3, #0
	moveq	r3, #1
	movw	r4, #136
	str	r3, [sp, r4]
	beq	while_body7
	b	while_next8
while_body7: 
	movw	r1, #248
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #132
	str	r3, [sp, r4]
	movw	r1, #132
	ldr	r1, [sp, r1]
	mov	r2, #1
	sub	r3, r1, r2
	movw	r4, #128
	str	r3, [sp, r4]
	movw	r1, #128
	ldr	r1, [sp, r1]
	movw	r2, #248
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block9
while_next8: 
	movw	r1, #248
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #124]
	ldr	r1, [sp, #124]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #120]
	ldr	r1, [sp, #120]
	movw	r2, #248
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
while_block9: 
	movw	r1, #244
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #116]
	ldr	r1, [sp, #116]
	mov	r2, #20
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #112]
	blt	while_body10
	b	while_next11
while_body10: 
	movw	r1, #244
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #108]
	ldr	r1, [sp, #108]
	mov	r2, #3
	add	r3, r1, r2
	str	r3, [sp, #104]
	ldr	r1, [sp, #104]
	movw	r2, #244
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block12
while_next11: 
	movw	r1, #244
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #100]
	ldr	r1, [sp, #100]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #96]
	ldr	r1, [sp, #96]
	movw	r2, #244
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block6
while_block12: 
	adrl	r1, EightWhile_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #92]
	ldr	r1, [sp, #92]
	mov	r2, #1
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #88]
	bgt	while_body13
	b	while_next14
while_body13: 
	adrl	r1, EightWhile_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #84]
	ldr	r1, [sp, #84]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #80]
	ldr	r1, [sp, #80]
	adrl	r2, EightWhile_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block15
while_next14: 
	adrl	r1, EightWhile_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #76]
	ldr	r1, [sp, #76]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	adrl	r2, EightWhile_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block9
while_block15: 
	adrl	r1, EightWhile_gvbb+12
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	mov	r2, #2
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #64]
	bgt	while_body16
	b	while_next17
while_body16: 
	adrl	r1, EightWhile_gvbb+12
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	mov	r2, #2
	sub	r3, r1, r2
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	adrl	r2, EightWhile_gvbb+12
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block18
while_next17: 
	adrl	r1, EightWhile_gvbb+12
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #52]
	ldr	r1, [sp, #52]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	adrl	r2, EightWhile_gvbb+12
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block12
while_block18: 
	adrl	r1, EightWhile_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	mov	r2, #3
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #40]
	blt	while_body19
	b	while_next20
while_body19: 
	adrl	r1, EightWhile_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #36]
	ldr	r1, [sp, #36]
	mov	r2, #10
	add	r3, r1, r2
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	adrl	r2, EightWhile_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block21
while_next20: 
	adrl	r1, EightWhile_gvbb+4
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	mov	r2, #8
	sub	r3, r1, r2
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	adrl	r2, EightWhile_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block15
while_block21: 
	adrl	r1, EightWhile_gvbb+8
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #16]
	blt	while_body22
	b	while_next23
while_body22: 
	adrl	r1, EightWhile_gvbb+8
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #8
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	adrl	r2, EightWhile_gvbb+8
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block21
while_next23: 
	adrl	r1, EightWhile_gvbb+8
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	adrl	r2, EightWhile_gvbb+8
	ldr	r2, [r2]
	str	r1, [r2]
	b	while_block18
EightWhile_retbb:
	movw	r4, #260
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
EightWhile_alignbb:
	.align	2
EightWhile_gvbb:
	.word	e
	.word	g
	.word	h
	.word	f
	.size	EightWhile, .-EightWhile
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 1
	@alloc = 4
	push	{r4, lr}
	sub	sp, sp, #4
	mov	r1, #1
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	mov	r1, #2
	adrl	r2, main_gvbb+4
	ldr	r2, [r2]
	str	r1, [r2]
	mov	r1, #4
	adrl	r2, main_gvbb+8
	ldr	r2, [r2]
	str	r1, [r2]
	mov	r1, #6
	adrl	r2, main_gvbb+12
	ldr	r2, [r2]
	str	r1, [r2]
	bl	EightWhile
	str	r0, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	g
	.word	h
	.word	e
	.word	f
	.size	main, .-main
