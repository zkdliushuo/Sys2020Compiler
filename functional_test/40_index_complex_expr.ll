; ModuleID = '40_index_complex_expr.sy'
source_filename  = "40_index_complex_expr.sy"

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
  %4 = alloca [5 x i32], i32 5
  store i32 5, i32* %0
  store i32 5, i32* %1
  store i32 1, i32* %2
  store i32 -2, i32* %3
  %5 = getelementptr inbounds [5 x i32], [5 x i32]* %4, i32 0, i32 0
  store i32 1, i32* %5
  %6 = getelementptr inbounds [5 x i32], [5 x i32]* %4, i32 0, i32 1
  store i32 2, i32* %6
  %7 = getelementptr inbounds [5 x i32], [5 x i32]* %4, i32 0, i32 2
  store i32 3, i32* %7
  %8 = getelementptr inbounds [5 x i32], [5 x i32]* %4, i32 0, i32 3
  store i32 4, i32* %8
  %9 = getelementptr inbounds [5 x i32], [5 x i32]* %4, i32 0, i32 4
  store i32 5, i32* %9
  %10 = alloca i32
  %11 = load i32, i32* %3
  %12 = mul i32 %11, 1
  %13 = sdiv i32 %12, 2
  %14 = add i32 %13, 4
  %15 = load i32, i32* %0
  %16 = load i32, i32* %1
  %17 = sub i32 %15, %16
  %18 = add i32 %14, %17
  %19 = load i32, i32* %2
  %20 = add i32 %19, 3
  %21 = sub i32 0, %20
  %22 = srem i32 %21, 2
  %23 = sub i32 %18, %22
  %24 = srem i32 %23, 5
  %25 = getelementptr inbounds [5 x i32], [5 x i32]* %4, i32 0, i32 %24
  %26 = load i32, i32* %25
  store i32 %26, i32* %10
  %27 = load i32, i32* %10
  call void @putint(i32 %27)
  %28 = load i32, i32* %2
  %29 = srem i32 %28, 2
  %30 = add i32 %29, 67
  %31 = load i32, i32* %0
  %32 = add i32 %30, %31
  %33 = load i32, i32* %1
  %34 = sub i32 %32, %33
  %35 = load i32, i32* %2
  %36 = add i32 %35, 2
  %37 = srem i32 %36, 2
  %38 = sub i32 0, %37
  %39 = sub i32 %34, %38
  %40 = srem i32 %39, 5
  %41 = getelementptr inbounds [5 x i32], [5 x i32]* %4, i32 0, i32 %40
  %42 = load i32, i32* %41
  store i32 %42, i32* %10
  %43 = load i32, i32* %10
  call void @putint(i32 %43)
  ret i32 0
}
