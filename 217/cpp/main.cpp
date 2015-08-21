#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> appears;
        for (int i = 0, len = nums.size(); i < len; ++i) {
            if (appears.find(nums[i]) != appears.end())
                return true;
            appears.insert(nums[i]);
        }
        return false;
    }
};

void test(vector<int>& nums) {
    int len = nums.size();
    cout << "[";   
    for (int i = 0; i < len - 1; ++i) {
        cout << nums[i] << ",";
    }
    if (len > 0)
        cout << nums[len - 1];
    cout << "], ";
    Solution s;
    if (s.containsDuplicate(nums))
        cout << "Have dulplicate(s)." << endl;
    else
        cout << "Have no dulplicate." << endl;
}

int main() {
    vector<int> nums;
    for(int i = 0; i < 10; ++i)
        nums.push_back(i);
    test(nums);
    nums.push_back(0);
    test(nums);
    return 0;
}
