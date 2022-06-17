; ModuleID = '63_simple_atoi.sy'
source_filename  = "63_simple_atoi.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @atoi_(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  store i32 0, i32* %2
  %3 = alloca i32
  store i32 1, i32* %3
  %4 = alloca i32
  store i32 0, i32* %4
  br label %while_block0

while_block0:
  %5 = load i32, i32* %4
  %6 = load i32*, i32** %1
  %7 = getelementptr inbounds i32, i32* %6, i32 %5
  %8 = load i32, i32* %7
  %9 = icmp eq i32 %8, 32
  br i1 %9, label %while_body1, label %while_next2

while_body1:
  %10 = load i32, i32* %4
  %11 = add i32 %10, 1
  store i32 %11, i32* %4
  br label %while_block0

while_next2:
  %12 = load i32, i32* %4
  %13 = load i32*, i32** %1
  %14 = getelementptr inbounds i32, i32* %13, i32 %12
  %15 = load i32, i32* %14
  %16 = icmp eq i32 %15, 43
  br i1 %16, label %then_bb3, label %next_or_bb6

then_bb3:
  %17 = load i32, i32* %4
  %18 = load i32*, i32** %1
  %19 = getelementptr inbounds i32, i32* %18, i32 %17
  %20 = load i32, i32* %19
  %21 = icmp eq i32 %20, 45
  br i1 %21, label %then_bb7, label %if_next_bb9

else_bb4:
  %22 = load i32, i32* %4
  %23 = load i32*, i32** %1
  %24 = getelementptr inbounds i32, i32* %23, i32 %22
  %25 = load i32, i32* %24
  %26 = icmp slt i32 %25, 48
  br i1 %26, label %then_bb10, label %next_or_bb13

if_next_bb5:
  br label %while_block14

next_or_bb6:
  %27 = load i32, i32* %4
  %28 = load i32*, i32** %1
  %29 = getelementptr inbounds i32, i32* %28, i32 %27
  %30 = load i32, i32* %29
  %31 = icmp eq i32 %30, 45
  br i1 %31, label %then_bb3, label %else_bb4

then_bb7:
  store i32 -1, i32* %3
  br label %if_next_bb9

if_next_bb9:
  %32 = load i32, i32* %4
  %33 = add i32 %32, 1
  store i32 %33, i32* %4
  br label %if_next_bb5

then_bb10:
  store i32 2147483647, i32* %2
  %34 = load i32, i32* %2
  ret i32 %34

if_next_bb12:
  br label %if_next_bb5

next_or_bb13:
  %35 = load i32, i32* %4
  %36 = load i32*, i32** %1
  %37 = getelementptr inbounds i32, i32* %36, i32 %35
  %38 = load i32, i32* %37
  %39 = icmp sgt i32 %38, 57
  br i1 %39, label %then_bb10, label %if_next_bb12

while_block14:
  %40 = load i32, i32* %4
  %41 = load i32*, i32** %1
  %42 = getelementptr inbounds i32, i32* %41, i32 %40
  %43 = load i32, i32* %42
  %44 = icmp ne i32 %43, 0
  br i1 %44, label %next_and_bb18, label %while_next16

while_body15:
  %45 = load i32, i32* %2
  %46 = mul i32 %45, 10
  %47 = load i32, i32* %4
  %48 = load i32*, i32** %1
  %49 = getelementptr inbounds i32, i32* %48, i32 %47
  %50 = load i32, i32* %49
  %51 = add i32 %46, %50
  %52 = sub i32 %51, 48
  store i32 %52, i32* %2
  %53 = load i32, i32* %4
  %54 = add i32 %53, 1
  store i32 %54, i32* %4
  br label %while_block14

while_next16:
  %55 = load i32, i32* %2
  %56 = load i32, i32* %3
  %57 = mul i32 %55, %56
  ret i32 %57

next_and_bb17:
  %58 = load i32, i32* %4
  %59 = load i32*, i32** %1
  %60 = getelementptr inbounds i32, i32* %59, i32 %58
  %61 = load i32, i32* %60
  %62 = icmp slt i32 %61, 58
  br i1 %62, label %while_body15, label %while_next16

next_and_bb18:
  %63 = load i32, i32* %4
  %64 = load i32*, i32** %1
  %65 = getelementptr inbounds i32, i32* %64, i32 %63
  %66 = load i32, i32* %65
  %67 = icmp sgt i32 %66, 47
  br i1 %67, label %next_and_bb17, label %while_next16
}

define i32 @main() {
enter_block:
  %0 = alloca [500 x i32], i32 500
  %1 = alloca i32
  store i32 0, i32* %1
  %2 = alloca i32
  store i32 0, i32* %2
  br label %while_block19

while_block19:
  %3 = load i32, i32* %1
  %4 = icmp ne i32 %3, 10
  br i1 %4, label %while_body20, label %while_next21

while_body20:
  %5 = call i32 @getch()
  store i32 %5, i32* %1
  %6 = load i32, i32* %2
  %7 = getelementptr inbounds [500 x i32], [500 x i32]* %0, i32 0, i32 %6
  %8 = load i32, i32* %1
  store i32 %8, i32* %7
  %9 = load i32, i32* %2
  %10 = add i32 %9, 1
  store i32 %10, i32* %2
  br label %while_block19

while_next21:
  %11 = load i32, i32* %2
  %12 = getelementptr inbounds [500 x i32], [500 x i32]* %0, i32 0, i32 %11
  store i32 0, i32* %12
  %13 = getelementptr inbounds [500 x i32], [500 x i32]* %0, i32 0, i32 0
  %14 = call i32 @atoi_(i32* %13)
  store i32 %14, i32* %2
  %15 = load i32, i32* %2
  call void @putint(i32 %15)
  ret i32 0
}
