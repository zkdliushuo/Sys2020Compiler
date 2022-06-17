; ModuleID = '61_rec_fibonacci.sy'
source_filename  = "61_rec_fibonacci.sy"

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

define i32 @f(i32) {
enter_block:
  %1 = alloca i32
  store i32 %0, i32* %1
  %2 = load i32, i32* %1
  %3 = icmp eq i32 %2, 1
  br i1 %3, label %then_bb0, label %if_next_bb2

then_bb0:
  ret i32 1

if_next_bb2:
  %4 = load i32, i32* %1
  %5 = icmp eq i32 %4, 2
  br i1 %5, label %then_bb3, label %if_next_bb5

then_bb3:
  ret i32 1

if_next_bb5:
  %6 = alloca i32
  %7 = alloca i32
  %8 = load i32, i32* %1
  %9 = sub i32 %8, 1
  store i32 %9, i32* %6
  %10 = load i32, i32* %1
  %11 = sub i32 %10, 2
  store i32 %11, i32* %7
  %12 = alloca i32
  %13 = load i32, i32* %6
  %14 = call i32 @f(i32 %13)
  %15 = load i32, i32* %7
  %16 = call i32 @f(i32 %15)
  %17 = add i32 %14, %16
  store i32 %17, i32* %12
  %18 = load i32, i32* %12
  ret i32 %18
}

define i32 @main() {
enter_block:
  %0 = call i32 @getint()
  store i32 %0, i32* @n
  %1 = alloca i32
  %2 = alloca i32
  %3 = load i32, i32* @n
  %4 = call i32 @f(i32 %3)
  store i32 %4, i32* %1
  %5 = load i32, i32* %1
  call void @putint(i32 %5)
  %6 = alloca i32
  store i32 10, i32* %6
  %7 = load i32, i32* %6
  call void @putch(i32 %7)
  %8 = load i32, i32* %1
  ret i32 %8
}
