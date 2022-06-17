; ModuleID = '24_if_test3.sy'
source_filename  = "24_if_test3.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @ififElse() {
enter_block:
  %0 = alloca i32
  store i32 5, i32* %0
  %1 = alloca i32
  store i32 10, i32* %1
  %2 = load i32, i32* %0
  %3 = icmp eq i32 %2, 5
  br i1 %3, label %then_bb0, label %if_next_bb2

then_bb0:
  %4 = load i32, i32* %1
  %5 = icmp eq i32 %4, 10
  br i1 %5, label %then_bb3, label %else_bb4

if_next_bb2:
  %6 = load i32, i32* %0
  ret i32 %6

then_bb3:
  store i32 25, i32* %0
  br label %if_next_bb5

else_bb4:
  %7 = load i32, i32* %0
  %8 = add i32 %7, 15
  store i32 %8, i32* %0
  br label %if_next_bb5

if_next_bb5:
  br label %if_next_bb2
}

define i32 @main() {
enter_block:
  %0 = call i32 @ififElse()
  ret i32 %0
}
