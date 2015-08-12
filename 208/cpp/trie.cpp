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
    // Initialize your data structure here.
    TrieNode() {
        for (int i = 0; i < NODES_SIZE; ++i)
            nodes[i] = NULL;
    }
    TrieNode(bool isLast) : isLast(isLast) {
        TrieNode();
    }
};

/**
 * 字典树
 */
class Trie {
public:
    Trie() {
        root = new TrieNode();
        root->isLast = true;
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode* tmp = root;
        while (word != "") {
            char c = word[0];
            word = word.substr(1);
            if (tmp->nodes[c - 'a'] == NULL) {
                TrieNode* newNode = new TrieNode(false);
                tmp->nodes[c - 'a'] = newNode;
            }
            tmp = tmp->nodes[c - 'a'];
        }
        if (!tmp->isLast) tmp->isLast = true;
    }

    // Returns if the word is in the trie.
    bool search(string word) {
        if (word == "") return true;
        char c = word[0];
        TrieNode* tmp = root->nodes[c - 'a'];
        word = word.substr(1);
        while (tmp != NULL && word != "") {
            c = word[0];
            tmp = tmp->nodes[c - 'a'];
            word = word.substr(1);
        }
        if (tmp == NULL) return false;
        return word == "" && tmp->isLast;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        if (prefix == "") return true;
        char c = prefix[0];
        TrieNode* tmp = root->nodes[c - 'a'];
        prefix= prefix.substr(1);
        while (tmp != NULL && prefix!= "") {
            c = prefix[0];
            tmp = tmp->nodes[c - 'a'];
            prefix= prefix.substr(1);
        }
        if (tmp == NULL) return false;
        return prefix == "";
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
int main() {
    Trie trie;
    trie.insert("abc");
    cout << "abc" << endl;
    trie.insert("abcd");
    cout << "abcd" << endl;
    trie.insert("ad");
    cout << "ad" << endl;
    trie.insert("ab");
    cout << "ab" << endl;

    cout << "search ab : " << trie.search("ab") << endl;
    cout << "search abc : " << trie.search("abc") << endl;
    cout << "search abcd : " << trie.search("abcd") << endl;
    cout << "search abcde : " << trie.search("abcde") << endl;
    cout << "prefix ab : " << trie.startsWith("ab") << endl;
    cout << "prefix abc : " << trie.startsWith("abc") << endl;
    cout << "prefix abcd : " << trie.startsWith("abcd") << endl;
    cout << "prefix abcde : " << trie.startsWith("abcde") << endl;
    return 0;
}
