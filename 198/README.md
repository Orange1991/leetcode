#Leetcode 198 House Robber 抢劫最大金额

##原题地址
https://leetcode.com/problems/house-robber/

##题目描述
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
你是一个专业的强盗，计划去抢一条街上的房子。每个房子里都有一定量的钱，唯一限制你抢掉所有房子里的钱的是：相邻的房子的安保系统是连接在一起的，如果相邻的两个房子在同一晚上都被盗的话就会自动报警。

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
给出一系列非负的整数代表每个房子内的金钱数量，计算你今晚不触发报警条件的情况下可以抢到的最多的钱。

**Tags** `Dynamic Programming`

##解题思路
对于求解这个问题，关键问题是对于某间房子，我们抢还是不抢。假设我们用rob[i]表示抢劫第i间房子的情况下在之后的所有房子里可以得到的最大金额，用notRob[i]表示不抢劫第i间房子的情况下在之后的所有房子里可以得到的最大金额。在**求解rob[i]时，抢劫第i间房子，很明显不能继续抢劫它的下一间房子**，因此rob[i]需要根据notRob[i+1]来计算，**对于notRob[i]，我们不抢第i间房子时，第i+1间房子既可以抢也可以不抢**，我们根据rob[i+1]和notRob[i+1]之间的较大者来计算notRob[i]。

**rob[i]** : 在抢劫第i间房子的情况下，可以从其之后的所有房子里（`nums[i]~nums[n]`）获得的金钱。

**notRob[i]** : 在不抢劫第i间房子的情况下，可以从其之后的所有房子里（`nums[i]~nums[n]`）获得的金钱。

有如下方程来计算：

> $rob[i] = num[i] + notRob[i + 1]$
如果抢劫了第i间，一定不能抢劫后面相邻的房子。

> $notRob[i] = bigger(rob[i + 1], notRob[i + 1])$
如果没有抢劫第i间，可以抢或者不抢后面相邻的房子。

##算法

> 1. 初始化最后一天的rob[n]=num[n]和notRob[n]=0
> 2. 从后往前处理，rob[i] = num[i] + notRob[i + 1]，notRob[i] = bigger(rob[i + 1], notRob[i + 1])
> 3. 返回bigger(rob[0], notRob[0]);

##代码

```
/**
 * 计算可能抢劫的最大数额
 * @param nums 每个房子中的金额
 * @param numsSize 房子数量
 * @return 抢劫的最大数额
 */
int rob(int* nums, int numsSize) {
    int bigger(int, int);

    if (numsSize == 0) return 0;
    
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
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/198/cpp/main.c](https://github.com/Orange1991/leetcode/blob/master/198/cpp/main.c)

##测试数据

    [4,3,5,6,1,2,0,4,2,5] : 21

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47301025

---
2015/8/5
