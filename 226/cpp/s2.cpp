#include <iostream>
#include <queue>
#include <vector>
#include "../../libs/binary_tree.h"

using namespace std;

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return NULL;
        vector<TreeNode*> last, cur, nextLast, nextCur;
        last.push_back(root);
        cur.push_back(root->right);
        cur.push_back(root->left);
        vector<TreeNode*>::iterator lastIt, lastEnd, curIt, curEnd;
        while (last.size() > 0) {
            lastIt = last.begin();
            lastEnd = last.end(); 
            curIt = cur.begin();
            curEnd = cur.end();
            while (lastIt != lastEnd) {
                (*lastIt)->left = *curIt;
                if (*curIt) {
                    nextLast.push_back(*curIt);
                    nextCur.push_back((*curIt)->right);
                    nextCur.push_back((*curIt)->left);
                }
                ++curIt;
                (*lastIt)->right = *curIt;
                if (*curIt) {
                    nextLast.push_back(*curIt);
                    nextCur.push_back((*curIt)->right);
                    nextCur.push_back((*curIt)->left);
                }
                ++curIt;
                ++lastIt;
            }    
            last.clear();
            last.insert(last.begin(), nextLast.begin(), nextLast.end());
            nextLast.clear();
            cur.clear();
            cur.insert(cur.begin(), nextCur.begin(), nextCur.end());
            nextCur.clear();
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
