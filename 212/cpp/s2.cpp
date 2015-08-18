#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

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

    /**
     * 查找单词
     * @param board 单词构造库
     * @param 查找成功的单词
     */
    vector<string> findWords(vector<vector<char> >& board) {
        int rows = board.size(), cols = board.size() == 0 ? 0 : board[0].size();
        vector<vector<bool> > used(rows, vector<bool>(cols, false));
        vector<string> ret;
        unordered_set<string> searched;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                findWords(searched, board, root, rows, cols, i, j, "", ret, used);
        return ret;
    }
private:
    TrieNode* root;
    void free(TrieNode * node) {
        if (node == NULL) return;
        for (int i = 0; i < node->NODES_SIZE; ++i)
            free(node->nodes[i]);
        delete(node);
    }
    void findWords(unordered_set<string> &searched, vector<vector<char> >& board, TrieNode* node, int& rows, int& cols, int x, int y, 
            string prefix, vector<string>& ret, vector<vector<bool> > used) {
        if (searched.find(prefix) != searched.end()) return;
        if (used[x][y]) return;
        char c = board[x][y];
        if (node->nodes[c - 'a'] == NULL) {
            searched.insert(prefix + c);
            return;
        }    
        else if (node->nodes[c - 'a']->isLast 
                && find(ret.begin(), ret.end(), prefix + c) == ret.end()) {
            ret.push_back(prefix + c); 
        }
        used[x][y] = true;
        int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
        int xx, yy;
        for (int i = 0; i < 4; ++i) {
            xx = x + dx[i];
            yy = y + dy[i];
            if (xx < 0 || xx >= rows || yy < 0 || yy >= cols)
                continue;
            findWords(searched, board, node->nodes[c - 'a'], rows, cols, xx, yy, prefix + c, ret, used);
        }
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char> >& board, vector<string>& words) {
        Trie trie;
        vector<string> ret;
        for (vector<string>::iterator it = words.begin(), end = words.end(); it != end; ++it)
            trie.insert(*it);
        ret = trie.findWords(board);
        trie.free();
        return ret;
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
