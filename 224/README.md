#Leetcode 224 Basic Calculator 基本计算器

##原题地址
https://leetcode.com/problems/basic-calculator/

##题目描述
Implement a basic calculator to evaluate a simple expression string.
实现基本的计算器，计算简单表达式的值。

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
表达式中可能会出现括号`(` `)`，加号`+`减号`-`，非负数以及空格。

You may assume that the given expression is always valid.
假设表达式都是正确的。

Some examples:
例如：

    "1 + 1" = 2
    " 2-1 + 2 " = 3
    "(1+(4+5+2)-3)+(6+8)" = 23

##解题思路
由于表达式中只有`+` `-`两种运算符，因此不用考虑优先级的问题，唯一需要处理的是括号带来的计算顺序问题。考虑遍历整个字符串，当遇到`(` `+` `-`或`合法数字`时，将相应字符或数字压栈，当遇到`)`时，从栈中弹出运算符及数字直到与这个括号匹配的开括号为止，并计算弹出的运算符和数字的结果，计算结束后压栈，然后继续遍历表达式。

在上述过程结束后，栈中还留有一些运算符合数字，但是不再包含括号，这时弹出所有运算符和数字进行一次运算即可得到最终结果。

##代码

```
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
```
> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/224/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/224/cpp/main.cpp)

##测试数据

    (1+(4+5+2 ) - 3) + (6+8)=23
    1 + 1=2
     2-1 + 2 =3
     2-(5-6) =3

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/48055965

---
2015/8/28
