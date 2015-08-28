#include <iostream>
#include <queue>

using namespace std;

class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        if (a.empty()) {
            a.push(x);
            while (!b.empty()) {
                a.push(b.front());
                b.pop();
            }
        } else {
            b.push(x);
            while (!a.empty()) {
                b.push(a.front());
                a.pop();
            }
        }
    }
    
    // Removes the element on top of the stack.
    void pop() {
        if (a.empty()) b.pop();
        else a.pop();
    }
    
    // Get the top element.
    int top() {
        return a.empty() ? b.front() : a.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return a.empty() && b.empty();
    }
private:
    // 两个队列模拟一个栈
    queue<int> a;
    queue<int> b;
};

int main() {
    cout << "add [1-100] to stack." << endl;
    Stack s;
    for (int i = 1; i < 101; ++i) s.push(i);
    while (!s.empty()) {
        cout << s.top() << "->";
        s.pop();
    }
    return 0;
}
