#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct MyPoint {
    int x;
    int y;
    MyPoint(int x, int y) : x(x), y(y) { }
};

class Solution {
public:
    /** 计算岛屿的个数 */
    int numIslands(vector<vector<char> >& grid) {
        int count = 0, rows = grid.size(), cols = rows > 0 ? grid[0].size() : 0;
        if (rows == 0 || cols == 0) return count;

        // 记录是否访问过
        vector<vector<bool> > visited(rows, vector<bool>(cols, false));
        // 用于遍历某一个岛相连接的所有岛
        queue<MyPoint*> q;
        // 用于查看某结点四周的结点
        int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
        int x = 0, y = 0, xx = 0, yy = 0;
        MyPoint *p;
        /* 遍历所有结点 */
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) { 
                    // 如果一个结点是1且没有访问过，则为新的小岛
                    q.push(new MyPoint(i, j)); // 小岛入队列
                    visited[i][j] = true; // 修改访问标志
                    ++count; // 小岛数量加1
                    while (!q.empty()) { // 修改与当前小岛相连的所有点的标志位
                        p = q.front();   // 广度优先遍历
                        q.pop();
                        x = p->x; 
                        y = p->y;
                        delete(p);
                        for (int k = 0; k < 4; ++k) { // 遍历某点的上下左右4个点
                            xx = x + dx[k];
                            yy = y + dy[k];
                            if (xx < 0 || xx >= rows || yy < 0 || yy >= cols)
                                continue; // 越界，跳过
                            if (grid[xx][yy] == '1' && !visited[xx][yy]) {
                                // 如果未曾访问过，修改访问标志，并加到队列中
                                visited[xx][yy] = true;
                                q.push(new MyPoint(xx, yy));
                            }
                        }
                    }
                }
            }

        return count;
    }
};

void test(vector<vector<char> > grid) {
    int rows = grid.size(), cols = rows > 0 ? grid[0].size() : 0;
    if (rows == 0 || cols == 0)
        cout << "Empty datas." << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << grid[i][j];
        cout << endl;
    }
    Solution s;
    int count = s.numIslands(grid);
    if (count <= 1)
        cout << "There is " << count << " island." << endl;
    else
        cout << "There are " << count << " islands." << endl;
}
int main() {
    vector<vector<char> > grid;
    vector<char> tmp;
    tmp.push_back('1'); tmp.push_back('1'); tmp.push_back('1'); tmp.push_back('1'); tmp.push_back('0');
    grid.push_back(tmp);
    tmp.clear();
    tmp.push_back('1'); tmp.push_back('1'); tmp.push_back('0'); tmp.push_back('1'); tmp.push_back('0');
    grid.push_back(tmp);
    tmp.clear();
    tmp.push_back('1'); tmp.push_back('1'); tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('0');
    grid.push_back(tmp);
    tmp.clear();
    tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('0');
    grid.push_back(tmp);
    test(grid);

    grid.clear();
    tmp.clear();
    tmp.push_back('1'); tmp.push_back('1'); tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('0');
    grid.push_back(tmp);
    tmp.clear();
    tmp.push_back('1'); tmp.push_back('1'); tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('0');
    grid.push_back(tmp);
    tmp.clear();
    tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('1'); tmp.push_back('0'); tmp.push_back('0');
    grid.push_back(tmp);
    tmp.clear();
    tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('0'); tmp.push_back('1'); tmp.push_back('1');
    grid.push_back(tmp);
    test(grid);

    return 0;
}
