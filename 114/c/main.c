#include <stdio.h>
#include <stdlib.h>

/**
 * 二叉树结点的定义.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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
    struct TreeNode n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16, n17, n18;
    n1.val = -6; n1.left = &n2; n1.right = &n3;
    n2.val = 8; n2.left = &n4; n2.right = &n5;
    n3.val = -4; n3.left = &n6; n3.right = NULL;
    n4.val = 8; n4.left = &n7; n4.right = &n8;
    n5.val = -5; n5.left = &n9; n5.right = &n10;
    n6.val = -1; n6.left = NULL; n6.right = NULL;
    n7.val = -9; n7.left = &n11; n7.right = &n12;
	n8.val = 9; n8.left = NULL; n8.right = NULL;
	n9.val = 8; n9.left = NULL; n9.right = &n13;
	n10.val = 8; n10.left = NULL; n10.right = &n14;
    n11.val = -5; n11.left = NULL; n11.right = NULL;
    n12.val = 6; n12.left = &n15; n12.right = &n16;
    n13.val = -4; n13.left = NULL; n13.right = NULL;
    n14.val = 4; n14.left = NULL; n14.right = &n17;
    n15.val = 8; n15.left = NULL; n15.right = NULL;
    n16.val = 8; n16.left = NULL; n16.right = NULL;
    n17.val = 5; n17.left = NULL; n17.right = &n18;
    n18.val = -9; n18.left = NULL; n18.right = NULL;

    flatten(&n1);
    
    struct TreeNode* p = &n1;
    while (p != NULL) {
    	printf("%d->", p->val);
        p = p->right;
    }

	return 0;
}
