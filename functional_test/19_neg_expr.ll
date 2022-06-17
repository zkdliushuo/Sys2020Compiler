; ModuleID = '19_neg_expr.sy'
source_filename  = "19_neg_expr.sy"

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
  %2 = alloca i32
  %3 = load i32, i32* @a
  %4 = load i32, i32* @b
  %5 = add i32 %3, %4
  %6 = sub i32 0, %5
  store i32 %6, i32* %2
  %7 = load i32, i32* %2
  call void @putint(i32 %7)
  ret i32 0
}
