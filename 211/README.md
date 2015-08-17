# Leetcode 211 Add and Search Word - Data structure design 添加/查找单词
##原题地址
https://leetcode.com/problems/add-and-search-word-data-structure-design/

##题目描述
Design a data structure that supports the following two operations:
设计一个数据结构来支持以下两个操作：

    void addWord(word)
    bool search(word)
    
`search(word)` can search a literal word or a regular expression string containing only letters `a-z` or `.`. A `.` means it can represent any one letter.
`search(word)`既可以查找一个字面上的直接量，也可以查找一个包含`a-z`和`.`的正则表达式，`.`表示任意字符。

For example:
例如：

    addWord("bad")
    addWord("dad")
    addWord("mad")
    search("pad") -> false
    search("bad") -> true
    search(".ad") -> true
    search("b..") -> true
    
Note:
注意：

You may assume that all words are consist of lowercase letters `a-z`.
你可以假设所有的输入只包含小写的 `a-z` 字符。

Hint:
提示：

You should be familiar with how a Trie works. If not, please work on this problem: Implement Trie (Prefix Tree) first.
你需要熟悉Trie字典树的工作机制。如果不熟悉的话，请先解决这个问题：[Implement Trie (Prefix Tree)](https://leetcode.com/problems/implement-trie-prefix-tree/)

##解题思路
提示中也提到了，需要熟悉Trie的工作机制，先解决[Leetcode 208 Implement Trie (Prefix Tree) 实现字典树 (前缀字典树)](http://blog.csdn.net/smile_watermelon/article/details/47659235)。本题中的单词字典与Trie基本类似，其构造过程（添加单词操作）完全一样，只有查找操作中需要支持`.`正则表达式。其解决思路也是比较简单的，如果遇到点字符，则尝试从某结点的所有子结点中查找剩余的子串，其他情况下从某确定的子结点中查找剩余的子串。

##代码

```
/**
 * 字典树的结点
 */
class TrieNode {
public:
    static const int NODES_SIZE = 26; // 子结点个数
    TrieNode* nodes[NODES_SIZE]; // 子结点
    bool isLast;    // 是否存在以此为结尾的单词
    // 初始化
    TrieNode() {
        for (int i = 0; i < NODES_SIZE; ++i)
            nodes[i] = NULL;
        isLast = false;
    }
};

/**
 * 字典
 */
class WordDictionary {
public:
    WordDictionary() {
        root = new TrieNode();
        root->isLast = true; // 空串""存在于字典中
    }

    /** 
     * Add a word into the data structure. 添加一个单词
     * @param word : the word that will be inserted into the trie. 要添加的单词
     */
    void addWord(string word) {
        TrieNode* tmp = root;
        while (word != "") { // 循环插入字符
            char c = word[0];
            word = word.substr(1);
            if (tmp->nodes[c - 'a'] == NULL) { // 如果不存在后继结点
                TrieNode* newNode = new TrieNode(); // 新建后继结点
                tmp->nodes[c - 'a'] = newNode; // 存储后继结点指针
            }
            tmp = tmp->nodes[c - 'a']; // 指向后继结点
        }
        tmp->isLast = true; // 最后一个字符插入结束，修改isLast，表示存在到此为止的单词
    }

    /**
     * Returns if the word is in the trie. 查找是否存在某个单词
     * A word could contain the dot character '.' to represent any one letter.
     * 一个单词里可以用点字符'.'代表任意字符。
     * @param word : the word to be searched. 要查找的单词
     * @return 存在返回true，否则false
     */
    bool search(string word) {
        return search(word, root);
    }

    /** 释放内存 */
    void free() {
        free(root);
    }
private:
    /** 字典根结点 */
    TrieNode* root;

    /**
     * Returns if the word is in the node. 查找是否存在某个单词
     * A word could contain the dot character '.' to represent any one letter.
     * 一个单词里可以用点字符'.'代表任意字符。
     * @param word : the word to be searched. 要查找的单词
     * @param node : the begin node to search. 被查找的结点
     * @return 存在返回true，否则false
    */
    bool search(string word, TrieNode* node) {
        if (word == "") return node->isLast;// word为空，当前结点是结尾结点则成功 
        char c = word[0];
        int index = c - 'a';
        if (c == '.') { // 遇到点字符
            int i;
            for (i = 0; i < root->NODES_SIZE; ++i) {
                if (node->nodes[i] != NULL) // 在任意不为空的分支下尝试查找
                    if (search(word.substr(1), node->nodes[i]))
                        break;  // 如果查找成功，则跳出循环，否则继续
            }
            // i==NODES_SIZE时所有子结点均查找失败
            return i < root->NODES_SIZE; 
        } else {    // 遇到特定字符
            if (node->nodes[index] != NULL) // 如果存在后继，则尝试查找
                return search(word.substr(1), node->nodes[index]);
            else return false;  // 否则查找失败
        }
    }

    /** 释放内存 */
    void free(TrieNode* node) {
        if (node == NULL) return;
        for (int i = 0; i < node->NODES_SIZE; ++i)
            free(node->nodes[i]);
        delete(node);
    }
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/211/cpp/dict.cpp](https://github.com/Orange1991/leetcode/blob/master/211/cpp/dict.cpp)

##测试数据

    (1)
    addWord("bad")
    addWord("dad")
    addWord("mad")
    search("pad") -> false
    search("bad") -> true
    search(".ad") -> true
    search("b..") -> true
    
    (2)
    addWord("at")
    addWord("and")
    addWord("an")
    addWord("add")
    search("a") -> false
    search(".at") -> false
    addWord("bat")
    search(".at") -> true
    search("an.") -> true
    search("a.d.") -> false
    search("b.") -> false
    search("a.d") -> true
    search(".") -> false


##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47728669

---
2015/8/17
