#include <iostream>
#include <string>
#include "stack_s.h"
#include "stack.h"
using namespace std;

// check if char is operator
bool isCharOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
// assing operatorPrecedence to operations
int operatorPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

// convert postfix to infix notation (without spaces)
string postfixToInfix(string postfix)
{
    Stack_s s1; // auxiliary string stack
    for (int i = 0; i < postfix.length(); i++)
    {
        // if operator is found push (1st arg + operator + 2nd arg)
        if (isCharOperator(postfix[i]))
        {
            string op1 = s1.getTop();
            s1.pop();
            string op2 = s1.getTop();
            s1.pop();
            s1.push("(" + op2 + postfix[i] + op1 + ")");
        }
        // if number is found combine digits and push
        else if (isdigit(postfix[i]) || postfix[i] == '.')
        {
            string operand;
            while (isdigit(postfix[i]) || postfix[i] == '.')
            {
                operand += postfix[i];
                i++;
            }
            s1.push(operand);
            i--;
        }
    }

    // returns combined expression (args and operators)
    return s1.getTop();
}

string infixToPostfix(string expression)
{
    Stack s; // operators -> higher operatorPrecedence == top
    string postfix = "";
    // runs through given expression
    for (int i = 0; i < expression.length(); i++)
    {
        // adds numbers in output string
        if (isdigit(expression[i]) || expression[i] == '.')
        {
            postfix += expression[i];
            while (isdigit(expression[i + 1]) || expression[i + 1] == '.')
            {
                i++;
                postfix += expression[i];
            }
            postfix += " "; // separate from next arg
        }
        else if (isCharOperator(expression[i]))
        {
            // if operator in stack has higher operatorPrecedence it's added first
            while (!s.isEmpty() && operatorPrecedence(s.getTop()) >= operatorPrecedence(expression[i]))
            {
                postfix += s.getTop();
                s.pop();
                postfix += " ";
            }
            // if not, it's added to the stack
            s.push(expression[i]);
        }
        // adds '(' to the stack
        else if (expression[i] == '(')
        {
            s.push(expression[i]);
        }
        // puts operators in correct order
        else if (expression[i] == ')')
        {
            while (!s.isEmpty() && s.getTop() != '(')
            {
                postfix += s.getTop();
                s.pop();
                postfix += " ";
            }
            if (!s.isEmpty() && s.getTop() == '(')
            {
                s.pop(); // remove the opening parenthesis from the stack
            }
        }
    }
    // pop any remaining operators in the stack and add them to the output string
    while (!s.isEmpty())
    {
        postfix += s.getTop();
        s.pop();
        postfix += " ";
    }
    return postfix;
}
