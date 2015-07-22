#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Point {
public:
    int x;
    int y;
    Point(int x, int y) x(x), y(y) : {}
}

class Solution {
public:
    void solve(vector<vector<char> >& board) {
        vector<vector<char> > copy = vector<vector<char> >(board.begin(), board.end());
        queue<Point *> q;
        int rowSize = board.size(), colSize = board.size() > 0 ? board[0].size() : 0;
        if (rowSize <= 2 || colSize <= 2) return;

        if (board[0][0] == 'O')
            q.push(new Point(0, 0));
        if (board[0][colSize - 1] == 'O')
            q.push(new Point(0, colSize - 1));
        if (board[rowSize - 1][0] == 'O')
            q.push(new Point(rowSize - 1, 0));
        if (board[rowSize - 1][colSize - 1] == 'O')
            q.push(new Point(rowSize - 1, colSize - 1));

        for (int i = 1; i < colSize - 1; ++i) {
            if (board[0][i] == 'O')
                q.push(new Point(0, i));
            if (board[rowSize - 1][i] == 'O')
                q.push(new Point(rowSize - 1, i));
        }

        for (int i = 1; i < rowSize - 1; ++i) {
            if (board[i][0] == 'O')
                q.push(new Point(i, 0));
            if (board[i][rowSize - 1] == 'O')
                q.push(new Point(i, rowSize - 1));
        }
    }
};
