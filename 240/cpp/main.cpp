#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * 二维数组中查找某元素
     * 查找成功返回ture，失败返回false
     * 二维数组每一行的数据递增，每一列的数据递增
     * @param matrix 二维数组
     * @param target 查找对象
     */
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return false;

        // 从右上角开始查找
        int matrixRowSize = matrix.size(), matrixColSize = matrix[0].size();
        int x = 0, y = matrixColSize - 1, diff;

        while (x < matrixRowSize && y > -1) {
            diff = matrix[x][y] - target;
            if (diff == 0) return true; // 如果查找成功，直接返回true
            else if (diff > 0) --y;     // 如果当前元素比target大，在其左侧区域查找
            else ++x;                   // 如果当前元素比target小，在其下方区域查找
        }

        // 执行至此，说明查找失败
        return false;
    }
};

int main() {
    vector<vector<int> > matrix;
    vector<int> line1; line1.push_back(1); line1.push_back(4); line1.push_back(7); line1.push_back(11); line1.push_back(15);
    vector<int> line2; line2.push_back(2); line2.push_back(5); line2.push_back(8); line2.push_back(12); line2.push_back(19);
    vector<int> line3; line3.push_back(3); line3.push_back(6); line3.push_back(9); line3.push_back(16); line3.push_back(22);
    vector<int> line4; line4.push_back(10); line4.push_back(13); line4.push_back(14); line4.push_back(17); line4.push_back(24);
    vector<int> line5; line5.push_back(18); line5.push_back(21); line5.push_back(23); line5.push_back(26); line5.push_back(30);
    matrix.push_back(line1);
    matrix.push_back(line2);
    matrix.push_back(line3);
    matrix.push_back(line4);
    matrix.push_back(line5);

    Solution s;
    if (s.searchMatrix(matrix, 0)) cout << "Find 0." << endl; else cout << "Can't find 0." << endl;
    if (s.searchMatrix(matrix, 18)) cout << "Find 18." << endl; else cout << "Can't find 18." << endl;

    return 0;
}
