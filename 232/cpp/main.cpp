#include <iostream>
#include <stack>

using namespace std;

class Queue {

public:
    // Push element x to the back of queue.
    void push(int x) {        
        in.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {        
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        out.pop();
    }

    // Get the front element.
    int peek(void) {   
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        return out.top();
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return in.empty() && out.empty();
    }
private:
    stack<int> in;
    stack<int> out;
};

int main() {
    Queue q;
    for (int i = 0; i < 100; ++i)
        q.push(i);
    while (!q.empty()) {
        cout << q.peek() << ",";
        q.pop();
    }
    return 0;
}
