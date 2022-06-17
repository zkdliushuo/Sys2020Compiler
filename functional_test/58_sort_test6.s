@ After Enter EntryBB
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ alloca Instruction %5 alloc space: [20 , 24]
	 @ alloca Instruction %6 alloc space: [24 , 64]
	 @ alloca Instruction %7 alloc space: [64 , 68]
	 @ alloca Instruction %8 alloc space: [68 , 72]
	 @ alloca Instruction %9 alloc space: [72 , 76]
	 @ load Instruction %10: 80
	 @ icmp Instruction %11: 84
	 @ load Instruction %12: 88
	 @ getelementptr inbounds Instruction %13: 92
	 @ load Instruction %14: 96
	 @ add Instruction %15: 100
	 @ load Instruction %16: 104
	 @ load Instruction %17: 108
	 @ icmp Instruction %18: 112
	 @ load Instruction %19: 116
	 @ load Instruction %20: 120
	 @ getelementptr inbounds Instruction %21: 124
	 @ load Instruction %22: 128
	 @ getelementptr inbounds Instruction %23: 132
	 @ load Instruction %24: 136
	 @ load Instruction %25: 140
	 @ getelementptr inbounds Instruction %26: 144
	 @ load Instruction %27: 148
	 @ getelementptr inbounds Instruction %28: 152
	 @ load Instruction %29: 156
	 @ add Instruction %30: 160
	 @ load Instruction %31: 164
	 @ add Instruction %32: 168
	 @ load Instruction %33: 172
	 @ icmp Instruction %34: 176
	 @ load Instruction %35: 180
	 @ getelementptr inbounds Instruction %36: 184
	 @ load Instruction %37: 188
	 @ getelementptr inbounds Instruction %38: 192
	 @ load Instruction %39: 196
	 @ load Instruction %40: 200
	 @ sub Instruction %41: 204
	 @ getelementptr inbounds Instruction %42: 208
	 @ load Instruction %43: 212
	 @ add Instruction %44: 216
	 @ load Instruction %45: 220
	 @ add Instruction %46: 224
	 @ load Instruction %47: 228
	 @ load Instruction %48: 232
	 @ icmp Instruction %49: 236
	 @ load Instruction %50: 240
	 @ sub Instruction %51: 244
	 @ load Instruction %52: 248
	 @ getelementptr inbounds Instruction %53: 252
	 @ load Instruction %54: 256
	 @ getelementptr inbounds Instruction %55: 260
	 @ load Instruction %56: 264
	 @ sub Instruction %57: 268
	 @ load Instruction %58: 272
	 @ getelementptr inbounds Instruction %59: 276
	 @ load Instruction %60: 280
	 @ getelementptr inbounds Instruction %61: 284
	 @ load Instruction %62: 288
	 @ sub Instruction %63: 292
	 @ load Instruction %64: 296
	 @ sub Instruction %65: 300
	 @ load Instruction %66: 304
	 @ getelementptr inbounds Instruction %67: 308
	 @ load Instruction %68: 312
	 @ getelementptr inbounds Instruction %69: 316
	 @ load Instruction %70: 320
	 @ load Instruction %71: 324
	 @ getelementptr inbounds Instruction %72: 328
	 @ load Instruction %73: 332
	 @ sub Instruction %74: 336
	 @ load Instruction %75: 340
	 @ getelementptr inbounds Instruction %76: 344
	 @ load Instruction %77: 348
	 @ load Instruction %78: 352
	 @ sub Instruction %79: 356
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
	 @ alloca Instruction %12 alloc space: [84 , 124]
	 @ getelementptr inbounds Instruction %13: 128
	 @ getelementptr inbounds Instruction %14: 132
	 @ load Instruction %15: 136
	 @ call Instruction %16: 140
	 @ load Instruction %17: 144
	 @ load Instruction %18: 148
	 @ icmp Instruction %19: 152
	 @ alloca Instruction %20 alloc space: [152 , 156]
	 @ load Instruction %21: 160
	 @ getelementptr inbounds Instruction %22: 164
	 @ load Instruction %23: 168
	 @ load Instruction %24: 172
	 @ load Instruction %25: 176
	 @ load Instruction %26: 180
	 @ add Instruction %27: 184
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
	.global	counting_sort
	.arch armv8-a
	.type	counting_sort, %function
