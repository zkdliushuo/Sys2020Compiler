; ModuleID = '53_sort_test1.sy'
source_filename  = "53_sort_test1.sy"

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

define i32 @bubblesort(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  %3 = alloca i32
  store i32 0, i32* %2
  br label %while_block0

while_block0:
  %4 = load i32, i32* %2
  %5 = load i32, i32* @n
  %6 = sub i32 %5, 1
  %7 = icmp slt i32 %4, %6
  br i1 %7, label %while_body1, label %while_next2

while_body1:
  store i32 0, i32* %3
  br label %while_block3

while_next2:
  ret i32 0

while_block3:
  %8 = load i32, i32* %3
  %9 = load i32, i32* @n
  %10 = load i32, i32* %2
  %11 = sub i32 %9, %10
  %12 = sub i32 %11, 1
  %13 = icmp slt i32 %8, %12
  br i1 %13, label %while_body4, label %while_next5

while_body4:
  %14 = load i32, i32* %3
  %15 = load i32*, i32** %1
  %16 = getelementptr inbounds i32, i32* %15, i32 %14
  %17 = load i32, i32* %16
  %18 = load i32, i32* %3
  %19 = add i32 %18, 1
  %20 = load i32*, i32** %1
  %21 = getelementptr inbounds i32, i32* %20, i32 %19
  %22 = load i32, i32* %21
  %23 = icmp sgt i32 %17, %22
  br i1 %23, label %then_bb6, label %if_next_bb8

while_next5:
  %24 = load i32, i32* %2
  %25 = add i32 %24, 1
  store i32 %25, i32* %2
  br label %while_block0

then_bb6:
  %26 = alloca i32
  %27 = load i32, i32* %3
  %28 = add i32 %27, 1
  %29 = load i32*, i32** %1
  %30 = getelementptr inbounds i32, i32* %29, i32 %28
  %31 = load i32, i32* %30
  store i32 %31, i32* %26
  %32 = load i32, i32* %3
  %33 = add i32 %32, 1
  %34 = load i32*, i32** %1
  %35 = getelementptr inbounds i32, i32* %34, i32 %33
  %36 = load i32, i32* %3
  %37 = load i32*, i32** %1
  %38 = getelementptr inbounds i32, i32* %37, i32 %36
  %39 = load i32, i32* %38
  store i32 %39, i32* %35
  %40 = load i32, i32* %3
  %41 = load i32*, i32** %1
  %42 = getelementptr inbounds i32, i32* %41, i32 %40
  %43 = load i32, i32* %26
  store i32 %43, i32* %42
  br label %if_next_bb8

if_next_bb8:
  %44 = load i32, i32* %3
  %45 = add i32 %44, 1
  store i32 %45, i32* %3
  br label %while_block3
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
  %13 = call i32 @bubblesort(i32* %12)
  store i32 %13, i32* %11
  br label %while_block9

while_block9:
  %14 = load i32, i32* %11
  %15 = load i32, i32* @n
  %16 = icmp slt i32 %14, %15
  br i1 %16, label %while_body10, label %while_next11

while_body10:
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
  br label %while_block9

while_next11:
  ret i32 0
}
