# SYS2020 抽象语法树生成

## ANTLR4  Requirement：

* CMake 3.5 or later
* Any GCC compatible C++ compiler, C++ 11 must be supported
* Any java runtime environment (JRE), preferring version for Java 8
* pkg-config
* uuid-dev

在ubuntu下，安装以上：

```
sudo apt install cmake g++ openjdk-8-jre-headless pkg-config uuid-dev
```

在windows上，你需要依次安装以上依赖；建议尝试使用cmake+VS2015的解决方案(可惜我自己试了试，没配出来，呜呜呜)。

## Build

1. 先下载[Antlr-4.7.2-complete.jar](https://www.antlr.org/download/antlr-4.7.2-complete.jar)，这个是Antlr依赖的java运行时，请放在合适的位置。
2. 请下载[antlr4-cpp-runtime-4.7.2-source.zip](https://www.antlr.org/download/antlr4-cpp-runtime-4.7.2-source.zip)，并手动编译，请将你编译出来的共享库(.so文件)放在/usr/local/lib下。
3. 在根目录下创建build文件夹，使用cmake生成makefile，然后再make。使用cmake的命令行参考如下：

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DANTLR_EXECUTABLE=/usr/local/lib/antlr-4.7.2-complete.jar ..
make
```

​	这里依赖.jar包，请将它改成你电脑上的路径。

4. 目标生成文件就是在build下的c1r_test，目标可执行文件读取的是std::cin，因此想要它处理文件输入，你可能需要使用管道。使用示例：

```shell
cat /test_cases/04_const_defn.sy | build/c1r_test
```

## FAQ

1. antlr的环境配不好？

   可能需要把下面的bash脚本加到.bashrc中，也可以在每次打开bash时依次执行下面的脚本

```bash
export CLASSPATH=".:/usr/local/lib/antlr-4.7.2-complete.jar:$CLASSPATH"
export LD_LIBRARY_PATH=/usr/local/lib/:$LD_LIBRARY_PATH
```

​	注意把上面的路径替换成你那里的实际路径。

## TODO

1. 类的析构时存在双重free的bug，我不知道这种东西该咋debug，不过暂时还不影响功能实现
2. 得想办法把.jar包去掉，具体的原理我还没研究
3. 把使用管道改成读取文件，以后改吧
4. 比赛库里的功能测试样例还没测完。我只测了一部分，不知道还有没有隐藏的bug
5. 现在代码中使用的前缀是c1，是我编译原理课上的语言，得抽空替换成我们的编译器的名字

我的想法：

​	等做完ir生成之后，再回来把上述问题一并解决。感觉很多都是使用好cmake就能解决的问题。