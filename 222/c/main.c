#include <stdio.h>
#include "../../libs/binary_tree.h"

int countNodes(struct TreeNode* root) {
    int leftestLen(struct TreeNode*);
    int rightestLen(struct TreeNode*);

    if (root == NULL) return 0;
    int leftLen = leftestLen(root);
    int rightLen = rightestLen(root);
    if (leftLen == rightLen) {
        int counts = 1, i;
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

int main() {
    struct TreeNode* tree = genBinaryTree("[1,2,3,4,5,6,7,8,9,10,11,12]");
    printf("%d\n", countNodes(tree));
    freeBinaryTree(tree);
}
