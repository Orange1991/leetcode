#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class Solution {
public:
    /** 简单表达式计算 */
    int calculate(string s) { 
        queue<int> nums;
        queue<char> ops;
        int cur = 0, len = s.size(), p;
        string tmp = "";
        int operandA, operandB;
        
        while (cur < len) {
            // 获取下一个操作数或操作符
            switch (s[cur]) {
                case ' ': break;    // 忽略空格
                case '+':           // 如果遇到 + -
                case '-': 
                    if (tmp != "") {// 添加可能存在的操作数
                        nums.push(strToInt(tmp));
                        tmp = "";
                    }
                    ops.push(s[cur]); // 添加特殊字符
                    break;
                case '*':           // 遇到 * /
                case '/':
                    operandA = strToInt(tmp);   // 第一个操作数
                    // 尝试获取下一个操作数
                    tmp = "";
                    p = cur + 1;
                    while (p < len && s[p] == ' ') ++p;
                    while (p < len && s[p] >= '0' && s[p] <= '9')
                        tmp += s[p++];
                    operandB = strToInt(tmp);
                    // 计算得到结果，存在tmp中，作为上一个合法操作数
                    tmp = s[cur] == '*' ? intToStr(operandA * operandB) 
                            : intToStr(operandA / operandB);
                    cur = p - 1;
                    break;
                default:    // 扩展操作数
                    tmp += s[cur];
                    break;
            }
            ++cur;
        }
        if (tmp != "") nums.push(strToInt(tmp));
        // 计算加减法
        int ans = nums.front();
        nums.pop();
        char op;
        while (!nums.empty()) {
            operandB = nums.front();
            nums.pop();
            op = ops.front();
            ops.pop();
            if (op == '+')
                ans += operandB;
            else
                ans -= operandB;
        }
        return ans;
    }
private:
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

void test(string s) {
    cout << s << "=";
    Solution obj;
    cout << obj.calculate(s) << endl;
}

int main() {
    test("3+2*2");
    test(" 3/2 ");
    test(" 2-1 + 2 ");
    test(" 3+5 / 2 ");
    
    return 0;
}
