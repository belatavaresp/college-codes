#include "infixPostfix.h"

// check if char is operator
bool isCOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isValidExpression(string k)
{
    // errors:
    // always treat as infix notation
    if (k[0] != '(')
    {
        string postfix = postfixToInfix(k);
        k = postfix;
    }

    // double operator (e.g. +*)
    for (int i = 1; i < k.size(); i++)
    {
        char c = k[i];
        if (isCOperator(c))
        {
            i++;
            c = k[i];
            int count = 1;
            if (isCOperator(c))
            {
                return 0;
            }
            else if (c == '(')
            {
                while (c == '(')
                {
                    i++;
                    c = k[i];
                    count++;
                }
                if (isCOperator(c))
                {
                    return 0;
                }
            }
            i -= count;
        }
    }

    // operator at end/beginning (e.g.1 +2-3    e.g.2 1-2+)
    if (isCOperator(k[1]))
    {
        return 0;
    }

    for (int i = 1; i < k.size(); i++)
    {
        char c = k[i];
        if (c == ')')
        {
            c = k[i - 1];
            if (isCOperator(c))
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }

    // division by zero (e.g.1 1/0    e.g.2 1/(0))
    for (int i = 1; i < k.size(); i++)
    {
        char c = k[i];
        if (c == '/')
        {
            i++;
            c = k[i];
            if (c == '0')
                return 0;
        }
    }

    return 1;
}