#include <queue>
#include <iostream>
#include <stdlib.h>

using namespace std;

class MyStack {

private:
    queue<int> queue1;
    queue<int> queue2;

public:
    // Push element x onto stack.
    void push(int x) {
        queue1.push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        if (queue1.empty()){
            cout << "ERROR:the stack is empty" << endl;
            exit(0);
        }

        //trans queue1's elements to queue2 except the first one
        while (queue1.size() > 1) {
            queue2.push(queue1.front());
            queue1.pop();
        }

        //pop the last value
        queue1.pop();

        //return the elements from queue2 to queue1
        while (!queue2.empty()) {
            queue1.push(queue2.front());
            queue2.pop();//clear queue2
        }

        return ;
    }

    // Get the top element.
    int top() {
        if (queue1.empty()){
            cout << "ERROR:the stack is empty" << endl;
            exit(0);
        }

        //trans queue1's elements to queue2 except the first one
        while (queue1.size() > 1) {
            queue2.push(queue1.front());
            queue1.pop();
        }

        //peek the last value
        int ret_value = queue1.front();
        queue1.pop();
        queue2.push(ret_value);//the last should be the last


        //return the elements from queue2 to queue1
        while (!queue2.empty()) {
            queue1.push(queue2.front());
            queue2.pop();//clear queue2
        }

        return ret_value;
    }

    // Return whether the stack is empty.
    bool empty() {
        return queue1.empty();
    }
};
