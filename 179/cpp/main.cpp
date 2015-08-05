#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

class Solution {
public:
    /** 
     * 生成最大数字
     * @param nums 备选数字
     * @return 最大数字字符串
     */
    string largestNumber(vector<int>& nums) {   
        int len = nums.size();

        /* 数字转化为字符串 */
        vector<string> strs;
        for (int i = 0; i < len; ++i) {
            char buff[20];
            sprintf(buff, "%d", nums[i]);
            strs.push_back(buff); 
        }

        /* 排序 */
        sort(strs.begin(), strs.end(), cmp);

        /* 拼接结果 */
        string ret;
        for (int i = 0; i < len; ++i) ret += strs[i];
        
        /* 特殊值0 */
        if (ret == "" || ret[0] == '0') ret = "0";

        return ret;
    }

    /** 按照a+b和b+a的字典序判定a和b的“大小”关系 */
    static bool cmp(string a, string b) { return a + b > b + a; }
};

void test(vector<int> &nums) {
    Solution s; 
    for (int i = 0, len = nums.size(); i < len; ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << s.largestNumber(nums) << endl;
}

int main() {
    vector<int> nums;
    nums.push_back(9);
    nums.push_back(98);
    nums.push_back(92);
    nums.push_back(8);
    nums.push_back(89);
    nums.push_back(5);
    nums.push_back(55);
    nums.push_back(5);
    nums.push_back(56);
    nums.push_back(567);
    nums.push_back(562);
    nums.push_back(545);
    nums.push_back(542);
    nums.push_back(52);
    nums.push_back(562);
    test(nums);

    nums.clear();
    nums.push_back(3);
    nums.push_back(30);
    nums.push_back(34);
    nums.push_back(5);
    nums.push_back(9);
    nums.push_back(0);
    test(nums);

    nums.clear();
    nums.push_back(2048);
    nums.push_back(48);
    test(nums);

    nums.clear();
    nums.push_back(2048);
    test(nums);

    nums.clear();
    nums.push_back(0);
    nums.push_back(0);
    test(nums);

    nums.clear();
    nums.push_back(8247);
    nums.push_back(824);
    test(nums);

    return 0;
}
