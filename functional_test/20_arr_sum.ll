; ModuleID = '20_arr_sum.sy'
source_filename  = "20_arr_sum.sy"

@a = global [5 x i32] zeroinitializer

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
  %0 = getelementptr inbounds [5 x i32], [5 x i32]* @a, i32 0, i32 0
  %1 = call i32 @getint()
  store i32 %1, i32* %0
  %2 = getelementptr inbounds [5 x i32], [5 x i32]* @a, i32 0, i32 1
  %3 = call i32 @getint()
  store i32 %3, i32* %2
  %4 = getelementptr inbounds [5 x i32], [5 x i32]* @a, i32 0, i32 2
  %5 = call i32 @getint()
  store i32 %5, i32* %4
  %6 = getelementptr inbounds [5 x i32], [5 x i32]* @a, i32 0, i32 3
  %7 = call i32 @getint()
  store i32 %7, i32* %6
  %8 = getelementptr inbounds [5 x i32], [5 x i32]* @a, i32 0, i32 4
  %9 = call i32 @getint()
  store i32 %9, i32* %8
  %10 = alloca i32
  store i32 4, i32* %10
  %11 = alloca i32
  store i32 0, i32* %11
  br label %while_block0

while_block0:
  %12 = load i32, i32* %10
  %13 = icmp sgt i32 %12, 1
  br i1 %13, label %while_body1, label %while_next2

while_body1:
  %14 = load i32, i32* %11
  %15 = load i32, i32* %10
  %16 = getelementptr inbounds [5 x i32], [5 x i32]* @a, i32 0, i32 %15
  %17 = load i32, i32* %16
  %18 = add i32 %14, %17
  store i32 %18, i32* %11
  %19 = load i32, i32* %10
  %20 = sub i32 %19, 1
  store i32 %20, i32* %10
  br label %while_block0

while_next2:
  %21 = load i32, i32* %11
  ret i32 %21
}
