#Leetcode 215 Kth Largest Element in an Array 数组中第k大的元素

##原题地址
https://leetcode.com/problems/kth-largest-element-in-an-array/

##题目描述
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
在一个无须数组中找出第k大的元素。

For example,
例如，

Given
给出

` [3,2,1,5,6,4]` and `k = 2`, 

return
返回

` 5`.

Note:
注意：
 
You may assume k is always valid, 1 ≤ k ≤ array's length.
假设k是有效的，即`1 ≤ k ≤ 数组长度`

**Tags** `Heap` `Divide and Conquer`

##解题思路
要求得数组中第k大的元素其实并不难，只要我们把数组排序，第k大元素很容易获得。如果是这样的话，我们使用任何一种排序手段都可以了，如果追求高效用快排就好。然而还有没有可以优化的地方呢？**有**，由于我们需要求第k大的元素，那么我们无须把所有元素都排好序，我们只要得到前k个元素就可以了，那有没有这样的排序方式呢？有，就是**堆排**。

在堆排中，我们先建立一个大顶堆（最大堆），然后根据k的值，依次移除堆顶元素并且调整堆结构，如此操作k-1次后在堆顶的就是第k大的元素。当我们获得第k大元素之后即可返回结果而无须对剩余元素进行排序处理，这无疑可以尽量减少操作，具有更有的效率。

##代码

###代码一

这个版本中把调整堆的方法独立出来，代码结构清晰。从堆的中间结点向堆顶以此调整堆结构，最后完成初始情况下的大顶堆。然后依次把最后一个元素放在堆顶以覆盖堆顶元素（可以认为是删除了当前最大元素），再调整堆的结构。操作k-1次后堆顶就是第k大元素。

为了不修改原始数据nums，先拷贝数据，然后在拷贝数据上处理。实际上可以直接在nums上处理（如果是下面的代码还需调整以下，在删除堆顶元素时，注意把堆顶元素和末尾元素对调而不是简单的覆盖），但这会影响原始数据，这要根据实际需求来选择。

```
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
```

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/215/c/s2.c](https://github.com/Orange1991/leetcode/blob/master/215/c/s2.c)

###代码二
这个版本中没有把调整堆的方法独立出来，整个处理函数使用循环而不使用递归，缺点是结构不够清晰，代码有冗余，复用程度低。

另外这个版本中直接在nums原始数据上进行处理，操作后结果会影响nums中数据的位置。

```
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
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/215/c/main.c](https://github.com/Orange1991/leetcode/blob/master/215/c/main.c)

##测试数据

    nums = [3,2,1,5,6,4], k = 1, the target number is 6
    nums = [3,2,1,5,6,4], k = 2, the target number is 5
    nums = [3,2,1,5,6,4], k = 3, the target number is 4
    nums = [3,2,1,5,6,4], k = 4, the target number is 3
    nums = [3,2,1,5,6,4], k = 5, the target number is 2
    nums = [3,2,1,5,6,4], k = 6, the target number is 1
    nums = [-1,2,0], k = 3, the target number is -1
    nums = [-1,2,0], k = 2, the target number is 0
    nums = [-1,2,0], k = 1, the target number is 2
    
##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47807159

---
2015/8/20
