; ModuleID = '49_decl_in_defn.sy'
source_filename  = "49_decl_in_defn.sy"

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
  store i32 12, i32* %0
  %1 = alloca i32
  %2 = load i32, i32* %0
  call void @putint(i32 %2)
  ret i32 0
}
