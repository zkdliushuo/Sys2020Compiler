; ModuleID = '04_func_defn.sy'
source_filename  = "04_func_defn.sy"

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

define i32 @func(i32) {
enter_block:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = load i32, i32* %1
  %3 = sub i32 %2, 1
  store i32 %3, i32* %1
  %4 = load i32, i32* %1
  ret i32 %4
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  store i32 10, i32* @a
  %1 = load i32, i32* @a
  %2 = call i32 @func(i32 %1)
  store i32 %2, i32* %0
  %3 = load i32, i32* %0
  ret i32 %3
}
