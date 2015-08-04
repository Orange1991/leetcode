#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BSTIterator {
public:
    stack<TreeNode *> mins;
    /** 初始化迭代器 */
    BSTIterator(TreeNode *root) {
        while (root != NULL) { // 添加元素
            mins.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !mins.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *tmp = mins.top(); // 获取并弹出最小元素
        mins.pop();
        int ret = tmp->val;
        tmp = tmp->right;
        // 添加元素被弹出结点的右子树上的较小元素
        while (tmp != NULL) { 
            mins.push(tmp);
            tmp = tmp->left;
        }
        return ret; // 返回最小元素
    }
};

class BSTConstructor {
public:
    /**
     * 根据有序（递增）序列生成平衡二叉查找树
     * @param nums : 递增序列
     */
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedSeqToBST(nums, 0, nums.size() - 1);
    }
    /**
     * 内存回收
     */
    void free(TreeNode* root) {
        if (root == NULL) return;
        free(root->left);
        free(root->right);
        delete(root);
    }
private:
    /**
     * 根据有序（递增）序列的某一子序列生成平衡二叉查找树
     * @param nums  : 递增序列
     * @param start : 子序列开始位置（包含）
     * @param end   : 子序列结束位置（包含）
     */
    TreeNode* sortedSeqToBST(vector<int>& nums, int start, int end) {
        /* 如果开始位置大于结束位置，返回NULL */
        if (start > end) return NULL;

        /* 计算中间位置的点
         * 这样可以保证左右子树的点的个数的差不大于1
         * 以满足题目构造平衡二叉树的要求 */
        int center = (start + end) / 2;

        /* 创建根节点 */
        /* 保存根节点的值 */
        TreeNode* node = new TreeNode(nums[center]);

        /* 分别使用中间点以左和以右的子序列构造左右子树 */
        node->left = sortedSeqToBST(nums, start, center - 1);
        node->right = sortedSeqToBST(nums, center + 1, end);

        return node;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */
int main() {
    vector<int> nums;
    for (int i = 0; i < 10; ++i) nums.push_back(i);
    BSTConstructor constructor;
    TreeNode *root = constructor.sortedArrayToBST(nums);
    BSTIterator i = BSTIterator(root);
    while (i.hasNext()) cout << i.next() << endl;
    constructor.free(root);
    return 0;
}
