#include <stdio.h>

/**
 * 二叉树结点的定义.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

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
