; ModuleID = '16_greater_eq.sy'
source_filename  = "16_greater_eq.sy"

@a = global i32 5
@s = global [10 x i32] [i32 9, i32 8, i32 7, i32 6, i32 5, i32 4, i32 3, i32 2, i32 1, i32 0]

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
  %0 = alloca i32
  store i32 0, i32* %0
  br label %while_block0

while_block0:
  %1 = load i32, i32* %0
  %2 = getelementptr inbounds [10 x i32], [10 x i32]* @s, i32 0, i32 %1
  %3 = load i32, i32* %2
  %4 = load i32, i32* @a
  %5 = icmp sge i32 %3, %4
  br i1 %5, label %while_body1, label %while_next2

while_body1:
  %6 = load i32, i32* %0
  %7 = add i32 %6, 1
  store i32 %7, i32* %0
  br label %while_block0

while_next2:
  %8 = load i32, i32* %0
  ret i32 %8
}
