#include <stdio.h>
#include <stdlib.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int zeroCount = 0, zeroIndex;
    int product = 1, i;
    // 遍历所有数字，求乘积，统计0的个数并记录0出现的位置
    for (i = 0; i < numsSize; ++i) {
        if (*(nums + i) == 0) {
            ++zeroCount;    // 0的个数加1
            zeroIndex = i;  // 记录0出现的位置
        } else product *= *(nums + i);  // 求乘积
    }

    int* ret = (int*)malloc(sizeof(int) * numsSize);
    if (zeroCount == 0) {   // 如果没有0
        for (i = 0; i < numsSize; ++i)  // 依次用product除以当前数字
            *(ret + i) = product / *(nums + i); // 即为目标值
    } else {    // 出现了0
        for (i = 0; i < numsSize; ++i)
            *(ret + i) = 0; // 所有位置先赋0
        if (zeroCount == 1) // 如果0仅出现了一次，那么这个0所在位置的乘积不为0
            *(ret + zeroIndex) = product;   // 赋值
    }
    *returnSize = numsSize;
    return ret;
}

void test(int* nums, int numsSize) {
    int size, i;
    int* ret = productExceptSelf(nums, numsSize, &size);
    printf("[");
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", *(nums + i));
    printf("%d] : ", *(nums + numsSize - 1));
    printf("[");
    for (i = 0; i < size - 1; ++i)
        printf("%d,", *(ret + i));
    printf("%d]\n", *(ret + size - 1));
    free(ret);
}
int main() {
    int nums1[] = {1, 2, 3, 4};
    test(nums1, 4);
    int nums2[] = {0, 0};
    test(nums2, 2);
    int nums3[] = {1, 2, 3, 4, 5, 0};
    test(nums3, 6);
    int nums4[] = {1, 2, 3, 0, 4, 0};
    test(nums4, 6);
    return 0;
}
