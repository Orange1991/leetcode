#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
    /** 简单表达式计算 */
    int calculate(string s) { 
        stack<string> expr, nums, ops;
        int cur = 0, len = s.size();
        string tmp = "";
        while (cur < len) {
            // 获取下一个操作数或操作符
            switch (s[cur]) {
                case ' ': break;    // 忽略空格
                case '+':           // 如果遇到特殊字符
                case '-': 
                case '(': 
                    if (tmp != "") {// 添加可能存在的操作数
                        expr.push(tmp);
                        tmp = "";
                    }
                    expr.push(tmp + s[cur]); // 添加特殊字符
                    break;
                case ')': {         // 遇到闭合括号
                    if (tmp != "") {// 添加可能存在的操作数
                        expr.push(tmp);
                        tmp = "";
                    }               // 计算最顶层的括号内的子表达式
                    int caled = calculate(expr);
                    expr.push(intToStr(caled)); // 添加到栈中
                    break;
                }
                default:    // 扩展操作数
                    tmp += s[cur];
                    break;
            }
            ++cur;
        }
        if (tmp != "") expr.push(tmp);
        return calculate(expr); // 计算
    }
private:
    /** 计算栈中最上层的括号内的表达式 */
    int calculate(stack<string>& s) {
        stack<int> nums; 
        stack<char> ops;
        string top;
        // 获取最顶层括号内的操作数和操作符
        while (!s.empty() && (top = s.top()) != "(") {
            if (top == "+" || top == "-")
                ops.push(top[0]);
            else
                nums.push(strToInt(top));
            s.pop();
        }
        if (!s.empty()) s.pop(); // 弹出"("
        // 计算子表达式结果
        int ans = nums.top(), num;
        nums.pop();
        while (!ops.empty()) {
            num = nums.top();
            nums.pop();
            if (ops.top() == '+')
                ans += num;
            else
                ans -= num;
            ops.pop();
        }
        return ans;
    }

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
    test("(1+(4+5+2 ) - 3) + (6+8)");
    test("1 + 1");
    test(" 2-1 + 2 ");
    test(" 2-(5-6) ");
    
    return 0;
}
