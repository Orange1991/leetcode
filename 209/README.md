#Leetcode 209 Minimum Size Subarray Sum

##原题地址
https://leetcode.com/problems/minimum-size-subarray-sum/

##题目描述
Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum ≥ s. If there isn't one, return 0 instead.
给出一个正整数数组，以及一个正整数s，找到最短的子数组且该子数组的和不小于s。如果不存在这样的子数组，返回0.

For example, given the array `[2,3,1,2,4,3]` and `s = 7`,
例如，给出数组`[2,3,1,2,4,3]`，`s=7`，

the subarray [4,3] has the minimal length under the problem constraint.
在上面给出的约束条件下，子数组`[4,3]`具有最短的长度。

##解题思路
这个问题比较简单，使用**两个指针**，其中一个指针fast向后移动，寻求满足sum>s的位置，另一个指针向前移动，试图在sum>s的条件下缩小子数组的长度的，并且更新最短长度len。

##代码
```
/**
 * 返回局部和大于等于s的最小子数组长度
 * @param s 给定的局部和
 * @param nums 数据数组
 * @param numsSize 数据个数
 * @return 满足条件的子数组的最小长度 如果不存在满足条件的子数组返回0
 */
int minSubArrayLen(int s, int* nums, int numsSize) {
    if (numsSize <= 0) return 0;
    
    int len = numsSize + 1, slow = 0, fast = 0, sum = *nums; // 初始化
    while (fast < numsSize) {
        while (fast < numsSize && sum < s) // 和小于s时fast往前移动
            sum += *(nums + ++fast);

        if (fast == numsSize) break; // 移动至结尾，且sum仍小于s，结束

        while (slow <= fast && sum >= s)  // 和大于等于s时，slow往前移动，试图缩小子数组
            sum -= *(nums + slow++); // slow往前移动，并更新子数组局部和
        
        if (len > fast - slow + 2)  // 试图缩小满足条件的子数组长度 
            len = fast - slow + 2;
    }

    // 如果len没有变化说明没有这样的子数组，返回0
    return len == numsSize + 1 ? 0 : len; 
}
```

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/209/c/main.c](https://github.com/Orange1991/leetcode/blob/master/209/c/main.c)

##测试数据

    [2,3,1,2,4,3], s=7 : len=2
    [5,1,3,5,10,7,4,9,2,15], s=15 : len=1
    [5,1,3,5,10,7,4,9,2,8], s=15 : len=2
    [5,1,3,5,10,7,4,9,2,15], s=100 : len=0

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47660763

---
2015/8/14
