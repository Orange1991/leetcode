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
    /* 如果价格数据为空，返回0  */
    if (pricesSize <= 0) return 0;

    int *min = (int *)malloc(sizeof(int) * pricesSize),
        *max = (int *)malloc(sizeof(int) * pricesSize);

    /* 统计某一天极其之前所有时间内价格的最小值  */
    int i, minimal = *prices, maximal = *(prices + pricesSize - 1);
    *min = minimal; *(max + pricesSize - 1) = maximal;
    for (i = 1; i < pricesSize; ++i) {
        if (*(prices + i) < minimal) minimal = *(prices + i);
        *(min + i) = minimal;
    }
    /* 统计某一天极其之后所有时间内价格的最大值  */
    for (i = pricesSize - 2; i > -1; --i) {
        if (*(prices + i) > maximal) maximal = *(prices + i);
        *(max + i) = maximal;
    }

    /* 计算最大收益 */
    int diff;
    maximal = *max - *min;
    for (i = 1; i < pricesSize; ++i) {
        diff = *(max + i) - *(min + i);
        if (diff > maximal)
            maximal = diff;
    }

    free(min);
    free(max);

    return maximal;
}

int main(void) {
    int prices[] = { 5, 1, 2, 0, 4, 3, 2, 1 }, num = 8;
    printf("%d\n", maxProfit(prices, num));
    return 0;
}
