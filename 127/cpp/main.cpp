#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& dict) {      
        int index = 0;
  
        dict.insert(beginWord);
        dict.insert(endWord);
        unordered_set<string>::iterator x = dict.begin(), y = dict.end();
        for(; x != y; ++x)
            cout << *x << " -> ";

        return dict.size();
    }
};

int main(void) {
    string startWord = "hit", endWord = "cog";
    unordered_set<string> dict;
    dict.insert("hot");
    dict.insert("dot");
    dict.insert("dog");
    dict.insert("lot");
    dict.insert("log");

    Solution s;
    cout << s.ladderLength(startWord, endWord, dict) << endl;;

}
