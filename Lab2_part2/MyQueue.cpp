#include <stack>
#include <iostream>
#include <stdlib.h>

using namespace std;

class MyQueue {

private:
    stack<int> stack1;//to store element
    stack<int> stack2;//临时转移stack1的元素，达到逆序效果
public:
    // Push element x to the back of queue.
    void push(int x) {
        stack1.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        //check if the queue is empty
        if (stack1.empty()) {
            cout << "ERROR: the queue is empty" << endl;
            exit(0);
        }

        //trans the elements to stack2 except the first one
        while(stack1.size() > 1) {
            stack2.push(stack1.top());
            stack1.pop();//pop the value
        }

        stack1.pop();//pop the first value

        //return the elements to stack1
        while(!stack2.empty()) {
            stack1.push(stack2.top());
            stack2.pop();//clear stack2
        }

        return ;
    }

    // Get the front element.
    int peek(void) {
        //check if the queue is empty
        if (stack1.empty()) {
            cout << "ERROR: the queue is empty" << endl;
            exit(0);
        }

        //trans the elements to stack2 except the first one
        while(stack1.size() > 1) {
            stack2.push(stack1.top());
            stack1.pop();//pop the value
        }

        int ret_value = stack1.top();//peek the first value

        //return the elements to stack1
        while(!stack2.empty()) {
            stack1.push(stack2.top());
            stack2.pop();//clear stack2
        }

        return ret_value;
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return stack1.empty();
    }
};
