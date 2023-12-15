#ifndef DIARIO_H
#define DIARIO_H

#include "alimento.hpp"
#include <vector>

//classe que lista os alimentos ingeridos
class Diario{
    public:
    //entradas e total devem ser publicos para poderem ser acessados pelo usuario
    std::vector<Alimento*> entradas;
    int total;

    //construtor 
    Diario();

    //insere um alimento apartir de seu codifgo e quantidade ingerida
    void inserirEntrada(int codigo, double quantidade);
    
    //calcula o total calórico
    int calcularTotal();

    //exibe o total e alerta quando o limite é ultrapassado
    void exibirTotal();
};

#endif