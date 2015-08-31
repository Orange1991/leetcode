#include <stdio.h>
#include <stdbool.h>
#include "../../libs/binary_tree.h"

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    bool isDecendentOf(struct TreeNode*, struct TreeNode*);
    if (root == p || root == q) return root;
    bool inLeft = isDecendentOf(p, root->left), inRight = isDecendentOf(q, root->right);
    if (!(inLeft ^ inRight)) return root;
    else if (inLeft) return lowestCommonAncestor(root->left, p, q);
    else return lowestCommonAncestor(root->right, p, q);
}

bool isDecendentOf(struct TreeNode* p, struct TreeNode* root) {
    if (root == NULL) return false;
    if (root == p) return true;
    return isDecendentOf(p, root->left) || isDecendentOf(p, root->right);
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
