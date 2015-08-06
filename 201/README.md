#Leetcode 201 Bitwise AND of Numbers Range 区间内整数按位与

##原题地址
https://leetcode.com/problems/bitwise-and-of-numbers-range/

##题目描述
Given a range [m, n] where 0 <= m <= n <= 2147483647, return the bitwise AND of all numbers in this range, inclusive.
给出一个区间 [m, n]，其中0 <= m <= n <= 2147483647，即m,n都是非负整数，返回这个区间内所有整数的按位与结果，包括m和n在内．

For example, given the range [5, 7], you should return 4.
例如，给出区间 [5, 7]，你应该返回4．

    5 --- 0000 0101
    6 --- 0000 0110
    7 --- 0000 0111
    _______________
    4 --- 0000 0100


##解题思路
显然，暴力解决方法是从m开始直到n求按位与，但很明显这太慢了，虽然时间复杂度是O(n)，但显然不是一个好的解法．我们可以注意到这样一点，在数字加1的时候，最低位肯定会从0变成1，或者从1变成0，不管哪样，两个数的最低位中势必有一个0，而一旦出现了一个0，这一位上的按位与结果将永远为0．假如在m->n的增加过程中，m的最高位也发生了改变，那么m之下的所有位都变成过0．那样的话结果也只能是0了．我们再来看两个相邻的数，m,m+1,在+1的时候，改变的位可能是多个，而且改变一定是0->1或者1->0，因此，发生改变的位在求AND操作后结果一定是0，因此只有那些没有改变的位才能在AND结果之后保留下来，于是对于m和m+1我们只要找到从最高位开始完全相同的位．同样对于m+1和m+2也是如此．但是如果我们真的按照这个逻辑来的话就跟暴力解法一样了．我们可以发现，对于m和n，找到他们从最高位开始完全相同的位，就是我们需要的结果．这也不难理解，m和n假如在最高位到x位之间的二进制位完全相同，这就说明在递增的过程中+1的操作永远没有改变过这些位，而相反第x-1到最后一位都至少改变过一次，而改变一定是0->1或者1->0，就是说在着m-n+1个操作数中至少有一个的第i位（i>=0 && i<=x-1）为0．因此，第x-1位之下全都为0，m和n从最高位开始的连续相同部分就是我们要的结果．

##算法

> 1. 偏移量offset = 0
> 2. 当m,n都不为0时执行循环，进入3
> 3. 如果m==n,返回m<<offset，否则4
> 4. m,n均右移一位，offset加1，进入3

##代码

```
int rangeBitwiseAnd(int m, int n) {   
    int offset = 0;
    while (m && n) {
        if (m == n) return m << offset;
        m >>= 1;
        n >>= 1;
        ++offset;
    }
    return 0;
}
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/201/c/main.c](https://github.com/Orange1991/leetcode/blob/master/201/c/main.c)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47320381

---
2015/8/6
