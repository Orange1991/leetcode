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
    vector<string> prefix;
    WordNode(string s, int n, vector<string> p) : word(s), step(n), prefix(p) { }
};

class Solution {
public:
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        /* 广度优先遍历 
         * 遍历到的新点入队列queue */
        queue<WordNode*> queue;
        vector<string> tmpVec;
        tmpVec.push_back(start);
        queue.push(new WordNode(start, 1, tmpVec));
        unordered_map<string, int> stepMap;
        stepMap.insert(make_pair(start, 1));
        vector<vector<string> > ret;
        int min = -1;
 
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
                    // 中获取begin到tmp的距离并加1
                    distance = tmpWord->step + 1; 

                    // 如果新字符串就是end
                    if (sbStr == end) {
                        // 如果这是第一次转换到end，记录最短距离
                        if (min < 0) min = distance;
                        // 如果距离大于最短距离，则自此之后的所有解都不是最短距离，直接返回结果集
                        else if (distance > min) return ret;
                        // 执行到此，说明是符合最短距离的可行解，添加到ret中
                        vector<string> last = tmpWord->prefix;
                        last.push_back(end);
                        ret.push_back(last);
                    }

                    // 如果字典中有这个字符串
                    if (dict.find(sbStr) != dict.end()) {
                        // 如果这个字符串是第一次被遍历到
                        // 则将其作为新字符串添加到队列queue中，并添加到stepMap中&记录距离
                        if (stepMap.find(sbStr) == stepMap.end()) {
                            vector<string> tmpStep = tmpWord->prefix;
                            tmpStep.push_back(sbStr);
                            queue.push(new WordNode(sbStr, distance, tmpStep));
                            stepMap.insert(make_pair(sbStr, distance));
                        } else if (distance == stepMap.find(sbStr)->second) {
                            // 如果不是第一次被遍历到，但是其step与当上一次被遍历到时的step相等
                            // 则将其作为新的字符串添加到队列queue中
                            vector<string> tmpStep = tmpWord->prefix;
                            tmpStep.push_back(sbStr);
                            queue.push(new WordNode(sbStr, distance, tmpStep));
                        }
                    }
                }
            }
        }

        return ret;
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

void out(string start, string end, unordered_set<string> &dict, vector<vector<string> > strs) {
    cout << "start: " << start << endl;
    cout << "end: " << end << endl;
    cout << "dictionary: [";
    unordered_set<string>::iterator s = dict.begin(), e = dict.end();
    for(++s; s != e; ++s) {
        cout << *s << ",";
    }
    cout << *(dict.begin()) << "]" << endl;
    for (int i = 0, len = strs.size(); i < len; ++i) {
        cout << "[";
        for (int j = 0; j < strs[i].size() - 1; ++j) {
            cout << strs[i][j] << ",";
        }
        cout << strs[i][strs[i].size() - 1] << "]" << endl;
    }
    cout << endl;
}

int main(void) {
    string startWord = "hit", endWord = "cog";
    unordered_set<string> dict;
    dict.insert("hot");
    dict.insert("dot");
    dict.insert("dog");
    dict.insert("lot");
    dict.insert("log");

    Solution s;
    vector<vector<string> > ret = s.findLadders(startWord, endWord, dict);
    out(startWord, endWord, dict, ret);

    startWord = "a";
    endWord = "b";
    dict.clear();
    dict.insert("a");
    dict.insert("b");
    dict.insert("c");

    ret = s.findLadders(startWord, endWord, dict);
    out(startWord, endWord, dict, ret);

    startWord = "aaa";
    endWord = "cbb";
    dict.clear();
    dict.insert("aba");
    dict.insert("aab");
    dict.insert("abb");

    ret = s.findLadders(startWord, endWord, dict);
    out(startWord, endWord, dict, ret);

    return 0;
}
