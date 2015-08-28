#include <iostream>
#include <queue>
#include <stack>
#include "../../libs/binary_tree.h"

using namespace std;

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;
        queue<TreeNode*> last, lastTmp, cur, curTmp;
        last.push(root);
        cur.push(root->right);
        cur.push(root->left);

        TreeNode* nodeTop, * nodeBottom;
        while (!last.empty()) {
            while (!last.empty()) {
                nodeTop = last.front();
                last.pop();
                nodeBottom = cur.front();
                cur.pop();
                nodeTop->left = nodeBottom;
                if (nodeBottom) {
                    lastTmp.push(nodeBottom);
                    curTmp.push(nodeBottom->right);
                    curTmp.push(nodeBottom->left);
                }
                nodeBottom = cur.front();
                cur.pop();
                nodeTop->right = nodeBottom;
                if (nodeBottom) {
                    lastTmp.push(nodeBottom);
                    curTmp.push(nodeBottom->right);
                    curTmp.push(nodeBottom->left);
                }
            }
            while (!lastTmp.empty()) {
                last.push(lastTmp.front());
                lastTmp.pop();
            }
            while (!curTmp.empty()) {
                cur.push(curTmp.front());
                curTmp.pop();
            }
        }
        return root;
    }
};

void levelTraversal(TreeNode* root) {
    if (root == NULL) return;
    queue<TreeNode*> q;
    q.push(root);
    TreeNode* tmp;
    while (!q.empty()) {
        tmp = q.front();
        q.pop();
        if (tmp == NULL) {
            cout << "NULL ";
            continue;
        }
        cout << tmp->val << " "; 
        q.push(tmp->left);      
        q.push(tmp->right);      
    }
    cout << endl;
}

int main() {
    TreeNode* tree = genBinaryTree("[4,7,2,1,3,6,9,5,4]");
    levelTraversal(tree);
    Solution s;
    tree = s.invertTree(tree);
    levelTraversal(tree);
    freeBinaryTree(tree);
    tree = genBinaryTree("1,2,3,4,null,null,5");
    levelTraversal(tree);
    tree = s.invertTree(tree);
    levelTraversal(tree);
    freeBinaryTree(tree);
    return 0;
}
