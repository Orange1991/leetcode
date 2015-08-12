#Best Time to Buy and Sell Stock III 至多两次买卖股票最大收益

##原题地址
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/

##题目描述
Say you have an array for which the ith element is the price of a given stock on day i.
假设你有一个数组，里面记录的是每一天的股票的价格。

Design an algorithm to find the maximum profit. You may complete at most two transactions.
设计一个算法来计算最大收益。你至多可以完成两次交易。

##解题思路

这个题跟121[Best Time to Buy and Sell Stock 单次买卖股票最大收益](https://github.com/Orange1991/leetcode/tree/master/121) 122[Best Time to Buy and Sell Stock II 不限次数买卖股票最大收益](https://github.com/Orange1991/leetcode/tree/master/122)。

这个题可以借鉴第一个题目中的思路。这个题是一个动态规划的题目。我们假设将1-n天分为1-day,day-n两部分，然后我们分别在两部分中至多进行一次交易获得两部分的最大值，将两部分加在一起就是一个待选的最大收益，day可以取1,2,...,n，所以会得到n个后选值，在候选值中选出最大的一个就是最大收益。借鉴121中计算最大收益的方法，我们可以在第一次遍历中计算1-day的最大收益formmer[n]，第二遍历时计算day-n的最大收益latter[n]，最后再遍历一次得到最大收益max。

公式：
$ max = max < formmer[i] + latter[i] ? fommer[i] + latter[i] : max $

这里需要说明的是，如果formmer[i]和latter[i]的值在计算的时候都用到了第i天的价格，即第i天卖出了股票才的到了formmer[i]，第i天买入了股票才得到了latter[i]，也并不妨碍我们的计算，因为这就相当于第i天没有买入和卖出，即所有时间内只进行了以此买卖，而不是两次。

ps: 2015年小米春季实习生招聘在线笔试第二题就是这个题，不过当时我没刷这个题，但是还是做出来啦～

---

发现一个**更牛逼**的方法，时间复杂度O(n)，空间复杂度O(1)。

博文 [http://blog.csdn.net/u012501459/article/details/46514309](http://blog.csdn.net/u012501459/article/details/46514309) 中的解法二。

最原始贴：[https://leetcode.com/discuss/18330/is-it-best-solution-with-o-n-o-1](https://leetcode.com/discuss/18330/is-it-best-solution-with-o-n-o-1)

*2015/8/12更新*

##算法描述
> 1. 遍历，计算出第x天之前一次交易可以得到的最大收益，存储在formmer[n]中
> 2. 遍历，计算出第x天之后一次交易可以得到的最大收益，存储在latter[n]中
> 3. 遍历，计算formmer[i] + latter[i] 得到最大收益max

##代码 C

```
/**
 * 计算最大收益
 * @param prices : 每日价格
 * @param pricesDize : 数据规模
 * @return : 最大收益 
 * @note : 至多进行两次买卖
 */
int maxProfit(int* prices, int pricesSize) {
    /* 如果价格数据为空或只有一个数据，返回0  */
    if (pricesSize <= 1) return 0;

    int *maxProfitDuringFormmerDays = (int *)malloc(sizeof(int) * pricesSize),
        *maxProfitDuringLatterDays = (int *)malloc(sizeof(int) * pricesSize);

    int day, diff, minPrice, maxPrice, maxProfit;
    
    /* 计算某一天极其之前所有时间内的最大利益  */
    minPrice = *prices; 
    maxProfit = 0;
    *maxProfitDuringFormmerDays = 0;
    for (day = 1; day < pricesSize; ++day) {
        diff = *(prices + day) - minPrice;
        if (diff < 0) minPrice = *(prices + day);
        else if (diff > maxProfit) maxProfit = diff;
        *(maxProfitDuringFormmerDays + day) = maxProfit;
    }

    /* 计算某一天极其之后所有时间内价格的最利益  */
    maxPrice = *(prices + pricesSize - 1);
    maxProfit = 0;
    *(maxProfitDuringLatterDays + pricesSize - 1) = 0;
    for (day = pricesSize - 2; day > -1; --day) {
        diff = maxPrice - *(prices + day);
        if (diff < 0) maxPrice = *(prices + day);
        else if (diff > maxProfit) maxProfit = diff;
        *(maxProfitDuringLatterDays + day) = maxProfit;
    }

    /* 计算最大收益 */
    int sum;
    maxProfit = 0;
    for (day = 0; day < pricesSize; ++day) {
        sum = *(maxProfitDuringFormmerDays + day) + *(maxProfitDuringLatterDays + day);
        if (sum > maxProfit) maxProfit = sum;
    }

    free(maxProfitDuringFormmerDays);
    free(maxProfitDuringLatterDays);

    return maxProfit;
}
```

> 完整代码[https://github.com/Orange1991/leetcode/blob/master/123/c/main.c](https://github.com/Orange1991/leetcode/blob/master/123/c/main.c)

##代码 CPP

```
class Solution {
public:
    /**
     * 计算最大收益
     * @param prices : 每日价格
     * @return : 最大收益 
     * @note : 至多进行两次买卖
     */
    int maxProfit(vector<int>& prices) {
        int pricesSize = prices.size();

        /* 如果价格数据为空或只有一个数据，返回0  */
        if (pricesSize <= 1) return 0;

        vector<int> maxProfitDuringFormmerDays(pricesSize),
                maxProfitDuringLatterDays(pricesSize);

        int day, diff, minPrice, maxPrice, maxProfit;
    
        /* 计算某一天极其之前所有时间内的最大利益  */
        minPrice = prices[0]; 
        maxProfit = 0;
        maxProfitDuringFormmerDays[0] = 0;
        for (day = 1; day < pricesSize; ++day) {
            diff = prices[day] - minPrice;
            if (diff < 0) minPrice = prices[day];
            else if (diff > maxProfit) maxProfit = diff;
            maxProfitDuringFormmerDays[day] = maxProfit;
        }

        /* 计算某一天极其之后所有时间内价格的最利益  */
        maxPrice = prices[pricesSize - 1];
        maxProfit = 0;
        maxProfitDuringLatterDays[pricesSize - 1] = 0;
        for (day = pricesSize - 2; day > -1; --day) {
            diff = maxPrice - prices[day];
            if (diff < 0) maxPrice = prices[day];
            else if (diff > maxProfit) maxProfit = diff;
            maxProfitDuringLatterDays[day] = maxProfit;
        }

        /* 计算最大收益 */
        int sum;
        maxProfit = 0;
        for (day = 0; day < pricesSize; ++day) {
            sum = maxProfitDuringFormmerDays[day] + maxProfitDuringLatterDays[day];
            if (sum > maxProfit) maxProfit = sum;
        }

       return maxProfit;
    }

};
```

> 完整代码[https://github.com/Orange1991/leetcode/blob/master/123/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/123/cpp/main.cpp)

##运行情况
| Lauguage | Status | Time |
| :------- | :----- | :--- |
| c        | Accept | 4ms  |
| cpp      | Accept | 12ms  |

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/46810503

---
2015/7/8
