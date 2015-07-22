#Surrounded Regions
##原题地址
https://leetcode.com/problems/surrounded-regions/

##题目描述
Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'.
给出一个2D图板，又字符'X'和'O'组成，捕捉被'X'包围的区域。

A region is captured by flipping all 'O's into 'X's in that surrounded region.
将被'X'包围的区域全部置为'X'就是对这个区域进行“逮捕”。

For example,
例如：

    X X X X
    X O O X
    X X O X
    X O X X

After running your function, the board should be:
在逮捕之后，应该变成：

    X X X X
    X X X X
    X X X X
    X O X X

##解题思路
广度优先遍历

> 1. 最外层如果有O的话一定不会被包围
> 2. 如果一个O不会被包围，那他的周围（上下左右）的O也不会被包围。

##算法描述
> 1. 拷贝原数据为copy
> 2. 将周围一圈中的'O'入栈queue
> 3. 原始数据的中间部分（除去周围一圈）全部置为'X'
> 4. 当queue不为空时，取出栈顶元素，并判定其上下左右的4个位置的原始数据（copy中存储着原始数据）是否为'O'，如果是则将其置为'O'

注意：为了防止重复访问，需要右标志位visited[x][y]来记录一个点是否已访问过。

空间复杂度O(n)，时间复杂度O(n)。

##代码 cpp

```
class MyPoint {
public:
    int x;
    int y;
    MyPoint(int x, int y) : x(x), y(y) {}
};

class Solution {
public:
    void solve(vector<vector<char> > &board) {
        int rowSize = board.size(), colSize = rowSize > 0 ? board[0].size() : 0;
        if (rowSize <= 2 || colSize <= 2) return;

        vector<vector<char> > copy = vector<vector<char> >(board.begin(), board.end());
        vector<vector<bool> > visited = vector<vector<bool> >(rowSize, vector<bool>(colSize, false));
 
        --rowSize;
        --colSize;
        queue<MyPoint *> q;
        if (copy[0][0] == 'O') {
            q.push(new MyPoint(0, 0));
            visited[0][0] = true;
        }
        if (copy[0][colSize] == 'O') {
            q.push(new MyPoint(0, colSize));
            visited[0][colSize] = true;
        }
        if (copy[rowSize][0] == 'O') {
            q.push(new MyPoint(rowSize, 0));
            visited[rowSize][0] = true;
        }
        if (copy[rowSize][colSize] == 'O') {
            q.push(new MyPoint(rowSize, colSize));
            visited[rowSize][colSize] = true;
        }
        for (int i = 1; i < colSize; ++i) {
            if (copy[0][i] == 'O')
                q.push(new MyPoint(0, i));
            if (copy[rowSize][i] == 'O')
                q.push(new MyPoint(rowSize, i));
        }
        for (int i = 1; i < rowSize; ++i) {
            if (copy[i][0] == 'O')
                q.push(new MyPoint(i, 0));
            if (copy[i][colSize] == 'O')
                q.push(new MyPoint(i, colSize));
        }
        
        for (int i = 1; i < rowSize; ++i)
            for (int j = 1; j < colSize; ++j)
                board[i][j] = 'X';
        
        MyPoint *tmp;
        int dalx[] = {-1, 0, 1, 0}, daly[] = {0, 1, 0, -1};
        int x, y;
        while (!q.empty()) {
            tmp = q.front();
            q.pop();
            
            for (int i = 0; i < 4; ++i) {
                x = tmp->x + dalx[i];
                y = tmp->y + daly[i];
                if (x < 1 || y < 1 || x > rowSize || y > colSize)
                    continue;
                if (copy[x][y] == 'O' && !visited[x][y]) {
                    board[x][y] = 'O';
                    visited[x][y] = true;
                    q.push(new MyPoint(x, y));
                }                   
            }
            delete(tmp);
        }
    }
};
```
> 完整代码[https://github.com/Orange1991/leetcode/blob/master/130/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/130/cpp/main.cpp)

##运行情况
Status : Accept
Time : 20ms

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47010835

---
2015/7/22
