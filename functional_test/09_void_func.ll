; ModuleID = '09_void_func.sy'
source_filename  = "09_void_func.sy"

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

define void @add(i32, i32) {
enter_block:
  %2 = alloca i32
  store i32 %0, i32* %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = load i32, i32* %2
  %5 = load i32, i32* %3
  %6 = add i32 %4, %5
  store i32 %6, i32* @c
  ret void
}

define i32 @main() {
enter_block:
  store i32 3, i32* @a
  store i32 2, i32* @b
  %0 = load i32, i32* @a
  %1 = load i32, i32* @b
  call void @add(i32 %0, i32 %1)
  %2 = load i32, i32* @c
  ret i32 %2
}
