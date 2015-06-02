#include <iostream>
#include <vector>

using namespace std;

/** 二叉树节点的定义 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /**
     * 根据前序遍历和中序遍历序列构造二叉树
     * 序列中不存在重复元素
     * input preorder : 前序遍历序列
     * input inorder  : 中序遍历序列
     * return         : 构造好的二叉树
     */
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        /* 如果序列为空，返回空节点 */
        if (preorder.size() == 0)
            return NULL;
        return buildTree(preorder, 0, preorder.size(), inorder, 0, inorder.size());
    }

private:
    /**
     * 根据前序遍历和中序遍历的子序列构造二叉树
     * 序列中不存在重复元素
     * input preorder : 前序遍历序列
     * input preStart : 前序子序列开始位置
     * input preEnd   : 前序子序列结束位置的下一个位置
     * input inorder  : 中序遍历序列
     * input inStart  : 中序子序列开始位置
     * input inEnd    : 中序子序列结束位置的下一个位置
     * return         : 构造好的二叉树
     */
    TreeNode* buildTree(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd) {
        /* 如果前序子序列为空，返回空节点 */
	if (preStart >= preEnd) return NULL;

	/* 构造根节点 
	 * 前序子序列的第一个值即为根节点的值 */
	TreeNode *root = new TreeNode(preorder[preStart]);	// 存储根节点的值
	
        /* 在中序子序列中查找根节点
	 * 其左侧的序列即为其左子树中序遍历的序列
	 * 同时在前序子序列中相应长度的子序列即为左子树前序遍历的序列
	 * 其右侧的序列即为其右子树中序遍历的序列
	 * 同时在前序子序列中相应长度的子序列即为右子树前序遍历的序列
         */
        int startTmp = inStart, endTmp = inStart;
        while (endTmp < inEnd && inorder[endTmp] != root->val) ++endTmp;

	root->left = buildTree(preorder, preStart + 1, preStart + endTmp - startTmp + 1, 
                inorder, startTmp, endTmp);	// 构造左子树
        root->right = buildTree(preorder, preStart + endTmp - startTmp + 1, preEnd,
                inorder, endTmp + 1, inEnd); // 构造右子树

        return root;

	}

};

/** 前序遍历 */
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    cout << root->val << ", ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

/** 中序遍历 */
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    cout << root->val << ", ";
    inorderTraversal(root->right);
}

int main() {
    Solution s;    
    int i, n = 6;
    vector<int> pre, in;
    pre.push_back(1);
    pre.push_back(2);
    pre.push_back(3);
    pre.push_back(4);
    pre.push_back(5);
    pre.push_back(6);
    in.push_back(3);
    in.push_back(2);
    in.push_back(1);
    in.push_back(4);
    in.push_back(6);
    in.push_back(5);
    cout << "Original Preorder : ";
    for (i = 0; i < n; ++i)
        cout << pre[i] << ", ";
    cout << endl << "Original Inorder : ";
    for (i = 0; i < n; ++i)
        cout << in[i] << ", ";

    struct TreeNode* tree = s.buildTree(pre, in);
    cout << endl << "Rebuild Tree Preorder : ";
    preorderTraversal(tree);
    cout << endl << "Rebuild Tree Inorder : ";
    inorderTraversal(tree);
    cout << endl;

    return 0;
}
