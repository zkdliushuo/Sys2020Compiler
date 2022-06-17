; ModuleID = '22_if_test1.sy'
source_filename  = "22_if_test1.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @ifElse() {
enter_block:
  %0 = alloca i32
  store i32 5, i32* %0
  %1 = load i32, i32* %0
  %2 = icmp eq i32 %1, 5
  br i1 %2, label %then_bb0, label %else_bb1

then_bb0:
  store i32 25, i32* %0
  br label %if_next_bb2

else_bb1:
  %3 = load i32, i32* %0
  %4 = mul i32 %3, 2
  store i32 %4, i32* %0
  br label %if_next_bb2

if_next_bb2:
  %5 = load i32, i32* %0
  ret i32 %5
}

define i32 @main() {
enter_block:
  %0 = call i32 @ifElse()
  ret i32 %0
}
