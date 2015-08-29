#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

class Solution {
public:
    /** 统计范围 */
    vector<string> summaryRanges(vector<int>& nums) {
        int start = 0, end, len = nums.size();
        vector<string> ret;
        string range;
        char s[16];
        while (start < len) {
            range = "";
            end = start + 1;
            while (end < len && nums[end] == nums[end - 1] + 1) 
                ++end;
            if (end == start + 1) {
                sprintf(s, "%d", nums[start]);
                range += s;
            } else { 
                sprintf(s, "%d", nums[start]);
                range += s;
                sprintf(s, "%d", nums[end - 1]);
                range += "->";
                range += s;
            }
            ret.push_back(range);
            start = end;
        }
        return ret;
    }
};

int main() {
    vector<int> nums;
    nums.push_back(0);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(4);
    nums.push_back(5);
    nums.push_back(7);
    Solution s;
    vector<string> ret = s.summaryRanges(nums);
    for (int i = 0, len = ret.size(); i < len; ++i)
        cout << ret[i] << endl;
    nums.clear();
    nums.push_back(-1);
    ret = s.summaryRanges(nums);
    for (int i = 0, len = ret.size(); i < len; ++i)
        cout << ret[i] << endl;
    return 0;
}
