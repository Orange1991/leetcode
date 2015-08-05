#include <iostream>
#include "../../libs/binary_tree.h"
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    /** 获取每一层最右侧的结点 */
    vector<int> rightSideView(TreeNode* root) {
        /* 两个队列交替使用，获取队尾的元素 */
        vector<int> ret;
        queue<TreeNode*> queues[2];

        /* 初始化，把第一层结点放入第一个队列*/
        if (root != NULL) queues[0].push(root);

        /* 交替使用队列，一个队列存储一层结点
         * 另一个队列存储下一层结点（或上一层结点） */
        int i = 0, j = 1, tmp;
        TreeNode *p;        
        while (!queues[0].empty() || !queues[1].empty()) {
            while (!queues[i].empty()) {
                p = queues[i].front();
                queues[i].pop();
                if (p->left) queues[j].push(p->left);
                if (p->right) queues[j].push(p->right);
                tmp = p->val;
            }
            // 遍历完某一层结点时，tmp是该层最右侧的结点的值
            ret.push_back(tmp); // 添加到结果集
            i = (i + 1) % 2; // 交换两个队列的角色
            j = (j + 1) % 2;
        }

        return ret;
    }
};

int main() {
    char *str = "[1,2,3,null,5,null,4]";
    TreeNode *tree = genBinaryTree(str);
    Solution s;
    vector<int> ret = s.rightSideView(tree);
    for (int i = 0, len = ret.size(); i < len; ++i)
        cout << ret[i] << " ";
    cout << endl;
    freeBinaryTree(tree);
    return 0;
}
