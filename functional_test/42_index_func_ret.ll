; ModuleID = '42_index_func_ret.sy'
source_filename  = "42_index_func_ret.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @_getMaxOfAll(i32*, i32) {
enter_block:
  %2 = alloca i32*
  store i32* %0, i32** %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = alloca i32
  store i32 -999999, i32* %4
  %5 = load i32, i32* %3
  %6 = sub i32 %5, 1
  store i32 %6, i32* %3
  br label %while_block0

while_block0:
  %7 = load i32, i32* %3
  %8 = icmp sgt i32 %7, -1
  br i1 %8, label %while_body1, label %while_next2

while_body1:
  %9 = load i32, i32* %3
  %10 = load i32*, i32** %2
  %11 = getelementptr inbounds i32, i32* %10, i32 %9
  %12 = load i32, i32* %11
  %13 = load i32, i32* %4
  %14 = icmp sgt i32 %12, %13
  br i1 %14, label %then_bb3, label %if_next_bb5

while_next2:
  %15 = load i32, i32* %4
  ret i32 %15

then_bb3:
  %16 = load i32, i32* %3
  %17 = load i32*, i32** %2
  %18 = getelementptr inbounds i32, i32* %17, i32 %16
  %19 = load i32, i32* %18
  store i32 %19, i32* %4
  br label %if_next_bb5

if_next_bb5:
  %20 = load i32, i32* %3
  %21 = sub i32 %20, 1
  store i32 %21, i32* %3
  br label %while_block0
}

define i32 @main() {
enter_block:
  %0 = alloca [3 x i32], i32 3
  %1 = getelementptr inbounds [3 x i32], [3 x i32]* %0, i32 0, i32 0
  store i32 -2, i32* %1
  %2 = getelementptr inbounds [3 x i32], [3 x i32]* %0, i32 0, i32 1
  store i32 2, i32* %2
  %3 = getelementptr inbounds [3 x i32], [3 x i32]* %0, i32 0, i32 2
  store i32 -7, i32* %3
  %4 = alloca i32
  %5 = getelementptr inbounds [3 x i32], [3 x i32]* %0, i32 0, i32 0
  %6 = call i32 @_getMaxOfAll(i32* %5, i32 3)
  %7 = getelementptr inbounds [3 x i32], [3 x i32]* %0, i32 0, i32 %6
  %8 = load i32, i32* %7
  store i32 %8, i32* %4
  %9 = load i32, i32* %4
  call void @putint(i32 %9)
  ret i32 0
}
