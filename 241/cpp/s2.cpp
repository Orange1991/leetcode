#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        unordered_map<string, vector<int> > map;
        return compute(input, map);
    }

private:
    vector<int> compute(string str, unordered_map<string, vector<int> >& map) {
        if (map.find(str) != map.end()) return map[str];
        int len = str.size(), signs = 0;
        vector<int> ret;
        for (int i = 0; i < len; ++i) {
            if (str[i] == '+' || str[i] == '-' || str[i] == '*') {
                ++signs;
                vector<int> left = compute(str.substr(0, i), map);
                vector<int> right = compute(str.substr(i + 1), map);
                for (int j = 0, l = left.size(), r = right.size(); j < l; ++j)
                    for (int k = 0; k < r; ++k)
                        ret.push_back(calculate(left[j], right[k], str[i]));
            }
        }
        if (signs == 0) ret.push_back(strToInt(str));
        map.insert(make_pair(str, ret));
        return ret;
    }
    
    int calculate(int a, int b, char op) {
        return op == '+' ? a + b : 
                op == '-' ? a - b : 
                op == '*' ? a * b : 0; 
    }
    
    /** 字符串转化为数字 */
    int strToInt(string s) {
        int ans = 0, len = s.size();
        if (len == 0) return 0;
        int symbol = s[0] == '-' ? -1 : 1;
        for (int i = s[0] == '+' || s[0] == '-' ? 1 : 0; i < len; ++i) {
            ans *= 10;
            ans += s[i] - '0';
        }
        return ans * symbol;
    }

};

void test(string str) {
    cout << str << " : ";
    Solution s;
    vector<int> ret = s.diffWaysToCompute(str);
    int size = ret.size();
    cout << "[";
    for (int i = 0; i < size - 1; ++i)
        cout << ret[i] << ",";
    cout << ret[size - 1] << "]" << endl;
}

int main() {
    test("2*3");
    test("2*3-4*5");
    return 0;
}
