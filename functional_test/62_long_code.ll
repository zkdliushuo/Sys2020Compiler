; ModuleID = '62_long_code.sy'
source_filename  = "62_long_code.sy"

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

define i32 @insertsort(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  store i32 1, i32* %2
  br label %while_block9

while_block9:
  %3 = load i32, i32* %2
  %4 = load i32, i32* @n
  %5 = icmp slt i32 %3, %4
  br i1 %5, label %while_body10, label %while_next11

while_body10:
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
  br label %while_block12

while_next11:
  ret i32 0

while_block12:
  %14 = load i32, i32* %11
  %15 = icmp sgt i32 %14, -1
  br i1 %15, label %next_and_bb15, label %while_next14

while_body13:
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
  br label %while_block12

while_next14:
  %26 = load i32, i32* %11
  %27 = add i32 %26, 1
  %28 = load i32*, i32** %1
  %29 = getelementptr inbounds i32, i32* %28, i32 %27
  %30 = load i32, i32* %6
  store i32 %30, i32* %29
  %31 = load i32, i32* %2
  %32 = add i32 %31, 1
  store i32 %32, i32* %2
  br label %while_block9

next_and_bb15:
  %33 = load i32, i32* %6
  %34 = load i32, i32* %11
  %35 = load i32*, i32** %1
  %36 = getelementptr inbounds i32, i32* %35, i32 %34
  %37 = load i32, i32* %36
  %38 = icmp slt i32 %33, %37
  br i1 %38, label %while_body13, label %while_next14
}

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
  br i1 %8, label %then_bb16, label %if_next_bb18

then_bb16:
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
  br label %while_block19

if_next_bb18:
  ret i32 0

while_block19:
  %18 = load i32, i32* %9
  %19 = load i32, i32* %11
  %20 = icmp slt i32 %18, %19
  br i1 %20, label %while_body20, label %while_next21

while_body20:
  br label %while_block22

while_next21:
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
  br label %if_next_bb18

while_block22:
  %40 = load i32, i32* %9
  %41 = load i32, i32* %11
  %42 = icmp slt i32 %40, %41
  br i1 %42, label %next_and_bb25, label %while_next24

while_body23:
  %43 = load i32, i32* %11
  %44 = sub i32 %43, 1
  store i32 %44, i32* %11
  br label %while_block22

while_next24:
  %45 = load i32, i32* %9
  %46 = load i32, i32* %11
  %47 = icmp slt i32 %45, %46
  br i1 %47, label %then_bb26, label %if_next_bb28

next_and_bb25:
  %48 = load i32, i32* %11
  %49 = load i32*, i32** %3
  %50 = getelementptr inbounds i32, i32* %49, i32 %48
  %51 = load i32, i32* %50
  %52 = load i32, i32* %13
  %53 = sub i32 %52, 1
  %54 = icmp sgt i32 %51, %53
  br i1 %54, label %while_body23, label %while_next24

then_bb26:
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
  br label %if_next_bb28

if_next_bb28:
  br label %while_block29

while_block29:
  %64 = load i32, i32* %9
  %65 = load i32, i32* %11
  %66 = icmp slt i32 %64, %65
  br i1 %66, label %next_and_bb32, label %while_next31

while_body30:
  %67 = load i32, i32* %9
  %68 = add i32 %67, 1
  store i32 %68, i32* %9
  br label %while_block29

while_next31:
  %69 = load i32, i32* %9
  %70 = load i32, i32* %11
  %71 = icmp slt i32 %69, %70
  br i1 %71, label %then_bb33, label %if_next_bb35

next_and_bb32:
  %72 = load i32, i32* %9
  %73 = load i32*, i32** %3
  %74 = getelementptr inbounds i32, i32* %73, i32 %72
  %75 = load i32, i32* %74
  %76 = load i32, i32* %13
  %77 = icmp slt i32 %75, %76
  br i1 %77, label %while_body30, label %while_next31

then_bb33:
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
  br label %if_next_bb35

if_next_bb35:
  br label %while_block19
}

