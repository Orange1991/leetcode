#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
        /* 广度优先遍历 
         * 遍历到的新点入队列queue */
        queue<string> queue;
        queue.push(start);
        unordered_map<string, int> stepMap;
        stepMap.insert(make_pair(start, 1));
 
        string sbStr, tmp;
        int len, distance;
        bool ended = false;
        while (!queue.empty()) {
            // 获取队首元素
            tmp = queue.front();
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
                    distance = stepMap.find(tmp)->second + 1; 

                    // 如果新字符串就是end
                    if (sbStr == end) {
                        queue.push(end);
                        stepMap.insert(make_pair(end, distance));
                        ended = true;
                        break;
                    }

                    // 如果字典中有这个字符串
                    if (dict.find(sbStr) != dict.end()) {
                        // 如果这个字符串是第一次被遍历到
                        // 则将其作为新字符串添加到队列queue中，并添加到stepMap中&记录距离
                        if (stepMap.find(sbStr) == stepMap.end()) {
                            queue.push(sbStr);
                            stepMap.insert(make_pair(sbStr, distance));
                        }
                    }
                }
                if (ended) break;
            }
            if (ended) break;
        }

        vector<vector<string> > ret;
        vector<string> path;
        unordered_map<string, int>::iterator endIt = stepMap.find(end);
        if (endIt != stepMap.end()) backtrack(start, end, endIt->second, path, stepMap, ret);
        return ret;
    }

private:
    void backtrack(string start, string end, int level, vector<string> path, unordered_map<string, int> map, vector<vector<string> > &ret) {
        if (start == end) {
            path.push_back(end);
            ret.push_back(vector<string>(path.rbegin(), path.rend()));
            return;
        }
        unordered_map<string, int>::iterator it = map.find(end), mapEnd = map.end();
        if (it == mapEnd || it->second != level) return;
        path.push_back(end);
        int len = end.size();
        string tmp;
        --level;
        for (int i = 0; i < len; ++i) {
            tmp = end;
            for (char c = 'a'; c <= 'z'; ++c) {
                if (end[i] == c) continue;
                tmp[i] = c;
                it = map.find(tmp);
                if (it != mapEnd && it->second == level) {
                    backtrack(start, tmp, level, path, map, ret);
                }
            }
        }
    }

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

    startWord = "hot";
    endWord = "dog";
    dict.clear();
    dict.insert("hot");
    dict.insert("dog");

    ret = s.findLadders(startWord, endWord, dict);
    out(startWord, endWord, dict, ret);

    return 0;
}
