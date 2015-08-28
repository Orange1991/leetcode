#Leetcode 226 Invert Binary Tree 反转二叉树

##原题地址
https://leetcode.com/problems/invert-binary-tree/

##题目描述
Invert a binary tree.
反转一棵二叉树。

from

         4
       /   \
      2     7
     / \   / \
    1   3 6   9
to

         4
       /   \
      7     2
     / \   / \
    9   6 3   1

Trivia:
轶事：

This problem was inspired by this original tweet by [Max Howell](https://twitter.com/mxcl):
这个问题的灵感来自Max Howell的[原始推文(tweet)](https://twitter.com/mxcl/status/608682016205344768)：

Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so fuck off.
90%的Google员工都在用你写的软件（Homebrew），然而你无法在一个白板上写出反转二叉树的算法，所以我们不要你。

关于这个事件，知乎上还有一个讨论 [如何评价 Homebrew 作者因为不会在白板上翻转二叉树而被谷歌面试拒绝？](http://www.zhihu.com/question/31187043?nr=1)

此处不作过多讨论，看一下这个题就好。

##解题思路
直观上来看，题目要求很清楚，就是左右对调。那么如何实现呢？可以考虑**将每一层的结点从右侧开始往左依次添加到一个队列中，然后把队列中的结点依次链接到上一层的结点上去（假设上一层已经完成了反转）**。

要想实现上述思路，我们假设第i-1层已经反转结束了，正要对第i层执行反转操作，我们从最右侧的结点开始，依次将每个结点node放入队列queueLast中，并且把每个结点的右孩子和左孩子放入队列queueCur中（先放右孩子再放左孩子）。这样处理结束后，queueLast中存储的就是第i层结点反转之后的从左至右的顺序，然后把queueCur中的结点依次链接到queueLast的结点上去即可完成第i层的反转。

##代码

```
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
            while (!last.empty()) { // 把下一层结点链接到上一层结点上去
                                    // 并反转下一层的结点
                nodeTop = last.front();
                last.pop();
                nodeBottom = cur.front();
                cur.pop();
                nodeTop->left = nodeBottom; // 把结点链接到上一层结点上去
                if (nodeBottom) {   // 把当前层的结点反转，放入队列，以备下层循环使用
                    lastTmp.push(nodeBottom);
                    curTmp.push(nodeBottom->right);
                    curTmp.push(nodeBottom->left);
                }
                nodeBottom = cur.front();
                cur.pop();
                nodeTop->right = nodeBottom; // 把结点链接到上一层结点上去
                if (nodeBottom) {   // 把当前层的结点反转，放入队列，以备下层循环使用
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
```

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/226/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/226/cpp/main.cpp)

除此之外，还有用vector实现的一个版本，有兴趣可参考[https://github.com/Orange1991/leetcode/blob/master/226/cpp/s2.cpp](https://github.com/Orange1991/leetcode/blob/master/226/cpp/s2.cpp)

##测试数据

    before invert : 4 7 2 1 3 6 9 5 4 NULL NULL NULL NULL NULL NULL NULL NULL NULL NULL 
    after invert : 4 2 7 9 6 3 1 NULL NULL NULL NULL NULL NULL 4 5 NULL NULL NULL NULL 
    before invert : 1 2 3 4 NULL NULL 5 NULL NULL NULL NULL 
    after invert : 1 3 2 5 NULL NULL 4 NULL NULL NULL NULL 
    
##博文地址
http://blog.csdn.net/smile_watermelon/article/details/48056191

---
2015/8/28
