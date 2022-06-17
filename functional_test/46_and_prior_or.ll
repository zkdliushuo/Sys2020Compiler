; ModuleID = '46_and_prior_or.sy'
source_filename  = "46_and_prior_or.sy"

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
  store i32 3, i32* %0
  store i32 8, i32* %1
  store i32 -4, i32* %2
  store i32 15, i32* %3
  %4 = alloca i32
  %5 = load i32, i32* %3
  %6 = load i32, i32* %1
  %7 = load i32, i32* %0
  %8 = sub i32 %6, %7
  %9 = srem i32 %5, %8
  %10 = icmp ne i32 %9, 0
  br i1 %10, label %next_and_bb4, label %next_or_bb3

then_bb0:
  %11 = load i32, i32* %3
  %12 = load i32, i32* %2
  %13 = add i32 %11, %12
  %14 = load i32, i32* %1
  %15 = sub i32 0, %14
  %16 = sub i32 %13, %15
  store i32 %16, i32* %4
  %17 = load i32, i32* %4
  call void @putint(i32 %17)
  br label %if_next_bb2

if_next_bb2:
  ret i32 0

next_or_bb3:
  %18 = load i32, i32* %3
  %19 = srem i32 %18, 3
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %next_and_bb5, label %if_next_bb2

next_and_bb4:
  %21 = load i32, i32* %0
  %22 = icmp sgt i32 %21, 0
  br i1 %22, label %then_bb0, label %next_or_bb3

next_and_bb5:
  %23 = load i32, i32* %2
  %24 = icmp sgt i32 %23, 0
  br i1 %24, label %then_bb0, label %if_next_bb2
}
