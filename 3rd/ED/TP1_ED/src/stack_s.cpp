#include "stack_s.h"
#include <iostream>

// standard implementation of string stack
Stack_s::Stack_s()
{
    this->top = -1;
}
void Stack_s::push(string n)
{
    ++top;
    w[top] = n;
}
bool Stack_s::isEmpty()
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
void Stack_s::pop()
{
    if (isEmpty())
        return;
    w[top] = "";
    --top;
}
string Stack_s::getTop()
{
    if (top == -1)
        return " ";
    return w[top];
}
