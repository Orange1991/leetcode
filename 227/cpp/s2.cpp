#include <iostream>
#include <stack>
#include <queue>

using namespace std;

class Solution {
public:
    /** 简单表达式计算 */
    int calculate(string s) { 
        queue<string> expr; // 波兰法后缀表达式
        stack<char> ops;    // 中缀表达式转后缀表达式时使用的符号栈
        
        // 中缀表达式转后缀表达式
        int cur = 0, len = s.size();
        string tmp = "";
        while (cur < len) {
            // 获取下一个操作数或操作符
            switch (s[cur]) {
                case ' ': break;    // 忽略空格
                case '+':           // 如果遇到特殊字符
                case '-': 
                    if (tmp != "") {// 添加可能存在的操作数
                        expr.push(tmp);
                        tmp = "";
                    }
                    // 弹出栈顶所有的运算符（+-优先级最低）
                    while (!ops.empty()) {
                        expr.push(tmp + ops.top());
                        ops.pop();
                    }
                    // 当前运算符入栈
                    ops.push(s[cur]);
                    break;
                case '*':
                case '/':
                    if (tmp != "") {// 添加可能存在的操作数
                        expr.push(tmp);
                        tmp = "";
                    }
                    // 弹出栈顶所有同级的运算符（*/）
                    while (!ops.empty()) {
                        char top = ops.top();
                        if (top != '+' && top != '-') {
                            expr.push(tmp + top);
                            ops.pop();
                        } else {
                            break;
                        }
                    }
                    // 当前运算符入栈
                    ops.push(s[cur]);
                    break;
                default:    // 扩展操作数
                    tmp += s[cur];
                    break;
            }
            ++cur;
        }
        if (tmp != "") expr.push(tmp);
        tmp = "";
        while (!ops.empty()) {
            expr.push(tmp + ops.top());
            ops.pop();
        }
        return calculate(expr); // 计算
    }
private:
    /** 逆向波兰表示法求值 */
    int calculate(queue<string>& s) {
        stack<int> nums; 
        string str;
        int a, b;
        while (!s.empty()) {
            str = s.front();
            s.pop();
            if (str == "+") {
                b = nums.top();
                nums.pop();
                a = nums.top();
                nums.pop(); 
                nums.push(a + b);
            } else if (str == "-") {
                b = nums.top();
                nums.pop();
                a = nums.top();
                nums.pop(); 
                nums.push(a - b);
            } else if (str == "*") {
                b = nums.top();
                nums.pop();
                a = nums.top();
                nums.pop(); 
                nums.push(a * b);
            } else if (str == "/") {
                b = nums.top();
                nums.pop();
                a = nums.top();
                nums.pop(); 
                nums.push(a / b);
            } else {
                nums.push(strToInt(str));
            }
        }
        return nums.top();
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
