; ModuleID = '21_suminput.sy'
source_filename  = "21_suminput.sy"

@n = global i32 0
@a = global [10 x i32] zeroinitializer

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @main() {
enter_block:
  %0 = call i32 @getint()
  store i32 %0, i32* @n
  %1 = load i32, i32* @n
  %2 = icmp sgt i32 %1, 10
  br i1 %2, label %then_bb0, label %if_next_bb2

then_bb0:
  ret i32 1

if_next_bb2:
  %3 = alloca i32
  %4 = alloca i32
  store i32 0, i32* %4
  %5 = load i32, i32* %4
  store i32 %5, i32* %3
  br label %while_block3

while_block3:
  %6 = load i32, i32* %4
  %7 = load i32, i32* @n
  %8 = icmp slt i32 %6, %7
  br i1 %8, label %while_body4, label %while_next5

while_body4:
  %9 = load i32, i32* %4
  %10 = getelementptr inbounds [10 x i32], [10 x i32]* @a, i32 0, i32 %9
  %11 = call i32 @getint()
  store i32 %11, i32* %10
  %12 = load i32, i32* %3
  %13 = load i32, i32* %4
  %14 = getelementptr inbounds [10 x i32], [10 x i32]* @a, i32 0, i32 %13
  %15 = load i32, i32* %14
  %16 = add i32 %12, %15
  store i32 %16, i32* %3
  %17 = load i32, i32* %4
  %18 = add i32 %17, 1
  store i32 %18, i32* %4
  br label %while_block3

while_next5:
  %19 = load i32, i32* %3
  call void @putint(i32 %19)
  %20 = alloca i32
  store i32 10, i32* %20
  %21 = load i32, i32* %20
  call void @putch(i32 %21)
  %22 = load i32, i32* %3
  ret i32 %22
}
