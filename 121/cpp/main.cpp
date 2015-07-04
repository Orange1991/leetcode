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
