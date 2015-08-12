#Leetcode 188 Best Time to Buy and Sell Stock IV 至多k次买卖股票最大收益

##原题地址
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

##题目描述
Say you have an array for which the ith element is the price of a given stock on day i.
假设你有一个数组，里面记录的是每一天的股票的价格。

Design an algorithm to find the maximum profit. You may complete at most k transactions.
设计一个算法来计算最大收益。你至多可以完成k次交易。

Note:
注意：
You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
你不能同时进行多次交易（即，在你买入股票之前必须卖掉手里的股票）。

##解题思路

这是这个系列的第四题，前三题如下：
> - [121 Best Time to Buy and Sell Stock 单次买卖股票最大收益 ](http://blog.csdn.net/smile_watermelon/article/details/46810549)
> - [122 Best Time to Buy and Sell Stock II 不限次数买卖股票最大收益](http://blog.csdn.net/smile_watermelon/article/details/46810121)
> - [Leetcode 123 Best Time to Buy and Sell Stock III 至多两次买卖股票最大收益](http://blog.csdn.net/smile_watermelon/article/details/46810503)

参考了网上诸多大神的代码，[有位大神](http://www.cnblogs.com/grandyang/p/4295761.html)说这个题是II和III的结合版。在某特殊情况下是II，其他情况下是III的升级。后面再详述。

网上的代码大致分两种，**时间复杂度O(n*k)**，**空间复杂度O(n)**，但是两种的角度不同。

第一种，大家可以看下面的博文：
> - [http://blog.csdn.net/linhuanmars/article/details/23236995](http://blog.csdn.net/linhuanmars/article/details/23236995)
> - [http://www.cnblogs.com/grandyang/p/4295761.html](http://www.cnblogs.com/grandyang/p/4295761.html)
> - [http://blog.csdn.net/ljiabin/article/details/44900389](http://blog.csdn.net/ljiabin/article/details/44900389)

另外一种，大家可以参考以下文章：
> - [http://blog.csdn.net/u012501459/article/details/46519085](http://blog.csdn.net/u012501459/article/details/46519085)
> - [https://leetcode.com/discuss/18330/is-it-best-solution-with-o-n-o-1](https://leetcode.com/discuss/18330/is-it-best-solution-with-o-n-o-1)

第一种维护两个数组，local[][]和global[][]，其中**global[i][j]表示到第i天时完成j次交易的最大收益**，**local[i][j]表示到第i天时完成j次交易并且最后一次交易发生在第i天时的最大收益**。

global的推导公式如下：
> global[i][j] = max(local[i][j], global[i-1][j]);
即，到第i天完成j次交易的最大收益，要么是第j次交易发生在第i天时的最大收益，要么是到第i-1天完成j次交易时的最大收益。

local的推导公式如下：
> local[i][j] = max(global[i-1][j-1]+max(diff,0), local[i-1][j]+diff);
需要看两个量，第一个是全局global到i-1天进行j-1次交易，然后加上今天的交易，如果今天是赚钱的话（也就是前面只要j-1次交易，最后一次交易取当前天）；第二个量则是取local第i-1天j次交易，然后加上今天的差值（这里因为local[i-1][j]比如包含第i-1天卖出的交易，所以现在变成第i天卖出，并不会增加交易次数，而且这里无论diff是不是大于0都一定要加上，因为否则就不满足local[i][j]必须在最后一天卖出的条件了）。

代码请看代码一。

第二种想法是维护两个数组buy和sell，**buy[i]表示完成第i笔交易的买入动作时的最大收益**，**sell[i]表示完成第i笔交易的卖出动作时的最大收益**。初始情况下buy[i]=MIN，sell[i]=0。

buy[i]的推导
> buy[i] = max(buy[i], sell[i-1]-prices[j])

即，第i-1次完成卖出时的最大收益再减去第j天的价格，有可能更新第i次完成买入时的最大收益。

sell[i]的推导
> sell[i] = max(sell[i], buy[i]+prices[j])

即，第i次完成买入时的最大收益再加上第j天的价格，有可能更新第i次卖出时的最大收益。

代码请见代码二。

##代码

###代码一

```
class Solution {
public:
    /**
     * 计算最大收益
     * @param k : 至多进行k次买卖
     * @param prices : 每日价格
     * @return : 最大收益 
     */
    int maxProfit(int k, vector<int>& prices) {
        int pricesSize = prices.size();

        /* 如果价格数据为空或只有一个数据，或者不能进行买卖，返回0  */
        if (pricesSize <= 1 || k <= 0) return 0;

        /* k>=pricesSize，相当于不限交易次数 */
        if (k >= pricesSize) {
            int max = 0;
            for (int i = 1; i < pricesSize; ++i)
                if (prices[i] > prices[i-1])
                    max += prices[i] - prices[i-1];
            return max;
        }

        int *local = new int[k + 1];
        int *global = new int[k + 1];
        for (int i = 0; i <= k; ++i)
            local[i] = global[i] = 0;

        for (int i = 1; i < pricesSize; ++i) {
            int diff = prices[i] - prices[i - 1];
            for (int j = k; j > 0; --j) {
                local[j] = bigger(global[j - 1] + bigger(diff, 0), local[j] + diff);
                global[j] = bigger(local[j], global[j]);
            }
        }

        int max = global[k];
        delete(local);
        delete(global);
        return max;
    }

private:
    int bigger(int a, int b) {
        return a > b ? a : b;
    }
};
```
> 完整代码  [https://github.com/Orange1991/leetcode/blob/master/188/cpp/solution2.cpp](https://github.com/Orange1991/leetcode/blob/master/188/cpp/solution2.cpp)

###代码二

```
class Solution {
public:
    /**
     * 计算最大收益
     * @param k : 至多进行k次买卖
     * @param prices : 每日价格
     * @return : 最大收益 
     */
    int maxProfit(int k, vector<int>& prices) {
        int pricesSize = prices.size();

        /* 如果价格数据为空或只有一个数据，或者不能进行买卖，返回0  */
        if (pricesSize <= 1 || k <= 0) return 0;

        /* k>=pricesSize，相当于不限交易次数 */
        if (k >= pricesSize) {
            int max = 0;
            for (int i = 1; i < pricesSize; ++i)
                if (prices[i] > prices[i-1])
                    max += prices[i] - prices[i-1];
            return max;
        }

        // 第i次买入和卖出时的最大收益
        vector<int> buy(pricesSize + 1, numeric_limits<int>::min()), sell(pricesSize + 1); 
    
        for (int day = 0; day < pricesSize; ++day) {
            for (int transaction = 1; transaction <= k; ++transaction) {
                buy[transaction] = bigger(buy[transaction], sell[transaction - 1] - prices[day]);
                sell[transaction] = bigger(sell[transaction], buy[transaction] + prices[day]);
            }
        }

        return sell[k];
    }

private:
    int bigger(int a, int b) {
        return a > b ? a : b;
    }
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/188/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/188/cpp/main.cpp)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47445981

---
2015/8/12

