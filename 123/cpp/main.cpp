#include <iostream>
#include <vector>

using namespace std;

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
