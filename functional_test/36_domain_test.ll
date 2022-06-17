; ModuleID = '36_domain_test.sy'
source_filename  = "36_domain_test.sy"

@a = global [2 x i32] zeroinitializer

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
  %2 = getelementptr inbounds [2 x i32], [2 x i32]* @a, i32 0, i32 0
  store i32 1, i32* %2
  %3 = getelementptr inbounds [2 x i32], [2 x i32]* @a, i32 0, i32 0
  %4 = load i32, i32* %3
  %5 = sub i32 3, %4
  %6 = load i32*, i32** %1
  %7 = getelementptr inbounds i32, i32* %6, i32 %5
  %8 = load i32, i32* %7
  ret i32 %8
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  %1 = alloca [3 x i32], i32 3
  %2 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 0
  store i32 -1, i32* %2
  %3 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 1
  store i32 4, i32* %3
  %4 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 2
  store i32 8, i32* %4
  %5 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 0
  %6 = call i32 @func(i32* %5)
  store i32 %6, i32* %0
  %7 = load i32, i32* %0
  %8 = getelementptr inbounds [3 x i32], [3 x i32]* %1, i32 0, i32 1
  %9 = load i32, i32* %8
  %10 = add i32 %7, %9
  ret i32 %10
}
