; ModuleID = '02_arr_defn4.sy'
source_filename  = "02_arr_defn4.sy"

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
  %0 = alloca [8 x i32], i32 8
  %1 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 0
  store i32 1, i32* %1
  %2 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 1
  store i32 2, i32* %2
  %3 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 2
  store i32 3, i32* %3
  %4 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 3
  store i32 4, i32* %4
  %5 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 4
  store i32 5, i32* %5
  %6 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 5
  store i32 6, i32* %6
  %7 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 6
  store i32 7, i32* %7
  %8 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 7
  store i32 8, i32* %8
  %9 = alloca [8 x i32], i32 8
  %10 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 0
  %11 = load i32, i32* %10
  %12 = getelementptr inbounds [8 x i32], [8 x i32]* %0, i32 0, i32 1
  %13 = load i32, i32* %12
  %14 = getelementptr inbounds [8 x i32], [8 x i32]* %9, i32 0, i32 0
  store i32 %11, i32* %14
  %15 = getelementptr inbounds [8 x i32], [8 x i32]* %9, i32 0, i32 1
  store i32 %13, i32* %15
  %16 = getelementptr inbounds [8 x i32], [8 x i32]* %9, i32 0, i32 2
  store i32 3, i32* %16
  %17 = getelementptr inbounds [8 x i32], [8 x i32]* %9, i32 0, i32 3
  store i32 4, i32* %17
  %18 = getelementptr inbounds [8 x i32], [8 x i32]* %9, i32 0, i32 4
  store i32 5, i32* %18
  %19 = getelementptr inbounds [8 x i32], [8 x i32]* %9, i32 0, i32 5
  store i32 6, i32* %19
  %20 = getelementptr inbounds [8 x i32], [8 x i32]* %9, i32 0, i32 6
  store i32 7, i32* %20
  %21 = getelementptr inbounds [8 x i32], [8 x i32]* %9, i32 0, i32 7
  store i32 8, i32* %21
  ret i32 0
}
