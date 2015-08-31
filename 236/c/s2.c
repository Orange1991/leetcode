#include <stdio.h>
#include <stdbool.h>
#include "../../libs/binary_tree.h"

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if (root == NULL || root == p || root == q) return root;
    struct TreeNode* l = lowestCommonAncestor(root->left, p, q);
    struct TreeNode* r = lowestCommonAncestor(root->right, p, q);
    if (l && r) return root;
    return l ? l : r;
}

int main() {
    struct TreeNode* tree = genBinaryTree("[3,5,1,6,2,0,8,null,null,7,4]");
    printf("5, 1 : %d\n", lowestCommonAncestor(tree, tree->left, tree->right)->val);
    printf("5, 4 : %d\n", lowestCommonAncestor(tree, tree->left, tree->left->right->right)->val);
    freeBinaryTree(tree);
    tree = genBinaryTree("1,2,3");
    printf("2, 3 : %d\n", lowestCommonAncestor(tree, tree->right, tree->left)->val);
    freeBinaryTree(tree);
    return 0; 
}
