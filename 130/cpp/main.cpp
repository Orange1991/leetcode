#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Point {
public:
    int x;
    int y;
    Point(int x, int y) : x(x), y(y) {}
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
        queue<Point *> q;
        if (copy[0][0] == 'O') {
            q.push(new Point(0, 0));
            visited[0][0] = true;
        }
        if (copy[0][colSize] == 'O') {
            q.push(new Point(0, colSize));
            visited[0][colSize] = true;
        }
        if (copy[rowSize][0] == 'O') {
            q.push(new Point(rowSize, 0));
            visited[rowSize][0] = true;
        }
        if (copy[rowSize][colSize] == 'O') {
            q.push(new Point(rowSize, colSize));
            visited[rowSize][colSize] = true;
        }
        for (int i = 1; i < colSize; ++i) {
            if (copy[0][i] == 'O')
                q.push(new Point(0, i));
            if (copy[rowSize][i] == 'O')
                q.push(new Point(rowSize, i));
        }
        for (int i = 1; i < rowSize; ++i) {
            if (copy[i][0] == 'O')
                q.push(new Point(i, 0));
            if (copy[i][colSize] == 'O')
                q.push(new Point(i, colSize));
        }
        
        for (int i = 1; i < rowSize; ++i)
            for (int j = 1; j < colSize; ++j)
                board[i][j] = 'X';
        
        Point *tmp;
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
                // 继续
                
            }
            delete(tmp);
        }
    }
};

int main() {
    return 0;
}
