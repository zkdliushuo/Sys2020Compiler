; ModuleID = '00_bitset1.sy'
source_filename  = "00_bitset1.sy"

@seed = global [3 x i32] [i32 19971231, i32 19981013, i32 1000000007]
@staticvalue = global i32 0
@a = global [10000 x i32] zeroinitializer

declare i32 @getint()

declare i32 @getch()

declare i32 @getarray(i32*)

declare void @putint(i32)

declare void @putch(i32)

declare void @putarray(i32, i32*)

declare void @putf()

declare void @_sysy_starttime(i32)

declare void @_sysy_stoptime(i32)

define i32 @set(i32*, i32, i32) {
enter_block:
  %3 = alloca i32*
  store i32* %0, i32** %3
  %4 = alloca i32
  store i32 %1, i32* %4
  %5 = alloca i32
  store i32 %2, i32* %5
  %6 = alloca i32
  store i32 30, i32* %6
  %7 = alloca [31 x i32], i32 31
  %8 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 0
  store i32 0, i32* %8
  %9 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 1
  store i32 0, i32* %9
  %10 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 2
  store i32 0, i32* %10
  %11 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 3
  store i32 0, i32* %11
  %12 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 4
  store i32 0, i32* %12
  %13 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 5
  store i32 0, i32* %13
  %14 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 6
  store i32 0, i32* %14
  %15 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 7
  store i32 0, i32* %15
  %16 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 8
  store i32 0, i32* %16
  %17 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 9
  store i32 0, i32* %17
  %18 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 10
  store i32 0, i32* %18
  %19 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 11
  store i32 0, i32* %19
  %20 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 12
  store i32 0, i32* %20
  %21 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 13
  store i32 0, i32* %21
  %22 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 14
  store i32 0, i32* %22
  %23 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 15
  store i32 0, i32* %23
  %24 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 16
  store i32 0, i32* %24
  %25 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 17
  store i32 0, i32* %25
  %26 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 18
  store i32 0, i32* %26
  %27 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 19
  store i32 0, i32* %27
  %28 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 20
  store i32 0, i32* %28
  %29 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 21
  store i32 0, i32* %29
  %30 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 22
  store i32 0, i32* %30
  %31 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 23
  store i32 0, i32* %31
  %32 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 24
  store i32 0, i32* %32
  %33 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 25
  store i32 0, i32* %33
  %34 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 26
  store i32 0, i32* %34
  %35 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 27
  store i32 0, i32* %35
  %36 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 28
  store i32 0, i32* %36
  %37 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 29
  store i32 0, i32* %37
  %38 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 30
  store i32 0, i32* %38
  %39 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 0
  store i32 1, i32* %39
  %40 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 1
  %41 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 0
  %42 = load i32, i32* %41
  %43 = mul i32 %42, 2
  store i32 %43, i32* %40
  %44 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 2
  %45 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 1
  %46 = load i32, i32* %45
  %47 = mul i32 %46, 2
  store i32 %47, i32* %44
  %48 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 3
  %49 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 2
  %50 = load i32, i32* %49
  %51 = mul i32 %50, 2
  store i32 %51, i32* %48
  %52 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 4
  %53 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 3
  %54 = load i32, i32* %53
  %55 = mul i32 %54, 2
  store i32 %55, i32* %52
  %56 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 5
  %57 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 4
  %58 = load i32, i32* %57
  %59 = mul i32 %58, 2
  store i32 %59, i32* %56
  %60 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 6
  %61 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 5
  %62 = load i32, i32* %61
  %63 = mul i32 %62, 2
  store i32 %63, i32* %60
  %64 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 7
  %65 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 6
  %66 = load i32, i32* %65
  %67 = mul i32 %66, 2
  store i32 %67, i32* %64
  %68 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 8
  %69 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 7
  %70 = load i32, i32* %69
  %71 = mul i32 %70, 2
  store i32 %71, i32* %68
  %72 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 9
  %73 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 8
  %74 = load i32, i32* %73
  %75 = mul i32 %74, 2
  store i32 %75, i32* %72
  %76 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 10
  %77 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 9
  %78 = load i32, i32* %77
  %79 = mul i32 %78, 2
  store i32 %79, i32* %76
  %80 = alloca i32
  store i32 10, i32* %80
  br label %while_block0

while_block0:
  %81 = load i32, i32* %80
  %82 = load i32, i32* %6
  %83 = icmp slt i32 %81, %82
  br i1 %83, label %while_body1, label %while_next2

while_body1:
  %84 = load i32, i32* %80
  %85 = add i32 %84, 1
  store i32 %85, i32* %80
  %86 = load i32, i32* %80
  %87 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 %86
  %88 = load i32, i32* %80
  %89 = sub i32 %88, 1
  %90 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 %89
  %91 = load i32, i32* %90
  %92 = mul i32 %91, 2
  store i32 %92, i32* %87
  br label %while_block0

while_next2:
  %93 = alloca i32
  store i32 0, i32* %93
  %94 = load i32, i32* %4
  %95 = load i32, i32* %6
  %96 = sdiv i32 %94, %95
  %97 = icmp sge i32 %96, 10000
  br i1 %97, label %then_bb3, label %if_next_bb5

then_bb3:
  ret i32 0

if_next_bb5:
  %98 = load i32, i32* %4
  %99 = load i32, i32* %6
  %100 = sdiv i32 %98, %99
  %101 = load i32*, i32** %3
  %102 = getelementptr inbounds i32, i32* %101, i32 %100
  %103 = load i32, i32* %102
  %104 = load i32, i32* %4
  %105 = load i32, i32* %6
  %106 = srem i32 %104, %105
  %107 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 %106
  %108 = load i32, i32* %107
  %109 = sdiv i32 %103, %108
  %110 = srem i32 %109, 2
  %111 = load i32, i32* %5
  %112 = icmp ne i32 %110, %111
  br i1 %112, label %then_bb6, label %if_next_bb8

then_bb6:
  %113 = load i32, i32* %4
  %114 = load i32, i32* %6
  %115 = sdiv i32 %113, %114
  %116 = load i32*, i32** %3
  %117 = getelementptr inbounds i32, i32* %116, i32 %115
  %118 = load i32, i32* %117
  %119 = load i32, i32* %4
  %120 = load i32, i32* %6
  %121 = srem i32 %119, %120
  %122 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 %121
  %123 = load i32, i32* %122
  %124 = sdiv i32 %118, %123
  %125 = srem i32 %124, 2
  %126 = icmp eq i32 %125, 0
  br i1 %126, label %then_bb9, label %if_next_bb11

if_next_bb8:
  %127 = load i32, i32* %4
  %128 = load i32, i32* %6
  %129 = sdiv i32 %127, %128
  %130 = load i32*, i32** %3
  %131 = getelementptr inbounds i32, i32* %130, i32 %129
  %132 = load i32, i32* %4
  %133 = load i32, i32* %6
  %134 = sdiv i32 %132, %133
  %135 = load i32*, i32** %3
  %136 = getelementptr inbounds i32, i32* %135, i32 %134
  %137 = load i32, i32* %136
  %138 = load i32, i32* %93
  %139 = add i32 %137, %138
  store i32 %139, i32* %131
  ret i32 0

then_bb9:
  %140 = load i32, i32* %5
  %141 = icmp eq i32 %140, 1
  br i1 %141, label %then_bb12, label %if_next_bb14

if_next_bb11:
  %142 = load i32, i32* %4
  %143 = load i32, i32* %6
  %144 = sdiv i32 %142, %143
  %145 = load i32*, i32** %3
  %146 = getelementptr inbounds i32, i32* %145, i32 %144
  %147 = load i32, i32* %146
  %148 = load i32, i32* %4
  %149 = load i32, i32* %6
  %150 = srem i32 %148, %149
  %151 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 %150
  %152 = load i32, i32* %151
  %153 = sdiv i32 %147, %152
  %154 = srem i32 %153, 2
  %155 = icmp eq i32 %154, 1
  br i1 %155, label %then_bb15, label %if_next_bb17

then_bb12:
  %156 = load i32, i32* %4
  %157 = load i32, i32* %6
  %158 = srem i32 %156, %157
  %159 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 %158
  %160 = load i32, i32* %159
  store i32 %160, i32* %93
  br label %if_next_bb14

if_next_bb14:
  br label %if_next_bb11

then_bb15:
  %161 = load i32, i32* %5
  %162 = icmp eq i32 %161, 0
  br i1 %162, label %then_bb18, label %if_next_bb20

if_next_bb17:
  br label %if_next_bb8

then_bb18:
  %163 = load i32, i32* %93
  %164 = load i32, i32* %4
  %165 = load i32, i32* %6
  %166 = srem i32 %164, %165
  %167 = getelementptr inbounds [31 x i32], [31 x i32]* %7, i32 0, i32 %166
  %168 = load i32, i32* %167
  %169 = sub i32 %163, %168
  store i32 %169, i32* %93
  br label %if_next_bb20

if_next_bb20:
  br label %if_next_bb17
}

