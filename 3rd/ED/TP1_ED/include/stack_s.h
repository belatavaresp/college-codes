#ifndef STACKS_H
#define STACKS_H
#include <string>
#define SIZE 1000
using namespace std;

class Stack_s
{
private:
    string w[SIZE];
    int top;

public:
    Stack_s();
    void push(string); // insert element in stack
    bool isEmpty();    // returns 1 if stack empty
    void pop();        // removes last added element
    string getTop();   // returns element at top
};

#endif