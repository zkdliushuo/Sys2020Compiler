; ModuleID = '51_recursion_test2.sy'
source_filename  = "51_recursion_test2.sy"

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
  %2 = load i32, i32* %1
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %then_bb0, label %if_next_bb2

then_bb0:
  ret i32 0

if_next_bb2:
  %4 = load i32, i32* %1
  %5 = icmp eq i32 %4, 1
  br i1 %5, label %then_bb3, label %if_next_bb5

then_bb3:
  ret i32 1

if_next_bb5:
  %6 = alloca i32
  %7 = load i32, i32* %1
  %8 = sub i32 %7, 1
  store i32 %8, i32* %6
  %9 = alloca i32
  %10 = load i32, i32* %1
  %11 = sub i32 %10, 2
  store i32 %11, i32* %9
  %12 = load i32, i32* %6
  %13 = call i32 @fib(i32 %12)
  %14 = load i32, i32* %9
  %15 = call i32 @fib(i32 %14)
  %16 = add i32 %13, %15
  ret i32 %16
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  store i32 10, i32* %0
  %1 = load i32, i32* %0
  %2 = call i32 @fib(i32 %1)
  ret i32 %2
}
