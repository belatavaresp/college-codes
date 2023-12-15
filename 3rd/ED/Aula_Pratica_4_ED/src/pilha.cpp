#include <iostream>
#include "pilha.h"
using namespace std;

Stack::Stack() {
}

bool Stack::pilhaVazia() {
    return cq.isEmpty();
}

void Stack::empilha(int value) {
    cq.enqueue(value);
}

void Stack::desempilha() {
    if (pilhaVazia()) {
        cout << "Error: Pilha vazia\n";
        return;
    }
    int size = cq.rear - cq.front + 1;
    for (int i = 0; i < size - 1; i++) {
        int value = cq.getFront();
        cq.dequeue();
        cq.enqueue(value);
    }
    cq.dequeue();
}

void Stack::destroiPilha() {
    cq = CircularQueue();
}

void Stack::imprimir() {
    if (pilhaVazia()) {
        cout << "Pilha vazia\n";
        return;
    }
    int size = cq.rear - cq.front + 1;
    for (int i = 0; i < size; i++) {
        int value = cq.getFront();
        cq.dequeue();
        cq.enqueue(value);
        cout << value << " ";
    }
    cout << endl;
}

CircularQueue Stack::getFila(){
    return this->cq;
}

