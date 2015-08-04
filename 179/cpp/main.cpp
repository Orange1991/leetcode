#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {   
        vector<string> numStrs = transform(nums);
        vector<string> strs = largestNumber("", numStrs);
        string ret;
        for (int i = 0, len = strs.size(); i < len; ++i) ret += strs[i];
        while (ret != "" && ret[0] == '0') ret = ret.substr(1);
        if (ret == "") return "0";
        return ret;
    }

private:
    vector<string> largestNumber(string prefix, vector<string>& nums) {
        vector<string> ret;
        if (nums.size() == 0) return ret;
        vector<vector<string> > groups(10, vector<string>());
        int index = 0;
        int count = 0;
        for (int i = 0, len = nums.size(); i < len; ++i) {
            if (nums[i] != "") {
                index = nums[i][0] - '0';
                groups[index].push_back(nums[i].substr(1));
            } else
                ++count;
        }
        int i;
        vector<string> tmp;
        if (prefix == "") {
            for (i = 9; i > -1; --i) {
                string prefixStr;
                prefixStr += '0' + i;
                tmp = largestNumber(prefixStr, groups[i]);
                ret.insert(ret.end(), tmp.begin(), tmp.end());
            }
        } else {
            int prefixValue = prefix[0] - '0';
            for (i = 9; i > prefixValue; --i) {
                string prefixStr;
                prefixStr += '0' + i;
                tmp = largestNumber(prefixStr, groups[i]);
                for (int j = 0, len = tmp.size(); j < len; ++j) { 
                    string str;
                    str += prefix;
                    str += tmp[j];
                    ret.push_back(str);
                }
            }

            for (int j = 0; j < count; ++j)
                ret.push_back(prefix);
            
            for (; i > -1; --i) { 
                string prefixStr;
                prefixStr += '0' + i;
                tmp = largestNumber(prefixStr, groups[i]);
                for (int j = 0, len = tmp.size(); j < len; ++j) { 
				    string str;
	    			str += prefix;
		    		str += tmp[j];
			    	ret.push_back(str);
                }
            }
        }

        return ret;
    }

    vector<string> transform(vector<int> &nums) {
        int tmp = 0;
        vector<string> ret;
        for (int i = 0, len = nums.size(); i < len; ++i) {
            tmp = nums[i];
            string str;
            if (tmp == 0) str = "0";
            else {
                while (tmp) {
                    str += (tmp % 10 + '0');
                    tmp /= 10;
                }
            }
            reverse(str.begin(), str.end());
            ret.push_back(str);
        }
        return ret;
    }
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

    return 0;
}
