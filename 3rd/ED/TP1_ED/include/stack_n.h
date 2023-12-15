#ifndef STACKN_H
#define STACKN_H
#define SIZE 1000
#include "node.h"
using namespace std;

class Stack_n
{
private:
    Node *w[SIZE];
    int top;

public:
    Stack_n();
    void push(Node *); // insere elemento na pilha
    bool isEmpty();    // retorna 1 se lista está vazia
    void pop();        // tira elemento da lista
    Node *getTop();    // retorna o elemento no topo
};

#endif