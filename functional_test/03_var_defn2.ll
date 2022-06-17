; ModuleID = '03_var_defn2.sy'
source_filename  = "03_var_defn2.sy"

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
  store i32 5, i32* @b
  %0 = alloca i32
  %1 = load i32, i32* @a
  %2 = mul i32 %1, 2
  %3 = load i32, i32* @b
  %4 = add i32 %2, %3
  %5 = add i32 %4, 3
  store i32 %5, i32* %0
  %6 = load i32, i32* %0
  ret i32 %6
}