define i32 @getMid(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  %3 = load i32, i32* @n
  %4 = srem i32 %3, 2
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %then_bb36, label %else_bb37

then_bb36:
  %6 = load i32, i32* @n
  %7 = sdiv i32 %6, 2
  store i32 %7, i32* %2
  %8 = load i32, i32* %2
  %9 = load i32*, i32** %1
  %10 = getelementptr inbounds i32, i32* %9, i32 %8
  %11 = load i32, i32* %10
  %12 = load i32, i32* %2
  %13 = sub i32 %12, 1
  %14 = load i32*, i32** %1
  %15 = getelementptr inbounds i32, i32* %14, i32 %13
  %16 = load i32, i32* %15
  %17 = add i32 %11, %16
  %18 = sdiv i32 %17, 2
  ret i32 %18

else_bb37:
  %19 = load i32, i32* @n
  %20 = sdiv i32 %19, 2
  store i32 %20, i32* %2
  %21 = load i32, i32* %2
  %22 = load i32*, i32** %1
  %23 = getelementptr inbounds i32, i32* %22, i32 %21
  %24 = load i32, i32* %23
  ret i32 %24
}

define i32 @getMost(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca [1000 x i32], i32 1000
  %3 = alloca i32
  store i32 0, i32* %3
  br label %while_block39

while_block39:
  %4 = load i32, i32* %3
  %5 = icmp slt i32 %4, 1000
  br i1 %5, label %while_body40, label %while_next41

while_body40:
  %6 = load i32, i32* %3
  %7 = getelementptr inbounds [1000 x i32], [1000 x i32]* %2, i32 0, i32 %6
  store i32 0, i32* %7
  %8 = load i32, i32* %3
  %9 = add i32 %8, 1
  store i32 %9, i32* %3
  br label %while_block39

while_next41:
  store i32 0, i32* %3
  %10 = alloca i32
  %11 = alloca i32
  store i32 0, i32* %10
  br label %while_block42

while_block42:
  %12 = load i32, i32* %3
  %13 = load i32, i32* @n
  %14 = icmp slt i32 %12, %13
  br i1 %14, label %while_body43, label %while_next44

while_body43:
  %15 = alloca i32
  %16 = load i32, i32* %3
  %17 = load i32*, i32** %1
  %18 = getelementptr inbounds i32, i32* %17, i32 %16
  %19 = load i32, i32* %18
  store i32 %19, i32* %15
  %20 = load i32, i32* %15
  %21 = getelementptr inbounds [1000 x i32], [1000 x i32]* %2, i32 0, i32 %20
  %22 = load i32, i32* %15
  %23 = getelementptr inbounds [1000 x i32], [1000 x i32]* %2, i32 0, i32 %22
  %24 = load i32, i32* %23
  %25 = add i32 %24, 1
  store i32 %25, i32* %21
  %26 = load i32, i32* %15
  %27 = getelementptr inbounds [1000 x i32], [1000 x i32]* %2, i32 0, i32 %26
  %28 = load i32, i32* %27
  %29 = load i32, i32* %10
  %30 = icmp sgt i32 %28, %29
  br i1 %30, label %then_bb45, label %if_next_bb47

while_next44:
  %31 = load i32, i32* %11
  ret i32 %31

then_bb45:
  %32 = load i32, i32* %15
  %33 = getelementptr inbounds [1000 x i32], [1000 x i32]* %2, i32 0, i32 %32
  %34 = load i32, i32* %33
  store i32 %34, i32* %10
  %35 = load i32, i32* %15
  store i32 %35, i32* %11
  br label %if_next_bb47

if_next_bb47:
  %36 = load i32, i32* %3
  %37 = add i32 %36, 1
  store i32 %37, i32* %3
  br label %while_block42
}

