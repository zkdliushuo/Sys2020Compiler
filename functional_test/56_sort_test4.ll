; ModuleID = '56_sort_test4.sy'
source_filename  = "56_sort_test4.sy"

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

define i32 @select_sort(i32*, i32) {
enter_block:
  %2 = alloca i32*
  store i32* %0, i32** %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = alloca i32
  %5 = alloca i32
  %6 = alloca i32
  store i32 0, i32* %4
  br label %while_block0

while_block0:
  %7 = load i32, i32* %4
  %8 = load i32, i32* %3
  %9 = sub i32 %8, 1
  %10 = icmp slt i32 %7, %9
  br i1 %10, label %while_body1, label %while_next2

while_body1:
  %11 = load i32, i32* %4
  store i32 %11, i32* %6
  %12 = load i32, i32* %4
  %13 = add i32 %12, 1
  store i32 %13, i32* %5
  br label %while_block3

while_next2:
  ret i32 0

while_block3:
  %14 = load i32, i32* %5
  %15 = load i32, i32* %3
  %16 = icmp slt i32 %14, %15
  br i1 %16, label %while_body4, label %while_next5

while_body4:
  %17 = load i32, i32* %6
  %18 = load i32*, i32** %2
  %19 = getelementptr inbounds i32, i32* %18, i32 %17
  %20 = load i32, i32* %19
  %21 = load i32, i32* %5
  %22 = load i32*, i32** %2
  %23 = getelementptr inbounds i32, i32* %22, i32 %21
  %24 = load i32, i32* %23
  %25 = icmp sgt i32 %20, %24
  br i1 %25, label %then_bb6, label %if_next_bb8

while_next5:
  %26 = load i32, i32* %6
  %27 = load i32, i32* %4
  %28 = icmp ne i32 %26, %27
  br i1 %28, label %then_bb9, label %if_next_bb11

then_bb6:
  %29 = load i32, i32* %5
  store i32 %29, i32* %6
  br label %if_next_bb8

if_next_bb8:
  %30 = load i32, i32* %5
  %31 = add i32 %30, 1
  store i32 %31, i32* %5
  br label %while_block3

then_bb9:
  %32 = alloca i32
  %33 = load i32, i32* %6
  %34 = load i32*, i32** %2
  %35 = getelementptr inbounds i32, i32* %34, i32 %33
  %36 = load i32, i32* %35
  store i32 %36, i32* %32
  %37 = load i32, i32* %6
  %38 = load i32*, i32** %2
  %39 = getelementptr inbounds i32, i32* %38, i32 %37
  %40 = load i32, i32* %4
  %41 = load i32*, i32** %2
  %42 = getelementptr inbounds i32, i32* %41, i32 %40
  %43 = load i32, i32* %42
  store i32 %43, i32* %39
  %44 = load i32, i32* %4
  %45 = load i32*, i32** %2
  %46 = getelementptr inbounds i32, i32* %45, i32 %44
  %47 = load i32, i32* %32
  store i32 %47, i32* %46
  br label %if_next_bb11

if_next_bb11:
  %48 = load i32, i32* %4
  %49 = add i32 %48, 1
  store i32 %49, i32* %4
  br label %while_block0
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
  store i32 0, i32* %11
  %12 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 0
  %13 = load i32, i32* @n
  %14 = call i32 @select_sort(i32* %12, i32 %13)
  store i32 %14, i32* %11
  br label %while_block12

while_block12:
  %15 = load i32, i32* %11
  %16 = load i32, i32* @n
  %17 = icmp slt i32 %15, %16
  br i1 %17, label %while_body13, label %while_next14

while_body13:
  %18 = alloca i32
  %19 = load i32, i32* %11
  %20 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 %19
  %21 = load i32, i32* %20
  store i32 %21, i32* %18
  %22 = load i32, i32* %18
  call void @putint(i32 %22)
  store i32 10, i32* %18
  %23 = load i32, i32* %18
  call void @putch(i32 %23)
  %24 = load i32, i32* %11
  %25 = add i32 %24, 1
  store i32 %25, i32* %11
  br label %while_block12

while_next14:
  ret i32 0
}
