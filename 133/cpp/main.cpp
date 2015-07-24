#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

/**
 * Definition for undirected graph.
 */
struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
    /** 
     * 无向图克隆
     */
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL) return NULL;

        // 复制生成的图
        UndirectedGraphNode *graph; 
        // 用于存放复制生成的新结点的label极其指针
        unordered_map<int, UndirectedGraphNode*> map; 
        // 用于存放原图中待复制neighbors字段的结点的指针
        queue <UndirectedGraphNode*> queue; 
        
        /**
         * 复制一个结点分为两步
         * 1.在内存中生成一个结点，并初始化其label字段
         * 2.生成其neighbors字段
         * 以下过程中，在复制结点时，先完成第一步，
         * 然后把原结点放入队列中，当再次从队列中取出该结点时再复制其neighbors
         */

        /* 复制第一个结点（仅在内存中生成该结点，其neighbors字段在后面生成） */
        queue.push(node); // 第一个结点放入队列
        graph = new UndirectedGraphNode(node->label); // 生成第一个结点，初始化label字段
        map.insert(make_pair(node->label, graph)); // 复制好的第一个结点放入map

        
        UndirectedGraphNode *cur, *nodeInMap;
        unordered_map<int, UndirectedGraphNode*>::iterator it;
        while (!queue.empty()) {
            cur = queue.front(); // 获取队首结点
            nodeInMap = map.find(cur->label)->second; // 找到该结点在map中的复制结点（指针）
            queue.pop();
            for (UndirectedGraphNode *neighbor : cur->neighbors) { // 遍历其neighbors
                it = map.find(neighbor->label);
                if (it == map.end()) { // 如果其某个neighbor还没有复制过，则复制该结点
                    // 在内存中新建结点
                    UndirectedGraphNode *newNode = new UndirectedGraphNode(neighbor->label);
                    // 添加neighbor到队列中以备复制neighbors字段
                    queue.push(neighbor);
                    // 新结点指针加入map
                    map.insert(make_pair(neighbor->label, newNode));
                    // 复制neighbor到结点nodeInMap的neighbors中
                    nodeInMap->neighbors.push_back(newNode);
                } else { // 如果某neighbor已经复制过，直接获取其指针并添加到复制结点nodeInMap的neighbors中
                    nodeInMap->neighbors.push_back(it->second);
                }
            }
        }

        return graph;
    }

};

/** 打印无向图 */
void out(UndirectedGraphNode *graph) {
    queue<UndirectedGraphNode *> queue;
    unordered_set<int> set;

    queue.push(graph);
    UndirectedGraphNode *cur;
    while (!queue.empty()) {
        cur = queue.front();
        queue.pop();
        cout << cur->label;
        set.insert(cur->label);
        for (UndirectedGraphNode *neighbor : cur->neighbors) {
            cout << "," << neighbor->label;
            if (set.find(neighbor->label) == set.end()) {
                set.insert(neighbor->label);
                queue.push(neighbor);
            }
        }
        cout << "#";
    }

    cout << endl;
}

/** 释放无向图内存 */
void free(UndirectedGraphNode *graph) {
    queue<UndirectedGraphNode *> queue;
    unordered_set<int> set;
    vector<UndirectedGraphNode*> list;
 
    queue.push(graph);
    UndirectedGraphNode *cur;
    while (!queue.empty()) {
        cur = queue.front();
        queue.pop();
        set.insert(cur->label);
        for (UndirectedGraphNode *neighbor : cur->neighbors) {
            if (set.find(neighbor->label) == set.end()) {
                set.insert(neighbor->label);
                queue.push(neighbor);
            }
        }
        list.push_back(cur);
    }

    for (UndirectedGraphNode *tmp : list) delete(tmp);
}

int main() {
    UndirectedGraphNode *n0, *n1, *n2;
    n0 = new UndirectedGraphNode(0);    
    n1 = new UndirectedGraphNode(1);    
    n2 = new UndirectedGraphNode(2); 

    n0->neighbors.push_back(n1);
    n0->neighbors.push_back(n2);
    n1->neighbors.push_back(n0);
    n1->neighbors.push_back(n2);
    n2->neighbors.push_back(n0);
    n2->neighbors.push_back(n1);
    n2->neighbors.push_back(n2);

    Solution s;
    UndirectedGraphNode *copy = s.cloneGraph(n0);   
    out(n0); 
    out(copy);

    free(n0);
    free(copy);

    return 0;
}
