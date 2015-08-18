#include <stdio.h>
#include <stdlib.h>

/**
 * 返回特殊的数字
 * 特殊数字仅出现y次，其余数字均出现x次，x>0，y>0，x>y
 * @param nums 数字集合
 * @param numsSize 集合大小
 * @param x 普通数字出现次数
 * @param y 特殊数字出现次数
 */
int specialNumber(int *nums, int numsSize, int x, int y) {
    int num, change, i;
    int* times = (int*)malloc(sizeof(int) * (x + 1));
    for (i = 1; i <= x; ++i) *(times + i) = 0;
    while (numsSize) {
        *times = ~0; // 置全1，保证*(times+1)结果的正确性
        // 获取当前要统计的数字
        num = *(nums + --numsSize); 
        for (i = x; i > 0; --i) { // 更新每一位掩码
            change = *(times + i - 1) & num; // 获得更新位
            *(times + i) |= change;  // 更新
            num &= ~change;         // 清空更新位
            *(times + i - 1) &= ~change;
        }
    }
    num = *(times + y);
    free(times);
    return num;
}
void test(int* nums, int numsSize, int x, int y) {
    printf("    [");
    int i;
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", *(nums + i));
    printf("%d] : each number appears %d times expect for the special one appears %d times, the special number is %d\n", *(nums + numsSize - 1), x, y, specialNumber(nums, numsSize, x, y));
}

int main() {
    int nums0[] = {1,2,3,4,1,2,3,1,2,3};
    int nums1[] = {1,1,2,2,3,4,4,5,5,66,66};
    int nums2[] = {1,1,1,3,3,3,44,44,55,55,55,111,111,111};
    int nums3[] = {1};
    test(nums0, 10, 3, 1);
    test(nums1, 11, 2, 1);
    test(nums2, 14, 3, 2);
    test(nums3, 1, 3, 1);
}
