; ModuleID = '31_while_if_test2.sy'
source_filename  = "31_while_if_test2.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @ifWhile() {
enter_block:
  %0 = alloca i32
  store i32 0, i32* %0
  %1 = alloca i32
  store i32 3, i32* %1
  %2 = load i32, i32* %0
  %3 = icmp eq i32 %2, 5
  br i1 %3, label %then_bb0, label %else_bb1

then_bb0:
  br label %while_block3

else_bb1:
  br label %while_block6

if_next_bb2:
  %4 = load i32, i32* %1
  ret i32 %4

while_block3:
  %5 = load i32, i32* %1
  %6 = icmp eq i32 %5, 2
  br i1 %6, label %while_body4, label %while_next5

while_body4:
  %7 = load i32, i32* %1
  %8 = add i32 %7, 2
  store i32 %8, i32* %1
  br label %while_block3

while_next5:
  %9 = load i32, i32* %1
  %10 = add i32 %9, 25
  store i32 %10, i32* %1
  br label %if_next_bb2

while_block6:
  %11 = load i32, i32* %0
  %12 = icmp slt i32 %11, 5
  br i1 %12, label %while_body7, label %while_next8

while_body7:
  %13 = load i32, i32* %1
  %14 = mul i32 %13, 2
  store i32 %14, i32* %1
  %15 = load i32, i32* %0
  %16 = add i32 %15, 1
  store i32 %16, i32* %0
  br label %while_block6

while_next8:
  br label %if_next_bb2
}

define i32 @main() {
enter_block:
  %0 = call i32 @ifWhile()
  ret i32 %0
}
