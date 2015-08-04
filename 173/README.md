#Leetcode 173 Binary Search Tree Iterator 二叉查找树迭代器

##原题地址
https://leetcode.com/problems/binary-search-tree-iterator/

##题目描述
Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.
实现一个适用于二叉查找树的迭代器，该迭代器通过二叉查找树的根结点来实例化。

Calling `next()` will return the next smallest number in the BST.
调用`next()`返回二叉查找树中的最小的元素。

Note: `next()` and `hasNext()` should run in average `O(1) time` and uses `O(h) memory`, where h is the height of the tree.
**注意**：`next()`和`hasNext()`运行的`平均时间复杂度为O(1)`，`空间复杂度为O(h)`，其中h是树的高度。

##解题思路

如果不看**注意**的话，一个非常简单的解决办法是遍历这棵二叉树，把二叉树的元素以从大到小的方式放到一个栈里，这样next()从栈顶获取元素，hasNext()调用栈不为空的判定方法。这种方法能满足题目中的时间复杂度要求，但是O(n)的空间复杂度无法满足题目中O(h)空间复杂度要求。

我们维护一个栈，暂且称之为最小元素栈，栈中存放的是结点指针，**向栈中添加元素**发生在两种情况下：1.初始化迭代器时；2.调用next()从栈中弹出一个元素时。我们结合下面的实例来描述这个栈中元素的添加和删除过程。对于hasNext()方法，调用栈的empty()方法即可，不做具体分析，仅分析next()方法以及迭代器的数据结构。

> 假设二叉查找树的结构如下：

             6
           /   \
          5     8
         /     / \
        1     7   9
         \      
          3  
         / \
        2   4

> （1）栈的初始化，我们把root一直到最左下角的结点都放到stack中，即把如下三个结点放在stack中。

            6    |   |
           /     |   |
          5      | 1 |
         /       | 5 |
        1        |_6_|  <---栈内情况
         注意：上图中栈中存放的应该是指针而不是1,5,6等元素，此处仅用作示意，不代表实际情况，请勿生疑。

>（2）第一次调用next()，此时弹出指向元素1的指针tmp，这时候栈内只剩下5,6，如果我们不对栈进行维护的话，我们再调用一次next()将会弹出5，这显然是不对的，因为二叉查找树中还有比5小比2大的元素。因此这时候，我们应当将二叉查找树，或者更准确的说，应该把元素1的右子树上的部分结点添加到栈中。
         
                 |   |
                 |   |
                 |   |
                 | 5 |
                 |_6_|  <---栈内情况
    
> （3）那么我们将1（tmp）的右子树上所有结点都放到栈内吗？不，此时添加结点的逻辑与初始化迭代器时类似，    我们只把从tmp->right为根一直到其最坐下角的结点都放到stack中，即，把3,2两个元素放到栈中。

                 |   |
                 | 2 |
                 | 3 |
                 | 5 |
                 |_6_|  <---栈内情况

> （4）再次调用next()时，返回的将是正确的答案2，然后2并没有右结点，则无须添加新的指针到栈中。

                 |   |
                 |   |
                 | 3 |
                 | 5 |
                 |_6_|  <---栈内情况

> （5）之后的过程与此类似，在此把每次调用next()之后的栈的存储情况列举如下：

                 |   |       |   |       |   |       |   |       |   |       |   |       |   |
                 |   |       |   |       |   |       |   |       |   |       |   |       |   |
                 | 4 |  -->  |   |  -->  |   |  -->  |   |  -->  |   |  -->  |   |  -->  |   |
                 | 5 |       | 5 |       |   |       | 7 |       |   |       |   |       |   |
                 |_6_|       |_6_|       |_6_|       |_8_|       |_8_|       |_9_|       |___|

综上所述，我们在栈中存储的是一部分极小值，且栈顶一定是当前树中未访问过的结点中的最小结点。在调用next()弹出最小结点时，需要把被弹出结点的右子树添加到栈中，也就是把比当前最小结点大但是比次小结点小的那些结点中的一部分（不是全部，只是左孩子分支上的一部分）添加到栈中。描述能力有限，大家还是结合上面的实例来理解一下吧。

然后我们来看，我们的这个数据结构是否满足题目要求。我们可以看到每一个结点一定要进入栈中，且该操作是在构造过程和next()中执行的，其中构造过程只执行一次，而next()执行多次。但是进栈的操作存在差异性，有时候调用next()不会往栈中添加任何元素，有时候会添加多个，但是至多不超过h个，其中h是树的高度，因为添加时只顺着树的左分支往下添加。我们一共要调用n次next()，在这n次调用中，每个结点都进栈/出栈，共n次入栈操作，n次出栈操作，平均起来，**每次next()只有`一次入栈操作+一次出栈操作`**，因此**满足平均时间复杂度O(1)**的要求。再看空间复杂度，刚才我们已经说过，在往栈中添加元素时**只顺着树的左分支往下添加**，因此**至多添加h个结点**，其中h就是树的高度，因此**满足空间复杂度O(h)**的要求。

##代码 cpp

```
class BSTIterator {
public:
    stack<TreeNode *> mins;
    /** 初始化迭代器 */
    BSTIterator(TreeNode *root) {
        while (root != NULL) { // 添加元素
            mins.push(root);
            root = root->left;
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !mins.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *tmp = mins.top(); // 获取并弹出最小元素
        mins.pop();
        int ret = tmp->val;
        tmp = tmp->right;
        // 添加元素被弹出结点的右子树上的较小元素
        while (tmp != NULL) { 
            mins.push(tmp);
            tmp = tmp->left;
        }
        return ret; // 返回最小元素
    }
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/tree/master/173/cpp/best.cpp](https://github.com/Orange1991/leetcode/tree/master/173/cpp/best.cpp)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47280679

---
2015/8/4
