#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** 链表节点的定义 */
struct ListNode {
    int val;
    struct ListNode *next;
};

/** 二叉树节点的定义  */
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

/**
 * 根据有序（递增）链表构造平衡二叉查找树
 * input head : 链表首节点
 * return     : 平衡二叉查找树
 */
struct TreeNode* sortedListToBST(struct ListNode* head) {
    struct TreeNode* sortedListSeqToBST(struct ListNode*, int);
    if (head == NULL) return NULL;

    /* 统计链表节点个数 */
    int count = 0;
    struct ListNode* p = head;
    while (p) {
        ++count;
        p = p->next;
    }

    return sortedListSeqToBST(head, count);
}

/**
 * 根据有序（递增）链表片段构造平衡二叉树
 * input head  : 链表起始节点
 * input count : 链表片段节点的个数
 * return      : 平衡二叉查找树
 */
struct TreeNode* sortedListSeqToBST(struct ListNode* head, int count) {
    /* 如果链表片段中没有节点，直接返回NULL */
    if (count <= 0) return NULL;

    /* 找到当前要作为TreeNode根节点的值的ListNode */
    int center = count / 2, i = 0;
    struct ListNode* p = head;
    while (i++ < center) p = p->next; // p最终指向的节点的值作为根节点的值

    /* 创建根节点 */
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = p->val; // 记录根节点的值

    /* 利用p之前的节点，构造左子树 */
    node->left = sortedListSeqToBST(head, count & 1 ? count - center - 1 : count - center);
   
     /* 利用p之后的节点，构造右子树 */
    node->right = sortedListSeqToBST(p->next, count - center - 1);

    return node;
}

/** 中序遍历二叉树 */
bool inorderTraversal(struct TreeNode* root, bool* isFirst, int* last) {
    if (root == NULL) return true;
    if (!inorderTraversal(root->left, isFirst, last)) return false;
    printf("%d->", root->val);
    if (*isFirst) {
        *isFirst = false;
        *last = root->val;
    } else {
        if (*last >= root->val) return false;
        *last = root->val;
    }
    if (!inorderTraversal(root->right, isFirst, last)) return false;
    return true;
}

/** 计算二叉树高度 */
int getHeight(struct TreeNode* root) {
    if (root == NULL) return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

/** 判断是否为平衡二叉树 */
bool isHeightBalanceTree(struct TreeNode* root) {
    if (root == NULL) return true;
    if (isHeightBalanceTree(root->left) && isHeightBalanceTree(root->right)) {
        int leftHeight = getHeight(root->left);
        int rightHeight = getHeight(root->right);
        if (leftHeight - rightHeight <= 1 && rightHeight - leftHeight <= 1)
            return true;
        else
            return false;
    }
    else
        return false;
}


int main() {
    struct ListNode head, *p = &head;
    head.val = 0;
    int i = 0;
    while (i++ < 10) {
        struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
        tmp->val = i;
        p->next = tmp;
        p = tmp;
    }

    struct TreeNode* tree = sortedListToBST(&head);
    if (tree == NULL) printf("fuck you");
    // 验证是否为二叉查找树
    // 中序遍历结果递增
    int last;
    bool isFirst = true;
    if (inorderTraversal(tree, &isFirst, &last))
        printf("是二叉查找树");
    else
        printf("不是二叉查找树");
    // 验证是否是平衡二叉树
    if (isHeightBalanceTree(tree))
        printf("\n是平衡二叉树\n");
    else 
        printf("\n不是平衡二叉树\n");

    return 0;
}