define i32 @revert(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  %3 = alloca i32
  %4 = alloca i32
  store i32 0, i32* %3
  store i32 0, i32* %4
  br label %while_block48

while_block48:
  %5 = load i32, i32* %3
  %6 = load i32, i32* %4
  %7 = icmp slt i32 %5, %6
  br i1 %7, label %while_body49, label %while_next50

while_body49:
  %8 = load i32, i32* %3
  %9 = load i32*, i32** %1
  %10 = getelementptr inbounds i32, i32* %9, i32 %8
  %11 = load i32, i32* %10
  store i32 %11, i32* %2
  %12 = load i32, i32* %3
  %13 = load i32*, i32** %1
  %14 = getelementptr inbounds i32, i32* %13, i32 %12
  %15 = load i32, i32* %4
  %16 = load i32*, i32** %1
  %17 = getelementptr inbounds i32, i32* %16, i32 %15
  %18 = load i32, i32* %17
  store i32 %18, i32* %14
  %19 = load i32, i32* %4
  %20 = load i32*, i32** %1
  %21 = getelementptr inbounds i32, i32* %20, i32 %19
  %22 = load i32, i32* %2
  store i32 %22, i32* %21
  %23 = load i32, i32* %3
  %24 = add i32 %23, 1
  store i32 %24, i32* %3
  %25 = load i32, i32* %4
  %26 = sub i32 %25, 1
  store i32 %26, i32* %4
  br label %while_block48

while_next50:
  ret i32 0
}

define i32 @arrCopy(i32*, i32*) {
enter_block:
  %2 = alloca i32*
  store i32* %0, i32** %2
  %3 = alloca i32*
  store i32* %1, i32** %3
  %4 = alloca i32
  store i32 0, i32* %4
  br label %while_block51

while_block51:
  %5 = load i32, i32* %4
  %6 = load i32, i32* @n
  %7 = icmp slt i32 %5, %6
  br i1 %7, label %while_body52, label %while_next53

while_body52:
  %8 = load i32, i32* %4
  %9 = load i32*, i32** %3
  %10 = getelementptr inbounds i32, i32* %9, i32 %8
  %11 = load i32, i32* %4
  %12 = load i32*, i32** %2
  %13 = getelementptr inbounds i32, i32* %12, i32 %11
  %14 = load i32, i32* %13
  store i32 %14, i32* %10
  %15 = load i32, i32* %4
  %16 = add i32 %15, 1
  store i32 %16, i32* %4
  br label %while_block51

while_next53:
  ret i32 0
}

define i32 @calSum(i32*, i32) {
enter_block:
  %2 = alloca i32*
  store i32* %0, i32** %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = alloca i32
  store i32 0, i32* %4
  %5 = alloca i32
  store i32 0, i32* %5
  br label %while_block54

while_block54:
  %6 = load i32, i32* %5
  %7 = load i32, i32* @n
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %while_body55, label %while_next56

while_body55:
  %9 = load i32, i32* %4
  %10 = load i32, i32* %5
  %11 = load i32*, i32** %2
  %12 = getelementptr inbounds i32, i32* %11, i32 %10
  %13 = load i32, i32* %12
  %14 = add i32 %9, %13
  store i32 %14, i32* %4
  %15 = load i32, i32* %5
  %16 = load i32, i32* %3
  %17 = srem i32 %15, %16
  %18 = load i32, i32* %3
  %19 = sub i32 %18, 1
  %20 = icmp ne i32 %17, %19
  br i1 %20, label %then_bb57, label %else_bb58

while_next56:
  ret i32 0

then_bb57:
  %21 = load i32, i32* %5
  %22 = load i32*, i32** %2
  %23 = getelementptr inbounds i32, i32* %22, i32 %21
  store i32 0, i32* %23
  br label %if_next_bb59

else_bb58:
  %24 = load i32, i32* %5
  %25 = load i32*, i32** %2
  %26 = getelementptr inbounds i32, i32* %25, i32 %24
  %27 = load i32, i32* %4
  store i32 %27, i32* %26
  store i32 0, i32* %4
  br label %if_next_bb59

if_next_bb59:
  %28 = load i32, i32* %5
  %29 = add i32 %28, 1
  store i32 %29, i32* %5
  br label %while_block54
}

