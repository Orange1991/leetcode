#include <iostream>
#include "../../libs/binary_tree.h"

using namespace std;

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        int sum = 0, val = 0;
        sumRootToLeaf(root, val, sum);
        return sum;
    }

private:
    void sumRootToLeaf(TreeNode *root, int val, int &sum) {
        if (root == NULL) return;

        val *= 10;
        val += root->val;

        if (root->left == NULL && root->right == NULL) {
            sum += val;
            return;
        }

        sumRootToLeaf(root->left, val, sum);
        sumRootToLeaf(root->right, val, sum);
    }
};

int main() { 
    char *data = "[1,2,3]";
    TreeNode *tree = genBinaryTree(data);
    Solution s;
    cout <<  s.sumNumbers(tree) << endl;
    freeBinaryTree(tree);
    return 0;
}
