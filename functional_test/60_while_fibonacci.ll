; ModuleID = '60_while_fibonacci.sy'
source_filename  = "60_while_fibonacci.sy"

@n = global i32 0

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @fib(i32) {
enter_block:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = alloca i32
  %3 = alloca i32
  %4 = alloca i32
  store i32 0, i32* %2
  store i32 1, i32* %3
  %5 = load i32, i32* %1
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %then_bb0, label %if_next_bb2

then_bb0:
  ret i32 0

if_next_bb2:
  %7 = load i32, i32* %1
  %8 = icmp eq i32 %7, 1
  br i1 %8, label %then_bb3, label %if_next_bb5

then_bb3:
  ret i32 1

if_next_bb5:
  br label %while_block6

while_block6:
  %9 = load i32, i32* %1
  %10 = icmp sgt i32 %9, 1
  br i1 %10, label %while_body7, label %while_next8

while_body7:
  %11 = load i32, i32* %2
  %12 = load i32, i32* %3
  %13 = add i32 %11, %12
  store i32 %13, i32* %4
  %14 = load i32, i32* %3
  store i32 %14, i32* %2
  %15 = load i32, i32* %4
  store i32 %15, i32* %3
  %16 = load i32, i32* %1
  %17 = sub i32 %16, 1
  store i32 %17, i32* %1
  br label %while_block6

while_next8:
  %18 = load i32, i32* %4
  ret i32 %18
}

define i32 @main() {
enter_block:
  %0 = call i32 @getint()
  store i32 %0, i32* @n
  %1 = alloca i32
  %2 = load i32, i32* @n
  %3 = call i32 @fib(i32 %2)
  store i32 %3, i32* %1
  %4 = load i32, i32* %1
  ret i32 %4
}
