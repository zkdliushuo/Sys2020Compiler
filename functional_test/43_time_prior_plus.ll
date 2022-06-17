; ModuleID = '43_time_prior_plus.sy'
source_filename  = "43_time_prior_plus.sy"

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
  store i32 20, i32* %0
  %1 = alloca i32
  store i32 5, i32* %1
  %2 = alloca i32
  store i32 6, i32* %2
  %3 = alloca i32
  store i32 -4, i32* %3
  %4 = load i32, i32* %0
  %5 = load i32, i32* %2
  %6 = load i32, i32* %3
  %7 = mul i32 %5, %6
  %8 = add i32 %4, %7
  %9 = load i32, i32* %1
  %10 = load i32, i32* %0
  %11 = load i32, i32* %3
  %12 = add i32 %10, %11
  %13 = srem i32 %9, %12
  %14 = load i32, i32* %0
  %15 = sdiv i32 %13, %14
  %16 = sub i32 %8, %15
  store i32 %16, i32* %0
  %17 = load i32, i32* %0
  call void @putint(i32 %17)
  ret i32 0
}
