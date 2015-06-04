#include <iostream>

using namespace std;

/** 链表节点的定义 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/** 二叉树节点的定义  */
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /**
     * 根据有序（递增）链表构造平衡二叉查找树
     * input head : 链表首节点
     * return     : 平衡二叉查找树
     */
    struct TreeNode* sortedListToBST(struct ListNode* head) {
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

private:
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
        TreeNode* node = new TreeNode(p->val); // 记录根节点的值

        /* 利用p之前的节点，构造左子树 */
        node->left = sortedListSeqToBST(head, count & 1 ? count - center - 1 : count - center);
   
        /* 利用p之后的节点，构造右子树 */
        node->right = sortedListSeqToBST(p->next, count - center - 1);

        return node;
     }
};

/** 中序遍历二叉树 */
bool inorderTraversal(struct TreeNode* root, bool* isFirst, int* last) {
    if (root == NULL) return true;
    if (!inorderTraversal(root->left, isFirst, last)) return false;
    cout << root->val << "->";
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
    ListNode head(0), *p = &head;
    int i = 0;
    while (i++ < 10) {
        ListNode* tmp = new ListNode(i);
        p->next = tmp;
        p = tmp;
    }

    Solution s;
    struct TreeNode* tree = s.sortedListToBST(&head);
    
    // 验证是否为二叉查找树
    // 中序遍历结果递增
    int last;
    bool isFirst = true;
    if (inorderTraversal(tree, &isFirst, &last))
        cout << "是二叉查找树";
    else
        cout << "不是二叉查找树";
    // 验证是否是平衡二叉树
    if (isHeightBalanceTree(tree))
        cout << endl << "是平衡二叉树" << endl;
    else 
        cout << endl << "不是平衡二叉树" << endl;

    return 0;
}
