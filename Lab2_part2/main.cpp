#include <iostream>
#include <queue>
#include <stack>
#include "MyQueue.cpp"
#include "MyStack.cpp"

using namespace std;

int main()
{
    queue<int> std_q;
    MyQueue my_q;

    stack<int> std_s;
    MyStack my_s;

    for(int i = 0; i < 20; i++){
        std_q.push(i);
        my_q.push(i);

        std_s.push(i);
        my_s.push(i);
    }

    for(int i = 0; i < 20; i++){
        //check myQueue
        if(std_q.front() != my_q.peek()) {
            cout << "error!!" << std_q.front() << "/" << my_q.peek() << endl;
        }

        //cout << std_q.front() << "/" << my_q.peek() << endl;

        std_q.pop();
        my_q.pop();

        //check myStack
        if(std_s.top() != my_s.top()) {
            cout << "error!!" << std_s.top() << "/" << my_s.top() << endl;
        }

        //cout << std_s.top() << "/" << my_s.top() << endl;

        std_s.pop();
        my_s.pop();
    }


    cout << my_s.empty() << "/" << my_q.empty();

    return 0;
}
