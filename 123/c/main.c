#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    int prices[] = { 5, 1, 2, 0, 4, 3, 2, 1 }, num = 8;
    printf("%d\n", maxProfit(prices, num));
    return 0;
}
