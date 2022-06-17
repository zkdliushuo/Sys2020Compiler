; ModuleID = '13_and.sy'
source_filename  = "13_and.sy"

@a = global i32 0
@b = global i32 0

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
  %0 = call i32 @getint()
  store i32 %0, i32* @a
  %1 = call i32 @getint()
  store i32 %1, i32* @b
  %2 = load i32, i32* @a
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %next_and_bb3, label %else_bb1

then_bb0:
  ret i32 1

else_bb1:
  ret i32 0

next_and_bb3:
  %4 = load i32, i32* @b
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %then_bb0, label %else_bb1
}
