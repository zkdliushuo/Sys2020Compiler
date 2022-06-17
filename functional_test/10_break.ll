; ModuleID = '10_break.sy'
source_filename  = "10_break.sy"

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
  store i32 10, i32* %0
  br label %while_block0

while_block0:
  %1 = load i32, i32* %0
  %2 = icmp sgt i32 %1, 0
  br i1 %2, label %while_body1, label %while_next2

while_body1:
  %3 = load i32, i32* %0
  %4 = sub i32 %3, 1
  store i32 %4, i32* %0
  %5 = load i32, i32* %0
  %6 = icmp eq i32 %5, 5
  br i1 %6, label %then_bb3, label %if_next_bb5

while_next2:
  %7 = load i32, i32* %0
  ret i32 %7

then_bb3:
  br label %while_next2

if_next_bb5:
  br label %while_block0
}