counting_sort: 
	@frame_size = 89
	@alloc = 356
	push	{r4, lr}
	movw	r4, #356
	sub	sp, sp, r4
	movw	r4, #352
	str	r0, [sp, r4]
	movw	r4, #348
	str	r1, [sp, r4]
	movw	r4, #344
	str	r2, [sp, r4]
	movw	r1, #352
	ldr	r1, [sp, r1]
	movw	r2, #340
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #348
	ldr	r1, [sp, r1]
	movw	r2, #336
	add	r2, sp, r2
	str	r1, [r2]
	movw	r1, #344
	ldr	r1, [sp, r1]
	movw	r2, #332
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #0
	movw	r2, #280
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #0
	movw	r2, #288
	add	r2, sp, r2
	str	r1, [r2]
	mov	r1, #0
	movw	r2, #284
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_block0: 
	movw	r1, #280
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #276
	str	r3, [sp, r4]
	movw	r1, #276
	ldr	r1, [sp, r1]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #272
	str	r3, [sp, r4]
	blt	while_body1
	b	while_next2
while_body1: 
	movw	r1, #280
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #268
	str	r3, [sp, r4]
	movw	r1, #292
	add	r1, sp, r1
	movw	r2, #268
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #264
	str	r3, [sp, r4]
	mov	r1, #0
	movw	r2, #264
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #280
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #260
	str	r3, [sp, r4]
	movw	r1, #260
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #256
	str	r3, [sp, r4]
	movw	r1, #256
	ldr	r1, [sp, r1]
	movw	r2, #280
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block0
while_next2: 
	b	while_block3
while_block3: 
	movw	r1, #288
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #252
	str	r3, [sp, r4]
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #248
	str	r3, [sp, r4]
	movw	r1, #252
	ldr	r1, [sp, r1]
	movw	r2, #248
	ldr	r2, [sp, r2]
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #244
	str	r3, [sp, r4]
	blt	while_body4
	b	while_next5
while_body4: 
	movw	r1, #288
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #240
	str	r3, [sp, r4]
	movw	r1, #340
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #236
	str	r3, [sp, r4]
	movw	r1, #236
	ldr	r1, [sp, r1]
	movw	r2, #240
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #232
	str	r3, [sp, r4]
	movw	r1, #232
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #228
	str	r3, [sp, r4]
	movw	r1, #292
	add	r1, sp, r1
	movw	r2, #228
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #224
	str	r3, [sp, r4]
	movw	r1, #288
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #220
	str	r3, [sp, r4]
	movw	r1, #340
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
	movw	r1, #292
	add	r1, sp, r1
	movw	r2, #208
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #204
	str	r3, [sp, r4]
	movw	r1, #204
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #200
	str	r3, [sp, r4]
	movw	r1, #200
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #196
	str	r3, [sp, r4]
	movw	r1, #196
	ldr	r1, [sp, r1]
	movw	r2, #224
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #288
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #192
	str	r3, [sp, r4]
	movw	r1, #192
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #188
	str	r3, [sp, r4]
	movw	r1, #188
	ldr	r1, [sp, r1]
	movw	r2, #288
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block3
while_next5: 
	mov	r1, #1
	movw	r2, #280
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block6
while_block6: 
	movw	r1, #280
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #184
	str	r3, [sp, r4]
	movw	r1, #184
	ldr	r1, [sp, r1]
	mov	r2, #10
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	movw	r4, #180
	str	r3, [sp, r4]
	blt	while_body7
	b	while_next8
