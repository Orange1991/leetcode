#include <stdio.h>
#include "../../libs/binary_tree.h"

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    int v, w;
    if (p->val < q->val) {
        v = p->val;
        w = q->val;
    } else {
        v = q->val;
        w = p->val;
    }
    while (root) {
        if (w < root->val)
            root = root->left;
        else if (v > root->val)
            root = root->right;
        else return root;
    }
    return root;
}

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

void test(struct TreeNode* root) {
    printf("1, 7 : %d\n", lowestCommonAncestor(root, root->left, root->right)->val);
    printf("4, 7 : %d\n", lowestCommonAncestor(root, root, root->right)->val);
    printf("1, 4 : %d\n", lowestCommonAncestor(root, root->left, root)->val);
    printf("0, 9 : %d\n", lowestCommonAncestor(root, root->left->left, root->right->right->right)->val);
    printf("0, 3 : %d\n", lowestCommonAncestor(root, root->left->left, root->left->right->right)->val);
    printf("2, 3 : %d\n", lowestCommonAncestor(root, root->left->right, root->left->right->right)->val);
    printf("5, 5 : %d\n", lowestCommonAncestor(root, root->right->left, root->right->left)->val);
}

int main() {
    int* nums = (int*)malloc(sizeof(int) * 10);
    int i;
    for (i = 0; i < 10; ++i) *(nums + i) = i;
    struct TreeNode* tree = sortedArrayToBST(nums, 10);
    test(tree);
    return 0; 
}
