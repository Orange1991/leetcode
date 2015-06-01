#include <stdlib.h>

/* 二叉树节点定义 */
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

/**
 * 根据前序遍历和中序遍历序列构造二叉树
 * 序列中不存在重复元素
 * input preorder     : 前序遍历序列
 * input preorderSize : 前序子序列长度
 * input inorder      : 中序遍历序列
 * input inorderSize  : 中序子序列长度
 * return             : 构造好的二叉树
 */
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    struct TreeNode* buildChildTree(int*, int, int, int*, int, int);

    /* 如果序列为空，返回空节点 */
    if (preorderSize == 0)
	return NULL;

    return buildChildTree(preorder, 0, preorderSize, inorder, 0, inorderSize);
}

/**
 * 根据前序遍历和中序遍历的子序列构造子二叉树
 * 序列中不存在重复元素
 * input preorder : 前序遍历序列
 * input preStart : 前序子序列开始位置
 * input preEnd   : 前序子序列结束位置的下一个位置
 * input inorder  : 中序遍历序列
 * input inStart  : 中序子序列开始位置
 * input inEnd    : 中序子序列结束位置的下一个位置
 * return         : 构造好的二叉树
 */
struct TreeNode* buildChildTree(int* preorder, int preStart, int preEnd, int* inorder, int inStart, int inEnd) {	

    /* 如果前序子序列为空，返回空节点 */
    if (preStart >= preEnd)
        return NULL;

    /* 构造根节点 
     * 前序子序列的第一个值即为根节点的值 */
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));	
    root->val = *(preorder + preStart);	// 存储根节点的值
    /* 在中序子序列中查找根节点
     * 其左侧的序列即为其左子树中序遍历的序列
     * 同时在前序子序列中相应长度的子序列即为左子树前序遍历的序列
     * 其右侧的序列即为其右子树中序遍历的序列
     * 同时在前序子序列中相应长度的子序列即为右子树前序遍历的序列
     */
    int startTmp = inStart, endTmp = inStart;
    while (endTmp < inEnd && *(inorder + endTmp) != root->val)
        ++endTmp;
    root->left = buildChildTree(preorder, preStart + 1, preStart + endTmp - startTmp + 1, 
            inorder, startTmp, endTmp);	// 构造左子树
    root->right = buildChildTree(preorder, preStart + endTmp - startTmp + 1, preEnd,
            inorder, endTmp + 1, inEnd); // 构造右子树

    return root;
}

/** 前序遍历 */
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%d, ", root->val);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

/** 中序遍历 */
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%d, ", root->val);
    inorderTraversal(root->right);
}

int main() {
    int n = 6, i;
    int* pre = (int*)malloc(sizeof(int) * n);
    int* in = (int*)malloc(sizeof(int) * n);
    *pre = 1; *(pre + 1) = 2; *(pre + 2) = 3; *(pre + 3) = 4; *(pre + 4) = 5; *(pre + 5) = 6;
    *in = 3; *(in + 1) = 2; *(in + 2) = 1; *(in + 3) = 4; *(in + 4) = 6; *(in + 5) = 5;
    printf("Original Preorder : ");
    for (i = 0; i < n; ++i)
        printf("%d, ", *(pre + i));
    printf("\nOriginal Inorder : ");
    for (i = 0; i < n; ++i)
        printf("%d, ", *(in + i));

    struct TreeNode* tree = buildTree(pre, n, in, n);
    printf("\nRebuild Tree Preorder : ");
    preorderTraversal(tree);
    printf("\nRebuild Tree Inorder : ");
    inorderTraversal(tree);
    printf("\n");

    return 0;
}
