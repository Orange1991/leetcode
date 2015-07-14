#include <iostream>
#include "../../libs/binary_tree.h"

using namespace std;

class Solution {
public:
    /**
     * 计算二叉树的最大路径和
     * @param : root 二叉树根结点
     * @return : 最大路径和
     */
    int maxPathSum(TreeNode *root) {
        if (root == NULL) return 0;
        int tmpMax = root->val;
    
        maxChildPathSum(root, &tmpMax);
        return tmpMax;
    }

private:
    /**
     * 计算二叉树子树的最大路径和以及整棵二叉树的最大路径和
     * 子树路径必须以根结点开始，以树中某一结点结束
     * 二叉树的最大路径和的路径，不必以根结点为开始结点
     * @param : root 二叉树根结点
     * @param : tmpMax 暂存整棵二叉树的最路径和的变量的地址
     * @return : 子树的最大路径和
     */  
    int maxChildPathSum(TreeNode *root, int *tmpMax) {
        if (root == NULL) return 0;

        /* 计算左右子树的最大路径和 */
        int leftMax = maxChildPathSum(root->left, tmpMax);
        int rightMax = maxChildPathSum(root->right, tmpMax);

        /* 尝试更新整棵二叉树的最大路径和 */    
        int tmp = root->val;
        if (leftMax > 0) tmp += leftMax;
        if (rightMax > 0) tmp += rightMax;
        if (tmp > *tmpMax) *tmpMax = tmp;

        /* 计算并返回子树的最大路径和 */
        int maxRoot = max(root->val, max(root->val + leftMax, root->val + rightMax));
        return maxRoot;
    }

    /* 求两个数中较大的数字 */
    int max(int arg1, int arg2) { return arg1 > arg2 ? arg1 : arg2; }
};

int main() {
    char *data = "[1,-2,3]";
    TreeNode *root = genBinaryTree(data);
    Solution s;
    cout << "The max path sum is " << s.maxPathSum(root) << endl;
    freeBinaryTree(root);
    return 0;
}
