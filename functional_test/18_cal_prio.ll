; ModuleID = '18_cal_prio.sy'
source_filename  = "18_cal_prio.sy"

@a = global i32 0
@b = global i32 0
@c = global i32 0

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
  %2 = call i32 @getint()
  store i32 %2, i32* @c
  %3 = alloca i32
  %4 = load i32, i32* @a
  %5 = load i32, i32* @b
  %6 = load i32, i32* @c
  %7 = mul i32 %5, %6
  %8 = add i32 %4, %7
  store i32 %8, i32* %3
  %9 = load i32, i32* %3
  ret i32 %9
}
