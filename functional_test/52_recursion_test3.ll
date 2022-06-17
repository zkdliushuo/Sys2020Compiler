; ModuleID = '52_recursion_test3.sy'
source_filename  = "52_recursion_test3.sy"

@a = global i32 0
@r = global i32 0

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @fac(i32) {
enter_block:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = load i32, i32* %1
  %3 = icmp slt i32 %2, 2
  br i1 %3, label %then_bb0, label %if_next_bb2

then_bb0:
  ret i32 1

if_next_bb2:
  %4 = load i32, i32* %1
  %5 = sub i32 %4, 1
  store i32 %5, i32* @a
  %6 = load i32, i32* @a
  %7 = call i32 @fac(i32 %6)
  store i32 %7, i32* @r
  %8 = load i32, i32* %1
  %9 = load i32, i32* @r
  %10 = mul i32 %8, %9
  store i32 %10, i32* @r
  %11 = load i32, i32* @r
  ret i32 %11
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  store i32 5, i32* %0
  %1 = load i32, i32* %0
  %2 = call i32 @fac(i32 %1)
  ret i32 %2
}
