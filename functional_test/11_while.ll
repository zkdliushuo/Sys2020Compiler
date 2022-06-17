; ModuleID = '11_while.sy'
source_filename  = "11_while.sy"

@a = global i32 0
@b = global i32 0

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
  store i32 0, i32* @b
  store i32 3, i32* @a
  br label %while_block0

while_block0:
  %0 = load i32, i32* @a
  %1 = icmp sgt i32 %0, 0
  br i1 %1, label %while_body1, label %while_next2

while_body1:
  %2 = load i32, i32* @b
  %3 = load i32, i32* @a
  %4 = add i32 %2, %3
  store i32 %4, i32* @b
  %5 = load i32, i32* @a
  %6 = sub i32 %5, 1
  store i32 %6, i32* @a
  br label %while_block0

while_next2:
  %7 = load i32, i32* @b
  ret i32 %7
}