define i32 @rand() {
enter_block:
  %0 = load i32, i32* @staticvalue
  %1 = getelementptr inbounds [3 x i32], [3 x i32]* @seed, i32 0, i32 0
  %2 = load i32, i32* %1
  %3 = mul i32 %0, %2
  %4 = getelementptr inbounds [3 x i32], [3 x i32]* @seed, i32 0, i32 1
  %5 = load i32, i32* %4
  %6 = add i32 %3, %5
  store i32 %6, i32* @staticvalue
  %7 = load i32, i32* @staticvalue
  %8 = getelementptr inbounds [3 x i32], [3 x i32]* @seed, i32 0, i32 2
  %9 = load i32, i32* %8
  %10 = srem i32 %7, %9
  store i32 %10, i32* @staticvalue
  %11 = load i32, i32* @staticvalue
  %12 = icmp slt i32 %11, 0
  br i1 %12, label %then_bb21, label %if_next_bb23

then_bb21:
  %13 = getelementptr inbounds [3 x i32], [3 x i32]* @seed, i32 0, i32 2
  %14 = load i32, i32* %13
  %15 = load i32, i32* @staticvalue
  %16 = add i32 %14, %15
  store i32 %16, i32* @staticvalue
  br label %if_next_bb23

if_next_bb23:
  %17 = load i32, i32* @staticvalue
  ret i32 %17
}

