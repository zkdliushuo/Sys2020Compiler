; ModuleID = '34_func_test2.sy'
source_filename  = "34_func_test2.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @func1() {
enter_block:
  %0 = alloca i32
  store i32 1, i32* %0
  %1 = load i32, i32* %0
  ret i32 %1
}

define i32 @func2() {
enter_block:
  %0 = alloca i32
  store i32 2, i32* %0
  %1 = load i32, i32* %0
  ret i32 %1
}

define i32 @func3() {
enter_block:
  %0 = alloca i32
  store i32 4, i32* %0
  %1 = load i32, i32* %0
  ret i32 %1
}

define i32 @func4() {
enter_block:
  %0 = alloca i32
  %1 = alloca i32
  store i32 8, i32* %1
  %2 = load i32, i32* %1
  store i32 %2, i32* %0
  %3 = alloca i32
  store i32 16, i32* %3
  %4 = load i32, i32* %0
  %5 = load i32, i32* %3
  %6 = add i32 %4, %5
  store i32 %6, i32* %0
  %7 = load i32, i32* %0
  ret i32 %7
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca i32
  store i32 32, i32* %0
  store i32 32, i32* %1
  store i32 32, i32* %2
  %3 = call i32 @func1()
  %4 = call i32 @func2()
  %5 = add i32 %3, %4
  %6 = call i32 @func3()
  %7 = add i32 %5, %6
  %8 = call i32 @func4()
  %9 = add i32 %7, %8
  %10 = load i32, i32* %0
  %11 = add i32 %9, %10
  %12 = load i32, i32* %1
  %13 = add i32 %11, %12
  %14 = load i32, i32* %2
  %15 = add i32 %13, %14
  ret i32 %15
}
