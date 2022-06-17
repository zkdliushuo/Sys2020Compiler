; ModuleID = '12_getint.sy'
source_filename  = "12_getint.sy"

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
  %1 = call i32 @getint()
  store i32 %1, i32* %0
  %2 = load i32, i32* %0
  ret i32 %2
}
