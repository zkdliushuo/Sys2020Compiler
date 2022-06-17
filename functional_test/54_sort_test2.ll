; ModuleID = '54_sort_test2.sy'
source_filename  = "54_sort_test2.sy"

@n = global i32 0

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @insertsort(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  store i32 1, i32* %2
  br label %while_block0

while_block0:
  %3 = load i32, i32* %2
  %4 = load i32, i32* @n
  %5 = icmp slt i32 %3, %4
  br i1 %5, label %while_body1, label %while_next2

while_body1:
  %6 = alloca i32
  %7 = load i32, i32* %2
  %8 = load i32*, i32** %1
  %9 = getelementptr inbounds i32, i32* %8, i32 %7
  %10 = load i32, i32* %9
  store i32 %10, i32* %6
  %11 = alloca i32
  %12 = load i32, i32* %2
  %13 = sub i32 %12, 1
  store i32 %13, i32* %11
  br label %while_block3

while_next2:
  ret i32 0

while_block3:
  %14 = load i32, i32* %11
  %15 = icmp sgt i32 %14, -1
  br i1 %15, label %next_and_bb6, label %while_next5

while_body4:
  %16 = load i32, i32* %11
  %17 = add i32 %16, 1
  %18 = load i32*, i32** %1
  %19 = getelementptr inbounds i32, i32* %18, i32 %17
  %20 = load i32, i32* %11
  %21 = load i32*, i32** %1
  %22 = getelementptr inbounds i32, i32* %21, i32 %20
  %23 = load i32, i32* %22
  store i32 %23, i32* %19
  %24 = load i32, i32* %11
  %25 = sub i32 %24, 1
  store i32 %25, i32* %11
  br label %while_block3

while_next5:
  %26 = load i32, i32* %11
  %27 = add i32 %26, 1
  %28 = load i32*, i32** %1
  %29 = getelementptr inbounds i32, i32* %28, i32 %27
  %30 = load i32, i32* %6
  store i32 %30, i32* %29
  %31 = load i32, i32* %2
  %32 = add i32 %31, 1
  store i32 %32, i32* %2
  br label %while_block0

next_and_bb6:
  %33 = load i32, i32* %6
  %34 = load i32, i32* %11
  %35 = load i32*, i32** %1
  %36 = getelementptr inbounds i32, i32* %35, i32 %34
  %37 = load i32, i32* %36
  %38 = icmp slt i32 %33, %37
  br i1 %38, label %while_body4, label %while_next5
}

define i32 @main() {
enter_block:
  store i32 10, i32* @n
  %0 = alloca [10 x i32], i32 10
  %1 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 0
  store i32 4, i32* %1
  %2 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 1
  store i32 3, i32* %2
  %3 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 2
  store i32 9, i32* %3
  %4 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 3
  store i32 2, i32* %4
  %5 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 4
  store i32 0, i32* %5
  %6 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 5
  store i32 1, i32* %6
  %7 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 6
  store i32 6, i32* %7
  %8 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 7
  store i32 5, i32* %8
  %9 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 8
  store i32 7, i32* %9
  %10 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 9
  store i32 8, i32* %10
  %11 = alloca i32
  %12 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 0
  %13 = call i32 @insertsort(i32* %12)
  store i32 %13, i32* %11
  br label %while_block7

while_block7:
  %14 = load i32, i32* %11
  %15 = load i32, i32* @n
  %16 = icmp slt i32 %14, %15
  br i1 %16, label %while_body8, label %while_next9

while_body8:
  %17 = alloca i32
  %18 = load i32, i32* %11
  %19 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 %18
  %20 = load i32, i32* %19
  store i32 %20, i32* %17
  %21 = load i32, i32* %17
  call void @putint(i32 %21)
  store i32 10, i32* %17
  %22 = load i32, i32* %17
  call void @putch(i32 %22)
  %23 = load i32, i32* %11
  %24 = add i32 %23, 1
  store i32 %24, i32* %11
  br label %while_block7

while_next9:
  ret i32 0
}
