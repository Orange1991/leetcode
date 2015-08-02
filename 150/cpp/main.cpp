#include <iostream>
#include <stack>
#include <vector>

using namespace std;

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

int main() {
    Solution s;
    vector<string> tokens;
    tokens.push_back("3");
    tokens.push_back("1");
    tokens.push_back("2");
    tokens.push_back("+");
    tokens.push_back("*");
    cout << s.evalRPN(tokens) << endl;
    
    tokens.clear();
    tokens.push_back("2");
    tokens.push_back("1");
    tokens.push_back("+");
    tokens.push_back("3");
    tokens.push_back("*");
    cout << s.evalRPN(tokens) << endl;

    tokens.clear();
    tokens.push_back("0");
    tokens.push_back("3");
    tokens.push_back("/");
    cout << s.evalRPN(tokens) << endl;
    return 0;
}
