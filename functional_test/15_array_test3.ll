; ModuleID = '15_array_test3.sy'
source_filename  = "15_array_test3.sy"

@a = global [25 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0, i32 0]

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @func(i32*) {
enter_block:
  %1 = alloca i32*
  store i32* %0, i32** %1
  %2 = alloca i32
  store i32 0, i32* %2
  %3 = alloca i32
  store i32 0, i32* %3
  %4 = alloca i32
  store i32 0, i32* %4
  br label %while_block0

while_block0:
  %5 = load i32, i32* %2
  %6 = icmp slt i32 %5, 5
  br i1 %6, label %while_body1, label %while_next2

while_body1:
  br label %while_block3

while_next2:
  %7 = load i32, i32* %4
  ret i32 %7

while_block3:
  %8 = load i32, i32* %3
  %9 = icmp slt i32 %8, 5
  br i1 %9, label %while_body4, label %while_next5

while_body4:
  %10 = load i32, i32* %4
  %11 = load i32, i32* %2
  %12 = load i32, i32* %3
  %13 = mul i32 %11, 5
  %14 = add i32 %13, %12
  %15 = load i32*, i32** %1
  %16 = getelementptr inbounds i32, i32* %15, i32 %14
  %17 = load i32, i32* %16
  %18 = add i32 %10, %17
  store i32 %18, i32* %4
  %19 = load i32, i32* %3
  %20 = add i32 %19, 1
  store i32 %20, i32* %3
  br label %while_block3

while_next5:
  %21 = load i32, i32* %2
  %22 = add i32 %21, 1
  store i32 %22, i32* %2
  br label %while_block0
}

define i32 @main() {
enter_block:
  %0 = getelementptr inbounds [25 x i32], [25 x i32]* @a, i32 0, i32 0
  %1 = call i32 @func(i32* %0)
  call void @putint(i32 %1)
  ret i32 0
}
