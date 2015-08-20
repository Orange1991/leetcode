#include <stdio.h>

/**
 * 返回nums中第k大的元素
 * @param nums 源数据
 * @param numsSize 源数据大小
 * @param k 目标数据排序
 * @return nums中第k大的元素
 */
int findKthLargest(int* nums, int numsSize, int k) {
    int center = numsSize / 2 - 1;
    // 建堆
    int process = center, cur, left, right, tmp, bigger;
    while (process > -1) { // 从中间结点开始到堆顶，依次调整
        cur = process--;
        while (cur <= center) { 
            left = 2 * cur + 1;
            right = 2 * cur + 2;
            if (right >= numsSize) { // 如果只有左孩子
                if (*(nums + cur) < *(nums + left)) { // 如果左孩子大，则交换
                    tmp = *(nums + cur);
                    *(nums + cur) = *(nums + left);
                    *(nums + left) = tmp;
                    cur = left; // 继续调整左孩子
                } else break; // 否则退出当前结点的调整
            } else { // 有左右孩子，获取其中较大者
                bigger = *(nums + left) > *(nums + right)
                        ? left : right;
                if (*(nums + cur) < *(nums + bigger)) { // 如果较大者大，则交换
                    tmp = *(nums + cur);
                    *(nums + cur) = *(nums + bigger);
                    *(nums + bigger) = tmp;
                    cur = bigger; // 继续调整较大者
                } else break; // 否则退出当前结点的调整
            }
        }
    }
    // 堆排序
    int end = numsSize - 1;
    while (--k) {
        tmp = *(nums + end); // 交换堆顶与堆底元素
        *(nums + end) = *nums;
        *nums = tmp;
        cur = 0;
        center = end / 2 - 1;
        while (cur <= center) { // 调整堆顶元素
           left = 2 * cur + 1;
            right = 2 * cur + 2;
            if (right >= end) { // 如果只有左孩子
                if (*(nums + cur) < *(nums + left)) { // 如果左孩子大，则交换
                    tmp = *(nums + cur);
                    *(nums + cur) = *(nums + left);
                    *(nums + left) = tmp;
                    cur = left; // 继续调整左孩子
                } else break; // 否则退出当前结点的调整 
            } else { // 有左右孩子，获取其中较大者
                bigger = *(nums + left) > *(nums + right)
                        ? left : right;
                if (*(nums + cur) < *(nums + bigger)) { // 如果较大者大，则交换
                    tmp = *(nums + cur);
                    *(nums + cur) = *(nums + bigger);
                    *(nums + bigger) = tmp;
                    cur = bigger; // 继续调整较大者
                } else break; // 否则退出当前结点的调整
            }   
        }
        --end;
    }
    return *nums;
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
    test(nums2, 3, 2);

    return 0;
}
