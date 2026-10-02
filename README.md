# CSAPP 学习记录

《Computer Systems: A Programmer's Perspective》课程的个人作业与学习笔记。

## 内容

- [Data Lab 解答](labs/datalab/bits.c)：13 个函数，每题包含解题思路和关键步骤注释。
- [CSAPP 笔记](notes/CSAPP.md)：来自 Obsidian 的原始 Markdown 笔记，保留公式、表格和 Mermaid 图。
- [验证记录](labs/datalab/VALIDATION.md)：2026-10-02 的测试结果。

Data Lab 目录同时包含原 handout 的测试源文件、头文件、Makefile 和说明，方便重新编译。`bits.c` 是个人解答，其余 Lab 支持文件来自 CSAPP 官方 handout。

## 运行测试

在具备 GCC 和 32 位编译支持的 Linux 或 WSL Ubuntu 环境中：

```bash
cd labs/datalab
make btest
./btest
```

只测试一个函数：

```bash
./btest -f floatPower2
```

运算限制检查使用官方 handout 中的 `dlc` 工具：

```bash
./dlc bits.c
```

`dlc` 不包含在本仓库中，可从 [官方 Data Lab handout](https://csapp.cs.cmu.edu/3e/datalab-handout.tar) 获取。原题说明见 [Data Lab PDF](https://csapp.cs.cmu.edu/3e/datalab.pdf)。

## 笔记

`notes/CSAPP.md` 是上传时的笔记副本；原笔记继续保存在本地 Obsidian 仓库中。本仓库可直接浏览 Markdown，也可以用 Obsidian 打开。
