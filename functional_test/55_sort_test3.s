@ After Enter EntryBB
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ alloca Instruction %5 alloc space: [20 , 24]
	 @ load Instruction %6: 28
	 @ load Instruction %7: 32
	 @ icmp Instruction %8: 36
	 @ alloca Instruction %9 alloc space: [36 , 40]
	 @ load Instruction %10: 44
	 @ alloca Instruction %11 alloc space: [44 , 48]
	 @ load Instruction %12: 52
	 @ alloca Instruction %13 alloc space: [52 , 56]
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ getelementptr inbounds Instruction %16: 68
	 @ load Instruction %17: 72
	 @ load Instruction %18: 76
	 @ load Instruction %19: 80
	 @ icmp Instruction %20: 84
	 @ load Instruction %21: 88
	 @ load Instruction %22: 92
	 @ getelementptr inbounds Instruction %23: 96
	 @ load Instruction %24: 100
	 @ alloca Instruction %25 alloc space: [100 , 104]
	 @ load Instruction %26: 108
	 @ sub Instruction %27: 112
	 @ load Instruction %28: 116
	 @ getelementptr inbounds Instruction %29: 120
	 @ load Instruction %30: 124
	 @ load Instruction %31: 128
	 @ call Instruction %32: 132
	 @ load Instruction %33: 136
	 @ add Instruction %34: 140
	 @ load Instruction %35: 144
	 @ getelementptr inbounds Instruction %36: 148
	 @ load Instruction %37: 152
	 @ load Instruction %38: 156
	 @ call Instruction %39: 160
	 @ load Instruction %40: 164
	 @ load Instruction %41: 168
	 @ icmp Instruction %42: 172
	 @ load Instruction %43: 176
	 @ sub Instruction %44: 180
	 @ load Instruction %45: 184
	 @ load Instruction %46: 188
	 @ icmp Instruction %47: 192
	 @ load Instruction %48: 196
	 @ load Instruction %49: 200
	 @ getelementptr inbounds Instruction %50: 204
	 @ load Instruction %51: 208
	 @ load Instruction %52: 212
	 @ sub Instruction %53: 216
	 @ icmp Instruction %54: 220
	 @ load Instruction %55: 224
	 @ load Instruction %56: 228
	 @ getelementptr inbounds Instruction %57: 232
	 @ load Instruction %58: 236
	 @ load Instruction %59: 240
	 @ getelementptr inbounds Instruction %60: 244
	 @ load Instruction %61: 248
	 @ load Instruction %62: 252
	 @ add Instruction %63: 256
	 @ load Instruction %64: 260
	 @ load Instruction %65: 264
	 @ icmp Instruction %66: 268
	 @ load Instruction %67: 272
	 @ add Instruction %68: 276
	 @ load Instruction %69: 280
	 @ load Instruction %70: 284
	 @ icmp Instruction %71: 288
	 @ load Instruction %72: 292
	 @ load Instruction %73: 296
	 @ getelementptr inbounds Instruction %74: 300
	 @ load Instruction %75: 304
	 @ load Instruction %76: 308
	 @ icmp Instruction %77: 312
	 @ load Instruction %78: 316
	 @ load Instruction %79: 320
	 @ getelementptr inbounds Instruction %80: 324
	 @ load Instruction %81: 328
	 @ load Instruction %82: 332
	 @ getelementptr inbounds Instruction %83: 336
	 @ load Instruction %84: 340
	 @ load Instruction %85: 344
	 @ sub Instruction %86: 348
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
	 @ Arg %2 Alloc : 12
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
	 @ alloca Instruction %12 alloc space: [84 , 88]
	 @ getelementptr inbounds Instruction %13: 92
	 @ load Instruction %14: 96
	 @ load Instruction %15: 100
	 @ call Instruction %16: 104
	 @ load Instruction %17: 108
	 @ load Instruction %18: 112
	 @ icmp Instruction %19: 116
	 @ alloca Instruction %20 alloc space: [116 , 120]
	 @ load Instruction %21: 124
	 @ getelementptr inbounds Instruction %22: 128
	 @ load Instruction %23: 132
	 @ load Instruction %24: 136
	 @ load Instruction %25: 140
	 @ load Instruction %26: 144
	 @ add Instruction %27: 148
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
	.global	QuickSort
	.arch armv8-a
	.type	QuickSort, %function
