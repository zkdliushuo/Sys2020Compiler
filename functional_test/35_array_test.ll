; ModuleID = '35_array_test.sy'
source_filename  = "35_array_test.sy"

@field = global [2 x i32] zeroinitializer

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @func(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = getelementptr inbounds [2 x i32], [2 x i32]* @field, i32 0, i32 0
  %3 = load i32, i32* %2
  %4 = sub i32 3, %3
  %5 = load i32*, i32** %1
  %6 = getelementptr inbounds i32, i32* %5, i32 %4
  %7 = load i32, i32* %6
  ret i32 %7
}

define i32 @main() {
enter_block:
  %0 = alloca [1 x i32], i32 1
  %1 = alloca [3 x i32], i32 3
  %2 = alloca i32
  %3 = getelementptr inbounds [2 x i32], [2 x i32]* @field, i32 0, i32 0
  store i32 1, i32* %3
  %4 = getelementptr inbounds [2 x i32], [2 x i32]* @field, i32 0, i32 1
  store i32 2, i32* %4
  %5 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 0
  store i32 -1, i32* %5
  %6 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 1
  %7 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 0
  %8 = load i32, i32* %7
  %9 = sub i32 %8, 2
  store i32 %9, i32* %6
  %10 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 1
  %11 = load i32, i32* %10
  store i32 %11, i32* %2
  %12 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 2
  store i32 16, i32* %12
  %13 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 0
  %14 = call i32 @func(i32* %13)
  %15 = add i32 %14, 2
  %16 = load i32, i32* %2
  %17 = add i32 %15, %16
  ret i32 %17
}
