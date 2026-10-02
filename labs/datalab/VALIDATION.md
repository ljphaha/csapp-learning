# Data Lab 验证记录

日期：2026-10-02。环境：WSL Ubuntu-24.04，GCC，Makefile 的 `-O -Wall -m32` 配置。

`btest` 得分 **36/36**，全部 13 个函数的 `Errors` 为 0：

| 函数 | 得分 |
| --- | --- |
| bitXor | 1/1 |
| tmin | 1/1 |
| isTmax | 1/1 |
| allOddBits | 2/2 |
| negate | 2/2 |
| isAsciiDigit | 3/3 |
| conditional | 3/3 |
| isLessOrEqual | 3/3 |
| logicalNeg | 4/4 |
| howManyBits | 4/4 |
| floatScale2 | 4/4 |
| floatFloat2Int | 4/4 |
| floatPower2 | 4/4 |

`./dlc bits.c` 无错误输出，运算规则及操作次数检查通过。

只补充解题注释后，去掉注释和空白的源代码 SHA-256 与修改前一致：

```text
702BB1ABE5096D4FAEB63F2775F13AF88C54CAC31B0724407D8C675E13FE792A
```

重新编译时，原 handout 的 `btest.c` 出现 `arg_test_range` 可能未初始化的警告；编译完成且上述测试通过。
