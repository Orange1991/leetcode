#Best Time to Buy and Sell Stock 单次买卖股票最大收益

##原题地址
https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

##题目描述
Say you have an array for which the ith element is the price of a given stock on day i.
假设你有一个数组，里面记录的是每一天的股票的价格。

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.
如果你至多只能完成一次交易（即，买一次股票、卖一次股票），设计一个算法来计算最大收益。

##解题思路
极大值减去极小值即可获得临时最大收益，一次遍历过程中不断更新临时最大收益。遍历结束时即获得最大收益。

##算法描述
> 1. 极小值low设为第一天的价格。
> 2. 遍历剩余的价格，设当前某一天的价格为cur，计算diff=cur-low，如果diff<0，则找到新的极小值；如果diff>max则更新最大收益max=diff，否则继续遍历下一天，重复第2步。
> 3. 返回最大收益max。

##代码 C

```
/**
 * 计算最大收益
 * @param prices : 每日价格
 * @param pricesDize : 数据规模
 * @return : 最大收益 
 * @note : 只进行一次买卖
 */
int maxProfit(int* prices, int pricesSize) {
    /* 如果价格数据为空或者只有一个数据，返回0  */
    if (pricesSize <= 1) return 0;

    int min = *prices, day, diff, max = 0;
    for (day = 1; day < pricesSize; ++day) {
        diff = *(prices + day) - min;
        if (diff < 0) min = *(prices + day);
        else if (diff > max) max = diff;
    }

    return max;
}
```

> 完整代码[https://github.com/Orange1991/leetcode/blob/master/121/c/main.c](https://github.com/Orange1991/leetcode/blob/master/121/c/main.c)

##代码 CPP

```
class Solution {
public:
    /**
     * 计算最大收益
     * @param prices : 每日价格
     * @return : 最大收益 
     * @note : 只进行一次买卖
     */
    int maxProfit(vector<int>& prices) {
        int pricesSize = prices.size();
        /* 如果价格数据为空,或者只有一个数据,返回0  */
        if (pricesSize <= 1) return 0;

        int day, diff, min = prices[0], max = 0;
        for (day = 1; day < pricesSize; ++day) {
            diff = prices[day] - min;
            if (diff < 0) min = prices[day];
            else if (diff > max) max = diff;
        }

        return max;
    }
};
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/121/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/121/cpp/main.cpp)

##运行情况
| Lauguage | Status | Time |
| :------- | :----- | :--- |
| c        | Accept | 4ms  |
| cpp      | Accept | 8ms  |

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/46810549

---
2015/7/8
