#ifndef TREE_H
#define TREE_H
#include <sstream>
#include <iostream>
#include "node.h"
#include "stack_n.h"
#include "stack.h"
using namespace std;

class Tree
{
private:
    Node *root;

public:
    Tree(string);
    double solve();
    double solveExpression(Node *);
};

#endif