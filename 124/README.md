#Binary Tree Maximum Path Sum 二叉树最大路径和
##原题链接
https://leetcode.com/problems/binary-tree-maximum-path-sum/

##题目描述
Given a binary tree, find the maximum path sum.
给出一棵二叉树，计算其最大路径和。

The path may start and end at any node in the tree.
路径的起止结点必须位于树内。

For example:
例如：

Given the below binary tree,
给出如下二叉树，


       1
      / \
     2   3

Return 6.
返回6（sum path 2-1-3）。

##解题思路
这个题目还是挺不好想的，我们需要找到问题的关键点。那么对于二叉树里的一条子路径，什么是关键点呢？我们先来做一个假设，假设我们已经找到这个路径path了，我认为关键点就是某一个结点是否处于这个路径内。但是如何找这个path呢？我们不妨假设，我们正在处理的子树的根结点root一定位于这个path内，我们计算当path一定经过了root时的最大路径和max(root)。那么max(root)该如何计算呢？我们假设我们已经求除了当path一定经过root->left时的最大路径和max(root->left)，也求除了当path一定经过root->right时的最大路径和max(root->right)，这时候，如果max(root->left)>0，那么对于root而言，将root->left和root连接起来的path的和一定比root自己构成的path的和要大；同理，如果max(root->right)>0，那么对于root而言，将root->left和root连接起来的path的和一定比root自己构成的path的和要大。然而对于一条路径来说，root要么跟root->left连接在一起，要么跟root->right连接在一起，要么root既不跟root->left也不跟root->right连接在一起，不然路径会出现分叉。因此我们需要对root->val+max(root->left)、root->val、root->val+max(root->right)求出其中的最大值来作为max(root)的值。

有了如上的步骤之后，我们到底该如何确定二叉树的最大路径和呢？实际上，我们上述过程是求得了**以某一个结点为根的子树的最大路径和，其中路径的起点为根，终点为子树中的某一结点**，我们注意到这个过程中，我们每次都只是从根的左右子结点中选择其中的一个来连接到path中，实际上，一个path是有可能既连接root->left，又连接root->right的，但是这种情况至多会出现在其中一个结点x上，否则就会出现路径的分叉了。因此，我们在求的max(root->left)、max(root->right)之后，尝试将root作为我们上面提到的x点，然后来计算由max(root->left)、max(root->right)、root->val可能构成的最大和tmp，然后判定tmp和当前缓存好的max（最大路径和），并更新max值即可。最后，这个max就是我们要求的最大路径和。

##算法

> 1. 如果root为NULL，返回0
> 2. 递归调用1-5，求得maxSum(root->left)和maxSum(root->right)
> 3. maxSum(root) = max(root->val, root->val + maxSum(root->left), root->val + maxSum(root->right))
> 4. 判定root->val 、 maxSum(root->left)、maxSum(root->right)三者可能构成的最大和（必须包含root->val），是否大于目前缓存的最大路径和tmp，如果是则更新tmp
> 5. 返回maxSum(root)的值
> 6. 递归调用结束后，tmp的值就是最大路径和

##代码c
```
/**
 * 计算二叉树的最大路径和
 * @param : root 二叉树根结点
 * @return : 最大路径和
 */
int maxPathSum(struct TreeNode *root) {
    int maxChildPathSum(struct TreeNode *, int *);
    if (root == NULL) return 0;
    int tmpMax = root->val;
    
    maxChildPathSum(root, &tmpMax);
    return tmpMax;
}

/**
 * 计算二叉树子树的最大路径和以及整棵二叉树的最大路径和
 * 子树路径必须以根结点开始，以树中某一结点结束
 * 二叉树的最大路径和的路径，不必以根结点为开始结点
 * @param : root 二叉树根结点
 * @param : tmpMax 暂存整棵二叉树的最路径和的变量的地址
 * @return : 子树的最大路径和
 */
int maxChildPathSum(struct TreeNode *root, int *tmpMax) {
    int max(int, int);

    if (root == NULL) return 0;

    /* 计算左右子树的最大路径和 */
    int leftMax = maxChildPathSum(root->left, tmpMax);
    int rightMax = maxChildPathSum(root->right, tmpMax);

    /* 尝试更新整棵二叉树的最大路径和 */    
    int tmp = root->val;
    if (leftMax > 0) tmp += leftMax;
    if (rightMax > 0) tmp += rightMax;
    if (tmp > *tmpMax) *tmpMax = tmp;


    /* 计算并返回子树的最大路径和 */
    int maxRoot = max(root->val, max(root->val + leftMax, root->val + rightMax));
    return maxRoot;
}

/* 求两个数中较大的数字 */
int max(int arg1, int arg2) { return arg1 > arg2 ? arg1 : arg2; }
```
>完整代码[https://github.com/Orange1991/leetcode/blob/master/124/c/main.c](https://github.com/Orange1991/leetcode/blob/master/124/c/main.c)
##代码cpp
```
class Solution {
public:
    /**
     * 计算二叉树的最大路径和
     * @param : root 二叉树根结点
     * @return : 最大路径和
     */
    int maxPathSum(TreeNode *root) {
        if (root == NULL) return 0;
        int tmpMax = root->val;
    
        maxChildPathSum(root, &tmpMax);
        return tmpMax;
    }

private:
    /**
     * 计算二叉树子树的最大路径和以及整棵二叉树的最大路径和
     * 子树路径必须以根结点开始，以树中某一结点结束
     * 二叉树的最大路径和的路径，不必以根结点为开始结点
     * @param : root 二叉树根结点
     * @param : tmpMax 暂存整棵二叉树的最路径和的变量的地址
     * @return : 子树的最大路径和
     */  
    int maxChildPathSum(TreeNode *root, int *tmpMax) {
        if (root == NULL) return 0;

        /* 计算左右子树的最大路径和 */
        int leftMax = maxChildPathSum(root->left, tmpMax);
        int rightMax = maxChildPathSum(root->right, tmpMax);

        /* 尝试更新整棵二叉树的最大路径和 */    
        int tmp = root->val;
        if (leftMax > 0) tmp += leftMax;
        if (rightMax > 0) tmp += rightMax;
        if (tmp > *tmpMax) *tmpMax = tmp;

        /* 计算并返回子树的最大路径和 */
        int maxRoot = max(root->val, max(root->val + leftMax, root->val + rightMax));
        return maxRoot;
    }

    /* 求两个数中较大的数字 */
    int max(int arg1, int arg2) { return arg1 > arg2 ? arg1 : arg2; }
};
```
>完整代码[https://github.com/Orange1991/leetcode/blob/master/124/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/124/cpp/main.cpp)

##测试数据

    输入：[2,1,3]
    输出： 6

    输入：[5,6,7,-4,null,-1,1,2]
    输出：19

    输入：[5,6,7,-4,null,null,-1,1,2]
    输出：18

    输入：[-5,6,7,-4,null,null,-1,1,2]
    输出：8
    
    输入：[1,-2,3]
    输出：4

##解决情况
| Lauguage | Status | Time |
| :------- | :----- | :--- |
| c        | Accept | 20ms |
| cpp      | Accept | 32ms |

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/46883371

---
2015/7/14
