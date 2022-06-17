; ModuleID = '07_return_var.sy'
source_filename  = "07_return_var.sy"

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
  ret i32 %0
}
