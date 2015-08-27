#Leetcode 222 Count Complete Tree Nodes 完全二叉树的结点数

##原题地址
https://leetcode.com/problems/count-complete-tree-nodes/

##题目描述
Given a complete binary tree, count the number of nodes.
给出一个完全二叉树，计算其结点数。

[Definition of a complete binary tree from Wikipedia](http://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees):
来自[维基百科的完全二叉树的定义](http://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees)：

In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.
除去最底层外的每一层都被完全填充，最底层的结点都尽量靠左。最底层（第h层）结点数在1-2h之间。

**Tags** `Tree` `Binary Search`

##解题思路
遍历肯定可以得到结果，但是这样的方法肯定会超时（实际上就是这样子）。Tags中有`Binary Search`，我们来看一个完全二叉树的例子：

                      1
                   /    \
                  2      3
                /   \   / \
               4     5 6   7
              / \   / \
             8   9 10 11

这个例子中树非常不好计算结点，如果一棵二叉树是**狭义的完全二叉树**的话就好了，这里狭义是指每一个结点要么有两个孩子，要么没有孩子。如：

                      1
                   /    \
                  2      3
                /   \   / \
               4     5 6   7

对于这样的二叉树，其结点数是非常好计算的：1+2+4，即2^0 + 2^1 + 2^2 = 2^3 - 1 =7;其复杂度为O(logn)。

那我们一开始那棵树是不是可以拆分成这样结构的子树呢？答案是可以的，我们可以拆成如下结构：

         1        2           3
                /   \        / \
               4     5      6   7
              / \   / \
             8   9 10 11
                  
对如上三部分分别求结点数，2^1-1=1; 2^3-1=7; 2^2-1=3; 然后求和1+7+3=11。

那么问题来了，该如何对二叉树进行拆分呢？首先，我们来找一种方法确定一棵普通完全二叉树是否是狭义上完全的二叉树，有一个比较直观的方法就是**看从根结点到最左下角和最右下角子结点的路径长度，如果二者相等，则此完全二叉树就是一个狭义的完全二叉树**；如果不是的话，我们就把根结点拆出来，然后递归求左右子树的结点个数。

这样做的复杂度如何呢？如下为最差情况


                        1
                   /        \
                  2           3
                /   \       /   \
               4     5     6     7
              / \   / \   / \   / \
             8   9 10 11 12 13 14 15
            /
           16
    （1）第一次求解：不符合条件，需拆分，拆分后为：
        1         2              3
                /   \          /   \
               4     5        6     7
              / \   / \      / \   / \
             8   9 10 11    12 13 14 15
            /
           16  
    （2）第二次求解，上面的三棵树中，第一和第三已经符合条件，直接公式计算出结果。
       第二棵树不符合条件，继续拆分：拆分后为：
        2          4        5   
                  / \      / \    
                 8   9    10 11   
                /
               16  
    （3）第三次求解，上面的三棵树中，第一和第三已经符合条件，直接公式计算出结果。
       第二棵树不符合条件，继续拆分：拆分后为：
       4         8        9  
                /
               16  
    （4）第四次求解，上面的三棵树中，第一和第三已经符合条件，直接公式计算出结果。
       第二棵树不符合条件，继续拆分：拆分后为：
       8        16
    （5）第五次求解，所有树都符合条件，计算出结果。

可以看出，递归只会延某一条路径进行，不会出现多个求解分支均进行递归的情况。**对于一个结点的左右子树，两者至多有一个不是狭义上的完全二叉树**。因此这个递归至多进行logn次。

在每次递归时，需要计算到最左下角和最右下角结点的路径长度，复杂度为logn，所以总体来说复杂度为O((logn)^2)？**如有错误，欢迎指正**。

##代码

```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countNodes(struct TreeNode* root) {
    int leftestLen(struct TreeNode*);
    int rightestLen(struct TreeNode*);

    if (root == NULL) return 0;
    int leftLen = leftestLen(root);
    int rightLen = rightestLen(root);
    if (leftLen == rightLen) {
        int i, counts = 1;
        for (i = 0; i < leftLen; ++i)
            counts *= 2;
        return counts - 1;
    }
    else
        return 1 + countNodes(root->left) + countNodes(root->right);
}

int leftestLen(struct TreeNode* root) {
    int len = 0;
    while (root) {
        ++len;
        root = root->left;
    }
    return len;
}

int rightestLen(struct TreeNode* root) {
    int len = 0;
    while (root) {
        ++len;
        root = root->right;
    }
    return len;
}
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/222/c/main.c](https://github.com/Orange1991/leetcode/blob/master/222/c/main.c)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/48031967

---
2015/8/27

