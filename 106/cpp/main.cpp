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
     * 根据中序遍历和后序遍历序列构造二叉树
     * 序列中不存在重复元素
     * input ineorder     : 中序遍历序列
     * input postorder    : 后序遍历序列
     * return             : 构造好的二叉树
     */
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        /* 如果序列为空，返回空节点 */
        if (inorder.size() == 0)
            return NULL;
        return buildTree(inorder, -1, inorder.size() - 1, postorder, -1, postorder.size() - 1);
    }

private:
    /**
     * 根据中序遍历和后序遍历的子序列构造子二叉树
     * 序列中不存在重复元素
     * input inorder    : 中序遍历序列
     * input inStart    : 中序子序列开始位置的上一个位置
     * input inEnd      : 中序子序列结束位置
     * input postorder  : 后序遍历序列
     * input postStart  : 后序子序列开始位置的上一个位置
     * input postEnd    : 后序子序列结束位置
     * return           : 构造好的二叉树
     */
    TreeNode* buildTree(vector<int> &inorder, int inStart, int inEnd, vector<int> &postorder, int postStart, int postEnd) {
	if (inStart >= inEnd) return NULL;

        /* 构造根节点 
         * 后序子序列的最后一个值即为根节点的值 */
	TreeNode *root = new TreeNode(postorder[postEnd]);	// 存储根节点的值
	/* 在中序子序列中查找根节点
         * 其右侧的序列即为其右子树中序遍历的序列
         * 同时在后序子序列中相应长度的子序列即为右子树后序遍历的序列
         * 其左侧的序列即为其左子树中序遍历的序列
         * 同时在前序子序列中相应长度的子序列即为左子树前序遍历的序列
         */
        int startTmp = inEnd, endTmp = inEnd;
        while (startTmp > inStart && inorder[startTmp] != root->val)
            --startTmp;
        root->right = buildTree(inorder, startTmp, endTmp,
                postorder, postEnd - endTmp + startTmp - 1, postEnd - 1);   // 构造>右子树
        root->left = buildTree(inorder, inStart, startTmp - 1,
                postorder, postStart, postEnd - endTmp + startTmp - 1);     // 构造>左子树

        return root;
    }

};

/** 后序遍历 */
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->val << ", ";
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
    vector<int> post, in;
    post.push_back(3);
    post.push_back(2);
    post.push_back(6);
    post.push_back(5);
    post.push_back(4);
    post.push_back(1);
    in.push_back(3);
    in.push_back(2);
    in.push_back(1);
    in.push_back(4);
    in.push_back(6);
    in.push_back(5);
    cout << "Original Postorder : ";
    for (i = 0; i < n; ++i)
        cout << post[i] << ", ";
    cout << endl << "Original Inorder : ";
    for (i = 0; i < n; ++i)
        cout << in[i] << ", ";

    struct TreeNode* tree = s.buildTree(in, post);
    cout << endl << "Rebuild Tree Postorder : ";
    postorderTraversal(tree);
    cout << endl << "Rebuild Tree Inorder : ";
    inorderTraversal(tree);
    cout << endl;

    return 0;
}
