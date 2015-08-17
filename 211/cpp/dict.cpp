#include <iostream>

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

void add(WordDictionary& dict, string s) {
    dict.addWord(s);
    cout << "    addWord(\"" << s << "\")" << endl;
}

void search(WordDictionary& dict, string s) {
    cout << "    search(\"" << s << "\") -> ";
    if (dict.search(s)) cout << "true" << endl;
    else cout << "false" << endl;
}

// Your WordDictionary object will be instantiated and called as such:
// WordDictionary wordDictionary;
// wordDictionary.addWord("word");
// wordDictionary.search("pattern");
int main() {
    WordDictionary dict;
    add(dict, "bad");
    add(dict, "dad");
    add(dict, "mad");
    search(dict, "pad");
    search(dict, "bad");
    search(dict, ".ad");
    search(dict, "b..");
    dict.free();

    cout << endl;

    WordDictionary d;
    add(d, "at");
    add(d, "and");
    add(d, "an");
    add(d, "add");

    search(d, "a");
    search(d, ".at");

    add(d, "bat");
    search(d, ".at");
    search(d, "an.");
    search(d, "a.d.");
    search(d, "b.");
    search(d, "a.d");
    search(d, ".");
    d.free();

    return 0;
}
