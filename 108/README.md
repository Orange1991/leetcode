#Convert Sorted Array to Binary Search Tree
##原题地址
https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

##题目描述
Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
给出一个有序数组（递增），使用该数组构造一个平衡二叉查找树。

##解题思路
动态规划问题。我们从待选范围内选取中间数字来构造根结点，然后该取比该数字小的所有数字来构造该根结点的左子树，然后取比该数字大的所有数字来构造该根结点的右子树。

需要注意的是，对于某组数据，其中间结点可能有多种选择策略，例如：
    
    [0, 1, 2, 3]
我们既可以选择1也可以选择2来构造根结点：

       1              2
      / \     or     / \
     0 [2,3]      [0,1] 3
在这两种情况下，其结果都是符合题目要求的，这里，我们仅选择其中一种来作为解决方案。在验证我们构造的二叉树是否是平衡二叉查找树时，我们仅判定它是否符合平衡二叉查找树的定义，但不判定具体是哪一种（leetcode应该也是这样的检查策略）。

##算法描述
> 1. 计算中间节点n/2，构造根节点；
2. 使用中间节点以左的n/2个节点，递归构造左子树；
3. 使用中间节点以右的n/2个节点，递归构造右子树。


##代码 C

```
/**
 * 根据有序（递增）序列生成平衡二叉查找树
 * input nums     : 递增序列
 * input numsSize : 递增序列的元素个树
 */
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    struct TreeNode* sortedSeqToBST(int*, int, int);
    return sortedSeqToBST(nums, 0, numsSize - 1);
}

/**
 * 根据有序（递增）序列的某一子序列生成平衡二叉查找树
 * input nums  : 递增序列
 * input start : 子序列开始位置（包含）
 * input end : 子序列结束位置（包含）
 */
struct TreeNode* sortedSeqToBST(int* nums, int start, int end) {
    /* 如果开始位置大于结束位置，返回NULL */
    if (start > end) return NULL;

    /* 创建根节点 */
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    
    /* 计算中间位置的点
     * 这样可以保证左右子树的点的个数的差不大于1
     * 以满足题目构造平衡二叉树的要求 */
    int center = (start + end) / 2;
    
    /* 保存根节点的值 */
    node->val = *(nums + center);    
    
    /* 分别使用中间点以左和以右的子序列构造左右子树 */
    node->left = sortedSeqToBST(nums, start, center - 1);
    node->right = sortedSeqToBST(nums, center + 1, end);
	
    return node;

}
```

> 完整代码[https://github.com/Orange1991/leetcode/blob/master/108/c/main.c](https://github.com/Orange1991/leetcode/blob/master/108/c/main.c)

##代码 CPP

```
class Solution {
public:
    /**
     * 根据有序（递增）序列生成平衡二叉查找树
     * input nums : 递增序列
     */
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedSeqToBST(nums, 0, nums.size() - 1);
    }

private:
    /**
     * 根据有序（递增）序列的某一子序列生成平衡二叉查找树
     * input nums  : 递增序列
     * input start : 子序列开始位置（包含）
     * input end   : 子序列结束位置（包含）
     */
    TreeNode* sortedSeqToBST(vector<int>& nums, int start, int end) {
        /* 如果开始位置大于结束位置，返回NULL */
        if (start > end) return NULL;

        /* 计算中间位置的点
         * 这样可以保证左右子树的点的个数的差不大于1
         * 以满足题目构造平衡二叉树的要求 */
        int center = (start + end) / 2;
    
        /* 创建根节点 */
        /* 保存根节点的值 */
        TreeNode* node = new TreeNode(nums[center]);
    
        /* 分别使用中间点以左和以右的子序列构造左右子树 */
        node->left = sortedSeqToBST(nums, start, center - 1);
        node->right = sortedSeqToBST(nums, center + 1, end);
	
        return node;

    }
};
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/108/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/108/cpp/main.cpp)

##解决情况
| Lauguage | Status | Time |
| :------- | :----- | :--- |
| c        | Accept | 4ms  |
| cpp      | Accept | 20ms  |


##博文地址
http://blog.csdn.net/smile_watermelon/article/details/46353103


---
2015/6/3
