#include <iostream>

using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    /**
     * 填充二叉树的next指针
     */
    void connect(struct TreeLinkNode *root) {
        if (root == NULL) return;

        struct TreeLinkNode *begin = NULL, *p = root, *pre, *next;
    
        while (p != NULL) {
            if (p->left != NULL) {
                begin = p->left;
                break;
            }
            else if (p->right != NULL) {
                begin = p->right;
                break;
            }
            else p = p->next;
        }

        if (begin == NULL) return;

        pre = begin;    
        if (begin == p->left && p->right != NULL) {
            next = p->right;
            pre->next = next;
            pre = next;
        }
        p = p->next;

        while ( p != NULL) {
            if(p->left != NULL) {
                next = p->left;
                pre->next = next;
                pre = next;
            } 
            if (p->right != NULL) {
                next = p->right;
                pre->next = next;
                pre = next;
            }
            p = p->next;
        }

        connect(begin);
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
    TreeLinkNode n1(1), n2(2), n3(3), n4(4), n5(5), n6(6);
    n1.left = &n2; n1.right = &n3;
    n2.left = &n4; n2.right = &n5;
    n3.right = &n6;
    n4.left = NULL; n4.right = NULL;
    n5.left = NULL; n5.right = NULL;
    n6.left = NULL; n6.right = NULL;

    Solution s;
    s.connect(&n1);
    print(&n1);
}

