; ModuleID = '09_if.sy'
source_filename  = "09_if.sy"

@a = global i32 0

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
  store i32 10, i32* @a
  %0 = load i32, i32* @a
  %1 = icmp sgt i32 %0, 0
  br i1 %1, label %then_bb0, label %if_next_bb2

then_bb0:
  ret i32 1

if_next_bb2:
  ret i32 0
}
