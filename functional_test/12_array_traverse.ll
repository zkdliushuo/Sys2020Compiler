; ModuleID = '12_array_traverse.sy'
source_filename  = "12_array_traverse.sy"

@a = global [12 x i32] zeroinitializer

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
  store i32 0, i32* %0
  %1 = alloca i32
  store i32 0, i32* %1
  br label %while_block0

while_block0:
  %2 = load i32, i32* %0
  %3 = icmp sle i32 %2, 5
  br i1 %3, label %while_body1, label %while_next2

while_body1:
  %4 = alloca i32
  %5 = load i32, i32* %0
  store i32 %5, i32* %4
  br label %while_block3

while_next2:
  ret i32 0

while_block3:
  %6 = load i32, i32* %4
  %7 = icmp sge i32 %6, 0
  br i1 %7, label %while_body4, label %while_next5

while_body4:
  %8 = load i32, i32* %4
  %9 = icmp slt i32 %8, 4
  br i1 %9, label %next_and_bb9, label %if_next_bb8

while_next5:
  %10 = load i32, i32* %0
  %11 = add i32 %10, 1
  store i32 %11, i32* %0
  br label %while_block0

then_bb6:
  %12 = load i32, i32* %0
  %13 = load i32, i32* %4
  %14 = sub i32 %12, %13
  %15 = load i32, i32* %4
  %16 = mul i32 %14, 4
  %17 = add i32 %16, %15
  %18 = getelementptr inbounds [12 x i32], [12 x i32]* @a, i32 0, i32 %17
  %19 = load i32, i32* %1
  store i32 %19, i32* %18
  store i32 1, i32* %1
  br label %if_next_bb8

if_next_bb8:
  %20 = load i32, i32* %4
  %21 = sub i32 %20, 1
  store i32 %21, i32* %4
  br label %while_block3

next_and_bb9:
  %22 = load i32, i32* %0
  %23 = load i32, i32* %4
  %24 = sub i32 %22, %23
  %25 = icmp slt i32 %24, 3
  br i1 %25, label %then_bb6, label %if_next_bb8
}
