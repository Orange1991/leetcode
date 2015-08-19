#Leetcode 212 Word Search II 单词查找

##原题地址
https://leetcode.com/problems/word-search-ii/

##题目描述
Given a 2D board and a list of words from the dictionary, find all words in the board.
给出一个二维board和一个单词字典，找出board里可以构成的所有字典里的单词。

Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
单词需要由相邻的字符构成，相邻是指水平或者竖直方向上相邻。同一个格子里的字符在一个单词里只能使用一次。

For example,
例如，

Given
给出

 `words = ["oath","pea","eat","rain"]` and `board =`

    [
        ['o','a','a','n'],
        ['e','t','a','e'],
        ['i','h','k','r'],
        ['i','f','l','v']
    ]
    
Return
返回

 `["eat","oath"]`.

Note:
注意：

You may assume that all inputs are consist of lowercase letters a-z.
假设输入全都是小写`a-z`字符。

Hints:
提示：

You would need to optimize your backtracking to pass the larger test. Could you stop backtracking earlier?
需要通过大的测试数据。你可以提前结束回溯吗？

If the current candidate does not exist in all words' prefix, you could stop backtracking immediately. What kind of data structure could answer such query efficiently? Does a hash table work? Why or why not? How about a Trie? If you would like to learn how to implement a basic trie, please work on this problem: Implement Trie (Prefix Tree) first.
如果一个候选者不是所有单词的前缀，那你可以立即结束回溯。试试Trie字典树。

