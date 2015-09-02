#Leetcode 4 Median of Two Sorted Arrays 有序数组的中位数

##原题地址
https://leetcode.com/problems/median-of-two-sorted-arrays/

##题目描述
There are two sorted arrays nums1 and nums2 of size m and n respectively. Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
有两个有序数组nums1[m]和nums2[n]。找出这两个数组的中位数。要求时间复杂度O(log(m+n))。

##解题思路

*参考 [leetcode之 median of two sorted arrays](http://blog.csdn.net/yutianzuijin/article/details/11499917/)*

##代码

```
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int findKth(int*, int, int*, int, int);
    int total = nums1Size + nums2Size;
    if (total & 0x1)
        return findKth(nums1, nums1Size, nums2, nums2Size, total / 2 + 1);
    else
        return (findKth(nums1, nums1Size, nums2, nums2Size, total / 2) +
                findKth(nums1, nums1Size, nums2, nums2Size, total / 2 + 1)) / 2.0;
}

/**
 * 在两个有序数组中找出第k小的数
 * @param nums1 有序数组1
 * @param nums1Size 有序数组1大小
 * @param nums2 有序数组2
 * @param nums2Size 有序数组2大小
 * @param k 目标结果在两个数组中的顺序
 * @return 第k小的数
 */
int findKth(int* nums1, int nums1Size, int* nums2, int nums2Size, int k) {
    int smaller(int, int);

    // 默认数组1的大小不大于数组2的大小
    if (nums1Size > nums2Size)  // 如果不符合默认情况，则反转数组的角色 
        return findKth(nums2, nums2Size, nums1, nums1Size, k);

    // 如果数组1大小为0，直接返回数组2中的第k个数
    if (nums1Size == 0) 
        return *(nums2 + k - 1);
   
    // 如果k=1，直接返回两数组的第一个元素中较小的那个
    if (k == 1)
        return smaller(*nums1, *nums2);

    // 将两个数组都分为两部分，根据中间值的大小来删除不可能的候选者，每次删除n/2个元素
    int p1 = smaller(nums1Size, k / 2), p2 = k - k / 2;
    if (*(nums1 + p1 - 1) < *(nums2 + p2 - 1))  // nums1的前p1部分肯定比第k个数小
        return findKth(nums1 + p1, nums1Size - p1, nums2, nums2Size, k - p1);
    else if (*(nums1 + p1 - 1) > *(nums2 + p2 - 1)) // nums2的前p2部分肯定比第k个数小
        return findKth(nums1, nums1Size, nums2 + p2, nums2Size - p2, k - p2);
    else    // 如果nums1[p1]=nums2[p2]，而p1+p2=k，因此找到第k个元素
        return *(nums1 + p1 -1);
}

inline int smaller(int a, int b) { return a < b ? a : b; }
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/4/c/main.c](https://github.com/Orange1991/leetcode/blob/master/4/c/main.c)

##测试数据

    [1,2,3,4,5,6,7,8]
    [9,10,11]
    the median is : 6.000000.

    [1,2,3,4,5,6,7,8]
    [1,2,3,4,5,6,7,8]
    the median is : 4.500000.

    [0]
    [1,2]
    the median is : 1.500000.

---
2015/9/2
