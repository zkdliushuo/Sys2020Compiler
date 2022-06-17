; ModuleID = '27_while_test1.sy'
source_filename  = "27_while_test1.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @doubleWhile() {
enter_block:
  %0 = alloca i32
  store i32 5, i32* %0
  %1 = alloca i32
  store i32 7, i32* %1
  br label %while_block0

while_block0:
  %2 = load i32, i32* %0
  %3 = icmp slt i32 %2, 100
  br i1 %3, label %while_body1, label %while_next2

while_body1:
  %4 = load i32, i32* %0
  %5 = add i32 %4, 30
  store i32 %5, i32* %0
  br label %while_block3

while_next2:
  %6 = load i32, i32* %1
  ret i32 %6

while_block3:
  %7 = load i32, i32* %1
  %8 = icmp slt i32 %7, 100
  br i1 %8, label %while_body4, label %while_next5

while_body4:
  %9 = load i32, i32* %1
  %10 = add i32 %9, 6
  store i32 %10, i32* %1
  br label %while_block3

while_next5:
  %11 = load i32, i32* %1
  %12 = sub i32 %11, 100
  store i32 %12, i32* %1
  br label %while_block0
}

define i32 @main() {
enter_block:
  %0 = call i32 @doubleWhile()
  ret i32 %0
}
