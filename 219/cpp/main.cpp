#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> appears;
        if (k < 0) k = -k;
        for (int i = 0, len = nums.size(); i < len; ++i) {
            if (appears[nums[i]] == 0 || i + 1 - appears[nums[i]] > k)
                appears[nums[i]] = i + 1;
            else {
                return true;
            }
        }
        return false;
    }
};

void test(vector<int>& nums, int k) {
    int len = nums.size();
    cout << "[";   
    for (int i = 0; i < len - 1; ++i) {
        cout << nums[i] << ",";
    }
    if (len > 0)
        cout << nums[len - 1];
    cout << "], k=" << k << ", ";
    Solution s;
    if (s.containsNearbyDuplicate(nums, k))
        cout << "Have nearby duplicate(s)." << endl;
    else
        cout << "Have no nearby duplicate." << endl;
}

int main() {
    vector<int> nums;
    for(int i = 0; i < 10; ++i)
        nums.push_back(i);
    nums.push_back(0);
    for(int i = 0; i < 10; ++i)
        test(nums, i + 1);
    return 0;
}
