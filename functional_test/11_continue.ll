; ModuleID = '11_continue.sy'
source_filename  = "11_continue.sy"

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
  %4 = icmp sgt i32 %3, 5
  br i1 %4, label %then_bb3, label %if_next_bb5

while_next2:
  %5 = load i32, i32* %0
  ret i32 %5

then_bb3:
  %6 = load i32, i32* %0
  %7 = sub i32 %6, 1
  store i32 %7, i32* %0
  br label %while_block0

if_next_bb5:
  %8 = load i32, i32* %0
  ret i32 %8
  br label %while_block0
}
