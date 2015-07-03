#include <iostream>
#include <vector>

using namespace std;

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