define i32 @avgPooling(i32*, i32) {
enter_block:
  %2 = alloca i32*
  store i32* %0, i32** %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = alloca i32
  %5 = alloca i32
  store i32 0, i32* %5
  store i32 0, i32* %4
  %6 = alloca i32
  br label %while_block60

while_block60:
  %7 = load i32, i32* %5
  %8 = load i32, i32* @n
  %9 = icmp slt i32 %7, %8
  br i1 %9, label %while_body61, label %while_next62

while_body61:
  %10 = load i32, i32* %5
  %11 = load i32, i32* %3
  %12 = sub i32 %11, 1
  %13 = icmp slt i32 %10, %12
  br i1 %13, label %then_bb63, label %else_bb64

while_next62:
  %14 = load i32, i32* @n
  %15 = load i32, i32* %3
  %16 = sub i32 %14, %15
  %17 = add i32 %16, 1
  store i32 %17, i32* %5
  br label %while_block69

then_bb63:
  %18 = load i32, i32* %4
  %19 = load i32, i32* %5
  %20 = load i32*, i32** %2
  %21 = getelementptr inbounds i32, i32* %20, i32 %19
  %22 = load i32, i32* %21
  %23 = add i32 %18, %22
  store i32 %23, i32* %4
  br label %if_next_bb65

else_bb64:
  %24 = load i32, i32* %5
  %25 = load i32, i32* %3
  %26 = sub i32 %25, 1
  %27 = icmp eq i32 %24, %26
  br i1 %27, label %then_bb66, label %else_bb67

if_next_bb65:
  %28 = load i32, i32* %5
  %29 = add i32 %28, 1
  store i32 %29, i32* %5
  br label %while_block60

then_bb66:
  %30 = load i32*, i32** %2
  %31 = getelementptr inbounds i32, i32* %30, i32 0
  %32 = load i32, i32* %31
  store i32 %32, i32* %6
  %33 = load i32*, i32** %2
  %34 = getelementptr inbounds i32, i32* %33, i32 0
  %35 = load i32, i32* %4
  %36 = load i32, i32* %3
  %37 = sdiv i32 %35, %36
  store i32 %37, i32* %34
  br label %if_next_bb68

else_bb67:
  %38 = load i32, i32* %4
  %39 = load i32, i32* %5
  %40 = load i32*, i32** %2
  %41 = getelementptr inbounds i32, i32* %40, i32 %39
  %42 = load i32, i32* %41
  %43 = add i32 %38, %42
  %44 = load i32, i32* %6
  %45 = sub i32 %43, %44
  store i32 %45, i32* %4
  %46 = load i32, i32* %5
  %47 = load i32, i32* %3
  %48 = sub i32 %46, %47
  %49 = add i32 %48, 1
  %50 = load i32*, i32** %2
  %51 = getelementptr inbounds i32, i32* %50, i32 %49
  %52 = load i32, i32* %51
  store i32 %52, i32* %6
  %53 = load i32, i32* %5
  %54 = load i32, i32* %3
  %55 = sub i32 %53, %54
  %56 = add i32 %55, 1
  %57 = load i32*, i32** %2
  %58 = getelementptr inbounds i32, i32* %57, i32 %56
  %59 = load i32, i32* %4
  %60 = load i32, i32* %3
  %61 = sdiv i32 %59, %60
  store i32 %61, i32* %58
  br label %if_next_bb68

if_next_bb68:
  br label %if_next_bb65

while_block69:
  %62 = load i32, i32* %5
  %63 = load i32, i32* @n
  %64 = icmp slt i32 %62, %63
  br i1 %64, label %while_body70, label %while_next71

while_body70:
  %65 = load i32, i32* %5
  %66 = load i32*, i32** %2
  %67 = getelementptr inbounds i32, i32* %66, i32 %65
  store i32 0, i32* %67
  %68 = load i32, i32* %5
  %69 = add i32 %68, 1
  store i32 %69, i32* %5
  br label %while_block69

while_next71:
  ret i32 0
}

