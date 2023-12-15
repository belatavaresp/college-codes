#include "usuario.hpp"

Usuario::Usuario(std::string nome, int idade, char genero,
                int altura, double peso, std::string email, int limite){
    setNome(nome);
    setIdade(idade);
    setGenero(genero);
    setAltura(altura);
    setPeso(peso);
    setEmail(email);

    //confere se há um limite setado pelo usuario
    //se não há, calcula o limite ideal
    if(limite != 0){
        setLimite(limite);
    }else{
        this->limite = calculaLimite();
        std::cout << "Seu limite ideal é " << this->limite << " calorias" << "\n\n";
    }
    this->diario = new Diario();
}

std::string Usuario::getNome(){
    return this->nome;
}
void Usuario::setNome(std::string nome){
    this->nome = nome;
}

int Usuario::getIdade(){
    return this->idade;
}
void Usuario::setIdade(int idade){
    this->idade = idade;
}

char Usuario::getGenero(){
    return this->genero;
}
void Usuario::setGenero(char genero){
    genero = std::tolower(genero);
    this->genero = genero;
}

int Usuario::getAltura(){
    return this->altura;
}
void Usuario::setAltura(int altura){
    this->altura = altura;
}

double Usuario::getPeso(){
    return this->peso;
}
void Usuario::setPeso(int peso){
    this->peso = peso;
}

std::string Usuario::getEmail(){
    return this->email;
}
void Usuario::setEmail(std::string email){
    this->email = email;
}

int Usuario::getLimite(){
    return this->limite;
}
void Usuario::setLimite(int limite){
    this->limite = limite;
}

Diario* Usuario::getDiario(){
    return this->diario;
}

void Usuario::mostrarEntradas(){
    std::cout << "\nVocê possui " << this->diario->entradas.size() << " entradas:" << std::endl;
    int i = 1;
    //acessa a descrição das entradas
    for(auto it = this->diario->entradas.begin(); it != this->diario->entradas.end(); it++){
        std::cout << "Entrada " << i << ":" << std::endl;
        (*it)->descricao();
        std::cout << std::endl;
        i++;
    }
    //confere o total e compara com limite calórico
    //envia o alerta caso tenha ultrapassado
    std::cout << "Total de calorias consumidas: ";
    this->diario->exibirTotal();
    if(this->diario->calcularTotal() > this->limite){
        std::cout << "ATENÇÃO VOCÊ ULTRAPASSOU O SEU LIMITE CALÓRICO!!!" << std::endl;}
}

int Usuario::calculaLimite(){
    //até dezoito anos de idade
    if(this->idade <= 18){
        if(this->genero == 'm' || this->genero == 'M'){
            //mulheres
            return (1.55 * ((this->peso * 13.384) + 692.6));
        }else{
            //homens
            return (1.55 * ((this->peso * 17.686) + 658.2));
        }
    //até trinta anos de idade
    }else if(this->idade <= 30){
        if(this->genero == 'm' || this->genero == 'M'){
            //mulheres
            return (1.55 * ((this->peso * 14.818) + 486.6));
        }else{
            //homens
            return (1.55 * ((this->peso * 15.057) + 692.2));
        }
    //até 60 anos de idade
    }else if(this->idade <= 60){
        if(this->genero == 'm' || this->genero == 'M'){
            //mulheres
            return (1.55 * ((this->peso * 8.126) + 845.6));
        }else{
            //homens
            return (1.55 * ((this->peso * 11.472) + 873.1));
        }
    //mais de 60 anos de idade
    }else{
        if(this->genero == 'm' || this->genero == 'M'){
            //mulheres
            return (1.55 * ((this->peso * 9.082) + 658.5));
        }else{
            //homens
            return (1.55 * ((this->peso * 11.711 ) + 587.7));
        }
    }
}


