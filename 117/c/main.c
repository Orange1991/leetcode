#include <stdio.h>

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left, *right, *next;
};

void connect(struct TreeLinkNode *root) {
    int height(struct TreeLinkNode *);
    struct TreeLinkNode* findLeftestNode(struct TreeLinkNode *, int);
    struct TreeLinkNode* findRightestNode(struct TreeLinkNode *, int);

    if (root == NULL) return;
    int heightLeft = height(root->left);
    int heightRight = height(root->right);
    int i = 1, end = heightLeft < heightRight ? heightLeft : heightRight;
    struct TreeLinkNode *left, *right;
    while (i++ <= end) {
        left = findRightestNode(root->left, i);
        right = findLeftestNode(root->right, i);
        left->next = right;
    }

    connect(root->left);
    connect(root->right);
}

/**
 * 获取二叉树高度
 */
int height(struct TreeLinkNode *root) {
    int bigger(int, int);
    if (root == NULL) return 0;
    return bigger(height(root->left), height(root->right)) + 1;
}

/** 获取两者中的较大数 */
int bigger(int param1, int param2) { return param1 > param2 ? param1 : param2; }

/**
 * 寻找root下某一层最左侧的结点
 */
struct TreeLinkNode* findLeftestNode(struct TreeLinkNode *root, int level) {
    int height(struct TreeLinkNode *);
    if (level == 1) return root;
    if (height(root->left) >= level - 1)
        return findLeftestNode(root->left, level - 1);
    else
        return findLeftestNode(root->right, level - 1);
}

/**
 * 寻找root下某一层最右侧的结点
 */
struct TreeLinkNode* findRightestNode(struct TreeLinkNode *root, int level) {
    int height(struct TreeLinkNode *);
    if (level == 1) return root;
    if (height(root->right) >= level - 1)
        return findRightestNode(root->right, level - 1);
    else
        return findRightestNode(root->left, level - 1);
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
