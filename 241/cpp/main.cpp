#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        int len = input.size();
        string operand = "";
        vector<int> nums;
        vector<char> ops;
        for (int i = 0; i < len; ++i) {
            switch (input[i]) {
                case ' ': break;
                case '+':
                case '-':
                case '*':
                    if (operand != "") {
                        nums.push_back(strToInt(operand));
                        operand = "";
                    }
                    ops.push_back(input[i]);
                    break;
                default:
                    operand += input[i];
            }
        }
        if (operand != "")
            nums.push_back(strToInt(operand));
        vector<int> ret;
        compute(nums, ops, ret);
        return ret;
    }

private:
    /** 按不同的顺序计算 */
    void compute(vector<int>& nums, vector<char>& ops, vector<int>& ret) {
        int opSize = ops.size();
        if (opSize == 0) {
            ret.push_back(nums[0]);
            return;
        }
        int a, b;
        char op;
        vector<int>::iterator numsBegin = nums.begin();
        vector<char>::iterator opsBegin = ops.begin();
        for (int i = 0; i < opSize; ++i) {
            a = nums[i];
            b = nums[i + 1];
            op = ops[i];
            nums.erase(nums.begin() + i);
            nums.erase(nums.begin() + i);
            ops.erase(ops.begin() + i);
            nums.insert(nums.begin() + i, calculate(a, b, op));
            compute(nums, ops, ret);
            nums.erase(nums.begin() + i);
            nums.insert(nums.begin() + i, a);
            nums.insert(nums.begin() + i + 1, b);
            ops.insert(ops.begin() + i, op);
        }
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

    /** 数字转化为字符串 */
    string intToStr(int num) {
        if (num == 0) return "0";
        int symbol = num >= 0 ? 1 : -1;
        string s = "";
        num *= symbol;
        while (num) {
            s = (char)(num % 10 + '0') + s;
            num /= 10;
        }
        if (symbol == -1)
            s = "-" + s;
        return s;
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
