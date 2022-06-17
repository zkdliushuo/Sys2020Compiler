; ModuleID = '55_sort_test3.sy'
source_filename  = "55_sort_test3.sy"

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

define i32 @QuickSort(i32*, i32, i32) {
enter_block:
  %3 = alloca i32*
  store i32* %0, i32** %3
  %4 = alloca i32
  store i32 %1, i32* %4
  %5 = alloca i32
  store i32 %2, i32* %5
  %6 = load i32, i32* %4
  %7 = load i32, i32* %5
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %then_bb0, label %if_next_bb2

then_bb0:
  %9 = alloca i32
  %10 = load i32, i32* %4
  store i32 %10, i32* %9
  %11 = alloca i32
  %12 = load i32, i32* %5
  store i32 %12, i32* %11
  %13 = alloca i32
  %14 = load i32, i32* %4
  %15 = load i32*, i32** %3
  %16 = getelementptr inbounds i32, i32* %15, i32 %14
  %17 = load i32, i32* %16
  store i32 %17, i32* %13
  br label %while_block3

if_next_bb2:
  ret i32 0

while_block3:
  %18 = load i32, i32* %9
  %19 = load i32, i32* %11
  %20 = icmp slt i32 %18, %19
  br i1 %20, label %while_body4, label %while_next5

while_body4:
  br label %while_block6

while_next5:
  %21 = load i32, i32* %9
  %22 = load i32*, i32** %3
  %23 = getelementptr inbounds i32, i32* %22, i32 %21
  %24 = load i32, i32* %13
  store i32 %24, i32* %23
  %25 = alloca i32
  %26 = load i32, i32* %9
  %27 = sub i32 %26, 1
  store i32 %27, i32* %25
  %28 = load i32*, i32** %3
  %29 = getelementptr inbounds i32, i32* %28, i32 0
  %30 = load i32, i32* %4
  %31 = load i32, i32* %25
  %32 = call i32 @QuickSort(i32* %29, i32 %30, i32 %31)
  store i32 %32, i32* %25
  %33 = load i32, i32* %9
  %34 = add i32 %33, 1
  store i32 %34, i32* %25
  %35 = load i32*, i32** %3
  %36 = getelementptr inbounds i32, i32* %35, i32 0
  %37 = load i32, i32* %25
  %38 = load i32, i32* %5
  %39 = call i32 @QuickSort(i32* %36, i32 %37, i32 %38)
  store i32 %39, i32* %25
  br label %if_next_bb2

while_block6:
  %40 = load i32, i32* %9
  %41 = load i32, i32* %11
  %42 = icmp slt i32 %40, %41
  br i1 %42, label %next_and_bb9, label %while_next8

while_body7:
  %43 = load i32, i32* %11
  %44 = sub i32 %43, 1
  store i32 %44, i32* %11
  br label %while_block6

while_next8:
  %45 = load i32, i32* %9
  %46 = load i32, i32* %11
  %47 = icmp slt i32 %45, %46
  br i1 %47, label %then_bb10, label %if_next_bb12

next_and_bb9:
  %48 = load i32, i32* %11
  %49 = load i32*, i32** %3
  %50 = getelementptr inbounds i32, i32* %49, i32 %48
  %51 = load i32, i32* %50
  %52 = load i32, i32* %13
  %53 = sub i32 %52, 1
  %54 = icmp sgt i32 %51, %53
  br i1 %54, label %while_body7, label %while_next8

then_bb10:
  %55 = load i32, i32* %9
  %56 = load i32*, i32** %3
  %57 = getelementptr inbounds i32, i32* %56, i32 %55
  %58 = load i32, i32* %11
  %59 = load i32*, i32** %3
  %60 = getelementptr inbounds i32, i32* %59, i32 %58
  %61 = load i32, i32* %60
  store i32 %61, i32* %57
  %62 = load i32, i32* %9
  %63 = add i32 %62, 1
  store i32 %63, i32* %9
  br label %if_next_bb12

if_next_bb12:
  br label %while_block13

while_block13:
  %64 = load i32, i32* %9
  %65 = load i32, i32* %11
  %66 = icmp slt i32 %64, %65
  br i1 %66, label %next_and_bb16, label %while_next15

while_body14:
  %67 = load i32, i32* %9
  %68 = add i32 %67, 1
  store i32 %68, i32* %9
  br label %while_block13

while_next15:
  %69 = load i32, i32* %9
  %70 = load i32, i32* %11
  %71 = icmp slt i32 %69, %70
  br i1 %71, label %then_bb17, label %if_next_bb19

next_and_bb16:
  %72 = load i32, i32* %9
  %73 = load i32*, i32** %3
  %74 = getelementptr inbounds i32, i32* %73, i32 %72
  %75 = load i32, i32* %74
  %76 = load i32, i32* %13
  %77 = icmp slt i32 %75, %76
  br i1 %77, label %while_body14, label %while_next15

then_bb17:
  %78 = load i32, i32* %11
  %79 = load i32*, i32** %3
  %80 = getelementptr inbounds i32, i32* %79, i32 %78
  %81 = load i32, i32* %9
  %82 = load i32*, i32** %3
  %83 = getelementptr inbounds i32, i32* %82, i32 %81
  %84 = load i32, i32* %83
  store i32 %84, i32* %80
  %85 = load i32, i32* %11
  %86 = sub i32 %85, 1
  store i32 %86, i32* %11
  br label %if_next_bb19

if_next_bb19:
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
  store i32 0, i32* %11
  %12 = alloca i32
  store i32 9, i32* %12
  %13 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 0
  %14 = load i32, i32* %11
  %15 = load i32, i32* %12
  %16 = call i32 @QuickSort(i32* %13, i32 %14, i32 %15)
  store i32 %16, i32* %11
  br label %while_block20

while_block20:
  %17 = load i32, i32* %11
  %18 = load i32, i32* @n
  %19 = icmp slt i32 %17, %18
  br i1 %19, label %while_body21, label %while_next22

while_body21:
  %20 = alloca i32
  %21 = load i32, i32* %11
  %22 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 %21
  %23 = load i32, i32* %22
  store i32 %23, i32* %20
  %24 = load i32, i32* %20
  call void @putint(i32 %24)
  store i32 10, i32* %20
  %25 = load i32, i32* %20
  call void @putch(i32 %25)
  %26 = load i32, i32* %11
  %27 = add i32 %26, 1
  store i32 %27, i32* %11
  br label %while_block20

while_next22:
  ret i32 0
}
