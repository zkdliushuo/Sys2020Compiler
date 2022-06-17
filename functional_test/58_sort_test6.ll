; ModuleID = '58_sort_test6.sy'
source_filename  = "58_sort_test6.sy"

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

define i32 @counting_sort(i32*, i32*, i32) {
enter_block:
  %3 = alloca i32*
  store i32* %0, i32** %3
  %4 = alloca i32*
  store i32* %1, i32** %4
  %5 = alloca i32
  store i32 %2, i32* %5
  %6 = alloca [10 x i32], i32 10
  %7 = alloca i32
  %8 = alloca i32
  %9 = alloca i32
  store i32 0, i32* %9
  store i32 0, i32* %7
  store i32 0, i32* %8
  br label %while_block0

while_block0:
  %10 = load i32, i32* %9
  %11 = icmp slt i32 %10, 10
  br i1 %11, label %while_body1, label %while_next2

while_body1:
  %12 = load i32, i32* %9
  %13 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %12
  store i32 0, i32* %13
  %14 = load i32, i32* %9
  %15 = add i32 %14, 1
  store i32 %15, i32* %9
  br label %while_block0

while_next2:
  br label %while_block3

while_block3:
  %16 = load i32, i32* %7
  %17 = load i32, i32* %5
  %18 = icmp slt i32 %16, %17
  br i1 %18, label %while_body4, label %while_next5

while_body4:
  %19 = load i32, i32* %7
  %20 = load i32*, i32** %3
  %21 = getelementptr inbounds i32, i32* %20, i32 %19
  %22 = load i32, i32* %21
  %23 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %22
  %24 = load i32, i32* %7
  %25 = load i32*, i32** %3
  %26 = getelementptr inbounds i32, i32* %25, i32 %24
  %27 = load i32, i32* %26
  %28 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %27
  %29 = load i32, i32* %28
  %30 = add i32 %29, 1
  store i32 %30, i32* %23
  %31 = load i32, i32* %7
  %32 = add i32 %31, 1
  store i32 %32, i32* %7
  br label %while_block3

while_next5:
  store i32 1, i32* %9
  br label %while_block6

while_block6:
  %33 = load i32, i32* %9
  %34 = icmp slt i32 %33, 10
  br i1 %34, label %while_body7, label %while_next8

while_body7:
  %35 = load i32, i32* %9
  %36 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %35
  %37 = load i32, i32* %9
  %38 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %37
  %39 = load i32, i32* %38
  %40 = load i32, i32* %9
  %41 = sub i32 %40, 1
  %42 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %41
  %43 = load i32, i32* %42
  %44 = add i32 %39, %43
  store i32 %44, i32* %36
  %45 = load i32, i32* %9
  %46 = add i32 %45, 1
  store i32 %46, i32* %9
  br label %while_block6

while_next8:
  %47 = load i32, i32* %5
  store i32 %47, i32* %8
  br label %while_block9

while_block9:
  %48 = load i32, i32* %8
  %49 = icmp sgt i32 %48, 0
  br i1 %49, label %while_body10, label %while_next11

while_body10:
  %50 = load i32, i32* %8
  %51 = sub i32 %50, 1
  %52 = load i32*, i32** %3
  %53 = getelementptr inbounds i32, i32* %52, i32 %51
  %54 = load i32, i32* %53
  %55 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %54
  %56 = load i32, i32* %8
  %57 = sub i32 %56, 1
  %58 = load i32*, i32** %3
  %59 = getelementptr inbounds i32, i32* %58, i32 %57
  %60 = load i32, i32* %59
  %61 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %60
  %62 = load i32, i32* %61
  %63 = sub i32 %62, 1
  store i32 %63, i32* %55
  %64 = load i32, i32* %8
  %65 = sub i32 %64, 1
  %66 = load i32*, i32** %3
  %67 = getelementptr inbounds i32, i32* %66, i32 %65
  %68 = load i32, i32* %67
  %69 = getelementptr inbounds [10 x i32], [10 x i32]* %6, i32 0, i32 %68
  %70 = load i32, i32* %69
  %71 = load i32*, i32** %4
  %72 = getelementptr inbounds i32, i32* %71, i32 %70
  %73 = load i32, i32* %8
  %74 = sub i32 %73, 1
  %75 = load i32*, i32** %3
  %76 = getelementptr inbounds i32, i32* %75, i32 %74
  %77 = load i32, i32* %76
  store i32 %77, i32* %72
  %78 = load i32, i32* %8
  %79 = sub i32 %78, 1
  store i32 %79, i32* %8
  br label %while_block9

while_next11:
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
  %12 = alloca [10 x i32], i32 10
  %13 = getelementptr inbounds [10 x i32], [10 x i32]* %0, i32 0, i32 0
  %14 = getelementptr inbounds [10 x i32], [10 x i32]* %12, i32 0, i32 0
  %15 = load i32, i32* @n
  %16 = call i32 @counting_sort(i32* %13, i32* %14, i32 %15)
  store i32 %16, i32* %11
  br label %while_block12

while_block12:
  %17 = load i32, i32* %11
  %18 = load i32, i32* @n
  %19 = icmp slt i32 %17, %18
  br i1 %19, label %while_body13, label %while_next14

while_body13:
  %20 = alloca i32
  %21 = load i32, i32* %11
  %22 = getelementptr inbounds [10 x i32], [10 x i32]* %12, i32 0, i32 %21
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
  br label %while_block12

while_next14:
  ret i32 0
}
