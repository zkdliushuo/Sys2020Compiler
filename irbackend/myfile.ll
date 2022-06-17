; ModuleID = 'gen_fib'
source_filename  = "gen_fib"

define i32 @fib(i32) {
fib_entry:
  %1 = alloca [3 x i32], i32 3
  %2 = alloca i32
  %3 = icmp eq i32 %0, 0
  br i1 %3, label %zero_case, label %non_zero_case

fib_return:
  %4 = load i32, i32* %2
  ret i32 %4

zero_case:
  store i32 0, i32* %2
  br label %fib_return

non_zero_case:
  %5 = icmp eq i32 %0, 1
  br i1 %5, label %one_case, label %recursive_case

one_case:
  store i32 1, i32* %2
  br label %fib_return

recursive_case:
  %6 = sub i32 %0, 1
  %7 = call i32 @fib(i32 %6)
  %8 = sub i32 %6, 1
  %9 = call i32 @fib(i32 %8)
  %10 = add i32 %7, %9
  store i32 %10, i32* %2
  br label %fib_return
}

define i32 @main() {
main_entry:
  %0 = alloca i32
  %1 = alloca i32
  %2 = alloca i32
  store i32 0, i32* %0
  store i32 0, i32* %1
  store i32 8, i32* %2
  br label %cond

main_return:
  %3 = load i32, i32* %0
  ret i32 %3

cond:
  %4 = load i32, i32* %1
  %5 = load i32, i32* %2
  %6 = icmp slt i32 %4, %5
  br i1 %6, label %loop, label %main_return

loop:
  %7 = load i32, i32* %1
  %8 = call i32 @fib(i32 %7)
  %9 = load i32, i32* %0
  %10 = add i32 %9, %8
  store i32 %10, i32* %0
  %11 = add i32 %7, 1
  store i32 %11, i32* %1
  br label %cond
}
