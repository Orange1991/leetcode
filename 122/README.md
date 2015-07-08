#Best Time to Buy and Sell Stock II 不限次数次买卖股票最大收益

##原题地址
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

##题目描述
Say you have an array for which the ith element is the price of a given stock on day i.
假设你有一个数组，里面记录的是每一天的股票的价格。

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times). However, you may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
设计一个算法来计算最大收益。你可以完成任意次数的交易（即，买买股票多次）。但是你不能同时进行多次交易（即，在你买入股票之前必须卖掉手里的股票）。

##解题思路
一拿到这个题目的时候，我想到的是动态规划，结果TLE，于是我开始重新看这个题。说实话，真的看不出来，于是从网上搜了一下，原来答案如此简单。用贪心非常好做。但是我发现，贪心算法可以解决的问题，都很难去发现他是一个贪心，当知道答案后又觉得，原来这么简单。还是得加强啊。

我们可以很自然的这么想，只要后面一天的价格比前一天高，那么我们一定可以将这个差价转化为收益。这样问题变得简单起来，从第二天开始往后遍历，比较其于前一天的价格，只要后面价格大于前面一天的价格，就把差价加到收益里去。特殊的，对于[1,2,3]这组数据，我们的最大收益为1+1=2，即第一天买入，第二天卖出，收入+1，第二天买入，第三题卖出，收入+1；第二天买入卖出抵消，就相当于第一天买入，第三题卖出，收入为3-1=2。

##算法描述
> 1. profit = 0
> 2. 从第2天开始遍历，判定当天价格是否大于前一天价格，若是，则将差价加到profit上，否则继续判定下一天，直到最后一天
> 3. 返回profit

##代码 C

```
/**
 * 计算最大收益
 * @param prices : 每天的股票价格
 * @param pricesSize : 数据规模
 * @return : 最大收益
 * @note : 可以买卖多次
 */
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize <= 1) return 0;

    int max = 0, day;
    for (day = 1; day < pricesSize; ++day)
        if (*(prices + day) > *(prices + day - 1))
        max += *(prices + day) - *(prices + day - 1);

    return max;
}
```

> 完整代码[https://github.com/Orange1991/leetcode/blob/master/122/c/main.c](https://github.com/Orange1991/leetcode/blob/master/122/c/main.c)

##代码 CPP

```
class Solution {
public:
    /**
     * 计算最大收益
     * @param prices : 每天的股票价格
     * @return : 最大收益
     * @note : 可以买卖多次
     */
    int maxProfit(vector<int>& prices) {
        int pricesSize = prices.size();
        if (pricesSize <= 1) return 0;

        int max = 0, day;
        for (day = 1; day < pricesSize; ++day)
            if (prices[day] > prices[day - 1])
            max += prices[day] - prices[day - 1];

        return max;
    }
};
```

> 完整代码[https://github.com/Orange1991/leetcode/blob/master/122/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/122/cpp/main.cpp)

##运行情况
| Lauguage | Status | Time |
| :------- | :----- | :--- |
| c        | Accept | 4ms  |
| cpp      | Accept | 8ms  |

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/46810121


---
2015/7/8
