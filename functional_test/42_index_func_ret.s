@ After Enter EntryBB
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ alloca Instruction %4 alloc space: [16 , 20]
	 @ load Instruction %5: 24
	 @ sub Instruction %6: 28
	 @ load Instruction %7: 32
	 @ icmp Instruction %8: 36
	 @ load Instruction %9: 40
	 @ load Instruction %10: 44
	 @ getelementptr inbounds Instruction %11: 48
	 @ load Instruction %12: 52
	 @ load Instruction %13: 56
	 @ icmp Instruction %14: 60
	 @ load Instruction %15: 64
	 @ load Instruction %16: 68
	 @ load Instruction %17: 72
	 @ getelementptr inbounds Instruction %18: 76
	 @ load Instruction %19: 80
	 @ load Instruction %20: 84
	 @ sub Instruction %21: 88
	 @ Arg %0 Alloc : 4
	 @ Arg %1 Alloc : 8
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 12]
	 @ getelementptr inbounds Instruction %1: 16
	 @ getelementptr inbounds Instruction %2: 20
	 @ getelementptr inbounds Instruction %3: 24
	 @ alloca Instruction %4 alloc space: [24 , 28]
	 @ getelementptr inbounds Instruction %5: 32
	 @ call Instruction %6: 36
	 @ getelementptr inbounds Instruction %7: 40
	 @ load Instruction %8: 44
	 @ load Instruction %9: 48
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	_getMaxOfAll
	.arch armv8-a
	.type	_getMaxOfAll, %function
_getMaxOfAll: 
	@frame_size = 22
	@alloc = 88
	push	{r4, lr}
	sub	sp, sp, #88
	str	r0, [sp, #84]
	str	r1, [sp, #80]
	ldr	r1, [sp, #84]
	add	r2, sp, #76
	str	r1, [r2]
	ldr	r1, [sp, #80]
	add	r2, sp, #72
	str	r1, [r2]
	movw	r1, #48577
	movt	r1, #65520
	mov	r1, r1
	add	r2, sp, #68
	str	r1, [r2]
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #64]
	ldr	r1, [sp, #64]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #60]
	ldr	r1, [sp, #60]
	add	r2, sp, #72
	str	r1, [r2]
	b	while_block0
while_block0: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #56]
	ldr	r1, [sp, #56]
	mov	r2, #-1
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #52]
	bgt	while_body1
	b	while_next2
while_body1: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #48]
	add	r1, sp, #76
	ldr	r3, [r1]
	str	r3, [sp, #44]
	ldr	r1, [sp, #44]
	ldr	r2, [sp, #48]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #40]
	ldr	r1, [sp, #40]
	ldr	r3, [r1]
	str	r3, [sp, #36]
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #32]
	ldr	r1, [sp, #36]
	ldr	r2, [sp, #32]
	cmp	r1, r2
	mov	r3, #0
	movgt	r3, #1
	str	r3, [sp, #28]
	bgt	then_bb3
	b	if_next_bb5
while_next2: 
	add	r1, sp, #68
	ldr	r3, [r1]
	str	r3, [sp, #24]
	ldr	r3, [sp, #24]
	b	_getMaxOfAll_retbb
then_bb3: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #20]
	add	r1, sp, #76
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
	add	r2, sp, #68
	str	r1, [r2]
	b	if_next_bb5
if_next_bb5: 
	add	r1, sp, #72
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	mov	r2, #1
	sub	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r1, [sp, #0]
	add	r2, sp, #72
	str	r1, [r2]
	b	while_block0
_getMaxOfAll_retbb:
	mov	r0, r3
	add	sp, sp, #88
	pop	{r4, lr}
	bx	lr
_getMaxOfAll_alignbb:
	.align	2
	.size	_getMaxOfAll, .-_getMaxOfAll
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 12
	@alloc = 48
	push	{r4, lr}
	sub	sp, sp, #48
	add	r1, sp, #36
	add	r1, r1, #0
	str	r1, [sp, #32]
	mov	r1, #-2
	ldr	r2, [sp, #32]
	str	r1, [r2]
	add	r1, sp, #36
	add	r1, r1, #4
	str	r1, [sp, #28]
	mov	r1, #2
	ldr	r2, [sp, #28]
	str	r1, [r2]
	add	r1, sp, #36
	add	r1, r1, #8
	str	r1, [sp, #24]
	mov	r1, #-7
	ldr	r2, [sp, #24]
	str	r1, [r2]
	add	r1, sp, #36
	add	r1, r1, #0
	str	r1, [sp, #16]
	ldr	r0, [sp, #16]
	mov	r1, #3
	bl	_getMaxOfAll
	str	r0, [sp, #12]
	add	r1, sp, #36
	ldr	r2, [sp, #12]
	lsl	r2, r2, #2
	add	r3, r1, r2
	str	r3, [sp, #8]
	ldr	r1, [sp, #8]
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #20
	str	r1, [r2]
	add	r1, sp, #20
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r0, [sp, #0]
	bl	putint
	mov	r3, #0
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #48
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
