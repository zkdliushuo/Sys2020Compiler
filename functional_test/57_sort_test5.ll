; ModuleID = '57_sort_test5.sy'
source_filename  = "57_sort_test5.sy"

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

define i32 @swap(i32*, i32, i32) {
enter_block:
  %3 = alloca i32*
  store i32* %0, i32** %3
  %4 = alloca i32
  store i32 %1, i32* %4
  %5 = alloca i32
  store i32 %2, i32* %5
  %6 = alloca i32
  %7 = load i32, i32* %4
  %8 = load i32*, i32** %3
  %9 = getelementptr inbounds i32, i32* %8, i32 %7
  %10 = load i32, i32* %9
  store i32 %10, i32* %6
  %11 = load i32, i32* %4
  %12 = load i32*, i32** %3
  %13 = getelementptr inbounds i32, i32* %12, i32 %11
  %14 = load i32, i32* %5
  %15 = load i32*, i32** %3
  %16 = getelementptr inbounds i32, i32* %15, i32 %14
  %17 = load i32, i32* %16
  store i32 %17, i32* %13
  %18 = load i32, i32* %5
  %19 = load i32*, i32** %3
  %20 = getelementptr inbounds i32, i32* %19, i32 %18
  %21 = load i32, i32* %6
  store i32 %21, i32* %20
  ret i32 0
}

define i32 @heap_ajust(i32*, i32, i32) {
enter_block:
  %3 = alloca i32*
  store i32* %0, i32** %3
  %4 = alloca i32
  store i32 %1, i32* %4
  %5 = alloca i32
  store i32 %2, i32* %5
  %6 = alloca i32
  %7 = load i32, i32* %4
  store i32 %7, i32* %6
  %8 = alloca i32
  %9 = load i32, i32* %6
  %10 = mul i32 %9, 2
  %11 = add i32 %10, 1
  store i32 %11, i32* %8
  br label %while_block0

while_block0:
  %12 = load i32, i32* %8
  %13 = load i32, i32* %5
  %14 = add i32 %13, 1
  %15 = icmp slt i32 %12, %14
  br i1 %15, label %while_body1, label %while_next2

while_body1:
  %16 = load i32, i32* %8
  %17 = load i32, i32* %5
  %18 = icmp slt i32 %16, %17
  br i1 %18, label %next_and_bb6, label %if_next_bb5

while_next2:
  ret i32 0

then_bb3:
  %19 = load i32, i32* %8
  %20 = add i32 %19, 1
  store i32 %20, i32* %8
  br label %if_next_bb5

if_next_bb5:
  %21 = load i32, i32* %6
  %22 = load i32*, i32** %3
  %23 = getelementptr inbounds i32, i32* %22, i32 %21
  %24 = load i32, i32* %23
  %25 = load i32, i32* %8
  %26 = load i32*, i32** %3
  %27 = getelementptr inbounds i32, i32* %26, i32 %25
  %28 = load i32, i32* %27
  %29 = icmp sgt i32 %24, %28
  br i1 %29, label %then_bb7, label %else_bb8

next_and_bb6:
  %30 = load i32, i32* %8
  %31 = load i32*, i32** %3
  %32 = getelementptr inbounds i32, i32* %31, i32 %30
  %33 = load i32, i32* %32
  %34 = load i32, i32* %8
  %35 = add i32 %34, 1
  %36 = load i32*, i32** %3
  %37 = getelementptr inbounds i32, i32* %36, i32 %35
  %38 = load i32, i32* %37
  %39 = icmp slt i32 %33, %38
  br i1 %39, label %then_bb3, label %if_next_bb5

then_bb7:
  ret i32 0

else_bb8:
  %40 = load i32*, i32** %3
  %41 = getelementptr inbounds i32, i32* %40, i32 0
  %42 = load i32, i32* %6
  %43 = load i32, i32* %8
  %44 = call i32 @swap(i32* %41, i32 %42, i32 %43)
  store i32 %44, i32* %6
  %45 = load i32, i32* %8
  store i32 %45, i32* %6
  %46 = load i32, i32* %6
  %47 = mul i32 %46, 2
  %48 = add i32 %47, 1
  store i32 %48, i32* %8
  br label %if_next_bb9

if_next_bb9:
  br label %while_block0
}

define i32 @heap_sort(i32*, i32) {
enter_block:
  %2 = alloca i32*
  store i32* %0, i32** %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = alloca i32
  %5 = alloca i32
  %6 = load i32, i32* %3
  %7 = sdiv i32 %6, 2
  %8 = sub i32 %7, 1
  store i32 %8, i32* %4
  br label %while_block10

while_block10:
  %9 = load i32, i32* %4
  %10 = icmp sgt i32 %9, -1
  br i1 %10, label %while_body11, label %while_next12

while_body11:
  %11 = load i32, i32* %3
  %12 = sub i32 %11, 1
  store i32 %12, i32* %5
  %13 = load i32*, i32** %2
  %14 = getelementptr inbounds i32, i32* %13, i32 0
  %15 = load i32, i32* %4
  %16 = load i32, i32* %5
  %17 = call i32 @heap_ajust(i32* %14, i32 %15, i32 %16)
  store i32 %17, i32* %5
  %18 = load i32, i32* %4
  %19 = sub i32 %18, 1
  store i32 %19, i32* %4
  br label %while_block10

while_next12:
  %20 = load i32, i32* %3
  %21 = sub i32 %20, 1
  store i32 %21, i32* %4
  br label %while_block13

while_block13:
  %22 = load i32, i32* %4
  %23 = icmp sgt i32 %22, 0
  br i1 %23, label %while_body14, label %while_next15

while_body14:
  %24 = alloca i32
  store i32 0, i32* %24
  %25 = load i32*, i32** %2
  %26 = getelementptr inbounds i32, i32* %25, i32 0
  %27 = load i32, i32* %24
  %28 = load i32, i32* %4
  %29 = call i32 @swap(i32* %26, i32 %27, i32 %28)
  store i32 %29, i32* %5
  %30 = load i32, i32* %4
  %31 = sub i32 %30, 1
  store i32 %31, i32* %5
  %32 = load i32*, i32** %2
  %33 = getelementptr inbounds i32, i32* %32, i32 0
  %34 = load i32, i32* %24
  %35 = load i32, i32* %5
  %36 = call i32 @heap_ajust(i32* %33, i32 %34, i32 %35)
  store i32 %36, i32* %5
  %37 = load i32, i32* %4
  %38 = sub i32 %37, 1
  store i32 %38, i32* %4
  br label %while_block13

while_next15:
  ret i32 0
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
  %14 = call i32 @heap_sort(i32* %12, i32 %13)
  store i32 %14, i32* %11
  br label %while_block16

while_block16:
  %15 = load i32, i32* %11
  %16 = load i32, i32* @n
  %17 = icmp slt i32 %15, %16
  br i1 %17, label %while_body17, label %while_next18

while_body17:
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
  br label %while_block16

while_next18:
  ret i32 0
}
