#include <stdio.h>
#include <stdlib.h>

/**
 * 抢劫环状社区获得最大金额
 * 不能抢劫相邻房屋，房屋呈环状，首尾相接
 * @param nums 每个房子内的金额
 * @param numsSize 房屋数量
 * @return 最大金额
 */
int rob(int* nums, int numsSize) {
    int rotStreet(int*, int);
    int bigger(int, int);

    /* 对于这个问题，我们选取任一房子A
     * 则在抢劫最大金额时，对A仅有两种情况：
     * 要么抢劫A，要么不抢劫A
     * (1)如果抢劫A，则A左右相邻的房子B和C一定不能抢，
     * 这时除去ABC的其他房子就可以看成是首尾不相接的一条街上的房子
     * 这时最大金额为sum1=nums[A]+robStreet(除去ABC的其他所有房子);
     * (2)如果不抢A，则除去A之外的所有房子可以看成是一条接上的房子
     * 这时最大金额为sum2=robStreet(除去A的其他所有房子)
     * sum1和sum2中较大者就是待求解
     * 特别的，我们可以选择第0所房子作为A */

    if (numsSize <= 0) return 0;
    if (numsSize == 2) return bigger(*nums, *(nums + 1));

    // 抢劫A时的最大金额
    int sum1 = *nums + robStreet(nums + 2, numsSize - 3);
    // 不抢A时的最大金额
    int sum2 = robStreet(nums + 1, numsSize - 1);
    
    return bigger(sum1, sum2);
}

/**
 * 抢劫一条街上的房子，计算可能抢劫的最大数额
 * 不能抢劫相邻的房子
 * @param nums 每个房子中的金额
 * @param numsSize 房子数量
 * @return 抢劫的最大数额
 */
int robStreet(int* nums, int numsSize) {
    int bigger(int, int);

    if (numsSize <= 0) return 0;

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
    int nums1[] = {0};
    test(nums1, 1);
    return 0;
}
