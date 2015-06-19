#include <stdio.h>
#include "../../libs/binary_tree.h"

/**
 * 扁平化处理二叉树
 */
void flatten(struct TreeNode* root) {    
    struct TreeNode* p;
    while (root != NULL) { // root不为空，则继续调整
        if (root->left) {  // 如果当前结点有左子树才调整
            p = root->left;// 指向左结点
            while (p->right) p = p->right; // 指向最右下角的结点
            p->right = root->right; // 把当前结点的右子树挂在左子树的最右下角结点上
            root->right = root->left; // 当前结点的左子树挂在右结点上
            root->left = NULL; // 当前结点的左子树置空
        } // 调整结束后，当前结点左结点为空，右结点不一定
        root = root->right; // 指向当前结点的右结点，继续调整
    }
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
