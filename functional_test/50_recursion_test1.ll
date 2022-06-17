; ModuleID = '50_recursion_test1.sy'
source_filename  = "50_recursion_test1.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @fact(i32) {
enter_block:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = load i32, i32* %1
  %3 = icmp eq i32 %2, 0
  br i1 %3, label %then_bb0, label %if_next_bb2

then_bb0:
  ret i32 1

if_next_bb2:
  %4 = alloca i32
  %5 = load i32, i32* %1
  %6 = sub i32 %5, 1
  store i32 %6, i32* %4
  %7 = load i32, i32* %1
  %8 = load i32, i32* %4
  %9 = call i32 @fact(i32 %8)
  %10 = mul i32 %7, %9
  ret i32 %10
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  store i32 4, i32* %0
  %1 = load i32, i32* %0
  %2 = call i32 @fact(i32 %1)
  ret i32 %2
}
