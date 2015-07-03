#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * 计算最大收益
     * @param prices : 每日价格
     * @return : 最大收益 
     * @note : 只进行一次买卖
     */
    int maxProfit(vector<int>& prices) {
        /* 如果价格数据为空，返回0  */
        if (prices.size() <= 0) return 0;

        vector<int> min(prices.size()), max(prices.size());
        
        /* 统计某一天极其之前所有时间内价格的最小值  */
        int i, pricesSize = prices.size(), minimal = prices[0], maximal = prices[pricesSize - 1];
        min[0] = minimal; max[pricesSize - 1] = maximal;
        for (i = 1; i < pricesSize; ++i) {
            if (prices[i] < minimal) minimal = prices[i];
            min[i] = minimal;
        }
        /* 统计某一天极其之后所有时间内价格的最大值  */
        for (i = pricesSize - 2; i > -1; --i) {
            if (prices[i] > maximal) maximal = prices[i];
            max[i] = maximal;
        }

        /* 计算最大收益 */
        int diff;
        maximal = max[0] - min[0];
        for (i = 1; i < pricesSize; ++i) {
            diff = max[i] - min[i];
            if (diff > maximal)
                maximal = diff;
        }

        return maximal;
    }
};

int main(void) {
    Solution s;
    vector<int> prices;
    prices.push_back(5);
    prices.push_back(1);
    prices.push_back(2);
    prices.push_back(0);
    prices.push_back(4);
    prices.push_back(3);
    prices.push_back(2);
    prices.push_back(1);
    cout << s.maxProfit(prices) << endl;
    return 0;
}