QuickSort: 
	@frame_size = 87
	@alloc = 348
	push	{r4, lr}
	movw	r4, #348
	sub	sp, sp, r4
	movw	r4, #344
	str	r0, [sp, r4]
	movw	r4, #340
	str	r1, [sp, r4]
	movw	r4, #336
	str	r2, [sp, r4]
	movw	r1, #344
	ldr	r1, [sp, r1]
	movw	r2, #332
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #340
	ldr	r1, [sp, r1]
	movw	r2, #328
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #336
	ldr	r1, [sp, r1]
	movw	r2, #324
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #328
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #320
	str	r3, [sp, r4]
	movw	r1, #324
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #316
	str	r3, [sp, r4]
	movw	r1, #320
	ldr	r1, [sp, r1]
	movw	r2, #316
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #312
	str	r3, [sp, r4]
	blt	then_bb0
	b	if_next_bb2
then_bb0: 
	movw	r1, #328
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #304
	str	r3, [sp, r4]
	movw	r1, #304
	ldr	r1, [sp, r1]
	movw	r2, #308
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #324
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #296
	str	r3, [sp, r4]
	movw	r1, #296
	ldr	r1, [sp, r1]
	movw	r2, #300
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #328
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #288
	str	r3, [sp, r4]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #284
	str	r3, [sp, r4]
	movw	r1, #284
	ldr	r1, [sp, r1]
	movw	r2, #288
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #280
	str	r3, [sp, r4]
	movw	r1, #280
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #276
	str	r3, [sp, r4]
	movw	r1, #276
	ldr	r1, [sp, r1]
	movw	r2, #292
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
if_next_bb2: 
	mov	r3, #0
	b	QuickSort_retbb
while_block3: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #272
	str	r3, [sp, r4]
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #268
	str	r3, [sp, r4]
	movw	r1, #272
	ldr	r1, [sp, r1]
	movw	r2, #268
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #264
	str	r3, [sp, r4]
	blt	while_body4
	b	while_next5
while_body4: 
	b	while_block6
while_next5: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #260
	str	r3, [sp, r4]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #256
	str	r3, [sp, r4]
	movw	r1, #256
	ldr	r1, [sp, r1]
	movw	r2, #260
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #252
	str	r3, [sp, r4]
	movw	r1, #292
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #248
	str	r3, [sp, r4]
	movw	r1, #248
	ldr	r1, [sp, r1]
	movw	r2, #252
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #240
	str	r3, [sp, r4]
	movw	r1, #240
	ldr	r1, [sp, r1]
	mov	r2, #1
	sub	r3, r1, r2
	movw	r4, #236
	str	r3, [sp, r4]
	movw	r1, #236
	ldr	r1, [sp, r1]
	movw	r2, #244
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #232
	str	r3, [sp, r4]
	movw	r1, #232
	ldr	r1, [sp, r1]
	add	r1, r1, #0
	movw	r4, #228
	str	r1, [sp, r4]
	movw	r1, #328
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #224
	str	r3, [sp, r4]
	movw	r1, #244
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #220
	str	r3, [sp, r4]
	movw	r0, #228
	ldr	r0, [sp, r0]
	movw	r1, #224
	ldr	r1, [sp, r1]
	movw	r2, #220
	ldr	r2, [sp, r2]
	bl	QuickSort
	movw	r4, #216
	str	r0, [sp, r4]
	movw	r1, #216
	ldr	r1, [sp, r1]
	movw	r2, #244
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #212
	str	r3, [sp, r4]
	movw	r1, #212
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #208
	str	r3, [sp, r4]
	movw	r1, #208
	ldr	r1, [sp, r1]
	movw	r2, #244
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #204
	str	r3, [sp, r4]
	movw	r1, #204
	ldr	r1, [sp, r1]
	add	r1, r1, #0
	movw	r4, #200
	str	r1, [sp, r4]
	movw	r1, #244
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #196
	str	r3, [sp, r4]
	movw	r1, #324
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #192
	str	r3, [sp, r4]
	movw	r0, #200
	ldr	r0, [sp, r0]
	movw	r1, #196
	ldr	r1, [sp, r1]
	movw	r2, #192
	ldr	r2, [sp, r2]
	bl	QuickSort
	movw	r4, #188
	str	r0, [sp, r4]
	movw	r1, #188
	ldr	r1, [sp, r1]
	movw	r2, #244
	add	r2, sp, r2
	str	r1, [r2]
	b	if_next_bb2
while_block6: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #184
	str	r3, [sp, r4]
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #180
	str	r3, [sp, r4]
	movw	r1, #184
	ldr	r1, [sp, r1]
	movw	r2, #180
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #176
	str	r3, [sp, r4]
	blt	next_and_bb9
	b	while_next8
while_body7: 
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #172
	str	r3, [sp, r4]
	movw	r1, #172
	ldr	r1, [sp, r1]
	mov	r2, #1
	sub	r3, r1, r2
	movw	r4, #168
	str	r3, [sp, r4]
	movw	r1, #168
	ldr	r1, [sp, r1]
	movw	r2, #300
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block6
while_next8: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #164
	str	r3, [sp, r4]
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #160
	str	r3, [sp, r4]
	movw	r1, #164
	ldr	r1, [sp, r1]
	movw	r2, #160
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #156
	str	r3, [sp, r4]
	blt	then_bb10
	b	if_next_bb12
