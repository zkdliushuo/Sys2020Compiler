; ModuleID = '04_const_defn.sy'
source_filename  = "04_const_defn.sy"

@x = constant i32 4

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
  %0 = load i32, i32* @x
  ret i32 %0
}
