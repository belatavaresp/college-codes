#include "alimento.hpp"
#include <fstream>

Alimento::Alimento(){}

void Alimento::setCodigo(int codigo){
    this->codigo = codigo;
}
int Alimento::getCodigo(){
    return this->codigo;
}

void Alimento::setCalorias(double calorias){
    this->calorias = calorias;
}
double Alimento::getCalorias(){
    return this->calorias;
}

void Alimento::setCarboidratos(double carboidratos){
    this->carboidratos = carboidratos;
}
double Alimento::getCarboidratos(){
    return this->carboidratos;
}

void Alimento::setGorduras(double gorduras){
    this->gorduras = gorduras;
}
double Alimento::getGorduras(){
    return this->gorduras;
}

void Alimento::setProteinas(double proteinas){
    this->proteinas = proteinas;
}
double Alimento::getProteinas(){
    return this->proteinas;
}

void Alimento::setQuantidade(double quantidade){
    this->quantidade = quantidade;
}
double Alimento::getQuantidade(){
    return this->quantidade;
}

double Alimento::totalCalorico(){
    //calorias estão por 100g, por isso são divididas por 100
    return ((this->calorias / 100) * this->quantidade);
 }