#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, unordered_set<string>& dict) {      
        /* 添加所有字符串到map */
        unordered_map<string, int> map;
        int index = 0;
        string tmp;
        map.insert(make_pair(beginWord, index++));
        map.insert(make_pair(endWord, index++));

        if (dict.find(beginWord) != dict.end())
            dict.erase(beginWord);
        if (dict.find(endWord) != dict.end())
            dict.erase(endWord);

        for(unordered_set<string>::iterator it = dict.begin(), itEnd = dict.end(); it != itEnd; ++it) {
            map.insert(make_pair(*it, index++));
        }

        /* 完成下标到字符串的映射 */
        vector<string> list(map.size());
        for (unordered_map<string, int>::iterator it = map.begin(), end = map.end(); it != end; ++it) {
            cout << it->second << "-->" << it->first << endl;            
            list[it->second] = it->first;
        }
// 往上都测试过了，没问题

        /* 构造无向图的邻接表 */
/*        int len = list.length;
        vector<int> head = new vector<int>(len);
        int indexOfArgNode = 0;
        vector<int> args, p;
        for (int i = 0; i < len; ++i) {
            heads[i] = -1;
        }
        for (int i = 0; i < len - 1; ++i) {
            for (int j = i + 1; j < len; ++j) {
                if (diff(list[i], list[j]) == 1) {
                    args.add(heads[i]);
                    p.add(j);
                    heads[i] = indexOfArgNode++;
                    args.add(heads[j]);
                    p.add(i);
                    heads[j] = indexOfArgNode++;
                }
            }
        }
  */      
        /* 广度优先遍历 */
  /*      int queue[] = new int[len], queCur = 0, queEnd = 0;
        boolean[] visited = new boolean[len];
        int[] distance = new int[len];
        for (int i = 0; i < len; ++i) {
            visited[i] = false;
            distance[i] = 0;
        }
        queue[queEnd++] = 0;
        visited[0] = true;
        int node, target;
        while (queCur < queEnd) {
            node = heads[queue[queCur]];
            while (node != -1) {
                target = p.get(node);
                if (!visited[target]) {
                    visited[target] = true;
                    queue[queEnd++] = target;
                    distance[target] = distance[queue[queCur]] + 1;
                }
                node = args.get(node);
            }
            ++queCur;
        }

        return visited[1] ? distance[1] + 1 : 0;
*/return 0;
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

}
