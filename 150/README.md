#Leetcode 150 Evaluate Reverse Polish Notation 反向波兰表示法求值

##原题地址
https://leetcode.com/problems/evaluate-reverse-polish-notation/

##题目描述
Evaluate the value of an arithmetic expression in [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation).
求解使用[反向波兰表示法](https://en.wikipedia.org/wiki/Reverse_Polish_notation)描述的一个算术表达式的值。

Valid operators are +, -, *, /. Each operand may be an integer or another expression.
合法的运算符有`+`,`-`,`*`,`/`。操作数是整数或者另一个表达式。

Some examples:
一些例子：

    ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9
    ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6

##解题思路
反向波兰表示法的特点就是操作符在操作数的后面（后缀表示法），最后面的操作符是最后执行的运算，因此我们可以从前面开始往后计算，当遇到数字时，将其作为操作数压栈，当遇到操作符时，从操作数栈栈顶取出两个操作数来完成一次计算，并把计算结果存到操作数栈中，到最后操作数栈中只留下一个操作数就是计算结果

##算法描述
> 1. 读取出下一个token，如果token不是操作符，则将其转换为相应的操作数压栈
> 2. 如果token是操作符，从栈中取出两个操作数来计算，将得到的值压入操作数栈中
> 3. 到最后一个token处理结束时，操作数栈栈顶元素就是计算结果

##代码 cpp

```
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> operands;
        vector<string>::iterator it = tokens.begin(), end = tokens.end();
        int opA, opB;

        while (it != end) {
            if (*it == "+" || *it == "-" || *it == "*" || *it == "/") {
                opB = operands.top();
                operands.pop();
                opA = operands.top();
                operands.pop();
                operands.push(cal(opA, opB, *it));
            } else {
                operands.push(valueOf(*it)); 
            }
            ++it;
        }

        return operands.top();       
    }

private:
    /** 字符串转换为相应数值 */
    int valueOf(string str) {
        if (str == "") return 0;
        int symbol = 1, index = 0, len = str.size(), val = 0;
        if (str[0] == '+') {
            index = 1;
        } else if (str[0] == '-') {
            index = 1;
            symbol = -1;
        }
        for (; index < len; ++index)
            val = val * 10 + str[index] - '0';
        return val * symbol;
    }

    /** 二元计算 */
    int cal(int opA, int opB, string op) {
        int val = 0;
        switch (op[0]) {
            case '+': val = opA + opB; break;
            case '-': val = opA - opB; break;
            case '*': val = opA * opB; break;
            case '/': val = opA / opB; break;
        }
        return val;
    }
};
```

> 完整代码[https://github.com/Orange1991/leetcode/blob/master/150/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/150/cpp/main.cpp)

##运行情况
| Language | Status | Time |
| :------- | :----- | :--- |
| cpp      | Accept | 16ms |
 

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/47206335

---
2015/8/2
