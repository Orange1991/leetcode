#include <stdio.h>

/**
 * 返回局部和大于等于s的最小子数组长度
 * @param s 给定的局部和
 * @param nums 数据数组
 * @param numsSize 数据个数
 * @return 满足条件的子数组的最小长度 如果不存在满足条件的子数组返回0
 */
int minSubArrayLen(int s, int* nums, int numsSize) {
    if (numsSize <= 0) return 0;
    
    int len = numsSize + 1, slow = 0, fast = 1, sum = *nums; // 初始化
    while (fast < numsSize) {
        while (fast < numsSize && sum < s) // 和小于s时fast往前移动
            sum += *(nums + fast++);

        while (slow < fast && sum >= s)  // 和大于等于s时，slow往前移动，试图缩小子数组
            sum -= *(nums + slow++); // slow往前移动，并更新子数组局部和
        
        if (len > fast - slow + 1)  // 试图缩小满足条件的子数组长度 
            len = fast - slow + 1;
    }

    // 如果len没有变化说明没有这样的子数组，返回0
    return len == numsSize + 1 ? 0 : len; 
}

void test(int s, int* nums, int numsSize) {
    int i;
    printf("[");
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", *(nums + i));
    printf("%d], s=%d : len=%d\n", *(nums + numsSize - 1), s, minSubArrayLen(s, nums, numsSize));
}

int main() {
    int num[] = {2, 3, 1, 2, 4, 3};
    test(7, num, 6);
    int nums[] = {5, 1, 3, 5, 10, 7, 4, 9, 2, 15};
    test(15, nums, 10);
    int nums1[] = {5, 1, 3, 5, 10, 7, 4, 9, 2, 8};
    test(15, nums1, 10);
    int nums2[] = {5, 1, 3, 5, 10, 7, 4, 9, 2, 15};
    test(100, nums2, 10);

    return 0;
}
