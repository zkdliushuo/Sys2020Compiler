; ModuleID = '05_add.sy'
source_filename  = "05_add.sy"

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
  store i32 10, i32* @a
  store i32 20, i32* @b
  %0 = alloca i32
  %1 = load i32, i32* @a
  %2 = load i32, i32* @b
  %3 = add i32 %1, %2
  store i32 %3, i32* %0
  %4 = load i32, i32* %0
  ret i32 %4
}
