; ModuleID = '65_word_count.sy'
source_filename  = "65_word_count.sy"

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @wc(i32*, i32) {
enter_block:
  %2 = alloca i32*
  store i32* %0, i32** %2
  %3 = alloca i32
  store i32 %1, i32* %3
  %4 = alloca i32
  %5 = alloca i32
  %6 = alloca i32
  store i32 0, i32* %5
  store i32 0, i32* %4
  store i32 0, i32* %6
  br label %while_block0

while_block0:
  %7 = load i32, i32* %5
  %8 = load i32, i32* %3
  %9 = icmp slt i32 %7, %8
  br i1 %9, label %while_body1, label %while_next2

while_body1:
  %10 = load i32, i32* %5
  %11 = load i32*, i32** %2
  %12 = getelementptr inbounds i32, i32* %11, i32 %10
  %13 = load i32, i32* %12
  %14 = icmp ne i32 %13, 32
  br i1 %14, label %then_bb3, label %else_bb4

while_next2:
  %15 = load i32, i32* %6
  ret i32 %15

then_bb3:
  %16 = load i32, i32* %4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %then_bb6, label %if_next_bb8

else_bb4:
  store i32 0, i32* %4
  br label %if_next_bb5

if_next_bb5:
  %18 = load i32, i32* %5
  %19 = add i32 %18, 1
  store i32 %19, i32* %5
  br label %while_block0

then_bb6:
  %20 = load i32, i32* %6
  %21 = add i32 %20, 1
  store i32 %21, i32* %6
  store i32 1, i32* %4
  br label %if_next_bb8

if_next_bb8:
  br label %if_next_bb5
}

define i32 @main() {
enter_block:
  %0 = alloca [500 x i32], i32 500
  %1 = alloca i32
  %2 = alloca i32
  store i32 0, i32* %2
  store i32 0, i32* %1
  br label %while_block9

while_block9:
  %3 = load i32, i32* %1
  %4 = icmp ne i32 %3, 10
  br i1 %4, label %while_body10, label %while_next11

while_body10:
  %5 = call i32 @getch()
  store i32 %5, i32* %1
  %6 = load i32, i32* %2
  %7 = getelementptr inbounds [500 x i32], [500 x i32]* %0, i32 0, i32 %6
  %8 = load i32, i32* %1
  store i32 %8, i32* %7
  %9 = load i32, i32* %2
  %10 = add i32 %9, 1
  store i32 %10, i32* %2
  br label %while_block9

while_next11:
  %11 = getelementptr inbounds [500 x i32], [500 x i32]* %0, i32 0, i32 0
  %12 = load i32, i32* %2
  %13 = call i32 @wc(i32* %11, i32 %12)
  store i32 %13, i32* %1
  %14 = load i32, i32* %1
  call void @putint(i32 %14)
  ret i32 0
}
