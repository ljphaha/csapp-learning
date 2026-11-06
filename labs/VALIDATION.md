# Bomb Lab 与 Cache Lab 验证

验证日期：2026-11-06。

环境：WSL2 Ubuntu 24.04，x86-64。Cache Lab 使用 `/home/liang/csapp/cachelab-handout` 的最新解答，上传副本的 `csim.c`、`trans.c`、`driver.py` 已核对 SHA-256 一致。

## Cache Lab

执行 `make` 后运行 `python3 driver.py`。

| 项目 | 得分 | 满分 | miss 次数 |
|---|---:|---:|---:|
| 缓存模拟器，8 组测试 | 27 | 27 | — |
| 32×32 转置 | 8 | 8 | 288 |
| 64×64 转置 | 8 | 8 | 1228 |
| 61×67 转置 | 10 | 10 | 1951 |
| 合计 | **53** | **53** | — |

这是所附 driver 的自动评分结果，不包含课程人工代码风格评分。

## Bomb Lab

执行 `./bomb answers.txt`，退出码为 0。六关依次通过，最终输出：

```text
Congratulations! You've defused the bomb!
```

答案与仓库附带的 `bomb` 二进制配套。`writeup.md` 包含 Phase 1–6 的推导和调试过程。
