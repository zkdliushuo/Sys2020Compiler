# SYS202语言生成IR代码及测试
[TOC]

## SYS2020调用中间表示后端生成IR
### `IRbuilder`程序依赖
`IRbuilder`依赖于`c1recognizer`，`irbackend`俩个库，在配置使用这俩个库时，请分别到相应的文件夹的`build`文件夹下(如果没有build文件夹，请自行创建)，先执行`cmake`，再执行`make install`，在服务器上，这俩个库的配置流程参考如下：
1. c1reognizer库：
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DANTLR_EXECUTABLE=/usr/local/lib/antlr-4.7.2-complete.jar ..
make insatll
```
其中，这个库由于依赖于antlr4的代码生成，编译时间较长，建议多核编译，如用30个逻辑核心来编译`make -j30 install`.

2. irbackend库：
```bash
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=../bin ..
make insatll
```
### `IRbuilder`程序运行
1. 程序编译
在服务器上的`IRbuilder/`根目录下，执行如下命令即可完成编译：
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug -Dc1recognizer_DIR=/home/bisheng/compiler/c1recognizer/bin/cmake -Dirbackend_DIR=/home/bisheng/compiler/irbackend/bin/cmake ..
make
```
2. 程序自动测评

在IRbuilder的根目录下，存在一个tesh.sh，可以把这个test.sh复制到build文件夹下，执行`bash test.sh`，脚本会调用管道模拟运行时库和IO动作，运行位于`compiler/test_cases`下的功能性测试样例。此外，我在`IRbuilder/src`下放置了一个`io.ll`，这是我用来模仿运行时库的一个由clang编译生成的llvm ir代码，为了支持变长参数，请大家在做优化和代码生成时也关注一下这个io.ll。

`Note: 组委会的意思是，变长参数的putf需要我们用其它io库函数实现，这一功能我主要是实现在了这个io.ll中，其应用到了一些c的库函数。`

`Reminder: 编译io.c时为了可以最后使用llvm-lld，需要先用clang编译io.c，我的做法是先用clang产生io.ll，再用llvm-linker链接俩个.ll生成bitcode,最后用llvm-llc编译这个bitcode，用clang生成可执行文件。clang生成ir：clang -emit-llvm -o io.ll -c io.c`

3. 程序手动验证
此阶段(在代码生成之前)需要按照下面的编译流程操作，以生成可以支持IO函数的可执行程序
```bash
./c1i xxx.sy
llvm-link xxx.ll ../src/io.ll -o xxx.bc
llc xxx.bc -filetype=obj;
clang xxx.o -o xxx
```

## SYS2020 调用LLVM的IR生成

### LLVM Requirment & Build

1. **获取 LLVM**

这里将在当前目录下建立一个名为`llvm`的目录，其中包含了`LLVM`和`Clang`。

```bash
wget http://releases.llvm.org/9.0.0/llvm-9.0.0.src.tar.xz
wget http://releases.llvm.org/9.0.0/cfe-9.0.0.src.tar.xz
tar xvf llvm-9.0.0.src.tar.xz
mv llvm-9.0.0.src llvm
tar xvf cfe-9.0.0.src.tar.xz
mv cfe-9.0.0.src llvm/tools/clang
```
> 注意，我在modules下面存放了这俩个需要下载的文件。

2. **编译并安装**

这里将在当前目录下建立一个名为`llvm-build`的目录（和`llvm`同级），用于构建`LLVM`和`Clang`，并将安装目录配置为和这两个目录同级的`llvm-install`目录。安装完之后将`llvm-install/bin`加入到环境变量`PATH`中。

```bash
mkdir llvm-build && cd llvm-build
cmake ../llvm -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=`cd .. && pwd`/llvm-install
make -j install
```

3. **安装 c1recognizer**

最好在配置ANTLR的时候将`antlr4-cpp/dist`目录加入`LD_LIBRARY_PATH`和`LIBRARY_PATH`

在`<your repo>/c1recognizer`目录下：

```bash
mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/your/install/prefix ..LIBRARY_PATH=/your/antlr4-cpp/dist 
make install
```

4. **编译 c1interpreter**

在`<your repo>/IRbuilder`下：

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=/your/llvm/installation/lib/cmake/llvm -Dc1recognizer_DIR=/your/c1recgonizer/installation/cmake ..
LIBRARY_PATH=/your/antlr4-cpp/dist make -j
```

这里通过配置`LLVM_DIR`和`c1recognizer_DIR`的值，指定了两个依赖库的寻找路径。

> 注意： 请替换其中的路径为你的安装位置，如果已经配置好PATH和LIBRARY_PATH变量，对应的命令可以忽略。

### 程序使用方法
1. 注意需要把你的`llvm-install/bin`加入到`$PATH`变量中
2. IRbuilder目录下存放了一个test.sh脚本，把这个脚本移动到build目录下，`bash test.sh`执行这个脚本，脚本将自动执行`../../build`目录下的所有.sy文件，并输出预期的程序输出
3. 不使用脚本的话，请在`build`目录下执行`c1i`，如果使用额外的`-emit-llvm`参数，生成的ir代码会被打印；如果不使用额外的参数，程序将直接执行，你需要使用`echo $?`命令查看main函数返回值。

### FAQ

1. antlr的环境的问题参照ASTbuilder的文档
2. llvm的下载比较慢，我把相关压缩包传到仓库上了，在moudules文件夹下
3. 在build目录下的c1i即为目标可执行文件，这一程序的功能是接受单个输入文件，通过使用你实现的`visitor`进行代码生成。生成后，若参数中指定了`-emit-llvm`，则将生成的代码打印，否则直接执行之。但是目前直接执行似乎有问题，估计是运行时库的问题，后面再改。打印生成的IR代码是可以的。

### TODO

1. 替换用到的LLVM的类和方法
2. starttime和stoptime的运行时库，putf的格式化字符串还没加入