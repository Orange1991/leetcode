#Leetcode 208 Implement Trie (Prefix Tree) 实现字典树 (前缀字典树)

##原题地址
https://leetcode.com/problems/implement-trie-prefix-tree/

##题目描述
Implement a `trie` with `insert`, `search`, and `startsWith` methods.
实现一个`Trie字典树`，实现 `insert` `search` `startsWith` 方法。

Note:
注意：

You may assume that all inputs are consist of lowercase letters a-z.
你可以假设所有的输入只包含小写的 `a-z` 字符。

**Tags** `Data Structure` `Trie`
##解题思路
首先，关于 `Trie` 的概念，请看[维基百科-Trie](https://en.wikipedia.org/wiki/Trie)，也可以参考[百度百科-字典树](http://baike.baidu.com/link?url=Lb6ciNaiSQMYEKxUsC-HVHd4gWzmDbS_A2DEUbk_BMOAujaa6VWpdjb56OFIl_FJ5MZh2WUxpDTnXRd5OKOYyK)。

Trie是一棵字典树，典型的如下图：
![Trie](http://img.blog.csdn.net/20150814104657815)

###性质
它有3个基本性质：
> 1. 根节点不包含字符，除根节点外每一个节点都只包含一个字符； 
> 2. 从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串； 
> 3. 每个节点的所有子节点包含的字符都不相同。

*参考[百度百科-字典树](http://baike.baidu.com/link?url=Lb6ciNaiSQMYEKxUsC-HVHd4gWzmDbS_A2DEUbk_BMOAujaa6VWpdjb56OFIl_FJ5MZh2WUxpDTnXRd5OKOYyK)*

###操作
其基本操作有：`查找`、`插入`和`删除`,当然删除操作比较少见。*参考[百度百科-字典树](http://baike.baidu.com/link?url=Lb6ciNaiSQMYEKxUsC-HVHd4gWzmDbS_A2DEUbk_BMOAujaa6VWpdjb56OFIl_FJ5MZh2WUxpDTnXRd5OKOYyK)*。

对于本题，要求我们实现 **`插入`** **`查找`**，其中查找又包括 `search` 和 `startWith`，下面略作解释。

```
/** 
 * insert a word into the trie. 插入一个单词
 * @param word : the word that will be inserted into the trie. 要插入的单词
 */
void insert(string word);

/**
 * Returns if the word is in the trie. 查找trie中是否存在某个单词
 * @param word : the word to be searched. 要查找的单词
 * @return 存在返回true，否则false
 */
bool search(string word);

/**
 * Returns if there is any word in the trie that starts with the given prefix.
 * 查找是否存在以prefix为前缀的单词
 * @param prefix : the given prefix. 给定的前缀
 * @return 存在返回true，否则false
 */
bool startsWith(string prefix);
```

`insert`不作过多解释。`search`和`startsWith`有什么不同呢？search是查找是否存在某个单词，startsWith是查找是否存在以某个字符串为前缀的单词，我们用以下实例来说明：

    insert("ab"); // 插入单词ab
    
    // 此时Trie结构如下：
    
              root
             a/
            (a)
           b/
          (ab)
    
    search("a");      // -> false
    startsWith("a");  // -> true
    search("ab");     // -> true
    startsWith("ab"); // -> true

    我们只向字典中插入了一个"ab"，因此search单词"a"是没有的，即search("a")=false，但是"ab"确实以"a"为前缀，因此startsWith("a")=true。由于字典中有"ab"，且"ab"也是以"ab"为前缀，因此search("ab")=true，startsWith("ab")=true。

###解题思路
主要方面有两个，**如何存放后继结点**和**如何表示到某一结点处的单词存在于字典中**。

由于题目限定了输入仅包括小写字母`a-z`，因此我们可以用`0-25`来简单映射`a-z`，维护一个数组`nodes[26]`来存储后继结点的指针，这就解决了第一个问题；另外我们给每个结点一个`isLast`的属性，当其为true时表示到此为止的单词存在于字典中，相反如果为false，表示这个结点仅仅是某个单词的前缀部分中的一个字符。

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
 * 字典树
 */
class Trie {
public:
    Trie() {
        root = new TrieNode();
        root->isLast = true; // 空串""存在于字典中
    }

    /** 
     * insert a word into the trie. 插入一个单词
     * @param word : the word that will be inserted into the trie. 要插入的单词
     */
    void insert(string word) {
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
     * Returns if the word is in the trie. 查找trie中是否存在某个单词
     * @param word : the word to be searched. 要查找的单词
     * @return 存在返回true，否则false
     */
    bool search(string word) {
        if (word == "") return true;
        char c = word[0];
        TrieNode* tmp = root->nodes[c - 'a'];
        word = word.substr(1);
        while (tmp != NULL && word != "") { // 沿路径查找
            c = word[0];
            tmp = tmp->nodes[c - 'a'];
            word = word.substr(1);
        }
        if (tmp == NULL) return false; // 如果没有后继结点，查找失败
        return tmp->isLast; // 有后继结点，且isLast，查找成功
    }

    /**
     * Returns if there is any word in the trie that starts with the given prefix.
     * 查找是否存在以prefix为前缀的单词
     * @param prefix : the given prefix. 给定的前缀
     * @return 存在返回true，否则false
     */
    bool startsWith(string prefix) {
        if (prefix == "") return true;
        char c = prefix[0];
        TrieNode* tmp = root->nodes[c - 'a'];
        prefix= prefix.substr(1);
        while (tmp != NULL && prefix!= "") { // 沿路径查找
            c = prefix[0];
            tmp = tmp->nodes[c - 'a'];
            prefix= prefix.substr(1);
        }
        if (tmp == NULL) return false; // 如果没有后继结点，查找失败
        else return true; // 查找成功
    }

private:
    TrieNode* root;
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/208/cpp/trie.cpp](https://github.com/Orange1991/leetcode/blob/master/208/cpp/trie.cpp)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47659235

---
2015/8/14

