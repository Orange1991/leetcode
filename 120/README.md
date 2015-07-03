#Triangle

##原题链接
https://leetcode.com/problems/triangle/

##题目描述
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
给出一个三角形（数据数组），找出从上往下的最小路径和。每一步只能移动到下一行中的相邻结点上。

For example, given the following triangle
例如，给出以下三角

    [
         [2],
        [3,4],
       [6,5,7],
      [4,1,8,3]
    ]

The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
则从上至下最小路径和为11（即，2 + 3 + 5 + 1 = 11）.

Note:
注意：

Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
如果你可以只使用O（n）的额外空间（n是三角形的行数），可以获得奖励分数。

##解题思路
简单的动态规划，唯一的问题是题目里给的空间复杂度的要求。先来说动态规划，当选择下面一层中的数字时，我们只能选择相邻的数字。什么是相邻的数字呢？拿上面的例子来说，对于2，下一行里3和4是相邻的；对于3来说，6和5是相邻的；对于4来说，5和7是相邻的；对于6来说，4和1是相邻的；对于5来说，1和8是相邻的；对于7来说，8和3是相邻的；对于4/1/8/3来说，没有下一行所以没有相邻数字了。如果我们把数字都对应到数据在每一行中的下标上，可以很容易发现，对于一个data[i][j]，和它相邻的数字就是data[i+1][j]和data[i+1][j+1]。这样一来问题就简单了。假如我们用minimus[i][j]来表示从第i行第j列处的数字开始往下到最后一层的最小路径和，那么有

> minimus[i][j] = data[i][j] + min(minimums[i+1][j] + minimums[i+1][j+1])

然而上述描述中需要一个O（n^2）的额外空间，接下来我们来解决这个问题。

由于我们在公式里需要递归求解子问题，那么我们不妨反过来想一下，先求解子问题，然后再解决父问题。即，**从下往上求解最小路径和**。我们可以发现如下规律，当我们求解minimum[i][j]时，我们会用到minimum[i+1][j]和minimum[i+1][j+1]，但是当求解完所有minimum[i]之后minimum[i+1]就没有用处了。既然如此，我们是否可以复用同一个空间来存储minimum的值呢？答案是可以的。进一步观察发现，存储最后一行的每个数字的最小路径和需要n个空间，因此至少我们需要n个空间，这也是题目里给出O（n）的空间复杂度的原因；之后存储倒数第二行时，我们只需要前面的n-1个空间……以此类推，第一行只需要一个空间来存储最小路径和，这也正是我们要求解的结果。

具体算法见下文。

##算法描述

> 1. 申请n个空间minNums[n]，初始化minNums[n]为数据triangle[][]的最后一行。最后一行的数字到最底层的最小路径和就是他们自己本身。
> 2. 从倒数第二行开始往上（row），从左向右（col）循环计算并更新minNums的值，minNums[col]=min(minNums[col], minNums[col+1]) + triangle[row][col]
> 3. 最后minNums[0]就是我们要的答案。

##代码实现

###c

```
/** 计算三角从上至小最小路径和 */
int minimumTotal(int **triangle, int numRows) {
    int *minNums = (int *)malloc(sizeof(int) * numRows);
    int i, j;

    /* 初始化 */
    for (i = 0; i < numRows; ++i)
        *(minNums + i) = *(*(triangle + numRows - 1) + i);

    /* 循环求解 */
    for (i = numRows - 2; i > -1; --i) {
        for (j = 0; j <= i; ++j)
            *(minNums + j) = *(*(triangle + i) + j) + 
                    (*(minNums + j) < *(minNums + j + 1) 
                    ? *(minNums + j) : *(minNums + j + 1));
   }

    i = *minNums;
    free(minNums);

    return i;
}
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/120/c/main.c](https://github.com/Orange1991/leetcode/blob/master/120/c/main.c)

###cpp

```
class Solution {
public:
    /** 计算三角从上至小最小路径和 */
    int minimumTotal(vector<vector<int> > &triangle) {
        vector<int> minNums = triangle[triangle.size() - 1];
        for (int i = triangle.size() - 2; i > - 1; --i)
            for (int j = 0; j <= i; ++j)
                minNums[j] = (minNums[j] < minNums[j + 1] ? minNums[j] : minNums[j + 1])
                        + triangle[i][j];
        return minNums[0];
    }
};
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/120/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/120/cpp/main.cpp)

##运行情况

| Lauguage | Status | Time |
| :------- | :----- | :--- |
| c        | Accept | 4ms  |
| cpp      | Accept | 8ms  |

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/46741303

---
// 2015/7/3
