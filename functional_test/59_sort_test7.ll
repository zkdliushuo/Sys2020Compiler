; ModuleID = '59_sort_test7.sy'
source_filename  = "59_sort_test7.sy"

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

define i32 @Merge(i32*, i32, i32, i32) {
enter_block:
  %4 = alloca i32*
  store i32* %0, i32** %4
  %5 = alloca i32
  store i32 %1, i32* %5
  %6 = alloca i32
  store i32 %2, i32* %6
  %7 = alloca i32
  store i32 %3, i32* %7
  %8 = alloca i32
  %9 = load i32, i32* %6
  %10 = load i32, i32* %5
  %11 = sub i32 %9, %10
  %12 = add i32 %11, 1
  store i32 %12, i32* %8
  %13 = alloca i32
  %14 = load i32, i32* %7
  %15 = load i32, i32* %6
  %16 = sub i32 %14, %15
  store i32 %16, i32* %13
  %17 = alloca [10 x i32], i32 10
  %18 = alloca [10 x i32], i32 10
  %19 = alloca i32
  store i32 0, i32* %19
  %20 = alloca i32
  store i32 0, i32* %20
  br label %while_block0

while_block0:
  %21 = load i32, i32* %19
  %22 = load i32, i32* %8
  %23 = icmp slt i32 %21, %22
  br i1 %23, label %while_body1, label %while_next2

while_body1:
  %24 = load i32, i32* %19
  %25 = getelementptr inbounds [10 x i32], [10 x i32]* %17, i32 0, i32 %24
  %26 = load i32, i32* %19
  %27 = load i32, i32* %5
  %28 = add i32 %26, %27
  %29 = load i32*, i32** %4
  %30 = getelementptr inbounds i32, i32* %29, i32 %28
  %31 = load i32, i32* %30
  store i32 %31, i32* %25
  %32 = load i32, i32* %19
  %33 = add i32 %32, 1
  store i32 %33, i32* %19
  br label %while_block0

while_next2:
  br label %while_block3

while_block3:
  %34 = load i32, i32* %20
  %35 = load i32, i32* %13
  %36 = icmp slt i32 %34, %35
  br i1 %36, label %while_body4, label %while_next5

while_body4:
  %37 = load i32, i32* %20
  %38 = getelementptr inbounds [10 x i32], [10 x i32]* %18, i32 0, i32 %37
  %39 = load i32, i32* %20
  %40 = load i32, i32* %6
  %41 = add i32 %39, %40
  %42 = add i32 %41, 1
  %43 = load i32*, i32** %4
  %44 = getelementptr inbounds i32, i32* %43, i32 %42
  %45 = load i32, i32* %44
  store i32 %45, i32* %38
  %46 = load i32, i32* %20
  %47 = add i32 %46, 1
  store i32 %47, i32* %20
  br label %while_block3

while_next5:
  store i32 0, i32* %19
  store i32 0, i32* %20
  %48 = alloca i32
  %49 = load i32, i32* %5
  store i32 %49, i32* %48
  br label %while_block6

while_block6:
  %50 = load i32, i32* %19
  %51 = load i32, i32* %8
  %52 = icmp ne i32 %50, %51
  br i1 %52, label %next_and_bb9, label %while_next8

while_body7:
  %53 = load i32, i32* %19
  %54 = getelementptr inbounds [10 x i32], [10 x i32]* %17, i32 0, i32 %53
  %55 = load i32, i32* %54
  %56 = load i32, i32* %20
  %57 = getelementptr inbounds [10 x i32], [10 x i32]* %18, i32 0, i32 %56
  %58 = load i32, i32* %57
  %59 = add i32 %58, 1
  %60 = icmp slt i32 %55, %59
  br i1 %60, label %then_bb10, label %else_bb11

while_next8:
  br label %while_block13

next_and_bb9:
  %61 = load i32, i32* %20
  %62 = load i32, i32* %13
  %63 = icmp ne i32 %61, %62
  br i1 %63, label %while_body7, label %while_next8

then_bb10:
  %64 = load i32, i32* %48
  %65 = load i32*, i32** %4
  %66 = getelementptr inbounds i32, i32* %65, i32 %64
  %67 = load i32, i32* %19
  %68 = getelementptr inbounds [10 x i32], [10 x i32]* %17, i32 0, i32 %67
  %69 = load i32, i32* %68
  store i32 %69, i32* %66
  %70 = load i32, i32* %48
  %71 = add i32 %70, 1
  store i32 %71, i32* %48
  %72 = load i32, i32* %19
  %73 = add i32 %72, 1
  store i32 %73, i32* %19
  br label %if_next_bb12

else_bb11:
  %74 = load i32, i32* %48
  %75 = load i32*, i32** %4
  %76 = getelementptr inbounds i32, i32* %75, i32 %74
  %77 = load i32, i32* %20
  %78 = getelementptr inbounds [10 x i32], [10 x i32]* %18, i32 0, i32 %77
  %79 = load i32, i32* %78
  store i32 %79, i32* %76
  %80 = load i32, i32* %48
  %81 = add i32 %80, 1
  store i32 %81, i32* %48
  %82 = load i32, i32* %20
  %83 = add i32 %82, 1
  store i32 %83, i32* %20
  br label %if_next_bb12

if_next_bb12:
  br label %while_block6

while_block13:
  %84 = load i32, i32* %19
  %85 = load i32, i32* %8
  %86 = icmp slt i32 %84, %85
  br i1 %86, label %while_body14, label %while_next15

while_body14:
  %87 = load i32, i32* %48
  %88 = load i32*, i32** %4
  %89 = getelementptr inbounds i32, i32* %88, i32 %87
  %90 = load i32, i32* %19
  %91 = getelementptr inbounds [10 x i32], [10 x i32]* %17, i32 0, i32 %90
  %92 = load i32, i32* %91
  store i32 %92, i32* %89
  %93 = load i32, i32* %48
  %94 = add i32 %93, 1
  store i32 %94, i32* %48
  %95 = load i32, i32* %19
  %96 = add i32 %95, 1
  store i32 %96, i32* %19
  br label %while_block13

while_next15:
  br label %while_block16

while_block16:
  %97 = load i32, i32* %20
  %98 = load i32, i32* %13
  %99 = icmp slt i32 %97, %98
  br i1 %99, label %while_body17, label %while_next18

while_body17:
  %100 = load i32, i32* %48
  %101 = load i32*, i32** %4
  %102 = getelementptr inbounds i32, i32* %101, i32 %100
  %103 = load i32, i32* %20
  %104 = getelementptr inbounds [10 x i32], [10 x i32]* %18, i32 0, i32 %103
  %105 = load i32, i32* %104
  store i32 %105, i32* %102
  %106 = load i32, i32* %48
  %107 = add i32 %106, 1
  store i32 %107, i32* %48
  %108 = load i32, i32* %20
  %109 = add i32 %108, 1
  store i32 %109, i32* %20
  br label %while_block16

while_next18:
  ret i32 0
}

