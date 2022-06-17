; ModuleID = '33_func_test1.sy'
source_filename  = "33_func_test1.sy"

@a = global i32 0

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @myFunc(i32, i32, i32) {
enter_block:
  %3 = alloca i32
  store i32 %0, i32* %3
  %4 = alloca i32
  store i32 %1, i32* %4
  %5 = alloca i32
  store i32 %2, i32* %5
  store i32 2, i32* %3
  %6 = alloca i32
  store i32 0, i32* %6
  %7 = load i32, i32* %6
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %then_bb0, label %if_next_bb2

then_bb0:
  ret i32 0

if_next_bb2:
  br label %while_block3

while_block3:
  %9 = load i32, i32* %4
  %10 = icmp sgt i32 %9, 0
  br i1 %10, label %while_body4, label %while_next5

while_body4:
  %11 = load i32, i32* %4
  %12 = sub i32 %11, 1
  store i32 %12, i32* %4
  br label %while_block3

while_next5:
  %13 = load i32, i32* %3
  %14 = load i32, i32* %4
  %15 = add i32 %13, %14
  ret i32 %15
}

define i32 @main() {
enter_block:
  store i32 3, i32* @a
  %0 = alloca i32
  %1 = call i32 @myFunc(i32 1, i32 2, i32 1)
  store i32 %1, i32* %0
  %2 = load i32, i32* @a
  %3 = load i32, i32* %0
  %4 = add i32 %2, %3
  ret i32 %4
}
