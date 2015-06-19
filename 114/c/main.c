#include <stdio.h>
#include <stdlib.h>
#include "../../libs/binary_tree.h"

/**
 * 递归扁平化处理二叉树
 * input last : 一个固定内存，用于存储上一个访问的结点的地址
 * input root : 当前要处理的二叉树的根结点
 */
void flattenRecursive(struct TreeNode** last, struct TreeNode* root) {
    if (root == NULL) return;
    (*last)->right = root; // 将root挂在*last存储的地址指向的右结点上
    (*last)->left = NULL;  // 将*last所存储的地址指向的左结点置空
    *last = root;    // 更新最后一个结点信息，last存储当前结点的地址

    // 暂存一下root的左右结点的地址，因为在递归调用中root的左右结点的值会被更改
    struct TreeNode* left = root->left, * right = root->right;
    // 递归，扁平化处理左子树
    flattenRecursive(last, left);
    // 递归，扁平化处理右子树
    flattenRecursive(last, right);
}

/**
 * 扁平化处理二叉树
 */
void flatten(struct TreeNode* root) {    
    if (root == NULL) return; // 空树直接返回
    // 一个固定内存，用于存储上一个访问的结点的地址
    struct TreeNode** last = (struct TreeNode**)malloc(sizeof(struct TreeNode*));
    struct TreeNode tmp;
    *last = &tmp;
    // 递归扁平化处理
    flattenRecursive(last, root);
    // 释放内存
    free(last);
}

int main() {
    char *str = "[-6,8,-4,8,-5,-1,null,-9,9,8,8,null,null,-5,6,null,null,null,-4,null,4,null,null,8,8,null,null,null,5,null,null,null,null,null,-9]";
    struct TreeNode *tree = genBinaryTree(str);

    flatten(tree);
    
    struct TreeNode* p = tree;
    while (p != NULL) {
    	printf("%d->", p->val);
        p = p->right;
    }
    printf("null\n");

    freeBinaryTree(tree);

    return 0;
}
