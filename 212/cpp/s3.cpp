#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

/**
 * 字典树的结点
 */
class TrieNode {
public:
    TrieNode* nodes[26]; // 子结点
    bool isLast;    // 是否存在以此为结尾的单词
    // 初始化
    TrieNode() {
        for (int i = 0; i < 26; ++i) nodes[i] = NULL;
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
        return tmp != NULL && tmp->isLast; // 有后继结点，且isLast，查找成功
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
        return tmp != NULL; // 如果没有后继结点，查找失败，否则查找成功
    }


    /** 释放内存 */
    void free() {
        free(root);
    }

private:
    TrieNode* root;

    void free(TrieNode * node) {
        if (node == NULL) return;
        for (int i = 0; i < 26; ++i)
            free(node->nodes[i]);
        delete(node);
    }
};

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

void test(vector<vector<char> >&board, vector<string>& words) {
    cout << "Given words = [";
    int rows, cols = words.size();
    for (int i = 0; i < cols - 1; ++i)
        cout << words[i] << ",";
    cout << words[cols - 1] << "], and board = " << endl;
    cout << "[" << endl;
    rows = board.size();
    cols = board.size() == 0 ? 0 : board[0].size();
    for (int i = 0; i < rows - 1; ++i) {
        cout << "    [";
        for (int j = 0; j < cols - 1; ++j)
            cout << board[i][j] << ",";
        cout << board[i][cols - 1] << "]," << endl;
    }
    cout << "    [";
    for (int j = 0; j < cols - 1; ++j)
        cout << board[rows - 1][j] << ",";
    cout << board[rows - 1][cols - 1] << "]" << endl << "]" << endl;
    Solution s;
    vector<string> ret = s.findWords(board, words);
    if (ret.size() == 0) {
        cout << "No words found." << endl;
        return;
    }
    cout << "Found words = [";
    cols = ret.size();
    for (int i = 0; i < cols - 1; ++i)
        cout << ret[i] << ",";
    cout << ret[cols - 1] << "]" << endl;
}

int main() {
    vector<vector<char> > board;
    int data[4][4] = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'} 
    };
    for (int i = 0; i < 4; ++i) {
        vector<char> vec;
        for (int j = 0; j < 4; ++j)
            vec.push_back(data[i][j]);
        board.push_back(vec);
    }
    vector<string> strs;
    strs.push_back("oath");
    strs.push_back("pea");
    strs.push_back("eat");
    strs.push_back("rain");
    test(board, strs);

    board.clear();
    vector<char> tmp;
    tmp.push_back('a');
    board.push_back(tmp);
    strs.clear();
    strs.push_back("a");
    test(board, strs);

    tmp.clear();
    board.clear();
    tmp.push_back('a');
    tmp.push_back('a');
    board.push_back(tmp);
    strs.clear();
    strs.push_back("aa");
    test(board, strs);
    
    board.clear();
    int data2[5][6] = {
        {'b','b','a','a','b','a'},
        {'b','b','a','b','a','a'},
        {'b','b','b','b','b','b'},
        {'a','a','a','b','a','a'},
        {'a','b','a','a','b','b'} 
    };
    for (int i = 0; i < 5; ++i) {
        vector<char> vec;
        for (int j = 0; j < 6; ++j)
            vec.push_back(data2[i][j]);
        board.push_back(vec);
    }

    strs.clear();
    strs.push_back("abbbababaa");
    test(board, strs); 

    strs.clear();
    board.clear();
    tmp.clear();
    tmp.push_back('a');
    tmp.push_back('b');
    board.push_back(tmp);
    board.push_back(tmp);
    strs.push_back("a");
    strs.push_back("aa");
    strs.push_back("aaa");
    strs.push_back("aaaa");
    strs.push_back("bbaa");
    strs.push_back("baa");
    test(board, strs);

    return 0;
}
