; ModuleID = '05_const_array_defn.sy'
source_filename  = "05_const_array_defn.sy"

@a = constant [5 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4]

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
  %0 = getelementptr inbounds [5 x i32], [5 x i32]* @a, i32 0, i32 4
  %1 = load i32, i32* %0
  ret i32 %1
}
