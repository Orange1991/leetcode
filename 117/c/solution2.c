#include <stdio.h>

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left, *right, *next;
};

/**
 * 填充二叉树的next指针
 */
void connect(struct TreeLinkNode *root) {
    if (root == NULL) return;

    struct TreeLinkNode *begin = NULL, *p = root, *pre, *next;
    
    while (p != NULL) {
        if (p->left != NULL) {
            begin = p->left;
            break;
        }
        else if (p->right != NULL) {
            begin = p->right;
            break;
        }
        else p = p->next;
    }

    if (begin == NULL) return;

    pre = begin;    
    if (begin == p->left) {
        if (p->right != NULL) {
            next = p->right;
            pre->next = next;
            pre = next;
            p = p->next;
        } 
        else p = p->next;
    }
    else p = p->next;

    while ( p != NULL) {
        if(p->left != NULL) {
            next = p->left;
            pre->next = next;
            pre = next;
        } 
        if (p->right != NULL) {
            next = p->right;
            pre->next = next;
            pre = next;
        }
        p = p->next;
    }

    connect(begin);
}

void print(struct TreeLinkNode *root) {
    if (root == NULL) return;
    if (root->next == NULL) printf("%d->null\n", root->val);
    else printf("%d->%d\n", root->val, root->next->val);

    print(root->left);
    print(root->right);
}

int main() {
    struct TreeLinkNode n1, n2, n3, n4, n5, n7;
    n1.val = 1; n1.left = &n2; n1.right = &n3; n1.next = NULL;
    n2.val = 2; n2.left = &n4; n2.right = &n5; n2.next = NULL;
    n3.val = 3; n3.left = NULL; n3.right = &n7; n3.next = NULL;
    n4.val = 4; n4.left = NULL; n4.right = NULL; n4.next = NULL;
    n5.val = 5; n5.left = NULL; n5.right = NULL; n5.next = NULL;
    n7.val = 7; n7.left = NULL; n7.right = NULL; n7.next = NULL;

    connect(&n1);

    print(&n1);
}
