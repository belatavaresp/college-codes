#include "tree.h"

// check if char is operator
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
// assing precedence to operations
int precedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

bool hasHigherPrecedence(char op1, char op2)
{
    return precedence(op1) > precedence(op2);
}

Tree::Tree(string exp)
{
    if (exp[0] == '(')
    {
        // implementation for infix exp
        Stack operators;
        Stack_n operands;

        // add closing parenthesis to end of expression to simplify parsing
        exp += ')';

        for (int i = 0; i < exp.length(); i++)
        {
            char c = exp[i];

            if (isspace(c))
            {
                // skip whitespace
                continue;
            }
            else if (isdigit(c))
            {
                // if digit, read entire number and push to operand stack
                stringstream ss;
                while (i < exp.length() && (isdigit(exp[i]) || exp[i] == '.'))
                {
                    ss << exp[i];
                    i++;
                }
                i--;
                double val;
                ss >> val;
                operands.push(new Node(val));
            }
            else if (c == '(')
            {
                // push opening parenthesis to operator stack
                operators.push(c);
            }
            else if (isOperator(c))
            {
                // pop operators from stack and add to postfix expression until top of stack has lower or equal precedence
                while (!operators.isEmpty() && operators.getTop() != '(' && hasHigherPrecedence(operators.getTop(), c))
                {
                    char op = operators.getTop();
                    operators.pop();
                    Node *right = operands.getTop();
                    operands.pop();
                    Node *left = operands.getTop();
                    operands.pop();
                    operands.push(new Node(op, left, right));
                }
                operators.push(c);
            }
            else if (c == ')')
            {
                // pop operators from stack and add to postfix expression until matching opening parenthesis is found
                while (!operators.isEmpty() && operators.getTop() != '(')
                {
                    char op = operators.getTop();
                    operators.pop();
                    Node *right = operands.getTop();
                    operands.pop();
                    Node *left = operands.getTop();
                    operands.pop();
                    operands.push(new Node(op, left, right));
                }
                if (operators.getTop() == '(')
                {
                    operators.pop();
                }
            }
        }
        root = operands.getTop();
    }
    else
    {
        // implementation for postfix exp
        Stack_n s;
        for (int i = 0; i < exp.length(); i++)
        {
            char c = exp[i];
            if (isdigit(c))
            {
                stringstream ss;
                while (i < exp.length() && (isdigit(exp[i]) || exp[i] == '.'))
                {
                    ss << exp[i];
                    i++;
                }
                i--;
                double val;
                ss >> val;
                Node *node = new Node(val);
                s.push(node);
            }
            else if (isOperator(c))
            {
                Node *node = new Node(c);
                node->right = s.getTop();
                s.pop();
                node->left = s.getTop();
                s.pop();
                s.push(node);
            }
        }
        root = s.getTop();
    }
}

double Tree::solve()
{
    return solveExpression(root);
}

double Tree::solveExpression(Node *node)
{
    {
        // If it's not an operator, return the value of the node
        if (!node->left && !node->right)
        {
            return node->value;
        }

        // Solve the left and right sub-trees recursively
        double leftVal = solveExpression(node->left);
        double rightVal = solveExpression(node->right);

        // Apply the operator based on the value of the current node
        switch ((char)node->value)
        {
        case '+':
            return leftVal + rightVal;
        case '-':
            return leftVal - rightVal;
        case '*':
            return leftVal * rightVal;
        case '/':
            if (rightVal == 0)
            {
                throw runtime_error("Divisão por zero!");
            }
            return leftVal / rightVal;
        default:
            return 0.0;
        }
    }
}