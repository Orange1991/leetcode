#include <iostream>
#include <vector>
#include "../../libs/binary_tree.h"

using namespace std;

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ret;
        paths(root, "", ret);
        return ret;
    }
    
private: 
    void paths(TreeNode* node, string path, vector<string>& ret) {
        if (node == NULL) return;
        char s[16];
        sprintf(s, "%d", node->val);
        if (node->left == NULL && node->right == NULL)  { 
            ret.push_back(path + s);
            return;
        }
        path = path + s + "->";
        paths(node->left, path, ret);
        paths(node->right, path, ret);
    }
};

void test(TreeNode* root) {
    Solution s;
    vector<string> ret = s.binaryTreePaths(root);
    int len = ret.size() - 1; 
    for (int i = 0; i < len; ++i)
        cout << ret[i] << ", ";
    cout << ret[len] << endl;
}

int main() {
    TreeNode* tree = genBinaryTree("1,2,3,null,5");
    test(tree);
    freeBinaryTree(tree);
    return 0;
}
