#include <stdio.h>

/**
 * 二叉树结点的定义.
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void flattenRecursive(struct TreeNode* last, struct TreeNode* root) {
    if (last == NULL) { 
        last = root;
	} else {
	    last->right = root;
        last = root;
    }

    if (root->left != NULL) flattenRecursive(last, root->left);
	if (root->right != NULL) flattenRecursive(last, root->right);
}

void flatten(struct TreeNode* root) {    
    if (root == NULL) return;
	struct TreeNode* last = NULL;
    flattenRecursive(last, root);
}

int main() {
    struct TreeNode n1, n2, n3, n4, n5, n6;
    n1.val = 1; n1.left = &n2; n1.right = &n3;
    n2.val = 2; n2.left = &n4; n2.right = &n5;
    n3.val = 5; n3.left = NULL; n3.right = &n6;
    n4.val = 3; n4.left = NULL; n4.right = NULL;
    n5.val = 4; n5.left = NULL; n5.right = NULL;
    n6.val = 6; n6.left = NULL; n6.right = NULL;

    flatten(&n1);
    
    struct TreeNode* p = &n1;
    while (p != NULL) {
    	printf("%d->", p->val);
		p = p->right;
    }

	return 0;
}
