; ModuleID = '28_while_test2.sy'
source_filename  = "28_while_test2.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @FourWhile() {
enter_block:
  %0 = alloca i32
  store i32 5, i32* %0
  %1 = alloca i32
  %2 = alloca i32
  store i32 6, i32* %1
  store i32 7, i32* %2
  %3 = alloca i32
  store i32 10, i32* %3
  br label %while_block0

while_block0:
  %4 = load i32, i32* %0
  %5 = icmp slt i32 %4, 20
  br i1 %5, label %while_body1, label %while_next2

while_body1:
  %6 = load i32, i32* %0
  %7 = add i32 %6, 3
  store i32 %7, i32* %0
  br label %while_block3

while_next2:
  %8 = load i32, i32* %0
  %9 = load i32, i32* %1
  %10 = load i32, i32* %3
  %11 = add i32 %9, %10
  %12 = add i32 %8, %11
  %13 = load i32, i32* %2
  %14 = add i32 %12, %13
  ret i32 %14

while_block3:
  %15 = load i32, i32* %1
  %16 = icmp slt i32 %15, 10
  br i1 %16, label %while_body4, label %while_next5

while_body4:
  %17 = load i32, i32* %1
  %18 = add i32 %17, 1
  store i32 %18, i32* %1
  br label %while_block6

while_next5:
  %19 = load i32, i32* %1
  %20 = sub i32 %19, 2
  store i32 %20, i32* %1
  br label %while_block0

while_block6:
  %21 = load i32, i32* %2
  %22 = icmp eq i32 %21, 7
  br i1 %22, label %while_body7, label %while_next8

while_body7:
  %23 = load i32, i32* %2
  %24 = sub i32 %23, 1
  store i32 %24, i32* %2
  br label %while_block9

while_next8:
  %25 = load i32, i32* %2
  %26 = add i32 %25, 1
  store i32 %26, i32* %2
  br label %while_block3

while_block9:
  %27 = load i32, i32* %3
  %28 = icmp slt i32 %27, 20
  br i1 %28, label %while_body10, label %while_next11

while_body10:
  %29 = load i32, i32* %3
  %30 = add i32 %29, 3
  store i32 %30, i32* %3
  br label %while_block9

while_next11:
  %31 = load i32, i32* %3
  %32 = sub i32 %31, 1
  store i32 %32, i32* %3
  br label %while_block6
}

define i32 @main() {
enter_block:
  %0 = call i32 @FourWhile()
  ret i32 %0
}
