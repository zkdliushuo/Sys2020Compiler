@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ load Instruction %1: 8
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ load Instruction %2: 12
	 @ alloca Instruction %3 alloc space: [12 , 16]
	 @ load Instruction %4: 20
	 @ load Instruction %5: 24
	 @ add Instruction %6: 28
	 @ load Instruction %7: 32
@ After Enter EntryBB
	 @ alloca Instruction %0 alloc space: [0 , 4]
	 @ alloca Instruction %1 alloc space: [4 , 8]
	 @ alloca Instruction %2 alloc space: [8 , 12]
	 @ call Instruction %3: 16
	 @ call Instruction %4: 20
	 @ add Instruction %5: 24
	 @ call Instruction %6: 28
	 @ add Instruction %7: 32
	 @ call Instruction %8: 36
	 @ add Instruction %9: 40
	 @ load Instruction %10: 44
	 @ add Instruction %11: 48
	 @ load Instruction %12: 52
	 @ add Instruction %13: 56
	 @ load Instruction %14: 60
	 @ add Instruction %15: 64
	.text
	.global	__aeabi_idivmod
	.global	__aeabi_idiv
	.align	2
	.text
	.align	2
	.global	func1
	.arch armv8-a
	.type	func1, %function
func1: 
	@frame_size = 2
	@alloc = 8
	push	{r4, lr}
	sub	sp, sp, #8
	mov	r1, #1
	add	r2, sp, #4
	str	r1, [r2]
	add	r1, sp, #4
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	func1_retbb
func1_retbb:
	mov	r0, r3
	add	sp, sp, #8
	pop	{r4, lr}
	bx	lr
func1_alignbb:
	.align	2
	.size	func1, .-func1
	.text
	.align	2
	.global	func2
	.arch armv8-a
	.type	func2, %function
func2: 
	@frame_size = 2
	@alloc = 8
	push	{r4, lr}
	sub	sp, sp, #8
	mov	r1, #2
	add	r2, sp, #4
	str	r1, [r2]
	add	r1, sp, #4
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	func2_retbb
func2_retbb:
	mov	r0, r3
	add	sp, sp, #8
	pop	{r4, lr}
	bx	lr
func2_alignbb:
	.align	2
	.size	func2, .-func2
	.text
	.align	2
	.global	func3
	.arch armv8-a
	.type	func3, %function
func3: 
	@frame_size = 2
	@alloc = 8
	push	{r4, lr}
	sub	sp, sp, #8
	mov	r1, #4
	add	r2, sp, #4
	str	r1, [r2]
	add	r1, sp, #4
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	func3_retbb
func3_retbb:
	mov	r0, r3
	add	sp, sp, #8
	pop	{r4, lr}
	bx	lr
func3_alignbb:
	.align	2
	.size	func3, .-func3
	.text
	.align	2
	.global	func4
	.arch armv8-a
	.type	func4, %function
func4: 
	@frame_size = 8
	@alloc = 32
	push	{r4, lr}
	sub	sp, sp, #32
	mov	r1, #8
	add	r2, sp, #24
	str	r1, [r2]
	add	r1, sp, #24
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #20]
	add	r2, sp, #28
	str	r1, [r2]
	mov	r1, #16
	add	r2, sp, #16
	str	r1, [r2]
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #12]
	add	r1, sp, #16
	ldr	r3, [r1]
	str	r3, [sp, #8]
	ldr	r1, [sp, #12]
	ldr	r2, [sp, #8]
	add	r3, r1, r2
	str	r3, [sp, #4]
	ldr	r1, [sp, #4]
	add	r2, sp, #28
	str	r1, [r2]
	add	r1, sp, #28
	ldr	r3, [r1]
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	func4_retbb
func4_retbb:
	mov	r0, r3
	add	sp, sp, #32
	pop	{r4, lr}
	bx	lr
func4_alignbb:
	.align	2
	.size	func4, .-func4
	.text
	.align	2
	.global	main
	.arch armv8-a
	.type	main, %function
main: 
	@frame_size = 16
	@alloc = 64
	push	{r4, lr}
	sub	sp, sp, #64
	mov	r1, #32
	add	r2, sp, #60
	str	r1, [r2]
	mov	r1, #32
	add	r2, sp, #56
	str	r1, [r2]
	mov	r1, #32
	add	r2, sp, #52
	str	r1, [r2]
	bl	func1
	str	r0, [sp, #48]
	bl	func2
	str	r0, [sp, #44]
	ldr	r1, [sp, #48]
	ldr	r2, [sp, #44]
	add	r3, r1, r2
	str	r3, [sp, #40]
	bl	func3
	str	r0, [sp, #36]
	ldr	r1, [sp, #40]
	ldr	r2, [sp, #36]
	add	r3, r1, r2
	str	r3, [sp, #32]
	bl	func4
	str	r0, [sp, #28]
	ldr	r1, [sp, #32]
	ldr	r2, [sp, #28]
	add	r3, r1, r2
	str	r3, [sp, #24]
	add	r1, sp, #60
	ldr	r3, [r1]
	str	r3, [sp, #20]
	ldr	r1, [sp, #24]
	ldr	r2, [sp, #20]
	add	r3, r1, r2
	str	r3, [sp, #16]
	add	r1, sp, #56
	ldr	r3, [r1]
	str	r3, [sp, #12]
	ldr	r1, [sp, #16]
	ldr	r2, [sp, #12]
	add	r3, r1, r2
	str	r3, [sp, #8]
	add	r1, sp, #52
	ldr	r3, [r1]
	str	r3, [sp, #4]
	ldr	r1, [sp, #8]
	ldr	r2, [sp, #4]
	add	r3, r1, r2
	str	r3, [sp, #0]
	ldr	r3, [sp, #0]
	b	main_retbb
main_retbb:
	mov	r0, r3
	add	sp, sp, #64
	pop	{r4, lr}
	bx	lr
main_alignbb:
	.align	2
	.size	main, .-main
