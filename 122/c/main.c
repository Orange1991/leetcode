#include <stdio.h>
#include <stdlib.h>

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

int main(void) {
    int prices[] = { 5, 1, 2, 0, 3, 2, 1, 4 }, num = 8;
    printf("%d\n", maxProfit(prices, num));
    return 0;
}
