#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * 返回和为n的k项组合
     * 备选数字只能是1-9，且在某特定组合内数字不能重复使用
     * @param k 组合项个数
     * @param n k项的和
     * @return 所有可能的组合
     */
    vector<vector<int> > combinationSum3(int k, int n) {
        vector<int> nums;
        vector<vector<int> > ans;
        // 在(0, 9]中选择和为n的k项组合
        combinationSum(nums, 0, k, n, ans);
        return ans;
    }
private:
    /**
     * 返回和为sum的count项组合
     * 备选数字只能是1-9，且在某特定组合内数字不能重复使用
     * 每次调用的效果是给和等于sum的count项组合选择第一个数字
     * @param nums 当前组合
     * @param last 当前组合的最大数字
     * @param count 组合项个数
     * @param sum 所有项的和
     * @param ans 可行解
     */
    void combinationSum(vector<int>& nums, int last, int count, int sum, vector<vector<int> >& ans) {
        // 添加可行解
        if (sum == 0 && count == 0) { ans.push_back(nums); return; }
        
        // 以下过程为在(last, end]区间内选择和为sum的count项组合的第一个数字
        int end = sum < 9 ? sum : 9; // 如果当前sum小于9，则缩小数字选取范围
        end -= count - 1; // 尝试缩小数字选取范围，为后面的count-1个数留取选择空间
        for (int i = last + 1; i <= end; ++i) { // 在选取范围内选择一个数字
            nums.push_back(i); // 添加到组合中
            combinationSum(nums, i, count - 1, sum - i, ans); // 递归调用，选取剩余的count-1个数
            nums.pop_back(); // 弹出组合中的最后一个数，以备下次循环选择另一个备选数字
        }
    }
};

void test(int k, int n) {
    Solution s;
    cout << "k = " << k << ", n = " << n << ", comninations = " << endl;
    vector<vector<int> > ans = s.combinationSum3(k, n);
    cout << "[" << endl;
    int rows = ans.size();
    if (rows == 0) {
        cout << "]" << endl;
        return;
    }
    for (int i = 0; i < rows - 1; ++i) {
        cout << "    [";
        int cols = ans[i].size();
        for (int j = 0; j < cols - 1; ++j)
            cout << ans[i][j] << ", ";
        cout << ans[i][cols - 1] << "]," << endl;
    }
    int cols = ans[rows - 1].size();
    if (cols != 0) { 
        cout << "    [";
        for (int j = 0; j < cols - 1; ++j) {
         cout << ans[rows - 1][j] << ", ";
        }
        cout << ans[rows - 1][cols - 1] << "]" << endl;
    }
    cout << "]" << endl;
}

int main() {
    test(3, 7);
    test(3, 9);
    test(3, 24);
    test(3, 25);
    test(8, 40);
}
