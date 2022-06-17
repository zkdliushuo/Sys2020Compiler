; ModuleID = '64_alpha_count.sy'
source_filename  = "64_alpha_count.sy"

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
  %0 = alloca [500 x i32], i32 500
  %1 = alloca i32
  %2 = alloca i32
  %3 = alloca i32
  store i32 0, i32* %3
  store i32 0, i32* %2
  store i32 0, i32* %1
  br label %while_block0

while_block0:
  %4 = load i32, i32* %1
  %5 = icmp ne i32 %4, 10
  br i1 %5, label %while_body1, label %while_next2

while_body1:
  %6 = call i32 @getch()
  store i32 %6, i32* %1
  %7 = load i32, i32* %1
  %8 = icmp sgt i32 %7, 40
  br i1 %8, label %next_and_bb7, label %next_or_bb6

while_next2:
  %9 = load i32, i32* %3
  call void @putint(i32 %9)
  ret i32 0

then_bb3:
  %10 = load i32, i32* %3
  %11 = add i32 %10, 1
  store i32 %11, i32* %3
  br label %if_next_bb5

if_next_bb5:
  %12 = load i32, i32* %2
  %13 = add i32 %12, 1
  store i32 %13, i32* %2
  br label %while_block0

next_or_bb6:
  %14 = load i32, i32* %1
  %15 = icmp sgt i32 %14, 96
  br i1 %15, label %next_and_bb8, label %if_next_bb5

next_and_bb7:
  %16 = load i32, i32* %1
  %17 = icmp slt i32 %16, 91
  br i1 %17, label %then_bb3, label %next_or_bb6

next_and_bb8:
  %18 = load i32, i32* %1
  %19 = icmp slt i32 %18, 123
  br i1 %19, label %then_bb3, label %if_next_bb5
}
