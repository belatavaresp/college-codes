#include "stack_n.h"
#include <iostream>

Stack_n::Stack_n()
{
    this->top = -1;
}
void Stack_n::push(Node *n)
{
    ++top;
    w[top] = n;
}
bool Stack_n::isEmpty()
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
void Stack_n::pop()
{
    if (isEmpty())
        return;
    w[top] = nullptr;
    --top;
}
Node *Stack_n::getTop()
{
    if (top == -1)
        return nullptr;
    return w[top];
}
