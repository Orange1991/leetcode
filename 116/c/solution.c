#include <stdio.h>

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left, *right, *next;
};

void connect(struct TreeLinkNode *root) {
    if (root == NULL) return;
    struct TreeLinkNode *left = root->left, *right = root->right;
    while (left != NULL) {
        left->next = right;
        left = left->right;
        right = right->left;
    }

    connect(root->left);
    connect(root->right);
}

void print(struct TreeLinkNode *root) {
    if (root == NULL) return;
    if (root->next == NULL) printf("%d->null\n", root->val);
    else printf("%d->%d\n", root->val, root->next->val);

    print(root->left);
    print(root->right);
}

int main() {
    struct TreeLinkNode n1, n2, n3, n4, n5, n6, n7;
    n1.val = 1; n1.left = &n2; n1.right = &n3; n1.next = NULL;
    n2.val = 2; n2.left = &n4; n2.right = &n5; n2.next = NULL;
    n3.val = 3; n3.left = &n6; n3.right = &n7; n3.next = NULL;
    n4.val = 4; n4.left = NULL; n4.right = NULL; n4.next = NULL;
    n5.val = 5; n5.left = NULL; n5.right = NULL; n5.next = NULL;
    n6.val = 6; n6.left = NULL; n6.right = NULL; n6.next = NULL;
    n7.val = 7; n7.left = NULL; n7.right = NULL; n7.next = NULL;

    connect(&n1);

    print(&n1);
}