next_and_bb9: 
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #152
	str	r3, [sp, r4]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #148
	str	r3, [sp, r4]
	movw	r1, #148
	ldr	r1, [sp, r1]
	movw	r2, #152
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #144
	str	r3, [sp, r4]
	movw	r1, #144
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #140
	str	r3, [sp, r4]
	movw	r1, #292
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #136
	str	r3, [sp, r4]
	movw	r1, #136
	ldr	r1, [sp, r1]
	mov	r2, #1
	sub	r3, r1, r2
	movw	r4, #132
	str	r3, [sp, r4]
	movw	r1, #140
	ldr	r1, [sp, r1]
	movw	r2, #132
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	movw	r4, #128
	str	r3, [sp, r4]
	bgt	while_body7
	b	while_next8
then_bb10: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #124]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #120]
	ldr	r1, [sp, #120]
	ldr	r2, [sp, #124]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #116]
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #112]
	movw	r1, #332
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
	ldr	r1, [sp, #100]
	ldr	r2, [sp, #116]
	str	r1, [r2]
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #96]
	ldr	r1, [sp, #96]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #92]
	ldr	r1, [sp, #92]
	movw	r2, #308
	add	r2, sp, r2
	str	r1, [r2]
	b	if_next_bb12
if_next_bb12: 
	b	while_block13
while_block13: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #88]
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #84]
	ldr	r1, [sp, #88]
	ldr	r2, [sp, #84]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #80]
	blt	next_and_bb16
	b	while_next15
while_body14: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #76]
	ldr	r1, [sp, #76]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	movw	r2, #308
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block13
while_next15: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #68]
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r1, [sp, #68]
	ldr	r2, [sp, #64]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #60]
	blt	then_bb17
	b	if_next_bb19
next_and_bb16: 
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #56]
	movw	r1, #332
	add	r1, sp, r1
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
	movw	r1, #292
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #40]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #36]
	blt	while_body14
	b	while_next15
then_bb17: 
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #32]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	ldr	r2, [sp, #32]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #24]
	movw	r1, #308
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #20]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #16]
	ldr	r1, [sp, #16]
	ldr	r2, [sp, #20]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #24]
	str	r1, [r2]
	movw	r1, #300
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	movw	r2, #300
	add	r2, sp, r2
	str	r1, [r2]
	b	if_next_bb19
if_next_bb19: 
	b	while_block3
QuickSort_retbb:
	movw	r4, #348
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
QuickSort_alignbb:
	.align	2
	.size	QuickSort, .-QuickSort
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 37
	@alloc = 148
	push	{r4, lr}
	movw	r4, #148
	sub	sp, sp, r4
	mov	r1, #10
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #0
	str	r1, [sp, #104]
	mov	r1, #4
	ldr	r2, [sp, #104]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #4
	str	r1, [sp, #100]
	mov	r1, #3
	ldr	r2, [sp, #100]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #8
	str	r1, [sp, #96]
	mov	r1, #9
	ldr	r2, [sp, #96]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #12
	str	r1, [sp, #92]
	mov	r1, #2
	ldr	r2, [sp, #92]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #16
	str	r1, [sp, #88]
	mov	r1, #0
	ldr	r2, [sp, #88]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #20
	str	r1, [sp, #84]
	mov	r1, #1
	ldr	r2, [sp, #84]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #24
	str	r1, [sp, #80]
	mov	r1, #6
	ldr	r2, [sp, #80]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #28
	str	r1, [sp, #76]
	mov	r1, #5
	ldr	r2, [sp, #76]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #32
	str	r1, [sp, #72]
	mov	r1, #7
	ldr	r2, [sp, #72]
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #36
	str	r1, [sp, #68]
	mov	r1, #8
	ldr	r2, [sp, #68]
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #64
	str	r1, [r2]
	mov	r1, #9
	add	r2, sp, #60
	str	r1, [r2]
	add	r1, sp, #108
	add	r1, r1, #0
	str	r1, [sp, #56]
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #52]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r0, [sp, #56]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #48]
	bl	QuickSort
	str	r0, [sp, #44]
	ldr	r1, [sp, #44]
	add	r2, sp, #64
	str	r1, [r2]
	b	while_block20
while_block20: 
	add	r1, sp, #64
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
	blt	while_body21
	b	while_next22
while_body21: 
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #24]
	add	r1, sp, #108
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
	add	r1, sp, #64
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #64
	str	r1, [r2]
	b	while_block20
while_next22: 
	mov	r3, #0
	b	main_retbb
main_retbb:
	movw	r4, #148
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	n
	.size	main, .-main
