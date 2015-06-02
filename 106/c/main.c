#include <stdio.h>
#include <stdlib.h>

/* 二叉树节点定义 */
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

/**
 * 根据中序遍历和后序遍历序列构造二叉树
 * 序列中不存在重复元素
 * input ineorder     : 中序遍历序列
 * input ineorderSize : 中序子序列长度
 * input postorder    : 后序遍历序列
 * input postorderSize: 后序子序列长度
 * return             : 构造好的二叉树
 */
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    struct TreeNode* buildChildTree(int*, int, int, int*, int, int);

    /* 如果序列为空，返回空节点 */
    if (inorderSize == 0)
	return NULL;

    return buildChildTree(inorder, -1, inorderSize - 1, postorder, -1, postorderSize - 1);
}

/**
 * 根据中序遍历和后序遍历的子序列构造子二叉树
 * 序列中不存在重复元素
 * input preorder : 中序遍历序列
 * input preStart : 中序子序列开始位置的上一个位置
 * input preEnd   : 中序子序列结束位置
 * input inorder  : 后序遍历序列
 * input inStart  : 后序子序列开始位置的上一个位置
 * input inEnd    : 后序子序列结束位置
 * return         : 构造好的二叉树
 */
struct TreeNode* buildChildTree(int* inorder, int inStart, int inEnd, int* postorder, int postStart, int postEnd) {	

    /* 如果前序子序列为空，返回空节点 */
    if (inStart >= inEnd)
        return NULL;

    /* 构造根节点 
     * 后序子序列的最后一个值即为根节点的值 */
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = *(postorder + postEnd);	// 存储根节点的值
    /* 在中序子序列中查找根节点
     * 其右侧的序列即为其右子树中序遍历的序列
     * 同时在后序子序列中相应长度的子序列即为右子树后序遍历的序列
     * 其左侧的序列即为其左子树中序遍历的序列
     * 同时在前序子序列中相应长度的子序列即为左子树前序遍历的序列
     */
    int startTmp = inEnd, endTmp = inEnd;
    while (startTmp > inStart && *(inorder + startTmp) != root->val)
        --startTmp;
    //return root;
    root->right = buildChildTree(inorder, startTmp, endTmp, 
            postorder, postEnd - endTmp + startTmp - 1, postEnd - 1);	// 构造右子树
    root->left = buildChildTree(inorder, inStart, startTmp - 1,
            postorder, postStart, postEnd - endTmp + startTmp - 1); 	// 构造左子树

    return root;
}

/** 后序遍历 */
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d, ", root->val);
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
    int* post = (int*)malloc(sizeof(int) * n);
    int* in = (int*)malloc(sizeof(int) * n);
    *post = 3; *(post + 1) = 2; *(post + 2) = 6; *(post + 3) = 5; *(post + 4) = 4; *(post + 5) = 1;
    *in = 3; *(in + 1) = 2; *(in + 2) = 1; *(in + 3) = 4; *(in + 4) = 6; *(in + 5) = 5;
    printf("Original Postorder : ");
    for (i = 0; i < n; ++i)
        printf("%d, ", *(post + i));
    printf("\nOriginal Inorder : ");
    for (i = 0; i < n; ++i)
        printf("%d, ", *(in + i));

    struct TreeNode* tree = buildTree(in, n, post, n);
    printf("\nRebuild Tree Postorder : ");
    postorderTraversal(tree);
    printf("\nRebuild Tree Inorder : ");
    inorderTraversal(tree);
    printf("\n");

    return 0;
}
