#Leetcode 213 House Robber II 抢劫最大金额

##原题链接
https://leetcode.com/problems/house-robber-ii/

##题目描述
Note: This is an extension of [House Robber](https://leetcode.com/problems/house-robber/).
注意：这题是[House Robber](https://leetcode.com/problems/house-robber-ii/)的扩展，解题详见[Leetcode 198 House Robber 抢劫最大金额](http://blog.csdn.net/smile_watermelon/article/details/47301025)。

After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.
抢劫完那条街道上的房子之后，这个贼有找到了实施自己盗窃行动的另一个地点，这样他才不会引来太多注意。这次，这里的搜有房子排成了一个圆圈，这意味着第一个房子和最后一个房子也是挨着的。与此同时，房子的安保系统还是和之前那条街上的一样（不能同时抢劫两所相邻的房子，否则会报警）。

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
给出一个非负整数数组，代表每个房子内的金钱数额，计算你今晚在不惊动警方的前提下可以抢劫的最大金额。

**Tag** `Dynamic Programming`

##解题思路
作为House Robber（[查看详解](http://blog.csdn.net/smile_watermelon/article/details/47301025)）的扩展题，这道题跟其非常相似，唯一不同的地方是现在多了一个条件，房子围成圈，即第一个房子和最后一个房子是相邻的。我们之前对House Robber的解决方案在这里肯定行不通，因为我们没有考虑第一个房子和最后一个房子不能同时抢劫的问题。然而，之前的解决方案也不是完全没有用处，我们可以把问题化简为House Robber问题，那么该如何做呢？

这里我们可以这么来考虑。对于房子中的任意一所房子A，我们在抢劫最大金额的情况下，只有两种情况：（1）抢劫A，（2）不抢A

    围成圈的房屋
      A B C D E F G H I
     T                 J
      S R Q P O N M L k

> (1) 当我们抢劫A的时候
> 与A相邻的房子不能抢了，这时剩下的房子可以随意抢劫，除去A及其相邻的房子就可以看成是不成环的一条街上的房子，这时就变成House Robber问题了，最大金额sum1=nums[A]+robStreet(除去A及其相邻房子的所有房子)。robStreet表示按照House Robber问题中抢劫一条街上的房子来计算得到最大金额

    除去A及其相邻的房屋，计算robStreet(除去A及其相邻的房子)
          C D E F G H I
                       J
      S R Q P O N M L k  
    
    等同于一条街上的房屋
    C D E F G H I J K L M N O P Q R S

> (2) 当我们不抢A的时候
> 除去A的所有房子都可以随意抢劫，除去A之外的所有房子就可以看成是不成环的一条街上的房子，这时也是House Robber问题，最大金额sum2=robStreet(除去A的所有房子)。


    除去A的所有房屋，计算robStreet(除去A的所有房子)
        B C D E F G H I
     T                 J
      S R Q P O N M L k  
    
    等同于一条街上的房屋
    B C D E F G H I J K L M N O P Q R S T

有了sum1和sum2之后，其中的较大者就是我们要求的值。即`max=bigger(sum1, sum2)`。

特别的，在书写代码时，我们可以选取第0个房子作为A，实际上选取哪一个对结果并没有影响。

##代码

```
/**
 * 抢劫环状社区获得最大金额
 * 不能抢劫相邻房屋，房屋呈环状，首尾相接
 * @param nums 每个房子内的金额
 * @param numsSize 房屋数量
 * @return 最大金额
 */
int rob(int* nums, int numsSize) {
    int rotStreet(int*, int);
    int bigger(int, int);

    /* 对于这个问题，我们选取任一房子A
     * 则在抢劫最大金额时，对A仅有两种情况：
     * 要么抢劫A，要么不抢劫A
     * (1)如果抢劫A，则A左右相邻的房子B和C一定不能抢，
     * 这时除去ABC的其他房子就可以看成是首尾不相接的一条街上的房子
     * 这时最大金额为sum1=nums[A]+robStreet(除去ABC的其他所有房子);
     * (2)如果不抢A，则除去A之外的所有房子可以看成是一条接上的房子
     * 这时最大金额为sum2=robStreet(除去A的其他所有房子)
     * sum1和sum2中较大者就是待求解
     * 特别的，我们可以选择第0所房子作为A */

    if (numsSize <= 0) return 0;
    if (numsSize == 2) return bigger(*nums, *(nums + 1));

    // 抢劫A时的最大金额
    int sum1 = *nums + robStreet(nums + 2, numsSize - 3);
    // 不抢A时的最大金额
    int sum2 = robStreet(nums + 1, numsSize - 1);
    
    return bigger(sum1, sum2);
}

/**
 * 抢劫一条街上的房子，计算可能抢劫的最大数额
 * 不能抢劫相邻的房子
 * @param nums 每个房子中的金额
 * @param numsSize 房子数量
 * @return 抢劫的最大数额
 */
int robStreet(int* nums, int numsSize) {
    int bigger(int, int);

    if (numsSize <= 0) return 0;

    // 抢劫某间房子时，可以从后面的所有房子里抢劫的最大金额
    int *maxWhenRob = (int *)malloc(sizeof(int) * numsSize);
    // 不抢劫某间房子时，可以从后面的所有房子里抢劫的最大金额
    int *maxWhenNotRob = (int *)malloc(sizeof(int) * numsSize);

    int index = numsSize - 1;
    /* 初始化最后一天的数据 */
    *(maxWhenRob + index) = *(nums + index);
    *(maxWhenNotRob + index) = 0;
    /* 循环处理之前的房子 */
    for (--index; index > -1; --index) {
        // 抢劫某间房子一定不能抢后面的相邻的房子
        *(maxWhenRob + index) = *(nums + index) + *(maxWhenNotRob + index + 1);
        // 不抢某间房子，其后面的房子可以抢也可以不抢，选其中的较大者
        *(maxWhenNotRob + index) = bigger(
                *(maxWhenRob + index + 1), *(maxWhenNotRob + index + 1));
    }

    int max = bigger(*maxWhenRob, *maxWhenNotRob);
    free(maxWhenRob);
    free(maxWhenNotRob);
    return max;
}

/** 返回两者中的较大者 */
int bigger(int a, int b) { return a > b ? a : b; }
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/213/c/main.c](https://github.com/Orange1991/leetcode/blob/master/213/c/main.c)

##测试数据

    [4,3,5,6,1,2,0,4,2,5] : 20

同一组数据在House Robber题目中计算结果为21.

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47791673

---
2015/8/19
