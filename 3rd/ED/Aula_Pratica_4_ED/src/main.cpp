#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include "pilha.h"
using namespace std;

int main() {
    srand(time(NULL));
    Stack s;
    for (int i = 0; i < 10; i++) {
        int value = rand() % 10;
        s.empilha(value);
    }
    cout << "Pilha gerada: ";
    s.imprimir();
    cout << endl << "Desempilhando 1x: ";
    s.desempilha();
    s.imprimir();

    cout << "Desempilhando...";
    while (!s.pilhaVazia()) {
        s.desempilha();
    }
    cout << endl;
    cout << "Pilha após desempilhar: ";
    s.imprimir();
    return 0;
}
