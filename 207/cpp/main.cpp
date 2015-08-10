#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    /**
     * 能否完成所有的课程
     * 拓扑排序,看有向图是否存在环
     * @param numCourses 课程数量
     * @param prerequisites 课程先序关系
     * @return 能完成返回true,否则false
     */
    bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites) {
        vector<int> heads(numCourses, -1), degree(numCourses, 0), points, args;
        pair<int, int> p;
        int from, to, count = 0, len = prerequisites.size();

        /* 构造有向图,邻接表 */
        for (int i = 0; i < len; ++i) {
            p = prerequisites[i];
            from = p.second;
            to = p.first;
            ++degree[to];
            args.push_back(heads[from]);
            points.push_back(to);
            heads[from] = count++;
        }

        /* 拓扑排序,依次移除入度为0的点 */
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) 
            if (degree[i] == 0) q.push(i);
        while (!q.empty()) {
            from = q.front();
            q.pop();
            to = heads[from];
            while (to != -1) {
                if(--degree[points[to]] == 0) q.push(points[to]);
                to = args[to];
            }
        }

        /* 判定是否所有的点入度都为0,若是则不存在环,否则存在环 */
        for (int i = 0; i < numCourses; ++i)
            if (degree[i] > 0) {
                 return false;
}
        return true;
    }
};

void test(int numCourses, vector<pair<int, int> >& prerequisites) {
    cout << numCourses << ", ";
    int len = prerequisites.size();
    if (len == 0) cout << " no prerequisite : ";
    else {
        cout << "[";
        pair<int, int> p;
        int i;
        for (i = 0; i < len - 1; ++i) {
            p = prerequisites[i];
            cout << "[" << p.first << "," << p.second << "],";
        }
        p = prerequisites[i];
            cout << "[" << p.first << "," << p.second << "]] : ";
    }
    Solution s;
    if (s.canFinish(numCourses, prerequisites))
        cout << "You can finish all the classes." << endl;
    else
       cout << "You can not finish all the classes." << endl;
}

void testFileData(const char* file) {
    ifstream is;
    is.open(file, ifstream::in);
    if (!is) {
        cout << "Unable to open ";
        cout << file << endl;
        return;
    }
    int n, from, to;
    char c;
    vector<pair<int, int> > p;
    is >> n >> c >> c;
    while (c != ']') {
        is >> c >> to >> c >> from >> c >> c;
        p.push_back(make_pair(to, from));
    }
    test(800, p);
}

int main() {
    int n;
    vector<pair<int, int> > p;
    p.push_back(make_pair(0, 1));
    test(2, p);

    p.push_back(make_pair(1, 0));
    test(2, p);

    p.clear();
    p.push_back(make_pair(1, 0));
    p.push_back(make_pair(2, 0));
    p.push_back(make_pair(2, 1));
    p.push_back(make_pair(3, 2));
    p.push_back(make_pair(4, 1));
    p.push_back(make_pair(5, 3));
    p.push_back(make_pair(5, 0));
    p.push_back(make_pair(5, 3));
    p.push_back(make_pair(5, 4));
    test(6, p);

    testFileData("./data.txt");
    return 0;
}
