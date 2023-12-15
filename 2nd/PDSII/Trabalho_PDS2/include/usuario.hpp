#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>
#include "diario.hpp"

//classe com os dados de um usuario
class Usuario{
    private:
    std::string nome;
    int idade;
    char genero;
    int altura;
    double peso;
    std::string email;
    int limite;
    
    public:
    //existe um diario associado a cada usuário
    Diario* diario;

    //mostra o total das entradas no diario do usuario
    void mostrarEntradas();
    
    //construtor/destrutor
    Usuario(std::string,int,char,int,double,std::string,int);
    ~Usuario();

    //metodos get e set
    std::string getNome();
    void setNome(std::string);

    int getIdade();
    void setIdade(int);

    char getGenero();
    void setGenero(char);

    int getAltura();
    void setAltura(int);

    double getPeso();
    void setPeso(int);

    std::string getEmail();
    void setEmail(std::string);

    int getLimite();
    void setLimite(int);

    Diario* getDiario();

    //calcula o limite calórico ideal
    int calculaLimite();
};

#endif