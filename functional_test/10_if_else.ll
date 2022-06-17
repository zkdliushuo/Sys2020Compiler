; ModuleID = '10_if_else.sy'
source_filename  = "10_if_else.sy"

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
  br i1 %1, label %then_bb0, label %else_bb1

then_bb0:
  ret i32 1

else_bb1:
  ret i32 0
}
