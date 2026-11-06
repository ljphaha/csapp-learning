/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    /*
     * 缓存：32 组 × 32 字节 = 1KB，直接映射。地址每隔 1024 字节回到同一组。
     * 关键问题：矩阵一行占多少字节 → 往下跳几行就会和本行抢同一个组。
     * 局部变量上限 12 个：t0~t7 + i,j,r,c 正好 12 个。
     */
    int t0,t1,t2,t3,t4,t5,t6,t7;

    /*
     * 32×32：一行 128 字节，隔 8 行才冲突 → 8×8 分块，块内 8 行互不冲突。
     * 唯一的冲突在对角块：A[r] 和 B[r] 落在同一组，读写会互相挤掉。
     * 解法：先把 A 的一整行 8 个数读进 t0~t7，再统一写进 B 的一列。
     */
    if (M == 32 && N == 32){
        for (int i=0;i<N;i+=8){
            for (int j=0;j<M;j+=8){
                for(int r=i;r<i+8;r++){
                    t0 = A[r][j];
                    t1 = A[r][j + 1];
                    t2 = A[r][j + 2];
                    t3 = A[r][j + 3];
                    t4 = A[r][j + 4];
                    t5 = A[r][j + 5];
                    t6 = A[r][j + 6];
                    t7 = A[r][j + 7];
                    B[j][r]=t0;
                    B[j+1][r]=t1;
                    B[j+2][r]=t2;
                    B[j+3][r]=t3;
                    B[j+4][r]=t4;
                    B[j+5][r]=t5;
                    B[j+6][r]=t6;
                    B[j+7][r]=t7;
                }
            }
        }
        return;
    }
    /*
     * 61×67：一行 244 字节，不整除 1024，冲突位置没有规律。
     * 直接普通分块，块大小靠实测：17 → 1951 次 miss（满分线 2000）。
     * 注意 A 是 N 行 M 列：r 配 N，c 配 M；最后一块不满，要做边界检查。
     */
    if (M == 61 && N == 67){
        for (int i=0;i<N;i+=17){
            for (int j=0;j<M;j+=17){
               for(int r=i;r<i+17&&r<N;r++){
                    for (int c=j;c<j+17&&c<M;c++){
                        B[c][r]=A[r][c];
                    }
               } 

            }
        }
        return;
    }
    /*
     * 64×64：一行 256 字节，隔 4 行就冲突 → 8×8 块里 B 的第 x 行和第 x+4 行互相挤。
     * 把 8×8 块看成四个 4×4：  A = | A1 A2 |    目标 B = | A1ᵀ A3ᵀ |
     *                              | A3 A4 |             | A2ᵀ A4ᵀ |
     * 原则：每一步只碰 B 的上 4 行或下 4 行，不同时碰。
     */
    if (M == 64 && N == 64){
        for (int i=0;i<N;i+=8){
            for (int j=0;j<M;j+=8){
                /*
                 * 第 1 步：读 A 的上 4 行（A1、A2），只写 B 的上 4 行。
                 * A1ᵀ 放进 B 左上（最终位置）；
                 * A2ᵀ 本该去 B 左下，但那是下 4 行，会冲突 → 先寄放在 B 右上。
                 */
                for(int r=i;r<i+4&&r<N;r++){
                    t0 = A[r][j];
                    t1 = A[r][j + 1];
                    t2 = A[r][j + 2];
                    t3 = A[r][j + 3];
                    t4 = A[r][j + 4];
                    t5 = A[r][j + 5];
                    t6 = A[r][j + 6];
                    t7 = A[r][j + 7];
                    B[j][r]=t0;
                    B[j+1][r]=t1;
                    B[j+2][r]=t2;
                    B[j+3][r]=t3;
                    B[j][r+4]=t4;
                    B[j+1][r+4]=t5;
                    B[j+2][r+4]=t6;
                    B[j+3][r+4]=t7;
                }
                /*
                 * 第 2 步：每轮处理 B 右上的一行 c。
                 *   ① 取出寄放在 B[c][i+4..i+7] 的 A2ᵀ → t0~t3（这一行在缓存里，命中）
                 *   ② 按列读 A3 的第 c 列 → t4~t7（只有一行 B 要腾空，所以 4 个变量够用；
                 *      若按行读 A3，要一次腾空右上整块 16 个值，变量不够）
                 *   ③ A3 的列写进 B 右上第 c 行（最终位置）
                 *   ④ 寄放的 A2ᵀ 写到 B 左下第 c+4 行（最终位置）。
                 *      第 c+4 行会挤掉第 c 行，但第 c 行此时已经写完了。
                 */
                for(int c=j;c<j+4;c++){
                    t0=B[c][i+4];
                    t1=B[c][i+5];
                    t2=B[c][i+6];
                    t3=B[c][i+7];
                    t4=A[i + 4][c];
                    t5=A[i + 5][c];
                    t6=A[i + 6][c];
                    t7=A[i + 7][c];
                    B[c][i+4]=t4;
                    B[c][i+5]=t5;
                    B[c][i+6]=t6;
                    B[c][i+7]=t7;
                    B[c+4][i]=t0;
                    B[c+4][i+1]=t1;
                    B[c+4][i+2]=t2;
                    B[c+4][i+3]=t3;
                }
                /*
                 * 第 3 步：A4 普通 4×4 转置到 B 右下。
                 * A 下 4 行、B 下 4 行在第 2 步都已加载进缓存，基本全命中。
                 */
                for(int r=i+4;r<i+8;r++){
                    t0=A[r][j+4];
                    t1=A[r][j+5];
                    t2=A[r][j+6];
                    t3=A[r][j+7];
                    B[j+4][r]=t0;
                    B[j+5][r]=t1;
                    B[j+6][r]=t2;
                    B[j+7][r]=t3;
                }
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

