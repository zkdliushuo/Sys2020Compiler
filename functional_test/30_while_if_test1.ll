; ModuleID = '30_while_if_test1.sy'
source_filename  = "30_while_if_test1.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @whileIf() {
enter_block:
  %0 = alloca i32
  store i32 0, i32* %0
  %1 = alloca i32
  store i32 0, i32* %1
  br label %while_block0

while_block0:
  %2 = load i32, i32* %0
  %3 = icmp slt i32 %2, 100
  br i1 %3, label %while_body1, label %while_next2

while_body1:
  %4 = load i32, i32* %0
  %5 = icmp eq i32 %4, 5
  br i1 %5, label %then_bb3, label %else_bb4

while_next2:
  %6 = load i32, i32* %1
  ret i32 %6

then_bb3:
  store i32 25, i32* %1
  br label %if_next_bb5

else_bb4:
  %7 = load i32, i32* %0
  %8 = icmp eq i32 %7, 10
  br i1 %8, label %then_bb6, label %else_bb7

if_next_bb5:
  %9 = load i32, i32* %0
  %10 = add i32 %9, 1
  store i32 %10, i32* %0
  br label %while_block0

then_bb6:
  store i32 42, i32* %1
  br label %if_next_bb8

else_bb7:
  %11 = load i32, i32* %0
  %12 = mul i32 %11, 2
  store i32 %12, i32* %1
  br label %if_next_bb8

if_next_bb8:
  br label %if_next_bb5
}

define i32 @main() {
enter_block:
  %0 = call i32 @whileIf()
  ret i32 %0
}
