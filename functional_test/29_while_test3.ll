; ModuleID = '29_while_test3.sy'
source_filename  = "29_while_test3.sy"

@g = global i32 0
@h = global i32 0
@f = global i32 0
@e = global i32 0

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @EightWhile() {
enter_block:
  %0 = alloca i32
  store i32 5, i32* %0
  %1 = alloca i32
  %2 = alloca i32
  store i32 6, i32* %1
  store i32 7, i32* %2
  %3 = alloca i32
  store i32 10, i32* %3
  br label %while_block0

while_block0:
  %4 = load i32, i32* %0
  %5 = icmp slt i32 %4, 20
  br i1 %5, label %while_body1, label %while_next2

while_body1:
  %6 = load i32, i32* %0
  %7 = add i32 %6, 3
  store i32 %7, i32* %0
  br label %while_block3

while_next2:
  %8 = load i32, i32* %0
  %9 = load i32, i32* %1
  %10 = load i32, i32* %3
  %11 = add i32 %9, %10
  %12 = add i32 %8, %11
  %13 = load i32, i32* %2
  %14 = add i32 %12, %13
  %15 = load i32, i32* @e
  %16 = load i32, i32* %3
  %17 = add i32 %15, %16
  %18 = load i32, i32* @g
  %19 = sub i32 %17, %18
  %20 = load i32, i32* @h
  %21 = add i32 %19, %20
  %22 = sub i32 %14, %21
  ret i32 %22

while_block3:
  %23 = load i32, i32* %1
  %24 = icmp slt i32 %23, 10
  br i1 %24, label %while_body4, label %while_next5

while_body4:
  %25 = load i32, i32* %1
  %26 = add i32 %25, 1
  store i32 %26, i32* %1
  br label %while_block6

while_next5:
  %27 = load i32, i32* %1
  %28 = sub i32 %27, 2
  store i32 %28, i32* %1
  br label %while_block0

while_block6:
  %29 = load i32, i32* %2
  %30 = icmp eq i32 %29, 7
  br i1 %30, label %while_body7, label %while_next8

while_body7:
  %31 = load i32, i32* %2
  %32 = sub i32 %31, 1
  store i32 %32, i32* %2
  br label %while_block9

while_next8:
  %33 = load i32, i32* %2
  %34 = add i32 %33, 1
  store i32 %34, i32* %2
  br label %while_block3

while_block9:
  %35 = load i32, i32* %3
  %36 = icmp slt i32 %35, 20
  br i1 %36, label %while_body10, label %while_next11

while_body10:
  %37 = load i32, i32* %3
  %38 = add i32 %37, 3
  store i32 %38, i32* %3
  br label %while_block12

while_next11:
  %39 = load i32, i32* %3
  %40 = sub i32 %39, 1
  store i32 %40, i32* %3
  br label %while_block6

while_block12:
  %41 = load i32, i32* @e
  %42 = icmp sgt i32 %41, 1
  br i1 %42, label %while_body13, label %while_next14

while_body13:
  %43 = load i32, i32* @e
  %44 = sub i32 %43, 1
  store i32 %44, i32* @e
  br label %while_block15

while_next14:
  %45 = load i32, i32* @e
  %46 = add i32 %45, 1
  store i32 %46, i32* @e
  br label %while_block9

while_block15:
  %47 = load i32, i32* @f
  %48 = icmp sgt i32 %47, 2
  br i1 %48, label %while_body16, label %while_next17

while_body16:
  %49 = load i32, i32* @f
  %50 = sub i32 %49, 2
  store i32 %50, i32* @f
  br label %while_block18

while_next17:
  %51 = load i32, i32* @f
  %52 = add i32 %51, 1
  store i32 %52, i32* @f
  br label %while_block12

while_block18:
  %53 = load i32, i32* @g
  %54 = icmp slt i32 %53, 3
  br i1 %54, label %while_body19, label %while_next20

while_body19:
  %55 = load i32, i32* @g
  %56 = add i32 %55, 10
  store i32 %56, i32* @g
  br label %while_block21

while_next20:
  %57 = load i32, i32* @g
  %58 = sub i32 %57, 8
  store i32 %58, i32* @g
  br label %while_block15

while_block21:
  %59 = load i32, i32* @h
  %60 = icmp slt i32 %59, 10
  br i1 %60, label %while_body22, label %while_next23

while_body22:
  %61 = load i32, i32* @h
  %62 = add i32 %61, 8
  store i32 %62, i32* @h
  br label %while_block21

while_next23:
  %63 = load i32, i32* @h
  %64 = sub i32 %63, 1
  store i32 %64, i32* @h
  br label %while_block18
}

define i32 @main() {
enter_block:
  store i32 1, i32* @g
  store i32 2, i32* @h
  store i32 4, i32* @e
  store i32 6, i32* @f
  %0 = call i32 @EightWhile()
  ret i32 %0
}
