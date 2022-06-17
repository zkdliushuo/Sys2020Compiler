; ModuleID = '06_var_defn_func.sy'
source_filename  = "06_var_defn_func.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @defn() {
enter_block:
  ret i32 4
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  %1 = call i32 @defn()
  store i32 %1, i32* %0
  %2 = load i32, i32* %0
  ret i32 %2
}
