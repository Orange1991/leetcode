#Leetcode 200 Number of Islands 岛的个数 

##原题地址
https://leetcode.com/problems/number-of-islands/

##题目描述
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
给出一个2D的地图，由陆地(1)和水(0)组成，数出岛的个数．一个岛被水环绕并且与相邻的陆地连接．你可以假设方阵的四周被水环绕．

Example 1:

    11110
    11010
    11000
    00000
Answer: 1

Example 2:

    11000
    11000
    00100
    00011
Answer: 3

**Tags** `Breadth-first Search` `Depth-first Search`

##解题思路
采用广度优先遍历的方法还是很容易解决这个问题的，我们尝试遍历所有的点，如果一个点是陆地且从未遍历过，则认为发现了新岛屿，在发现了新岛屿后使用广度优先的方式扩展该岛屿以防止重复计数．

##算法
> 1. 遍历每一个结点，如果某结点是陆地且未访问过，岛数目加1，修改未访问标志位，然后把该点放入队列中，以备扩展岛屿使用，进入2
> 2. 队列不为空时，取出点，然后尝试对其上下左右的四个点进行扩展，如果其邻点是陆地且未访问过，则修改标志位并入队列．第2步运行结束时一个新岛的扩展结束，回到1．
> 3. 1中提到的遍历结束时，程序结束．

##代码　cpp

```
class Solution {
public:
    /** 计算岛屿的个数 */
    int numIslands(vector<vector<char> >& grid) {
        int count = 0, rows = grid.size(), cols = rows > 0 ? grid[0].size() : 0;
        if (rows == 0 || cols == 0) return count;

        // 记录是否访问过
        vector<vector<bool> > visited(rows, vector<bool>(cols, false));
        // 用于遍历某一个岛相连接的所有岛
        queue<int> q;
        // 用于查看某结点四周的结点
        int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
        int x = 0, y = 0, xx = 0, yy = 0;
        /* 遍历所有结点 */
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) { 
                    // 如果一个结点是1且没有访问过，则为新的小岛
                    q.push(i); // 小岛入队列
                    q.push(j);
                    visited[i][j] = true; // 修改访问标志
                    ++count; // 小岛数量加1
                    while (!q.empty()) { // 修改与当前小岛相连的所有点的标志位
                        x = q.front();   // 广度优先遍历
                        q.pop();
                        y = q.front();
                        q.pop();
                        for (int k = 0; k < 4; ++k) { // 遍历某点的上下左右4个点
                            xx = x + dx[k];
                            yy = y + dy[k];
                            if (xx < 0 || xx >= rows || yy < 0 || yy >= cols)
                                continue; // 越界，跳过
                            if (grid[xx][yy] == '1' && !visited[xx][yy]) {
                                // 如果未曾访问过，修改访问标志，并加到队列中
                                visited[xx][yy] = true;
                                q.push(xx);
                                q.push(yy);
                            }
                        }
                    }
                }
            }

        return count;
    }
};
```
> 完整代码　[https://github.com/Orange1991/leetcode/blob/master/200/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/200/cpp/main.cpp)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47316935

---
2015/8/6
