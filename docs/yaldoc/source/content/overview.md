# 1. 项目总览

## 1.1 项目简介

YAL，全称为 Yet Another LLVM 。是 USTC Yet Another 系列项目中的一员。在吸收了 LLVM 编译项目的长处之后，结合自己所学过的编译原理理论，构建自己的编译器。可以说，YAL 以 LLVM 结构为骨，C++ 编程技术为血肉，编译原理思想为魂。

如《礼记》而言，“骨肉归复于土，命也若魂气则无不之也”。 YAL 亦是如此，骨架和血肉可归于大地而腐朽，而其中的思想，如多级 IR、寄存器分配、代码选择等，才是该项目的核心。坦白而言， YAL 并非一个完备通用的编译器，但是此项目，给予我们一次复现现代编译器的机会，实现“龙虎鲸”书中诸多算法和思想。

心之精爽，是谓魂魄，魂魄去之，何能长久？下面的文档里，我们将逐步详细介绍 YAL 项目的三魂七魄。

### 1.1.1 YAL 针对语言

SysY 语言是本次大赛要实现的编程语言，是 C 语言的一个子集。每个 SysY 程序的源码存储在一个扩展名为 sy 的文件中。该文件中有且仅有一个名为 main 的主函数定义，还可以包含若干全局变量声明、常量声明和其他函数定义 SysY 语言支持 int 类型和元素为 int 类型且按行优先存储的多维数组类型，其中 int 型 整数为 32 位有符号数；const 修饰符用于声明常量。

SysY 语言本身没有提供输入/输出(I/O)的语言构造，I/O 是以运行时库方式 提供，库函数可以在 SysY 程序中的函数内调用。部分 SysY 运行时库函数的参 数类型会超出 SysY 支持的数据类型，如可以为字符串。SysY 编译器需要能处理 这种情况，将 SysY 程序中这样的参数正确地传递给 SysY 运行时库。有关在 SysY 程序中可以使用哪些库函数，请参见 SysY 运行时库文档。

函数：函数可以带参数也可以不带参数，参数的类型可以是 int 或者数组类 型；函数可以返回 int 类型的值，或者不返回值(即声明为 void 类型)。当参数为 int 时，按值传递；而参数为数组类型时，实际传递的是数组的起始地址，并且形 参只有第一维的长度可以空缺。函数体由若干变量声明和语句组成。

变量/常量声明：可以在一个变量/常量声明语句中声明多个变量或常量，声 明时可以带初始化表达式。所有变量/常量要求先定义再使用。在函数外声明的为全局变量/常量，在函数内声明的为局部变量/常量。

语句：语句包括赋值语句、表达式语句(表达式可以为空)、语句块、if 语句、 while 语句、break 语句、continue 语句、return 语句。语句块中可以包含若干变量声明和语句。

表达式：支持基本的算术运算（+、-、\*、/、%）、关系运算（==、!=、<、>、<=、>=）和逻辑运算（!、&&、||），非 0 表示真、0 表示假，而关系运算或逻辑 运算的结果用 1 表示真、0 表示假。算符的优先级和结合性以及计算规则(含逻辑运算的“短路计算”)与 C 语言一致。

