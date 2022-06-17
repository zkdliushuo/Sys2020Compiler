; ModuleID = '32_while_if_test3.sy'
source_filename  = "32_while_if_test3.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @deepWhileBr(i32, i32) {
enter_block:
  %2 = alloca i32
  store i32 %0, i32* %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = alloca i32
  %5 = load i32, i32* %2
  %6 = load i32, i32* %3
  %7 = add i32 %5, %6
  store i32 %7, i32* %4
  br label %while_block0

while_block0:
  %8 = load i32, i32* %4
  %9 = icmp slt i32 %8, 75
  br i1 %9, label %while_body1, label %while_next2

while_body1:
  %10 = alloca i32
  store i32 42, i32* %10
  %11 = load i32, i32* %4
  %12 = icmp slt i32 %11, 100
  br i1 %12, label %then_bb3, label %if_next_bb5

while_next2:
  %13 = load i32, i32* %4
  ret i32 %13

then_bb3:
  %14 = load i32, i32* %4
  %15 = load i32, i32* %10
  %16 = add i32 %14, %15
  store i32 %16, i32* %4
  %17 = load i32, i32* %4
  %18 = icmp sgt i32 %17, 99
  br i1 %18, label %then_bb6, label %if_next_bb8

if_next_bb5:
  br label %while_block0

then_bb6:
  %19 = alloca i32
  %20 = load i32, i32* %10
  %21 = mul i32 %20, 2
  store i32 %21, i32* %19
  br i1 true, label %then_bb9, label %if_next_bb11

if_next_bb8:
  br label %if_next_bb5

then_bb9:
  %22 = load i32, i32* %19
  %23 = mul i32 %22, 2
  store i32 %23, i32* %4
  br label %if_next_bb11

if_next_bb11:
  br label %if_next_bb8
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  store i32 2, i32* %0
  %1 = load i32, i32* %0
  %2 = load i32, i32* %0
  %3 = call i32 @deepWhileBr(i32 %1, i32 %2)
  ret i32 %3
}
