#include <iostream>
#include <stack>
#include "../../libs/binary_tree.h"

using namespace std;

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        ++k;
        TreeNode head;
        head.right = root;
        stack<TreeNode*> s;
        s.push(&head);
        int ret;

        TreeNode* cur;
        while (!s.empty()) {
            cur = s.top();
            s.pop();
            --k;
            if (k == 0) {
                ret = cur->val;
                break;
            }
            cur = cur->right;
            while (cur) {
                s.push(cur);
                cur = cur->left;
            }
        }
        return ret;
    }
};

void test(char str[]) {
    cout << str << " : ";
    TreeNode* tree = genBinaryTree(str);
    Solution s;
    for (int i = 1; i <= 20; ++i)
        cout << s.kthSmallest(tree, i) << ",";  
    cout << endl;
    freeBinaryTree(tree);
}

int main() {
    char str[] = "[10,6,15,3,8,12,18,1,5,7,9,11,13,16,19,null,2,4,null,null,null,null,null,null,null,null,14,null,17,null,20]";
    test(str);
    return 0;
}
