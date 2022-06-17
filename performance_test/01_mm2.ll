; ModuleID = '01_mm2.sy'
source_filename  = "01_mm2.sy"

@N = constant i32 1024
@A = global [1048576 x i32] zeroinitializer
@B = global [1048576 x i32] zeroinitializer
@C = global [1048576 x i32] zeroinitializer

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define void @mm(i32, i32*, i32*, i32*) {
enter_block:
  %4 = alloca i32
  store i32 %0, i32* %4
  %5 = alloca i32*
  store i32* %1, i32** %5
  %6 = load i32, i32* @N
  %7 = alloca i32*
  store i32* %2, i32** %7
  %8 = load i32, i32* @N
  %9 = alloca i32*
  store i32* %3, i32** %9
  %10 = load i32, i32* @N
  %11 = alloca i32
  %12 = alloca i32
  %13 = alloca i32
  store i32 0, i32* %11
  store i32 0, i32* %12
  br label %while_block0

while_block0:
  %14 = load i32, i32* %11
  %15 = load i32, i32* %4
  %16 = icmp slt i32 %14, %15
  br i1 %16, label %while_body1, label %while_next2

while_body1:
  store i32 0, i32* %12
  br label %while_block3

while_next2:
  store i32 0, i32* %11
  store i32 0, i32* %12
  store i32 0, i32* %13
  br label %while_block6

while_block3:
  %17 = load i32, i32* %12
  %18 = load i32, i32* %4
  %19 = icmp slt i32 %17, %18
  br i1 %19, label %while_body4, label %while_next5

while_body4:
  %20 = load i32, i32* %11
  %21 = load i32, i32* %12
  %22 = mul i32 %20, %10
  %23 = add i32 %22, %21
  %24 = load i32*, i32** %9
  %25 = getelementptr inbounds i32, i32* %24, i32 %23
  store i32 0, i32* %25
  %26 = load i32, i32* %12
  %27 = add i32 %26, 1
  store i32 %27, i32* %12
  br label %while_block3

while_next5:
  %28 = load i32, i32* %11
  %29 = add i32 %28, 1
  store i32 %29, i32* %11
  br label %while_block0

while_block6:
  %30 = load i32, i32* %13
  %31 = load i32, i32* %4
  %32 = icmp slt i32 %30, %31
  br i1 %32, label %while_body7, label %while_next8

while_body7:
  store i32 0, i32* %11
  br label %while_block9

while_next8:
  ret void

while_block9:
  %33 = load i32, i32* %11
  %34 = load i32, i32* %4
  %35 = icmp slt i32 %33, %34
  br i1 %35, label %while_body10, label %while_next11

while_body10:
  %36 = load i32, i32* %11
  %37 = load i32, i32* %13
  %38 = mul i32 %36, %6
  %39 = add i32 %38, %37
  %40 = load i32*, i32** %5
  %41 = getelementptr inbounds i32, i32* %40, i32 %39
  %42 = load i32, i32* %41
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %then_bb12, label %if_next_bb14

while_next11:
  %44 = load i32, i32* %13
  %45 = add i32 %44, 1
  store i32 %45, i32* %13
  br label %while_block6

then_bb12:
  %46 = load i32, i32* %11
  %47 = add i32 %46, 1
  store i32 %47, i32* %11
  br label %while_block9

if_next_bb14:
  store i32 0, i32* %12
  br label %while_block15

while_block15:
  %48 = load i32, i32* %12
  %49 = load i32, i32* %4
  %50 = icmp slt i32 %48, %49
  br i1 %50, label %while_body16, label %while_next17

while_body16:
  %51 = load i32, i32* %11
  %52 = load i32, i32* %12
  %53 = mul i32 %51, %10
  %54 = add i32 %53, %52
  %55 = load i32*, i32** %9
  %56 = getelementptr inbounds i32, i32* %55, i32 %54
  %57 = load i32, i32* %11
  %58 = load i32, i32* %12
  %59 = mul i32 %57, %10
  %60 = add i32 %59, %58
  %61 = load i32*, i32** %9
  %62 = getelementptr inbounds i32, i32* %61, i32 %60
  %63 = load i32, i32* %62
  %64 = load i32, i32* %11
  %65 = load i32, i32* %13
  %66 = mul i32 %64, %6
  %67 = add i32 %66, %65
  %68 = load i32*, i32** %5
  %69 = getelementptr inbounds i32, i32* %68, i32 %67
  %70 = load i32, i32* %69
  %71 = load i32, i32* %13
  %72 = load i32, i32* %12
  %73 = mul i32 %71, %8
  %74 = add i32 %73, %72
  %75 = load i32*, i32** %7
  %76 = getelementptr inbounds i32, i32* %75, i32 %74
  %77 = load i32, i32* %76
  %78 = mul i32 %70, %77
  %79 = add i32 %63, %78
  store i32 %79, i32* %56
  %80 = load i32, i32* %12
  %81 = add i32 %80, 1
  store i32 %81, i32* %12
  br label %while_block15

while_next17:
  %82 = load i32, i32* %11
  %83 = add i32 %82, 1
  store i32 %83, i32* %11
  br label %while_block9
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  %1 = call i32 @getint()
  store i32 %1, i32* %0
  %2 = alloca i32
  %3 = alloca i32
  store i32 0, i32* %2
  store i32 0, i32* %3
  br label %while_block18

while_block18:
  %4 = load i32, i32* %2
  %5 = load i32, i32* %0
  %6 = icmp slt i32 %4, %5
  br i1 %6, label %while_body19, label %while_next20

while_body19:
  store i32 0, i32* %3
  br label %while_block21

while_next20:
  store i32 0, i32* %2
  store i32 0, i32* %3
  br label %while_block24

while_block21:
  %7 = load i32, i32* %3
  %8 = load i32, i32* %0
  %9 = icmp slt i32 %7, %8
  br i1 %9, label %while_body22, label %while_next23

while_body22:
  %10 = load i32, i32* %2
  %11 = load i32, i32* %3
  %12 = mul i32 %10, 1024
  %13 = add i32 %12, %11
  %14 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @A, i32 0, i32 %13
  %15 = call i32 @getint()
  store i32 %15, i32* %14
  %16 = load i32, i32* %3
  %17 = add i32 %16, 1
  store i32 %17, i32* %3
  br label %while_block21

while_next23:
  %18 = load i32, i32* %2
  %19 = add i32 %18, 1
  store i32 %19, i32* %2
  br label %while_block18

while_block24:
  %20 = load i32, i32* %2
  %21 = load i32, i32* %0
  %22 = icmp slt i32 %20, %21
  br i1 %22, label %while_body25, label %while_next26

while_body25:
  store i32 0, i32* %3
  br label %while_block27

while_next26:
  call void @_sysy_starttime(i32 65)
  store i32 0, i32* %2
  br label %while_block30

while_block27:
  %23 = load i32, i32* %3
  %24 = load i32, i32* %0
  %25 = icmp slt i32 %23, %24
  br i1 %25, label %while_body28, label %while_next29

while_body28:
  %26 = load i32, i32* %2
  %27 = load i32, i32* %3
  %28 = mul i32 %26, 1024
  %29 = add i32 %28, %27
  %30 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @B, i32 0, i32 %29
  %31 = call i32 @getint()
  store i32 %31, i32* %30
  %32 = load i32, i32* %3
  %33 = add i32 %32, 1
  store i32 %33, i32* %3
  br label %while_block27

while_next29:
  %34 = load i32, i32* %2
  %35 = add i32 %34, 1
  store i32 %35, i32* %2
  br label %while_block24

while_block30:
  %36 = load i32, i32* %2
  %37 = icmp slt i32 %36, 5
  br i1 %37, label %while_body31, label %while_next32

while_body31:
  %38 = load i32, i32* %0
  %39 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @A, i32 0, i32 0
  %40 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @B, i32 0, i32 0
  %41 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @C, i32 0, i32 0
  call void @mm(i32 %38, i32* %39, i32* %40, i32* %41)
  %42 = load i32, i32* %0
  %43 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @A, i32 0, i32 0
  %44 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @C, i32 0, i32 0
  %45 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @B, i32 0, i32 0
  call void @mm(i32 %42, i32* %43, i32* %44, i32* %45)
  %46 = load i32, i32* %2
  %47 = add i32 %46, 1
  store i32 %47, i32* %2
  br label %while_block30

while_next32:
  %48 = alloca i32
  store i32 0, i32* %48
  store i32 0, i32* %2
  br label %while_block33

while_block33:
  %49 = load i32, i32* %2
  %50 = load i32, i32* %0
  %51 = icmp slt i32 %49, %50
  br i1 %51, label %while_body34, label %while_next35

while_body34:
  store i32 0, i32* %3
  br label %while_block36

while_next35:
  call void @_sysy_stoptime(i32 84)
  %52 = load i32, i32* %48
  call void @putint(i32 %52)
  call void @putch(i32 10)
  ret i32 0

while_block36:
  %53 = load i32, i32* %3
  %54 = load i32, i32* %0
  %55 = icmp slt i32 %53, %54
  br i1 %55, label %while_body37, label %while_next38

while_body37:
  %56 = load i32, i32* %48
  %57 = load i32, i32* %2
  %58 = load i32, i32* %3
  %59 = mul i32 %57, 1024
  %60 = add i32 %59, %58
  %61 = getelementptr inbounds [1048576 x i32], [1048576 x i32]* @B, i32 0, i32 %60
  %62 = load i32, i32* %61
  %63 = add i32 %56, %62
  store i32 %63, i32* %48
  %64 = load i32, i32* %3
  %65 = add i32 %64, 1
  store i32 %65, i32* %3
  br label %while_block36

while_next38:
  %66 = load i32, i32* %2
  %67 = add i32 %66, 1
  store i32 %67, i32* %2
  br label %while_block33
}
