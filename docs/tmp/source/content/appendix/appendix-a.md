# Appendix A： 相关工具

## 1. Sphinx

YAL 系列项目文档和 Python 官方使用的文档工具一样。是 **Sphinx** 系列。

Sphinx 官网： https://www.sphinx-doc.org/en/master/index.html

推荐的 Sphinx + Markdown 参考构建步骤：

https://gist.github.com/johncrossland/9f6f54d559e9136773172aa0a429b46f#id19

构建之后，于 `docs/yal` 目录下可以使用

``` bash
make html
```

生成 html。建议每次生成前使用

``` bash
make clean
```

清理一下。

## 2. Compiler Explorer

在研究编译器生成代码的效果，这里使用里一个在线快速生成汇编代码的项目：

[Compiler Explorer](https://gcc.godbolt.org/)

最大的优点是可以即使看到我们的源代码对应的汇编代码。

## 3. Pencil Project

Pencil Projerct 是一个快速原型构建的绘图软件。本项目文档中的各种绘制均为 Pencil Project 绘制。

项目官网：[Pencil Project](https://pencil.evolus.vn/)

 