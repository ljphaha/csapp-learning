/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
/*
 * 解题思路：异或 (XOR) 在两位不同的时候得到 1。
 * 分别找出“x 为 0、y 为 1”和“x 为 1、y 为 0”的位，再合并。
 * 题目不能使用 |，因此用德摩根定律：a | b = ~(~a & ~b)。
 */
int bitXor(int x, int y) {
  int a=~x &y;       /* 选出 x 为 0、y 为 1 的位 */
  int b=~y &x;       /* 选出 x 为 1、y 为 0 的位 */
  int c=~(~a&~b);    /* 等价于 a | b，只使用 ~ 和 & */
  return c;         /* 合并后的每一位就是对应的异或结果 */
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
/*
 * 解题思路：在本 Lab 的 32 位补码 (two's complement) 模型中，
 * 最小整数是 -2^31，位模式为 1000...0000：只有第 31 位为 1。
 * 把 1 左移 31 位即可构造这个模式；位编号从最低位的 0 开始。
 */
int tmin(void) {
  return 1<<31;     /* 设置符号位，其余 31 位为 0，得到 Tmin */
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
/*
 * 解题思路：Tmax 的位模式为 0111...1111，x + 1 与 ~x 的位模式相同。
 * 用 !(A ^ B) 判断两者是否相等。但 -1 也满足这个等式，必须排除。
 * 以下按 Lab 的 32 位补码运算模型理解 x + 1。
 */
int isTmax(int x) {
  int a=!((x+1)^~x); /* 两者异或为 0 表示相等，! 把结果变成 0/1 */
  int b=!!(x+1);     /* x 为 -1 时 x + 1 为 0，b 为 0；其余情况为 1 */
  int c=a&b;        /* 同时满足等式并排除 -1，才是 Tmax */
  return c;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
/*
 * 解题思路：构造掩码 (mask) 0xAAAAAAAA，其第 1、3、...、31 位为 1。
 * 因为整数题的常量不能超过 0xFF，先从 0xAA 逐步扩展到 32 位。
 * x & 掩码只保留奇数编号位；结果等于掩码，说明这些位全部为 1。
 */
int allOddBits(int x) {
  int a,b,c;
  a=0xAA;           /* 8 位模式 10101010 */
  a=a<<8;           /* 移到第 15~8 位，低 8 位补 0 */
  a=a|0xAA;         /* 拼成 16 位掩码 0xAAAA */
  b=a<<16;          /* 把 16 位模式放到高 16 位 */
  b=b|a;            /* 拼成 32 位掩码 0xAAAAAAAA */
  c=x&b;            /* 清除偶数编号位，只检查奇数编号位 */
  return !(c^b);    /* c 与 b 相等时返回 1，否则返回 0 */
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
/*
 * 解题思路：补码取负的规则是逐位取反再加 1，即 -x 的位模式为 ~x + 1。
 * 本 Lab 按 32 位补码位模式运算；Tmin 取负后仍是 Tmin 的位模式。
 */
int negate(int x) {
  int a=~x;         /* ~ 是逐位取反，不是逻辑非 ! */
  return a+1;       /* 加 1 完成补码取负 */
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
/*
 * 解题思路：ASCII 数字字符的编码是 0x30~0x39。
 * 先要求去掉低 4 位后的全部高位恰好为 3，再检查低 4 位是否为 0~9。
 * 低 4 位加 6：0~9 得到 6~15，不产生第 4 位进位；10~15 则会进位。
 */
int isAsciiDigit(int x) {
  int t=x>>4;       /* 不只是检查一个高位数字，也排除更高位非零的输入 */

  int y= x&0xF;     /* 掩码 0xF = 1111，提取低 4 位，值在 0~15 */
  y=y+6;           /* 检查低 4 位是否达到 10，达到时和至少为 16 */
  y=y>>4;          /* 无进位时为 0，有进位时为 1 */
  return !(t^3)&!(y^0); /* 高位等于 3，且低 4 位不超过 9，才返回 1 */
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
/*
 * 解题思路：不用 if，而是把“x 是否非零”扩展成全 0 或全 1 的掩码。
 * x 非零时 a = -1（32 位全 1），选中 y；x 为零时 a = 0，选中 z。
 * a & y 和 ~a & z 只有一边保留原值，最后用 | 合并。
 */
int conditional(int x, int y, int z) {
  int a,a1,a2;
  a= !! x;          /* 先归一化：非零变 1，零仍是 0 */
  a=~a+1;          /* 对 0/1 取负，得到 0/-1；-1 不是单独一位的 1 */
  a1=a&y;          /* a 全 1 时保留 y，全 0 时清除 y */
  a2=~a&z;         /* 相反的掩码：x 为零时保留 z，否则清除 z */
  return a1|a2;    /* 把选中的那一个值作为结果 */
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
/*
 * 解题思路：先看 x 和 y 是否异号。异号时，x 为负就有 x <= y。
 * 同号时，计算 y - x；同号相减不会超出有符号范围，差非负就有 x <= y。
 * 异号相减可能溢出，因此异号时不使用 diff 的符号来决定结果。
 * 减法用 y + (~x + 1) 表示，因为这题不允许使用减号。
 */
int isLessOrEqual(int x, int y) {
    int xSign = (x >> 31) & 1;  /* x 为负时是 1，否则是 0 */
    int ySign = (y >> 31) & 1;  /* y 为负时是 1，否则是 0 */
    int differentSign = xSign ^ ySign;  /* 异号为 1，同号为 0 */
    int diff = y + ~x + 1;             /* 按 Lab 补码模型计算 y - x */

    return (differentSign & xSign) |   /* 异号：看 x 是否为负 */
           (!differentSign & !(diff >> 31)); /* 同号：看差是否非负 */
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
/*
 * 解题思路：零及其相反数都是零；非零的 x 与其补码相反数，至少一个
 * 符号位为 1。Tmin 的相反数仍是 Tmin，但符号位也为 1，不需单独排除。
 * 把两个符号位按位或，得到“是否非零”的 0/1，再异或 1 反转结果。
 */
int logicalNeg(int x) {
  int a=~x+1;       /* 构造相反数的 32 位补码位模式 */
  x=(x>>31)&1;      /* 提取原 x 的符号位，结果只有 0 或 1 */
  a=(a>>31)&1;      /* 提取相反数的符号位 */
        
  return (x|a)^1;   /* 非零时 1 ^ 1 = 0；零时 0 ^ 1 = 1 */
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
/*
 * 解题思路：先把负数取反，让正负数统一转化为“查找最高的 1”。
 * 然后用二分查找 (binary search)，依次检查高 16、8、4、2、1 位。
 * 每找到非零的高半区就右移过去，并累计移位数，得到最高 1 的位置。
 * 位编号从 0 开始，还需加上这一位本身和符号位。
 * 对 0 和 -1，归一化后是 0，没有数值位，只需要 1 个符号位。
 */
int howManyBits(int x) {
    int b16, b8, b4, b2, b1;

    /* x >> 31：负数得到全 1，非负数得到全 0；异或后分别取反/不变 */
    x = x ^ (x >> 31);

    /* !! 把“这一段是否非零”变成 0/1，再左移得到移位量 */
    b16 = !!(x >> 16) << 4;  /* 高 16 位有 1 就取 16，否则取 0 */
    x = x >> b16;           /* 把最高 1 所在的半区移动到低位，缩小范围 */

    b8 = !!(x >> 8) << 3;    /* 剩余值的高 8 位有 1，就再移动 8 位 */
    x = x >> b8;

    b4 = !!(x >> 4) << 2;    /* 再检查高 4 位，得到 4 或 0 */
    x = x >> b4;

    b2 = !!(x >> 2) << 1;    /* 再检查高 2 位，得到 2 或 0 */
    x = x >> b2;

    b1 = !!(x >> 1);         /* 最后检查第 1 位，得到 1 或 0 */
    x = x >> b1;            /* 非零输入剩下 1，零输入仍剩下 0 */

    /* 前面累计的是最高 1 的位置；x 是剩下的 0 或 1；
       最后的 1 是符号位 */
    return b16 + b8 + b4 + b2 + b1 + x + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
/*
 * 解题思路：uf 是 IEEE 754 单精度浮点编码，而不是浮点值本身。
 * 拆出符号位 s、8 位指数 exp 和 23 位小数字段 frac，按指数分类。
 * exp = 255：保留 NaN/无穷大的原编码；exp = 0：把 frac 左移一位。
 * 规格化数 (normalized number) 乘二只需让 exp 加 1，符号保持不变。
 * 若原 exp = 254，乘二溢出为无穷大，必须清零 frac，避免变成 NaN。
 */
unsigned floatScale2(unsigned uf) {
  int exp=(uf>>23)&0xFF;     /* 右移 23 位，再用 8 个 1 去掉符号位 */
  unsigned s=uf>>31;        /* 无符号右移补 0，得到符号位 0/1 */
  unsigned frac=uf&0x7FFFFF; /* 0x7FFFFF 是低 23 位全 1 的掩码 */
  if(exp==255){
    return uf;             /* NaN 原样返回；正负无穷乘二仍为原来的无穷 */
  }
  else if(exp==0){
    /* 零/非规格化数 (subnormal)：小数字段左移；进位到第 23 位时
       会自然形成 exp = 1 的规格化数。符号位保留，包括负零。 */
    return(s<<31|frac<<1);
  }
  else{
    if (exp==254){
      frac=0;              /* 下一步 exp 将变成 255，frac 必须为 0 表示无穷 */
    }
    exp=exp+1;             /* 真正指数 E 加 1，带偏移量的 exp 也加 1 */
    return s<<31|exp<<23|frac; /* 各字段移回原位置，再用 | 拼成返回编码 */
  }
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
/*
 * 解题思路：把浮点位编码转换成实际的 int 值，并向零截断小数。
 * E < 0 时绝对值小于 1，结果为 0；零和非规格化数也进入这个分支。
 * 其余有限规格化数补上默认的 1：M = 1.frac * 2^23。
 * 根据 E - 23 移动 M：右移丢掉小数，左移恢复较大的整数值，再恢复符号。
 * E >= 31 时统一返回 0x80000000u，覆盖越界、NaN 和无穷大。
 * 唯一合法的 E = 31 情况 -2^31，其结果也恰好是这个位模式。
 */
int floatFloat2Int(unsigned uf) {
  int exp=(uf>>23)&0xFF;     /* 提取存储的指数；exp 本身不是实际指数 E */
  unsigned s=uf>>31;        /* 保存符号，后面用来决定返回正值还是负值 */
  unsigned frac=uf&0x7FFFFF; /* 提取低 23 位小数字段 */
  int E=exp-127;            /* 规格化数的实际指数；exp = 0 时也会得到负值 */
  if(E<0){
    return 0;              /* 绝对值小于 1，向零截断后为 0 */
  }
  else{
    unsigned M=frac| 1u<<23; /* 第 23 位补隐含的 1；1u 是 unsigned 的 1 */
    if(E<23){
      M=M>>(23-E);         /* 此处 0 <= E < 23；无符号右移丢掉小数位 */
    }
    else if(E>=31){
      return 0x80000000u;   /* 在左移前拦截大指数；exp = 255 时 E = 128 */
    }
    else{
      M=M<<(E-23);         /* 此处 23 <= E <= 30；E = 23 时移 0 位 */
    }
    if (s == 1) {
      return -M;           /* M 是绝对值；按本 Lab 的 32 位环境返回负值 */
    }
    return M;              /* 正数直接返回整数的绝对值，不再拼浮点字段 */
  }
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
/*
 * 解题思路：输入 x 是有符号的指数，输出是正数 2^x 的浮点位编码。
 * -126 <= x <= 127：规格化数 1.0 * 2^x，exp = x + 127，frac = 0。
 * x >= 128：超出范围，返回正无穷，即 exp = 255、frac = 0。
 * -149 <= x < -126：非规格化数，exp = 0，靠 frac 中一个 1 表示数值。
 * 最低小数位代表 2^-23，再乘固定的 2^-126，得到最小正数 2^-149。
 * 因此设置 frac 的第 x + 149 位即可；x < -149 时按题目要求返回零。
 */
unsigned floatPower2(int x) {
  int s;
  unsigned exp,frac;
  if(x>=-126 && x<128){
    s=0;                   /* 2^x 始终为正，负指数不代表负数 */
    exp=x+127;             /* 加上偏移量 (bias) 127，得到 1~254 的指数编码 */
    frac=0;                /* 有效数为 1.0，默认的 1 无需存入 frac */
  }
  else if(x>=128){
    s=0;                   /* 溢出结果是正无穷 */
    exp=255;               /* 全 1 指数表示特殊值 */
    frac=0;                /* 指数为 255 时，小数字段为 0 才表示无穷 */
  }
  else if(x>=-149 && x<-126){
    s=0;                   /* 非规格化数仍为正 */
    exp=0;                 /* 此时使用 0.frac * 2^-126，不补默认的 1 */
    frac=1u<<(149+x);       /* 移位量为 0~22：-149 设第 0 位，-127 设第 22 位 */
  }
  else{
    return 0;              /* x < -149：小于最小可表示的正数，按要求返回 +0 */
  }
  return s<<31|exp<<23|frac; /* 字段回到原位置，返回编码而不是整数值 2^x */
}
