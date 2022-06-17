; ModuleID = '13_array_traverse2.sy'
source_filename  = "13_array_traverse2.sy"

@a = global [27 x i32] zeroinitializer

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
  store i32 0, i32* %0
  store i32 0, i32* %1
  store i32 0, i32* %2
  %3 = alloca i32
  store i32 0, i32* %3
  br label %while_block0

while_block0:
  %4 = load i32, i32* %0
  %5 = icmp slt i32 %4, 3
  br i1 %5, label %while_body1, label %while_next2

while_body1:
  br label %while_block3

while_next2:
  ret i32 0

while_block3:
  %6 = load i32, i32* %1
  %7 = icmp slt i32 %6, 3
  br i1 %7, label %while_body4, label %while_next5

while_body4:
  br label %while_block6

while_next5:
  %8 = load i32, i32* %0
  %9 = add i32 %8, 1
  store i32 %9, i32* %0
  br label %while_block0

while_block6:
  %10 = load i32, i32* %2
  %11 = icmp slt i32 %10, 3
  br i1 %11, label %while_body7, label %while_next8

while_body7:
  %12 = load i32, i32* %0
  %13 = load i32, i32* %1
  %14 = load i32, i32* %2
  %15 = mul i32 %12, 3
  %16 = add i32 %15, %13
  %17 = mul i32 %16, 3
  %18 = add i32 %17, %14
  %19 = getelementptr inbounds [27 x i32], [27 x i32]* @a, i32 0, i32 %18
  %20 = load i32, i32* %3
  store i32 %20, i32* %19
  %21 = load i32, i32* %3
  %22 = add i32 %21, 1
  store i32 %22, i32* %3
  %23 = load i32, i32* %2
  %24 = add i32 %23, 1
  store i32 %24, i32* %2
  br label %while_block6

while_next8:
  %25 = load i32, i32* %1
  %26 = add i32 %25, 1
  store i32 %26, i32* %1
  br label %while_block3
}
