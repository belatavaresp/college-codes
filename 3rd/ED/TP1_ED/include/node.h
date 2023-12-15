#ifndef NODE_H
#define NODE_H
#include <string>

using namespace std;

class Node
{
public:
    double value;
    Node *left;
    Node *right;

    Node(double val)
    {
        value = val;
        left = right = nullptr;
    }
    Node(double val, Node *left, Node *right)
    {
        value = val;
        this->left = left;
        this->right = right;
    }
};

#endif