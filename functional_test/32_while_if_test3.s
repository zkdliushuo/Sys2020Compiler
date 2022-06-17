@ After Enter EntryBB
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ load Instruction %6: 28
	 @ add Instruction %7: 32
	 @ load Instruction %8: 36
	 @ icmp Instruction %9: 40
	 @ alloca Instruction %10 alloc space: [40 , 44]
	 @ load Instruction %11: 48
	 @ icmp Instruction %12: 52
	 @ load Instruction %13: 56
	 @ load Instruction %14: 60
	 @ load Instruction %15: 64
	 @ add Instruction %16: 68
	 @ load Instruction %17: 72
	 @ icmp Instruction %18: 76
	 @ alloca Instruction %19 alloc space: [76 , 80]
	 @ load Instruction %20: 84
	 @ mul Instruction %21: 88
	 @ load Instruction %22: 92
	 @ mul Instruction %23: 96
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
	 @ load Instruction %2: 12
	 @ call Instruction %3: 16
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	deepWhileBr
	.arch armv8-a
	.type	deepWhileBr, %function
deepWhileBr: 
	@frame_size = 24
	@alloc = 96
	push	{r4, lr}
	sub	sp, sp, #96
	str	r0, [sp, #92]
	str	r1, [sp, #88]
	ldr	r1, [sp, #92]
	add	r2, sp, #84
	str	r1, [r2]
	ldr	r1, [sp, #88]
	add	r2, sp, #80
	str	r1, [r2]
	add	r1, sp, #84
	ldr	r3, [r1]
	str	r3, [sp, #72]
	add	r1, sp, #80
	ldr	r3, [r1]
	str	r3, [sp, #68]
	ldr	r1, [sp, #72]
	ldr	r2, [sp, #68]
	add	r3, r1, r2
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	add	r2, sp, #76
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	mov	r2, #75
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #56]
	blt	while_body1
	b	while_next2
while_body1: 
	mov	r1, #42
	add	r2, sp, #52
	str	r1, [r2]
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #48]
	ldr	r1, [sp, #48]
	mov	r2, #100
	cmp	r1, r2
	mov	r3, #0
	movlt	r3, #1
	str	r3, [sp, #44]
	blt	then_bb3
	b	if_next_bb5
while_next2: 
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #40]
	ldr	r3, [sp, #40]
	b	deepWhileBr_retbb
then_bb3: 
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #36]
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #36]
	ldr	r2, [sp, #32]
	add	r3, r1, r2
	str	r3, [sp, #28]
	ldr	r1, [sp, #28]
	add	r2, sp, #76
	str	r1, [r2]
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r1, [sp, #24]
	mov	r2, #99
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #20]
	bgt	then_bb6
	b	if_next_bb8
if_next_bb5: 
	b	while_block0
then_bb6: 
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #12]
	mov	r2, #2
	mul	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	add	r2, sp, #16
	str	r1, [r2]
if_next_bb8: 
	b	if_next_bb5
then_bb9: 
	add	r1, sp, #16
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #2
	mul	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #76
	str	r1, [r2]
	b	if_next_bb11
if_next_bb11: 
	b	if_next_bb8
deepWhileBr_retbb:
	mov	r0, r3
	add	sp, sp, #96
	pop	{r4, lr}
	bx	lr
deepWhileBr_alignbb:
	.align	2
	.size	deepWhileBr, .-deepWhileBr
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 4
	@alloc = 16
	push	{r4, lr}
	sub	sp, sp, #16
	mov	r1, #2
	add	r2, sp, #12
	str	r1, [r2]
	add	r1, sp, #12
	ldr	r3, [r1]
	str	r3, [sp, #8]
	add	r1, sp, #12
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r0, [sp, #8]
	ldr	r1, [sp, #4]
	bl	deepWhileBr
	str	r0, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #16
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