while_body7: 
	movw	r1, #280
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #176
	str	r3, [sp, r4]
	movw	r1, #292
	add	r1, sp, r1
	movw	r2, #176
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #172
	str	r3, [sp, r4]
	movw	r1, #280
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #168
	str	r3, [sp, r4]
	movw	r1, #292
	add	r1, sp, r1
	movw	r2, #168
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #164
	str	r3, [sp, r4]
	movw	r1, #164
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #160
	str	r3, [sp, r4]
	movw	r1, #280
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #156
	str	r3, [sp, r4]
	movw	r1, #156
	ldr	r1, [sp, r1]
	mov	r2, #1
	sub	r3, r1, r2
	movw	r4, #152
	str	r3, [sp, r4]
	movw	r1, #292
	add	r1, sp, r1
	movw	r2, #152
	ldr	r2, [sp, r2]
	lsl	r2, r2, #2
	add	r3, r1, r2
	movw	r4, #148
	str	r3, [sp, r4]
	movw	r1, #148
	ldr	r1, [sp, r1]
	ldr	r3, [r1]
	movw	r4, #144
	str	r3, [sp, r4]
	movw	r1, #160
	ldr	r1, [sp, r1]
	movw	r2, #144
	ldr	r2, [sp, r2]
	add	r3, r1, r2
	movw	r4, #140
	str	r3, [sp, r4]
	movw	r1, #140
	ldr	r1, [sp, r1]
	movw	r2, #172
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #280
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #136
	str	r3, [sp, r4]
	movw	r1, #136
	ldr	r1, [sp, r1]
	mov	r2, #1
	add	r3, r1, r2
	movw	r4, #132
	str	r3, [sp, r4]
	movw	r1, #132
	ldr	r1, [sp, r1]
	movw	r2, #280
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block6
while_next8: 
	movw	r1, #332
	add	r1, sp, r1
	ldr	r3, [r1]
	movw	r4, #128
	str	r3, [sp, r4]
	movw	r1, #128
	ldr	r1, [sp, r1]
	movw	r2, #284
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block9
while_block9: 
	movw	r1, #284
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #124]
	ldr	r1, [sp, #124]
	mov	r2, #0
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #120]
	bgt	while_body10
	b	while_next11
while_body10: 
	movw	r1, #284
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #116]
	ldr	r1, [sp, #116]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #112]
	movw	r1, #340
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
	movw	r1, #292
	add	r1, sp, r1
	ldr	r2, [sp, #100]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #96]
	movw	r1, #284
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #92]
	ldr	r1, [sp, #92]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #88]
	movw	r1, #340
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #84]
	ldr	r1, [sp, #84]
	ldr	r2, [sp, #88]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #80]
	ldr	r1, [sp, #80]
	ldr	r3, [r1]
	str	r3, [sp, #76]
	movw	r1, #292
	add	r1, sp, r1
	ldr	r2, [sp, #76]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #72]
	ldr	r1, [sp, #72]
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #68]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	ldr	r2, [sp, #96]
	str	r1, [r2]
	movw	r1, #284
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #56]
	movw	r1, #340
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
	ldr	r2, [sp, #44]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #40]
	ldr	r1, [sp, #40]
	ldr	r3, [r1]
	str	r3, [sp, #36]
	movw	r1, #336
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #36]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #28]
	movw	r1, #284
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #20]
	movw	r1, #340
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
	ldr	r2, [sp, #28]
	str	r1, [r2]
	movw	r1, #284
	add	r1, sp, r1
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	movw	r2, #284
	add	r2, sp, r2
	str	r1, [r2]
	b	while_block9
while_next11: 
	mov	r3, #0
	b	counting_sort_retbb
counting_sort_retbb:
	movw	r4, #356
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
counting_sort_alignbb:
	.align	2
	.size	counting_sort, .-counting_sort
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 46
	@alloc = 184
	push	{r4, lr}
	movw	r4, #184
	sub	sp, sp, r4
	mov	r1, #10
	adrl	r2, main_gvbb+0
	ldr	r2, [r2]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #0
	movw	r4, #140
	str	r1, [sp, r4]
	mov	r1, #4
	movw	r2, #140
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #4
	movw	r4, #136
	str	r1, [sp, r4]
	mov	r1, #3
	movw	r2, #136
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #8
	movw	r4, #132
	str	r1, [sp, r4]
	mov	r1, #9
	movw	r2, #132
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #12
	movw	r4, #128
	str	r1, [sp, r4]
	mov	r1, #2
	movw	r2, #128
	ldr	r2, [sp, r2]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #16
	str	r1, [sp, #124]
	mov	r1, #0
	ldr	r2, [sp, #124]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #20
	str	r1, [sp, #120]
	mov	r1, #1
	ldr	r2, [sp, #120]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #24
	str	r1, [sp, #116]
	mov	r1, #6
	ldr	r2, [sp, #116]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #28
	str	r1, [sp, #112]
	mov	r1, #5
	ldr	r2, [sp, #112]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #32
	str	r1, [sp, #108]
	mov	r1, #7
	ldr	r2, [sp, #108]
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #36
	str	r1, [sp, #104]
	mov	r1, #8
	ldr	r2, [sp, #104]
	str	r1, [r2]
	mov	r1, #0
	add	r2, sp, #100
	str	r1, [r2]
	movw	r1, #144
	add	r1, sp, r1
	add	r1, r1, #0
	str	r1, [sp, #56]
	add	r1, sp, #60
	add	r1, r1, #0
	str	r1, [sp, #52]
	adrl	r1, main_gvbb+0
	ldr	r1, [r1]
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r0, [sp, #56]
	ldr	r1, [sp, #52]
	ldr	r2, [sp, #48]
	bl	counting_sort
	str	r0, [sp, #44]
	ldr	r1, [sp, #44]
	add	r2, sp, #100
	str	r1, [r2]
	b	while_block12
while_block12: 
	add	r1, sp, #100
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
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #24]
	add	r1, sp, #60
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
	add	r1, sp, #100
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #100
	str	r1, [r2]
	b	while_block12
while_next14: 
	mov	r3, #0
	b	main_retbb
main_retbb:
	movw	r4, #184
	mov	r0, r3
	add	sp, sp, r4
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
main_gvbb:
	.word	n
	.size	main, .-main