SysY 语言的描述：[SysY Language Rule](https://gitlab.eduxiji.net/nscscc/docs/-/blob/master/SysY语言定义.pdf)

SysY Runtime Support：[SysY Language Runtime](https://gitlab.eduxiji.net/nscscc/docs/-/blob/master/SysY%E8%BF%90%E8%A1%8C%E6%97%B6%E5%BA%93.pdf)

### 1.1.2 YAL 针对平台

指令集为 Arm v8 指令集，目标平台为 Raspberry Pi 4。更多信息可以参考：

[Raspberry Pi 4](https://www.raspberrypi.org/)

## 1.2 构建方法

YAL 项目的目录结构采用尽可能简单的方法进行实现，目前的版本只有两个类型的文件：.h 和 .cpp 类型。使用的运行时库仅有：`libantlr4-runtime`

可以直接使用 `yum`，`apt` 等包管理直接安装，也可以参考 [Github Antlr4-runtime](https://github.com/antlr/antlr4) 进行构建。之后可以自行配置完成。

这里提供一个参考构建方法

（目标平台为 Ubuntu 20.04.1 LTS x86_64 系统，5.4.0-42-generic 内核）

1. 使用

   ```bash
   sudo apt install libantlr4-runtime-dev
   ```

   进行安装 antlr 运行时库。

2. 创建构建目录

   ```bash
   mkdir build
   cd build
   ```

3. 编写 Makefile 文件

   ```makefile
   CURRENT_PATH = $(PWD)/..
   INCLUDE_PATH = ${CURRENT_PATH}/include
   SOURCE_PATH  = ${CURRENT_PATH}/src
   BUILD_PATH   = ${CURRENT_PATH}/build

   INCLUDE_PATH_ANTLR = -I${INCLUDE_PATH}/antlr
   INCLUDE_PATH_YAL   = -I${INCLUDE_PATH}/yal

   INCLUDE_ALL = ${INCLUDE_PATH_ANTLR} ${INCLUDE_PATH_YAL}

   SOURCE_PATH_CODEGEN    = ${SOURCE_PATH}/codegen
   SOURCE_PATH_IRBACKEND  = ${SOURCE_PATH}/irbackend
   SOURCE_PATH_IRBUILDER  = ${SOURCE_PATH}/irbuilder
   SOURCE_PATH_RECOGNIZER = ${SOURCE_PATH}/recognizer

   OBJECTS_PATH_CODEGEN = $\
   	ModuleAnalyse.o $\
   	SemiMachine.o

   OBJECTS_PATH_IRBACKEND = $\
   	Argument.o $\
       AsmWriter.o $\
   	BasicBlock.o $\
   	Constants.o $\
   	Deadcode.o $\
   	DominatorTree.o $\
   	Function.o $\
   	GlobalVariable.o $\
   	Instructions.o $\
   	LiveVar.o $\
   	LLVMContext.o $\
   	Mem2Reg.o $\
   	Module.o $\
   	Pass.o $\
   	PropConstant.o $\
   	RegAssign.o $\
   	SlotTracker.o $\
   	Type.o $\
   	Use.o $\
   	User.o $\
   	Value.o

   OBJECTS_PATH_IRBUILDER = $\
   	assembly_builder.o $\
   	runtime.o

   OBJECTS_PATH_RECOGNIZER = $\
       C1Lexer.o $\
       C1ParserBaseListener.o $\
       C1ParserBaseVisitor.o $\
       C1Parser.o $\
       C1ParserListener.o $\
       C1ParserVisitor.o $\
       error_listener.o $\
       error_reporter.o $\
       recognizer.o $\
       syntax_tree_builder.o $\
       syntax_tree.o

   OBJECTS_PATH_MAIN = main.o

   CPP_TOOL = clang++
   CPP_FLAGS = -std=c++17 -O2 -g
   PROG ?= compiler
   
   all:$(PROG)

   $(PROG): $(OBJECTS_PATH_IRBACKEND) $(OBJECTS_PATH_IRBUILDER) $(OBJECTS_PATH_CODEGEN) $(OBJECTS_PATH_RECOGNIZER) $(OBJECTS_PATH_MAIN)
   	$(CPP_TOOL) -lm -lantlr4-runtime \
   	-o $(BUILD_PATH)/compiler \
   	$(BUILD_PATH)/*.o

   link:
   	$(CPP_TOOL) -lm -lantlr4-runtime \
   	-o $(BUILD_PATH)/compiler \
   	$(BUILD_PATH)/*.o

   $(OBJECTS_PATH_IRBACKEND): %.o: $(SOURCE_PATH_IRBACKEND)/%.cpp
   	$(CPP_TOOL) -c $(CPP_FLAGS) \
   	$(INCLUDE_ALL) \
   	$< -o $(BUILD_PATH)/$@

   $(OBJECTS_PATH_RECOGNIZER): %.o: $(SOURCE_PATH_RECOGNIZER)/%.cpp
   	$(CPP_TOOL) -c $(CPP_FLAGS) \
   	$(INCLUDE_ALL) \
   	$< -o $(BUILD_PATH)/$@

   $(OBJECTS_PATH_IRBUILDER): %.o: $(SOURCE_PATH_IRBUILDER)/%.cpp
   	$(CPP_TOOL) -c $(CPP_FLAGS) \
   	$(INCLUDE_ALL) \
   	$< -o $(BUILD_PATH)/$@

   $(OBJECTS_PATH_CODEGEN): %.o: $(SOURCE_PATH_CODEGEN)/%.cpp
   	$(CPP_TOOL) -c $(CPP_FLAGS) \
   	$(INCLUDE_ALL) \
   	$< -o $(BUILD_PATH)/$@

   $(OBJECTS_PATH_MAIN): %.o: $(SOURCE_PATH)/%.cpp
   	$(CPP_TOOL) -c $(CPP_FLAGS) \
   	$(INCLUDE_ALL) \
   	$< -o $(BUILD_PATH)/$@

   .PHONY: clean

   clean:
   	rm *.o
   	rm compiler
   ```
   

之后使用

   ```bash
   make
   ```

编译项目。

## 1.3 开发规范

### 1.3.1 程序风格规范

这里为了向 LLVM 致敬，我们参考了 LLVM 项目的代码风格。

具体风格说明参考：[LLVM Code Style](https://llvm.org/docs/CodingStandards.html)

### 1.3.2 文档风格规范

文档的风格可以参考一般混合语种文档风格。文档语法为 Markdown 语法。

对于文档的空格和换行符进行说明：

1. 本文档秉持剔除过多的不必要的符号的原则，进行文档撰写，在不必要的时候，尽量不实用连续的空格和连续的换行符。

2. 本文档是中文文档，涉及中英文交汇之处，用一个空格隔开。如果英文语段的前（后）是行首、行尾、中文标点符号，那么我们则不使用空格。对于长段英语语段，则维持英语编辑排版的一般规则，在非行末的英文标点之后加上空格。

   正确的例子：

   ```
   这里为了致敬 LLVM，我们参考了 LLVM 项目的代码风格。
   ```

   错误的例子：

   ```
   这里为了致敬 LLVM ，我们参考了LLVM项目的代码风格。
   ```

3. 对于的特殊语法单位：引用、链接，如果出现需要分割的情况，分割空格应当出现在语法单位之外。

   正确的例子：

   ```
   可以直接使用 `yum`，`apt` 等包管理直接安装
   ```

   错误的例子：

   ```
   可以直接使用` yum`,`apt `等包管理直接安装
   ```

4. 一级标题和二级标题、二级标题和二级标题之间额外使用一个换行。请以本文档为例。

## 1.4 开发人员简介

- 刘硕
- 黄业琦
- 丁伯尧
- 彭昀

