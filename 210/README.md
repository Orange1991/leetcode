#Leetcode 210 Course Schedule II 课程表II

##原题地址
https://leetcode.com/problems/course-schedule-ii/

##题目描述
There are a total of n courses you have to take, labeled from 0 to n - 1.
你需要上n个课程，标记为0~n-1。

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
有些课程有前导课，比如你要上课程0必须先上课程1，我们用一个整数对[0,1]来表示。

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
给出课程的总数和一系列的课程先导关系对，返回可以上完所有的课程的上课顺序。

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
可能存在多种正确的顺序，你只需要返回其中一种即可。如果不可能上完所有课程，返回一个空数组。

For example:
例如：

`2, [[1,0]]`

There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is `[0,1]`
共有2个课程，你需要先上课程0再上课程1，因此正确的顺序是`[0,1]`。

`4, [[1,0],[2,0],[3,1],[3,2]]`

There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is `[0,1,2,3]`. Another correct ordering is`[0,2,1,3]`.
共有4个课程，你需要先上课程1和2再上课程3，而且上完课程0之后才能上课程1和2。因此一种正确的顺序是`[0,1,2,3]`，另一种是`[0,2,1,3]`

Note:
注意：

The input prerequisites is a graph represented by a list of edges, not adjacency matrices. 
输入的先序关系代表着一个图的边，不是邻接矩阵。

Hints:
提示：

> 1. This problem is equivalent to finding if a cycle exists in a directed graph. If a cycle exists, no topological ordering exists and therefore it will be impossible to take all courses.
这个问题等价于判定一个有向图中是否存在环。如果存在环，就不存在拓扑序，也就是不可能上完所有的课程。
> 2. Topological Sort via DFS.
> 拓扑排序可以用深度优先搜索来实现。
> 3. Topological sort could also be done via BFS.
> 拓扑排序可以用广度优先搜索来实现。

**Tags** `Depth-first Search` `Breadth-first Search` `Graph` `Topological Sort`

##解题思路
这个题是[Leetcode 207 Course Schedule](http://blog.csdn.net/smile_watermelon/article/details/47402521)的延伸，解法与其类似，只是多了一个按序添加完成的课程。此处不作过多解释，可以看之前的文章。使用广度优先搜索和深度优先搜索均可实现拓扑排序，最后加一步判断是否存在环，如果存在环则返回空集合。bfs和dfs的区别在于是按照**入度**还是**出度**来考虑问题上。

##代码

###bfs

```
class Solution {
public:
    /** 
     * 完成所有的课程的顺序
     * bfs拓扑排序
     * @param numCourses 课程数量
     * @param prerequisites 课程先序关系
     * @return 能完成返回课程顺序,否则返回空
     */
    vector<int> findOrder(int numCourses, vector<pair<int, int> >& prerequisites) {
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

        /* bfs拓扑排序,依次移除入度为0的点 */
        vector<int> ret;
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) 
            if (degree[i] == 0) q.push(i);
        while (!q.empty()) {
            from = q.front();
            ret.push_back(from); // 课程完成，添加到结果集中
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
                ret.clear();
                break;
            }   

        return ret;
    }   
};
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/210/cpp/bfs.cpp](https://github.com/Orange1991/leetcode/blob/master/210/cpp/bfs.cpp)

###dfs
```
class Solution {
public:
    /** 
     * 完成所有的课程的顺序
     * dfs拓扑排序
     * @param numCourses 课程数量
     * @param prerequisites 课程先序关系
     * @return 能完成返回课程顺序,否则返回空
     */
    vector<int> findOrder(int numCourses, vector<pair<int, int> >& prerequisites) {
        vector<int> heads(numCourses, -1), degree(numCourses, 0), points, args;
        pair<int, int> p;
        int from, to, count = 0, len = prerequisites.size();

        /* 构造有向图,邻接表 */
        for (int i = 0; i < len; ++i) {
            p = prerequisites[i];
            from = p.second;
            to = p.first;
            ++degree[from];
            args.push_back(heads[to]);
            points.push_back(from);
            heads[to] = count++;
        }   

        /* dfs拓扑排序,依次移除出度为0的点 */
        vector<int> ret;
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) 
            if (degree[i] == 0) q.push(i);
        while (!q.empty()) {
            to = q.front();
            ret.push_back(to); // 课程完成添加到结果集中
            q.pop();
            from = heads[to];
            while (from != -1) {
                if(--degree[points[from]] == 0) q.push(points[from]);
                from = args[from];
            }   
        }   

        /* 判定是否所有的点入度都为0,若是则不存在环,否则存在环 */
        for (int i = 0; i < numCourses; ++i)
            if (degree[i] > 0) {
                ret.clear();
                break;
        }   

        /* 逆序 */
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
```

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/210/cpp/dfs.cpp](https://github.com/Orange1991/leetcode/blob/master/210/cpp/dfs.cpp)

##测试数据

    bfs:
    2, [[0,1]] : [1,0]
    2, [[0,1],[1,0]] : You can not finish all the classes.
    4, [[1,0],[2,0],[3,1],[3,2]] : [0,2,1,3]
    6, [[1,0],[2,0],[2,1],[3,2],[4,1],[5,3],[5,0],[5,3],[5,4]] : [0,1,4,2,3,5]

    dfs:
    2, [[0,1]] : [1,0]
    2, [[0,1],[1,0]] : You can not finish all the classes.
    4, [[1,0],[2,0],[3,1],[3,2]] : [0,1,2,3]
    6, [[1,0],[2,0],[2,1],[3,2],[4,1],[5,3],[5,0],[5,3],[5,4]] : [0,1,2,3,4,5]

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47663819

---
2015/8/14
