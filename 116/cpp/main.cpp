#include <iostream>

using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {

public:
    void connect(TreeLinkNode *root) { 
        if (root == NULL) return;
        TreeLinkNode *left = root->left, *right = root->right;
        while (left != NULL) {
            left->next = right;
            left = left->right;
            right = right->left;
        }

        connect(root->left);
        connect(root->right);
    }

};

void print(TreeLinkNode *root) {
    if (root == NULL) return;
    if (root->next == NULL) cout << root->val << "->null" << endl;
    else cout << root->val << "->" << root->next->val << endl;

    print(root->left);
    print(root->right);
}

int main() {
    TreeLinkNode n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7);
    n1.left = &n2; n1.right = &n3;
    n2.left = &n4; n2.right = &n5;
    n3.left = &n6; n3.right = &n7;
    n4.left = NULL; n4.right = NULL;
    n5.left = NULL; n5.right = NULL;
    n6.left = NULL; n6.right = NULL;
    n7.left = NULL; n7.right = NULL;

    Solution s;
    s.connect(&n1);
    print(&n1);
}
