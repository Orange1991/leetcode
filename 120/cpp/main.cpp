#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * 计算三角从上至下最小和
     */
    int minimumTotal(vector<vector<int> > &triangle) {
        vector<int> minNums = triangle[triangle.size() - 1];
        for (int i = triangle.size() - 2; i > - 1; --i)
            for (int j = 0; j <= i; ++j)
                minNums[j] = (minNums[j] < minNums[j + 1] ? minNums[j] : minNums[j + 1])
                        + triangle[i][j];
        return minNums[0];
    }
};

int main(void) {
    Solution s;
    vector<vector<int> > triangle;
    vector<int> data0, data1, data2, data3; 
    data0.push_back(2);
    data1.push_back(3); data1.push_back(4);
    data2.push_back(6); data2.push_back(5); data2.push_back(7);
    data3.push_back(4); data3.push_back(1); data3.push_back(8); data3.push_back(3);
    triangle.push_back(data0);
    triangle.push_back(data1);
    triangle.push_back(data2);
    triangle.push_back(data3);

    cout << s.minimumTotal(triangle) << endl;
    return 0;
}
