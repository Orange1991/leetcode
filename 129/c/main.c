#include <stdio.h>
#include "../../libs/binary_tree.h"

int sumNumbers(struct TreeNode *root) {
    void sumRootToLeaf(struct TreeNode *, int, int *);   
    int sum = 0, val = 0;
    sumRootToLeaf(root, val, &sum);
    return sum;
}

void sumRootToLeaf(struct TreeNode *root, int val, int *sum) {
    if (root == NULL) return;

    val *= 10;
    val += root->val;

    if (root->left == NULL && root->right == NULL) {
        *sum += val;
        return;
    }

    sumRootToLeaf(root->left, val, sum);
    sumRootToLeaf(root->right, val, sum);
}

int main() {
    char *str = "[1,2,3]";
    struct TreeNode *tree = genBinaryTree(str);
    printf("%d\n", sumNumbers(tree));
    freeBinaryTree(tree);
    return 0;
}
