#Leetcode 204 Count Primes 质数的个数

##原题地址
https://leetcode.com/problems/count-primes/

##题目描述
Count the number of prime numbers less than a non-negative number, n.
计算比非负整数n小的所有数中质数的个数。

##解题思路
在原题中的 **hint** 有非常详细的分析。

##代码

```
int countPrimes(int n) {
    bool* isPrime = (bool*)malloc(sizeof(bool) * n);

    // 初始化为true
    int i, j;
    for (i = 0; i < n; ++i) *(isPrime + i) = true;

    // 标记非质数
    for (i = 2; i * i < n; ++i) {
        if (!*(isPrime + i)) continue;
        for (j = i * i; j < n; j += i)
            *(isPrime + j) = false;
    }
    
    // 统计
    int count = 0;
    for (i = 2; i < n; ++i)
        if (*(isPrime + i)) ++count;

    free(isPrime);
    return count;
}
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/204/c/main.c](https://github.com/Orange1991/leetcode/blob/master/204/c/main.c)

---
2015/8/7
