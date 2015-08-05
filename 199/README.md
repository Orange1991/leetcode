#Leetcode 199 Binary Tree Right Side View 二叉树右视图

##原题地址
https://leetcode.com/problems/binary-tree-right-side-view/

##题目描述
Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.
给出一个二叉树，设想你从树的右侧看过来，返回你从上往下可以看到的结点．

For example:
例如：

Given the following binary tree,
给出如下的二叉树

       1            <---
     /   \
    2     3         <---
     \     \
      5     4       <---

You should return [1, 3, 4].
你需要返回[1, 3, 4].

##解题思路
首先可以明确的是，看到的结点是每一层的结点中最右侧的结点，我们要做的就是按照层序把每一层最右侧的结点找出来并返回．然后针对按照层序的关键点，我们可以考虑层序遍历的类似思路．层序遍历中需要用到队列，这里我们考虑也使用队列．但是与层序遍历不同的是，我们需要非常明确的区分开不同的层，以保存每层的最后一个结点．我们可以使用两个队列，一个队列中存储某一层的结点，另一个队列存储下一层的结点，这样做到把不同层的结点区分开来．

##代码 cpp

```
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
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/199/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/199/cpp/main.cpp)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47304343

---
2015/8/5
