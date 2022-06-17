; ModuleID = '38_if_complex_expr.sy'
source_filename  = "38_if_complex_expr.sy"

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
  store i32 2, i32* %4
  %5 = load i32, i32* %3
  %6 = mul i32 %5, 1
  %7 = sdiv i32 %6, 2
  %8 = icmp slt i32 %7, 0
  br i1 %8, label %then_bb0, label %next_or_bb3

then_bb0:
  %9 = load i32, i32* %4
  call void @putint(i32 %9)
  br label %if_next_bb2

if_next_bb2:
  %10 = load i32, i32* %3
  %11 = srem i32 %10, 2
  %12 = add i32 %11, 67
  %13 = icmp slt i32 %12, 0
  br i1 %13, label %then_bb5, label %next_or_bb8

next_or_bb3:
  %14 = load i32, i32* %0
  %15 = load i32, i32* %1
  %16 = sub i32 %14, %15
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %next_and_bb4, label %if_next_bb2

next_and_bb4:
  %18 = load i32, i32* %2
  %19 = add i32 %18, 3
  %20 = srem i32 %19, 2
  %21 = icmp ne i32 %20, 0
  br i1 %21, label %then_bb0, label %if_next_bb2

then_bb5:
  store i32 4, i32* %4
  %22 = load i32, i32* %4
  call void @putint(i32 %22)
  br label %if_next_bb7

if_next_bb7:
  ret i32 0

next_or_bb8:
  %23 = load i32, i32* %0
  %24 = load i32, i32* %1
  %25 = sub i32 %23, %24
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %next_and_bb9, label %if_next_bb7

next_and_bb9:
  %27 = load i32, i32* %2
  %28 = add i32 %27, 2
  %29 = srem i32 %28, 2
  %30 = icmp ne i32 %29, 0
  br i1 %30, label %then_bb5, label %if_next_bb7
}
