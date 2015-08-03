#include <stdio.h>

/** 求最大子数组乘积 */
int maxProduct(int* nums, int numsSize) {   
    int subHead = 0, subTail = 0, max = *nums, index = 0, negNums = 0, product = 0;
    int start = 0, end = 0;

    /* 初始化最大值为数组中的最大元素 */
    for (index = 1; index < numsSize; ++index)
        if (max < *(nums + index)) max = *(nums + index);

    /* 将数组处理成不包含0的多个子数组
     * 子数组以subHead（包含）开始，以subTail（不包含）结尾 */
    while (subHead < numsSize) {
        // 略过当前子数组首部的0
        while (subHead < numsSize && *(nums + subHead) == 0) ++subHead;
        if (subHead == numsSize) break; // 如果没有下一个子数组，则处理结束
        subTail = subHead + 1; // 初始化subTail
        // 继续扩展子数组，直到数组结尾或者某一个元素为0
        while (subTail < numsSize && *(nums + subTail) != 0) ++subTail;

        // 至此，可以保证subHead和subTail之间的元素全都不为0

        /* 如果当前子数组仅有一个元素，则最大乘积只可能是其唯一的元素 */
        if (subTail == subHead + 1) {
            if (max < *(nums + subHead)) max = *(nums + subHead);
            subHead = subTail + 1;
            continue; // 当前子数组处理结束，继续下一个子数组的处理
        }

        /* 统计子数组中负数的个数 */
        negNums = 0;
        for (index = subHead; index < subTail; ++index)
            if (*(nums + index) < 0) ++negNums;
        
        /* 求最大乘积 */
        if (negNums & 1) { // 如果子数组中负数的个数为奇数
                           // 最大乘积是第一个负数元素之后的所有元素的乘积
                           // 或者最后一个负数元素之前的所有元素的乘积

            /* 求第一个负数元素之后的所有元素的乘积 */
            start = subHead;
            end = subTail;
            for (; start < subTail; ++start) // 找到第一个负数元素
                if (*(nums + start) < 0) break;
            ++start;
            if (start < end) { // 第一个负数元素不是最后一个元素
                product = 1;
                for (index = start; index < end; ++index) 
                    product *= *(nums + index);
                if (max < product) max = product;
            }

            /* 求最后一个负数元素之前的所有元素的乘积 */
            start = subHead;
            end = subTail;
            for (; end > start; --end) // 找到最后一个负数元素
                if (*(nums + end - 1) < 0) break;
            --end;
            if (end > start) { // 最后一个负数元素不是第一个元素
                product = 1;
                for (index = start; index < end; ++index) 
                    product *= *(nums + index);
                if (max < product) max = product;
            }
        } else { // 如果子数组中负数的个数为偶数，则最大乘积是所有元素的乘积
            product = 1;
            for (index = subHead; index < subTail; ++index)
                product *= *(nums + index);
            if (max < product) max = product;
        }

        subHead = subTail + 1;
    }

    return max;
}

void test(int* nums, int numsSize) {
    int i = 0;
    printf("[");
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d, ", *(nums + i));
    printf("%d] : %d\n", *(nums + i), maxProduct(nums, numsSize));
}

int main() {
    int nums1[] = {-2}, nums2[] = {1, 0, 0, 0},
        nums3[] = {0, -2, -3}, nums4[] = {5, 6, -3, 0},
        nums5[] = {0, -2, 0, -2, -3, 4, 0, 5, 6, -3},
        nums6[] = {0, -2, 0, -2, -3, 4, 0, 5, 6, -3, 0, -2, 2, 3, 4, -3, -1},
        nums7[] = {2, -5, -2, -4, 3}, nums8[] = {-2, 0, -1};

    test(nums1, 1);
    test(nums2, 4);
    test(nums3, 3);
    test(nums4, 4);
    test(nums5, 10);
    test(nums6, 17);
    test(nums7, 5);
    test(nums8, 3);

    return 0;
}
