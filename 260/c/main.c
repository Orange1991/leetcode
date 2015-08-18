#include <stdio.h>
#include <stdlib.h>

/**
 * 找出仅出现一次的两个数字
 * @param nums 数组，其中只有两个元素仅出现一次，其余元素均出现两次
 * @param numsSize 数组大小
 * @param returnSize 返回数组大小
 * @return 仅出现一次的两个数字
 */
int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int* ret = (int*)malloc(sizeof(int) * 2);
    *returnSize = 2;
    
    // a: 目标结果a
    // b: 目标结果b
    // tmp: a^b的结果
    // one: a和b最低的不相同的位
    int tmp = 0, a = 0, b = 0, i, one = 1;
    for (i = 0; i < numsSize; ++i) // 计算a^b
        tmp ^= *(nums + i);
    while (!(tmp & 1)) { // 获取a和b最低的不相同的位
        one <<= 1;
        tmp >>= 1;
    }
    // 按a和b最低的不相同的位把所有数据分为两组
    // a和b分别分在两个组里，问题转化为两个2n+1的问题
    // 两组分别异或即可得到两个目标结果
    for (i = 0; i < numsSize; ++i) 
        if (one & *(nums + i))
            a ^= *(nums + i);
        else
            b ^= *(nums + i);
    *ret = a;
    *(ret + 1) = b;
    return ret;
}

void test(int* nums, int numsSize) {
    int i, size;
    printf("    [");
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", *(nums + i));
    int* ret = singleNumber(nums, numsSize, &size);
    printf("%d] : [%d,%d]\n", *(nums + numsSize - 1), *ret, *(ret + 1));
    free(ret);
}
int main() {
    int nums[] = {1, 2, 1, 3, 5, 2};
    test(nums, 6);
}
