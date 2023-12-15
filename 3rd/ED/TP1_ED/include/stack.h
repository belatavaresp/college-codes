#ifndef STACK_H
#define STACK_H
#include <string>
#define SIZE 1000
using namespace std;

class Stack
{
private:
    char w[SIZE];
    int top;

public:
    Stack();
    void push(char); // insert element in stack
    bool isEmpty();  // returns 1 if stack empty
    void pop();      // removes last added element
    char getTop();   // returs element at top
};

#endif