define i32 @main() {
enter_block:
  store i32 32, i32* @n
  %0 = alloca [32 x i32], i32 32
  %1 = alloca [32 x i32], i32 32
  %2 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 0
  store i32 7, i32* %2
  %3 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 1
  store i32 23, i32* %3
  %4 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 2
  store i32 89, i32* %4
  %5 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 3
  store i32 26, i32* %5
  %6 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 4
  store i32 282, i32* %6
  %7 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 5
  store i32 254, i32* %7
  %8 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 6
  store i32 27, i32* %8
  %9 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 7
  store i32 5, i32* %9
  %10 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 8
  store i32 83, i32* %10
  %11 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 9
  store i32 273, i32* %11
  %12 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 10
  store i32 574, i32* %12
  %13 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 11
  store i32 905, i32* %13
  %14 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 12
  store i32 354, i32* %14
  %15 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 13
  store i32 657, i32* %15
  %16 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 14
  store i32 935, i32* %16
  %17 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 15
  store i32 264, i32* %17
  %18 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 16
  store i32 639, i32* %18
  %19 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 17
  store i32 459, i32* %19
  %20 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 18
  store i32 29, i32* %20
  %21 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 19
  store i32 68, i32* %21
  %22 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 20
  store i32 929, i32* %22
  %23 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 21
  store i32 756, i32* %23
  %24 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 22
  store i32 452, i32* %24
  %25 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 23
  store i32 279, i32* %25
  %26 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 24
  store i32 58, i32* %26
  %27 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 25
  store i32 87, i32* %27
  %28 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 26
  store i32 96, i32* %28
  %29 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 27
  store i32 36, i32* %29
  %30 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 28
  store i32 39, i32* %30
  %31 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 29
  store i32 28, i32* %31
  %32 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 30
  store i32 1, i32* %32
  %33 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 31
  store i32 290, i32* %33
  %34 = alloca i32
  %35 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 0
  %36 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %37 = call i32 @arrCopy(i32* %35, i32* %36)
  store i32 %37, i32* %34
  %38 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %39 = call i32 @revert(i32* %38)
  store i32 %39, i32* %34
  %40 = alloca i32
  store i32 0, i32* %40
  br label %while_block72

while_block72:
  %41 = load i32, i32* %40
  %42 = icmp slt i32 %41, 32
  br i1 %42, label %while_body73, label %while_next74

while_body73:
  %43 = load i32, i32* %40
  %44 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 %43
  %45 = load i32, i32* %44
  store i32 %45, i32* %34
  %46 = load i32, i32* %34
  call void @putint(i32 %46)
  %47 = load i32, i32* %40
  %48 = add i32 %47, 1
  store i32 %48, i32* %40
  br label %while_block72

while_next74:
  %49 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %50 = call i32 @bubblesort(i32* %49)
  store i32 %50, i32* %34
  store i32 0, i32* %40
  br label %while_block75

while_block75:
  %51 = load i32, i32* %40
  %52 = icmp slt i32 %51, 32
  br i1 %52, label %while_body76, label %while_next77

while_body76:
  %53 = load i32, i32* %40
  %54 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 %53
  %55 = load i32, i32* %54
  store i32 %55, i32* %34
  %56 = load i32, i32* %34
  call void @putint(i32 %56)
  %57 = load i32, i32* %40
  %58 = add i32 %57, 1
  store i32 %58, i32* %40
  br label %while_block75

while_next77:
  %59 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %60 = call i32 @getMid(i32* %59)
  store i32 %60, i32* %34
  %61 = load i32, i32* %34
  call void @putint(i32 %61)
  %62 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %63 = call i32 @getMost(i32* %62)
  store i32 %63, i32* %34
  %64 = load i32, i32* %34
  call void @putint(i32 %64)
  %65 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 0
  %66 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %67 = call i32 @arrCopy(i32* %65, i32* %66)
  store i32 %67, i32* %34
  %68 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %69 = call i32 @bubblesort(i32* %68)
  store i32 %69, i32* %34
  store i32 0, i32* %40
  br label %while_block78

while_block78:
  %70 = load i32, i32* %40
  %71 = icmp slt i32 %70, 32
  br i1 %71, label %while_body79, label %while_next80

while_body79:
  %72 = load i32, i32* %40
  %73 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 %72
  %74 = load i32, i32* %73
  store i32 %74, i32* %34
  %75 = load i32, i32* %34
  call void @putint(i32 %75)
  %76 = load i32, i32* %40
  %77 = add i32 %76, 1
  store i32 %77, i32* %40
  br label %while_block78

while_next80:
  %78 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 0
  %79 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %80 = call i32 @arrCopy(i32* %78, i32* %79)
  store i32 %80, i32* %34
  %81 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %82 = call i32 @insertsort(i32* %81)
  store i32 %82, i32* %34
  store i32 0, i32* %40
  br label %while_block81

while_block81:
  %83 = load i32, i32* %40
  %84 = icmp slt i32 %83, 32
  br i1 %84, label %while_body82, label %while_next83

while_body82:
  %85 = load i32, i32* %40
  %86 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 %85
  %87 = load i32, i32* %86
  store i32 %87, i32* %34
  %88 = load i32, i32* %34
  call void @putint(i32 %88)
  %89 = load i32, i32* %40
  %90 = add i32 %89, 1
  store i32 %90, i32* %40
  br label %while_block81

while_next83:
  %91 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 0
  %92 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %93 = call i32 @arrCopy(i32* %91, i32* %92)
  store i32 %93, i32* %34
  store i32 0, i32* %40
  store i32 31, i32* %34
  %94 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %95 = load i32, i32* %40
  %96 = load i32, i32* %34
  %97 = call i32 @QuickSort(i32* %94, i32 %95, i32 %96)
  store i32 %97, i32* %34
  br label %while_block84

while_block84:
  %98 = load i32, i32* %40
  %99 = icmp slt i32 %98, 32
  br i1 %99, label %while_body85, label %while_next86

while_body85:
  %100 = load i32, i32* %40
  %101 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 %100
  %102 = load i32, i32* %101
  store i32 %102, i32* %34
  %103 = load i32, i32* %34
  call void @putint(i32 %103)
  %104 = load i32, i32* %40
  %105 = add i32 %104, 1
  store i32 %105, i32* %40
  br label %while_block84

while_next86:
  %106 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 0
  %107 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %108 = call i32 @arrCopy(i32* %106, i32* %107)
  store i32 %108, i32* %34
  %109 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %110 = call i32 @calSum(i32* %109, i32 4)
  store i32 %110, i32* %34
  store i32 0, i32* %40
  br label %while_block87

while_block87:
  %111 = load i32, i32* %40
  %112 = icmp slt i32 %111, 32
  br i1 %112, label %while_body88, label %while_next89

while_body88:
  %113 = load i32, i32* %40
  %114 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 %113
  %115 = load i32, i32* %114
  store i32 %115, i32* %34
  %116 = load i32, i32* %34
  call void @putint(i32 %116)
  %117 = load i32, i32* %40
  %118 = add i32 %117, 1
  store i32 %118, i32* %40
  br label %while_block87

while_next89:
  %119 = getelementptr inbounds [32 x i32], [32 x i32]* %0, i32 0, i32 0
  %120 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %121 = call i32 @arrCopy(i32* %119, i32* %120)
  store i32 %121, i32* %34
  %122 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 0
  %123 = call i32 @avgPooling(i32* %122, i32 3)
  store i32 %123, i32* %34
  store i32 0, i32* %40
  br label %while_block90

while_block90:
  %124 = load i32, i32* %40
  %125 = icmp slt i32 %124, 32
  br i1 %125, label %while_body91, label %while_next92

while_body91:
  %126 = load i32, i32* %40
  %127 = getelementptr inbounds [32 x i32], [32 x i32]* %1, i32 0, i32 %126
  %128 = load i32, i32* %127
  store i32 %128, i32* %34
  %129 = load i32, i32* %34
  call void @putint(i32 %129)
  %130 = load i32, i32* %40
  %131 = add i32 %130, 1
  store i32 %131, i32* %40
  br label %while_block90

while_next92:
  ret i32 0
}
