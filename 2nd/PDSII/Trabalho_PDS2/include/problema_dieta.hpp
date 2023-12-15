#ifndef PROBLEMA_DIETA_H
#define PROBLEMA_DIETA_H

#include <iostream>
#include <cmath>
#include <vector>

class Simplex{

    private:
        int linhas, colunas;
        
        // Armazena os valores dos coeficientes das variáveis das restrições
        std::vector <std::vector<float> > A;
        // Armazena o valor das restrições
        std::vector<float> B;
        // Armazena os valores dos coeficientes da função objetivo
        std::vector<float> C;

        // Armazena o custo mínimo em reais
        float custoMin;
        // Define se a função é ilimitada ou não
        bool ilimitada;

    public:
        Simplex(std::vector <std::vector<float>>,std::vector<float>,std::vector<float>);
        bool calculoAlgoritmoSimplex();
        bool verificaOtimizacao();
        void escalonamento(int,int);
        int encontraColunaPivo();
        int encontraLinhaPivo(int);
        void calculaSimplex();
};

#endif