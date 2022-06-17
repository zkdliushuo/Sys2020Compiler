; ModuleID = '44_add_prior_equal.sy'
source_filename  = "44_add_prior_equal.sy"

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
  store i32 1, i32* %0
  store i32 4, i32* %1
  store i32 28, i32* %2
  %3 = alloca i32
  %4 = load i32, i32* %2
  %5 = load i32, i32* %0
  %6 = add i32 %4, %5
  %7 = load i32, i32* %1
  %8 = icmp ne i32 %6, %7
  br i1 %8, label %then_bb0, label %if_next_bb2

then_bb0:
  %9 = load i32, i32* %2
  %10 = load i32, i32* %1
  %11 = sub i32 0, %10
  %12 = srem i32 %9, %11
  store i32 %12, i32* %3
  %13 = load i32, i32* %3
  call void @putint(i32 %13)
  br label %if_next_bb2

if_next_bb2:
  %14 = load i32, i32* %1
  %15 = load i32, i32* %2
  %16 = sub i32 %14, %15
  %17 = load i32, i32* %0
  %18 = icmp eq i32 %16, %17
  br i1 %18, label %then_bb3, label %if_next_bb5

then_bb3:
  %19 = load i32, i32* %2
  %20 = load i32, i32* %1
  %21 = srem i32 %19, %20
  %22 = load i32, i32* %1
  %23 = add i32 %21, %22
  store i32 %23, i32* %3
  %24 = load i32, i32* %3
  call void @putint(i32 %24)
  br label %if_next_bb5

if_next_bb5:
  ret i32 0
}