define i32 @MergeSort(i32*, i32, i32) {
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
  br i1 %8, label %then_bb19, label %if_next_bb21

then_bb19:
  %9 = alloca i32
  %10 = load i32, i32* %4
  %11 = load i32, i32* %5
  %12 = add i32 %10, %11
  %13 = sdiv i32 %12, 2
  store i32 %13, i32* %9
  %14 = alloca i32
  %15 = load i32*, i32** %3
  %16 = getelementptr inbounds i32, i32* %15, i32 0
  %17 = load i32, i32* %4
  %18 = load i32, i32* %9
  %19 = call i32 @MergeSort(i32* %16, i32 %17, i32 %18)
  store i32 %19, i32* %14
  %20 = load i32, i32* %9
  %21 = add i32 %20, 1
  store i32 %21, i32* %14
  %22 = load i32*, i32** %3
  %23 = getelementptr inbounds i32, i32* %22, i32 0
  %24 = load i32, i32* %14
  %25 = load i32, i32* %5
  %26 = call i32 @MergeSort(i32* %23, i32 %24, i32 %25)
  store i32 %26, i32* %14
  %27 = load i32*, i32** %3
  %28 = getelementptr inbounds i32, i32* %27, i32 0
  %29 = load i32, i32* %4
  %30 = load i32, i32* %9
  %31 = load i32, i32* %5
  %32 = call i32 @Merge(i32* %28, i32 %29, i32 %30, i32 %31)
  store i32 %32, i32* %14
  br label %if_next_bb21

if_next_bb21:
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
  %12 = alloca i32
  %13 = load i32, i32* @n
  %14 = sub i32 %13, 1
  store i32 %14, i32* %12
  %15 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 0
  %16 = load i32, i32* %11
  %17 = load i32, i32* %12
  %18 = call i32 @MergeSort(i32* %15, i32 %16, i32 %17)
  store i32 %18, i32* %11
  br label %while_block22

while_block22:
  %19 = load i32, i32* %11
  %20 = load i32, i32* @n
  %21 = icmp slt i32 %19, %20
  br i1 %21, label %while_body23, label %while_next24

while_body23:
  %22 = load i32, i32* %11
  %23 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 %22
  %24 = load i32, i32* %23
  store i32 %24, i32* %12
  %25 = load i32, i32* %12
  call void @putint(i32 %25)
  store i32 10, i32* %12
  %26 = load i32, i32* %12
  call void @putch(i32 %26)
  %27 = load i32, i32* %11
  %28 = add i32 %27, 1
  store i32 %28, i32* %11
  br label %while_block22

while_next24:
  ret i32 0
}
