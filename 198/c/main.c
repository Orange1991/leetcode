#include <stdio.h>
#include <stdlib.h>

/**
 * 计算可能劫掠到的最大数额
 * @param nums 每个房子中的金额
 * @param numsSize 房子数量
 * @return 劫掠到的最大数额
 */
int rob(int* nums, int numsSize) {
    int bigger(int, int);

    if (numsSize == 0) return 0;
    
    // 抢劫某间房子时，可以从后面的所有房子里抢劫的最大金额
    int *maxWhenRob = (int *)malloc(sizeof(int) * numsSize);
    // 不抢劫某间房子时，可以从后面的所有房子里抢劫的最大金额
    int *maxWhenNotRob = (int *)malloc(sizeof(int) * numsSize);

    int index = numsSize - 1;
    /* 初始化最后一天的数据 */
    *(maxWhenRob + index) = *(nums + index);
    *(maxWhenNotRob + index) = 0;
    /* 循环处理之前的房子 */
    for (--index; index > -1; --index) {
        // 抢劫某间房子一定不能抢后面的相邻的房子
        *(maxWhenRob + index) = *(nums + index) + *(maxWhenNotRob + index + 1);
        // 不抢某间房子，其后面的房子可以抢也可以不抢，选其中的较大者
        *(maxWhenNotRob + index) = bigger(
                *(maxWhenRob + index + 1), *(maxWhenNotRob + index + 1));
    }

    int max = bigger(*maxWhenRob, *maxWhenNotRob);
    free(maxWhenRob);
    free(maxWhenNotRob);
    return max;
}

/** 返回两者中的较大者 */
int bigger(int a, int b) { return a > b ? a : b; }

void test(int* nums, int numsSize) {
    printf("    [");
    int i = 0;
    while (i < numsSize - 1) printf("%d,", *(nums + i++));
    printf("%d] : %d\n", *(nums + i), rob(nums, numsSize));
}

int main() {
    int nums[] = {4, 3, 5, 6, 1, 2, 0, 4, 2, 5};
    test(nums, 10);
    return 0;
}
