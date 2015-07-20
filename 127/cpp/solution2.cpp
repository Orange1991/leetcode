#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

class WordNode {
public:
    string word;
    int step;
    WordNode(string s, int n) : word(s), step(n) { }
};

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& dict) {      
        /* 广度优先遍历 
         * 遍历到的新点入队列queue
         * 同时将源点beginWord到新点的距离存在visited中 */
        queue<WordNode*> queue;
        queue.push(new WordNode(beginWord, 1));
        unordered_set<string> visited;
        visited.insert(beginWord);

        string sbStr, tmp;
        WordNode *tmpWord;
        int len, distance;
        while (!queue.empty()) {
            // 获取队首元素
            tmpWord = queue.front();
            tmp = tmpWord->word;
            queue.pop();
            // 依次将字符串的某一位替换为a-z中的字母
            len = tmp.size();
            for (int i = 0; i < len; ++i) {
                for (char c = 'a'; c <= 'z'; ++c) {
                    // 如果替换后字符串没有变化，则跳过此次尝试
                    if (tmp[i] == c) continue;

                    // 拷贝原字符串，并修改某一位为某一个字符
                    sbStr = tmp;
                    sbStr[i] = c;
                    // 从visited中获取beginWord到tmp的距离并加1
                    distance = tmpWord->step + 1; 

                    // 如果新字符串就是endWord，返回距离
                    if (sbStr == endWord)
                        return distance;

                    // 如果字典中有这个字符串，并且这个字符串是第一次被遍历到
                    // 则将其作为新字符串添加到队列queue中，并添加到visited中&记录距离
                    if (dict.find(sbStr) != dict.end() && visited.find(sbStr) == visited.end()) {
                        queue.push(new WordNode(sbStr, distance));
                        visited.insert(sbStr);
                    }
                }
            }
        }

        // 执行至此，说明图为非连通图，beginWord和endWord之间不能转换
        return 0;

    }

private:
    /** 判定两个字符串的差异度是否为1 */
    bool isOneCharDiff(string str1, string str2) {
        int count = 0, len = str1.size();
        for (int i = 0; i < len; ++i) {
            if (str1[i] != str2[i]) {
                ++count;
                if (count > 1)
                    return false;
            }
        }
        return count == 1;
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
    cout << s.ladderLength(startWord, endWord, dict) << endl;
    
    startWord = "a";
    endWord = "b";
    dict.clear();
    dict.insert("a");
    dict.insert("b");
    dict.insert("c");
    cout << s.ladderLength(startWord, endWord, dict) << endl;

}
