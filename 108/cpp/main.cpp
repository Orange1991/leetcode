#include <iostream>
#include <vector>

using namespace std;

/**
 * 二叉树节点的定义
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /**
     * 根据有序（递增）序列生成平衡二叉查找树
     * input nums : 递增序列
     */
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedSeqToBST(nums, 0, nums.size() - 1);
    }

private:
    /**
     * 根据有序（递增）序列的某一子序列生成平衡二叉查找树
     * input nums  : 递增序列
     * input start : 子序列开始位置（包含）
     * input end   : 子序列结束位置（包含）
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
 * 中序遍历二叉树
 */
bool inorderTraversal(TreeNode* root, bool* isFirst, int* last) {
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

int getHeight(TreeNode* root) {
    if (root == NULL) return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

bool isHeightBalanceTree(TreeNode* root) {
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
    int n = 10, i;
    vector<int> nums(n);
    for (i = 0; i < n; ++i) nums[i] = i;
    Solution s;
    TreeNode* tree = s.sortedArrayToBST(nums);
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
}
