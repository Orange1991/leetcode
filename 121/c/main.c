#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    int prices[] = { 5, 1, 2, 0, 4, 3, 2, 1 }, num = 8;
    printf("%d\n", maxProfit(prices, num));
    return 0;
}
