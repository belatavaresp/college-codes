#ifndef STACK_HPP
#define STACK_HPP

#include "fila.h"

class Stack {
private:
    CircularQueue cq;

public:
    Stack();
    bool pilhaVazia();
    void empilha(int value);
    void desempilha();
    void destroiPilha();
    void imprimir();
    CircularQueue getFila();
};

#endif
