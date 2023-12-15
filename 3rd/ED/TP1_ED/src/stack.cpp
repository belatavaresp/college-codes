#include "stack.h"
#include <iostream>

// standard implementation of char stack
Stack::Stack()
{
    this->top = -1;
}
void Stack::push(char n)
{
    ++top;
    w[top] = n;
}
bool Stack::isEmpty()
{
    if (this->top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Stack::pop()
{
    if (isEmpty())
        return;
    w[top] = 0;
    --top;
}
char Stack::getTop()
{
    if (top == -1)
        return '0';
    return w[top];
}
