; ModuleID = '45_equal_prior_logic.sy'
source_filename  = "45_equal_prior_logic.sy"

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
  store i32 10, i32* %0
  store i32 6, i32* %1
  store i32 4, i32* %2
  store i32 5, i32* %3
  %4 = alloca i32
  %5 = load i32, i32* %1
  %6 = load i32, i32* %2
  %7 = add i32 %5, %6
  %8 = load i32, i32* %0
  %9 = icmp eq i32 %7, %8
  br i1 %9, label %next_and_bb3, label %if_next_bb2

then_bb0:
  %10 = load i32, i32* %1
  %11 = load i32, i32* %2
  %12 = load i32, i32* %3
  %13 = sdiv i32 %11, %12
  %14 = mul i32 %13, 2
  %15 = add i32 %10, %14
  store i32 %15, i32* %4
  %16 = load i32, i32* %4
  call void @putint(i32 %16)
  br label %if_next_bb2

if_next_bb2:
  %17 = load i32, i32* %2
  %18 = icmp slt i32 %17, 0
  br i1 %18, label %then_bb4, label %next_or_bb7

next_and_bb3:
  %19 = load i32, i32* %3
  %20 = load i32, i32* %0
  %21 = sdiv i32 %20, 2
  %22 = icmp ne i32 %19, %21
  br i1 %22, label %then_bb0, label %if_next_bb2

then_bb4:
  store i32 1, i32* %4
  %23 = load i32, i32* %4
  call void @putint(i32 %23)
  br label %if_next_bb6

if_next_bb6:
  ret i32 0

next_or_bb7:
  %24 = load i32, i32* %0
  %25 = load i32, i32* %2
  %26 = sub i32 %24, %25
  %27 = load i32, i32* %1
  %28 = icmp eq i32 %26, %27
  br i1 %28, label %next_and_bb8, label %if_next_bb6

next_and_bb8:
  %29 = load i32, i32* %0
  %30 = load i32, i32* %3
  %31 = mul i32 %30, 2
  %32 = icmp ne i32 %29, %31
  br i1 %32, label %then_bb4, label %if_next_bb6
}
