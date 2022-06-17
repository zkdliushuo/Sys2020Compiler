; ModuleID = '08_arr_assign.sy'
source_filename  = "08_arr_assign.sy"

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
  %0 = getelementptr inbounds [10 x i32], [10 x i32]* @a, i32 0, i32 0
  store i32 1, i32* %0
  ret i32 0
}
