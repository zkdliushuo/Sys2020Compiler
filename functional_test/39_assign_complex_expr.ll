; ModuleID = '39_assign_complex_expr.sy'
source_filename  = "39_assign_complex_expr.sy"

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
  %2 = alloca i32
  %3 = alloca i32
  %4 = alloca i32
  store i32 5, i32* %0
  store i32 5, i32* %1
  store i32 1, i32* %2
  store i32 -2, i32* %3
  %5 = load i32, i32* %3
  %6 = mul i32 %5, 1
  %7 = sdiv i32 %6, 2
  %8 = load i32, i32* %0
  %9 = load i32, i32* %1
  %10 = sub i32 %8, %9
  %11 = add i32 %7, %10
  %12 = load i32, i32* %2
  %13 = add i32 %12, 3
  %14 = sub i32 0, %13
  %15 = srem i32 %14, 2
  %16 = sub i32 %11, %15
  store i32 %16, i32* %4
  %17 = load i32, i32* %4
  call void @putint(i32 %17)
  %18 = load i32, i32* %3
  %19 = srem i32 %18, 2
  %20 = add i32 %19, 67
  %21 = load i32, i32* %0
  %22 = load i32, i32* %1
  %23 = sub i32 %21, %22
  %24 = sub i32 0, %23
  %25 = add i32 %20, %24
  %26 = load i32, i32* %2
  %27 = add i32 %26, 2
  %28 = srem i32 %27, 2
  %29 = sub i32 0, %28
  %30 = sub i32 %25, %29
  store i32 %30, i32* %4
  %31 = load i32, i32* %4
  %32 = add i32 %31, 3
  store i32 %32, i32* %4
  %33 = load i32, i32* %4
  call void @putint(i32 %33)
  ret i32 0
}