define i32 @main() {
enter_block:
  %0 = alloca i32
  %1 = call i32 @getint()
  store i32 %1, i32* %0
  %2 = call i32 @getint()
  store i32 %2, i32* @staticvalue
  call void @_sysy_starttime(i32 56)
  %3 = alloca i32
  %4 = alloca i32
  br label %while_block24

while_block24:
  %5 = load i32, i32* %0
  %6 = icmp sgt i32 %5, 0
  br i1 %6, label %while_body25, label %while_next26

while_body25:
  %7 = load i32, i32* %0
  %8 = sub i32 %7, 1
  store i32 %8, i32* %0
  %9 = call i32 @rand()
  %10 = srem i32 %9, 300000
  store i32 %10, i32* %3
  %11 = call i32 @rand()
  %12 = srem i32 %11, 2
  store i32 %12, i32* %4
  %13 = getelementptr inbounds [10000 x i32], [10000 x i32]* @a, i32 0, i32 0
  %14 = load i32, i32* %3
  %15 = load i32, i32* %4
  %16 = call i32 @set(i32* %13, i32 %14, i32 %15)
  br label %while_block24

while_next26:
  call void @_sysy_stoptime(i32 64)
  %17 = getelementptr inbounds [10000 x i32], [10000 x i32]* @a, i32 0, i32 0
  call void @putarray(i32 10000, i32* %17)
  ret i32 0
}
