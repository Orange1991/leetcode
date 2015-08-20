#include <stdio.h>
#include <stdlib.h>

/**
 * 返回nums中第k大的元素
 * @param nums 源数据
 * @param numsSize 源数据大小
 * @param k 目标数据排序
 * @return nums中第k大的元素
 */
int findKthLargest(int* nums, int numsSize, int k) {
    void heapify(int*, int, int);
    // 建堆
    int* heap = (int*)malloc(sizeof(int) * numsSize), i;
    for (i = 0; i < numsSize; ++i) *(heap + i) = *(nums + i);
    int process = numsSize / 2 - 1;
    while (process > -1)
        heapify(heap, numsSize, process--);
    // 依次移除堆顶元素（当前最大）
    int end = numsSize - 1, tmp;
    while (--k) {
        *heap = *(heap + end);
        heapify(heap, end--, 0);
    }
    tmp = *heap;
    free(heap);
    return tmp;
}

/** 调整堆 */
void heapify(int* heap, int heapSize, int point) {
    int center = heapSize / 2 - 1;
    if (point > center) return;
    int left = 2 * point + 1, right = left + 1, tmp, bigger;
    if (right >= heapSize) { // 不存在右孩子
        if (*(heap + point) < *(heap + left)) { // 如果比左孩子小，则两者交换
            tmp = *(heap + point);
            *(heap + point) = *(heap + left);
            *(heap + left) = tmp;
            heapify(heap, heapSize, left); // 递归调整左孩子
        }
    } else { // 存在右孩子，与左右孩子中较大者交换
        bigger = *(heap + left) > *(heap + right) ? left : right;
        if (*(heap + point) < *(heap + bigger)) { // 如果比左右孩子中较大者小，则交换
            tmp = *(heap + point);
            *(heap + point) = *(heap + bigger);
            *(heap + bigger) = tmp;
            heapify(heap, heapSize, bigger); // 递归调整
        }
    }
    
}

void test(int* nums, int numsSize, int k) {
    printf("    nums = [");
    int i;
    for (i = 0; i < numsSize - 1; ++i)
        printf("%d,", *(nums + i));
    printf("%d], k = %d, ", *(nums + numsSize - 1), k);
    printf("the target number is %d\n", findKthLargest(nums, numsSize, k));
}

int main() {
    int nums1[] = {3, 2, 1, 5, 6, 4};
    test(nums1, 6, 1);
    test(nums1, 6, 2);
    test(nums1, 6, 3);
    test(nums1, 6, 4);
    test(nums1, 6, 5);
    test(nums1, 6, 6);

    int nums2[] = {-1, 2, 0};
    test(nums2, 3, 3);
    test(nums2, 3, 2);
    test(nums2, 3, 1);

    return 0;
}