##解题思路
有了[Leetcode 208 Implement Trie (Prefix Tree) 实现字典树 (前缀字典树)](http://blog.csdn.net/smile_watermelon/article/details/47659235)，思路还是很清楚的，使用给定的字符串构造Trie字典树，然后尝试在board里找到字典中的单词。在board中构造单词的时候，如果当前单词在字典中找不到任何以其为前缀的单词，则继续构造下去也不可能获得可行解，此时可以直接结束本次构造。

根据如上逻辑，我们使用Trie的startsWith方法可以很容易的知道当前候选者是否是字典中某单词的前缀，如果是，则继续使用search方法判定，当前候选者是否是字典中的单词，否则可以直接结束本次构造。详细请见代码三。

然而上述方法中仍然存在可以**优化**的地方。我们在构造候选者的时候是每次添加一个字符，因此我们不必每次都调用startsWith方法，这里存在重复搜索，我们完全可以使用**上一次匹配中的最后一个TrieNode结点**，然后继续判定其是否有当前新添加的字符的后继结点；另外对于判定是否存在某个单词也不必再调用search，这里search和startsWith也是重复操作，我们获得TrieNode之后，直接使用TrieNode.isLast来判定是否是字典里的单词即可。然而这一切是建立在我们可以获得Trie树的根结点的前提下的，如果我们只有一个不可定制的Trie数据结构，如果我们只能使用它的insert/startsWith/search方法，那么我们将只能使用前面说的方法。但是好在，我们现在在解决Word Search II时，可以随意定制Trie数据结构。详细请见代码一、代码二。

关于代码一和代码二，其差别仅仅在于对于字符重复使用的判定方法上，代码一中直接使用board，将使用过的字符设为一个特殊字符，如空格`' '`，如果某字符为`' '`则说明在此单词中已经使用过该位置的字符；在使用过后再将字符改回原先的字符即可。而代码二中是使用了一个`bool used[][]`数组，来完成刚才的逻辑，即使用过的位置设为true，使用结束后设为false。

在此，还要再说一点。在使用used数组的方法中，一开始我并没有使用回溯的思路，由于这样会导致结果错误（一个字符使用过任意一次后即变为true），于是我在传递used数组时使用的值传递，因此每次调用都会拷贝一个二维数组used，这无疑是非常耗时的，也导致了TLE。解决方法就是在传递used时传递引用，并且使用回溯的方法，在递归结束时修改字符使用标志。使用board+特殊字符的方式时也需要注意将字符改回原先的字符。

*参考 [My AC very clean C++ code](https://leetcode.com/discuss/49167/my-ac-very-clean-c-code)*

##代码

###代码一

```
class Solution {
public:
    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        // 创建字典树
        Trie trie;
        for (vector<string>::iterator it = words.begin(), end = words.end(); it != end; ++it)
            trie.insert(*it);
        // 查找
        vector<string> ret = findWords(board, trie);
        // 释放内存
        trie.free();
        return ret;
    }
private:
    /**
     * 查找单词
     * @param board 单词构造库
     * @param trie 字典树
     * @return 查找成功的单词
     */
    vector<string> findWords(vector<vector<char> >& board, Trie& trie) {
        int rows = board.size(), cols = board.size() == 0 ? 0 : board[0].size();
        unordered_set<string> set;
        TrieNode* root = trie.getRoot();
        // 从任一字符开始，尝试查找单词
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                findWords(board, root, rows, cols, i, j, "", set);
        vector<string> ret(set.begin(), set.end());
        return ret;
    }

    /**
     * 查找单词
     * @param board 单词构造库
     * @param node 字典树结点
     * @param rows 单词构造库行数
     * @param cols 单词构造库列数
     * @param x 当前字符所在位置的x坐标
     * @param y 当前字符所在位置的y坐标
     * @param prefix 当前单词
     * @param set 查找成功的单词
     */
    void findWords(vector<vector<char> >& board, TrieNode* node, int& rows, int& cols, int x, int y, 
            string prefix, unordered_set<string>& set) {
        // 下标越界或者字符已经使用过，则退出
        if (x < 0 || x >= rows || y < 0 || y >= cols || board[x][y] == ' ') return;

        char c = board[x][y]; // 当前字符
        prefix += c; // 扩展新单词
        TrieNode* cur = node->nodes[c - 'a']; // 获取字典树后继结点
        if (cur == NULL) return; // 后继为空，说明以当前prefix为前缀继续构造无法获得目标单词，退出
        else if (cur->isLast)  // 如果当前指针是单词结尾，则发现新单词
            set.insert(prefix); // 添加
        board[x][y] = ' '; // 表示当前字符已经使用过
        // 继续向四周扩展
        findWords(board, cur, rows, cols, x - 1, y, prefix, set);
        findWords(board, cur, rows, cols, x + 1, y, prefix, set);
        findWords(board, cur, rows, cols, x, y - 1, prefix, set);
        findWords(board, cur, rows, cols, x, y + 1, prefix, set);
        board[x][y] = c; // 修改，表示当前字符未使用过，可以继续使用
    }
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/212/cpp/s1.cpp](https://github.com/Orange1991/leetcode/blob/master/212/cpp/s1.cpp)

###代码二

```
class Solution {
public:
    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        // 创建字典树
        Trie trie(words);
        // 查找单词
        vector<string> ret = findWords(board, trie);
        // 释放内存
        trie.free();
        return ret;
    }
private:
    /**
     * 查找单词
     * @param board 单词构造库
     * @param trie 字典树
     * @return 查找成功的单词
     */
    vector<string> findWords(vector<vector<char> >& board, Trie& trie) {
        int rows = board.size(), cols = board.size() == 0 ? 0 : board[0].size();
        vector<vector<bool> > used(rows, vector<bool>(cols, false));
        unordered_set<string> set;
        TrieNode* root = trie.getRoot();
        // 从任一字符开始，尝试查找单词
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                findWords(board, root, rows, cols, i, j, "", set, used);
        vector<string> ret(set.begin(), set.end());
        return ret;
    }

    /** 
     * 查找单词
     * @param board 单词构造库
     * @param node 字典树结点
     * @param rows 单词构造库行数
     * @param cols 单词构造库列数
     * @param x 当前字符所在位置的x坐标
     * @param y 当前字符所在位置的y坐标
     * @param prefix 当前单词
     * @param set 查找成功的单词
     × @param used 字符是否已经使用的标志
     */
    void findWords(vector<vector<char> >& board, TrieNode* node, int& rows, int& cols, int x, int y, 
            string prefix, unordered_set<string>& set, vector<vector<bool> >& used) {
        // 下标越界或者字符已经使用过，则退出
        if (x < 0 || x >= rows || y < 0 || y >= cols || used[x][y]) return;
        prefix += board[x][y]; // 扩展新单词
        TrieNode* cur = node->nodes[board[x][y] - 'a']; // 获取字典树后继结点
        if (cur == NULL) return; // 后继为空，说明以当前prefix为前缀继续构造无法获得目标单词，退出
        else if (cur->isLast) // 如果当前指针是单词结尾，则发现新单词
            set.insert(prefix); // 添加
        used[x][y] = true; // 表示当前字符已经使用过
        // 继续向四周扩展
        findWords(board, cur, rows, cols, x - 1, y, prefix, set, used);
        findWords(board, cur, rows, cols, x + 1, y, prefix, set, used);
        findWords(board, cur, rows, cols, x, y - 1, prefix, set, used);
        findWords(board, cur, rows, cols, x, y + 1, prefix, set, used);
        used[x][y] = false; // 修改，表示当前字符未使用过，可以继续使用
    }
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/212/cpp/s2.cpp](https://github.com/Orange1991/leetcode/blob/master/212/cpp/s2.cpp)

###代码三

```
class Solution {
public:
    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        // 创建字典树
        Trie trie;
        for (vector<string>::iterator it = words.begin(), end = words.end(); it != end; ++it)
            trie.insert(*it);
        // 查找
        vector<string> ret = findWords(board, trie);
        // 释放内存
        trie.free();
        return ret;
    }
private:
    /**
     * 查找单词
     * @param board 单词构造库
     * @param trie 字典树
     * @return 查找成功的单词
     */
    vector<string> findWords(vector<vector<char> >& board, Trie& trie) {
        int rows = board.size(), cols = board.size() == 0 ? 0 : board[0].size();
        unordered_set<string> set;
        // 从任一字符开始，尝试查找单词
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                findWords(board, trie, rows, cols, i, j, "", set);
        vector<string> ret(set.begin(), set.end());
        return ret;
    }

    /**
     * 查找单词
     * @param board 单词构造库
     * @param trie 字典树
     * @param rows 单词构造库行数
     * @param cols 单词构造库列数
     * @param x 当前字符所在位置的x坐标
     * @param y 当前字符所在位置的y坐标
     * @param prefix 当前单词
     * @param set 查找成功的单词
     */
    void findWords(vector<vector<char> >& board, Trie& trie, int& rows, int& cols, int x, int y, 
            string prefix, unordered_set<string>& set) {
        // 下标越界或者字符已经使用过，则退出
        if (x < 0 || x >= rows || y < 0 || y >= cols || board[x][y] == ' ') return;

        char c = board[x][y]; // 当前字符
        prefix += c; // 扩展新单词
        if (!trie.startsWith(prefix)) return; // 说明以当前prefix为前缀继续构造无法获得目标单词，退出
        if (trie.search(prefix)) set.insert(prefix); // 发现新单词
        board[x][y] = ' '; // 表示当前字符已经使用过
        // 继续向四周扩展
        findWords(board, trie, rows, cols, x - 1, y, prefix, set);
        findWords(board, trie, rows, cols, x + 1, y, prefix, set);
        findWords(board, trie, rows, cols, x, y - 1, prefix, set);
        findWords(board, trie, rows, cols, x, y + 1, prefix, set);
        board[x][y] = c; // 修改，表示当前字符未使用过，可以继续使用
    }
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/212/cpp/s3.cpp](https://github.com/Orange1991/leetcode/blob/master/212/cpp/s3.cpp)

此外，除了使用words构建字典，然后在board中尝试查找以外，还有一种思路是，使用board构造所有字符串，然后使用这些字符串构造字典，再查询字典中存在的words中的字符串（因为最终查找的字符串既存在与words中也存在与board构造的字符串中，因此两者均可以作为字典），然而这样的情况下需要穷举所有board可能构造的字符串，太耗时了，TLE是肯定的。不过我还是实现了以下，事实证明结果是正确的，但是运行起来真的是慢得要命，我一度以为是死循环了，感兴趣的话可以看一下 [https://github.com/Orange1991/leetcode/blob/master/212/cpp/s4.cpp](https://github.com/Orange1991/leetcode/blob/master/212/cpp/s4.cpp)。

##测试数据

    (1) Given words = [oath,pea,eat,rain], and board = 
    [
        [o,a,a,n],
        [e,t,a,e],
        [i,h,k,r],
        [i,f,l,v]
    ]
    Found words = [eat,oath]

    (2) Given words = [a], and board = 
    [
        [a]
    ]
    Found words = [a]

    (3) Given words = [aa], and board = 
    [
        [a,a]
    ]
    Found words = [aa]

    (4) Given words = [abbbababaa], and board = 
    [
        [b,b,a,a,b,a],
        [b,b,a,b,a,a],
        [b,b,b,b,b,b],
        [a,a,a,b,a,a],
        [a,b,a,a,b,b]
    ]
    Found words = [abbbababaa]

    (5) Given words = [a,aa,aaa,aaaa,bbaa,baa], and board = 
    [
        [a,b],
        [a,b]
    ]
    Found words = [a,baa,bbaa,aa]

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47779197

---
2015/8/19
