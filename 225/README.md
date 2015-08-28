#Leetcode 225 Implement Stack using Queues 使用队列实现栈

##原题地址
https://leetcode.com/problems/implement-stack-using-queues/

##题目描述
Implement the following operations of a stack using queues.
使用队列来实现一个栈，主要包含以下方法：

> - push(x) -- Push element x onto stack. 入栈
> - pop() -- Removes the element on top of the stack. 出栈
> - top() -- Get the top element. 获取栈顶元素
> - empty() -- Return whether the stack is empty. 返回栈是否为空

Notes:
注意：

You must use only standard operations of a queue -- which means only push to back, peek/pop from front, size, and is empty operations are valid.
只能使用队列的标准操作，即：`push` 在队尾插入，`peek/pop` 从队首弹出，`size` 获取队列大小，`empty` 是否为空。

You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).
假设所有操作都是合法的（例如，不会在栈为空时调用pop和top方法）。

##解题思路
使用两个队列来模拟一个栈。假设有两个栈A和B，至少保持其中一个为空。

**1. 入栈 `push()`**

当我们**插入一个元素x时，将x放入其中为空的队列中，然后把另一个队列中的所有元素按顺序放入这个队列中**。如下：

    演示 1,2,3,4入栈

    (1) push(1)
       --------------       --------------
    A:  1                B:               
       --------------       --------------
    (2) push(2)
       --------------       --------------
    A:                   B:  2,1           
       --------------       --------------
    (3) push(3)
       --------------       --------------
    A:  3,2,1             B:                
       --------------       --------------
    (4) push(4)
       --------------       --------------
    A:                   B:  4,3,2,1               
       --------------       --------------

**2. 获取栈顶元素 `top()` / 出栈 `pop()` **

获取栈顶元素和出栈操作比较简单，由于两个队列中有一个为空，我们只需要从不为空的那个队列中取出或弹出队首的元素即可。

    (5) top() ---> return 4
       --------------       --------------
    A:                   B:  4,3,2,1               
       --------------       --------------
    (5) pop()
       --------------       --------------
    A:                   B:  3,2,1               
       --------------       --------------

**3. 是否为空 `empty()`**
当两个队列同时为空时，说明栈为空。

##代码
代码真的非常简单

```
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
```

> 完整代码 [https://github.com/Orange1991/leetcode/blob/master/225/cpp/main.cpp](https://github.com/Orange1991/leetcode/blob/master/225/cpp/main.cpp)

##博文地址
http://blog.csdn.net/smile_watermelon/article/details/48056125

---
2015/8/28
