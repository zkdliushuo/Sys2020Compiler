; ModuleID = '47_minus_with_sub.sy'
source_filename  = "47_minus_with_sub.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @main() {
enter_block:
  %0 = alloca i32
  %1 = alloca i32
  store i32 -2, i32* %0
  store i32 1, i32* %1
  %2 = load i32, i32* %0
  %3 = load i32, i32* %1
  %4 = sub i32 0, %3
  %5 = sub i32 %2, %4
  %6 = load i32, i32* %0
  %7 = load i32, i32* %1
  %8 = add i32 %6, %7
  %9 = sub i32 0, %8
  %10 = load i32, i32* %0
  %11 = load i32, i32* %1
  %12 = sub i32 %10, %11
  %13 = sub i32 0, %12
  %14 = srem i32 %9, %13
  %15 = add i32 %5, %14
  store i32 %15, i32* %0
  %16 = load i32, i32* %0
  call void @putint(i32 %16)
  ret i32 0
}
