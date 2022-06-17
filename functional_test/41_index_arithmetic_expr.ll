; ModuleID = '41_index_arithmetic_expr.sy'
source_filename  = "41_index_arithmetic_expr.sy"

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
  %2 = alloca [3 x i32], i32 3
  store i32 56, i32* %0
  store i32 12, i32* %1
  %3 = getelementptr inbounds [3 x i32], [3 x i32]* %2, i32 0, i32 0
  store i32 1, i32* %3
  %4 = getelementptr inbounds [3 x i32], [3 x i32]* %2, i32 0, i32 1
  store i32 2, i32* %4
  %5 = getelementptr inbounds [3 x i32], [3 x i32]* %2, i32 0, i32 2
  store i32 3, i32* %5
  %6 = alloca i32
  %7 = load i32, i32* %0
  %8 = load i32, i32* %1
  %9 = srem i32 %7, %8
  %10 = load i32, i32* %1
  %11 = add i32 %9, %10
  %12 = sdiv i32 %11, 5
  %13 = sub i32 %12, 2
  %14 = getelementptr inbounds [3 x i32], [3 x i32]* %2, i32 0, i32 %13
  %15 = load i32, i32* %14
  store i32 %15, i32* %6
  %16 = load i32, i32* %6
  call void @putint(i32 %16)
  ret i32 0
}
