#ifndef ALIMENTO_H
#define ALIMENTO_H

class Alimento{
    private:
    int codigo;

    //nutrientes por 100g/100ml
    double calorias;
    double carboidratos;
    double gorduras;
    double proteinas;

    //quantidade ingerida
    double quantidade;

    public:
    //construtor/destrutor
    Alimento();

    //metodos get e set
    int getCodigo();
    void setCodigo(int);
    
    double getCalorias();
    void setCalorias(double);

    double getCarboidratos();
    void setCarboidratos(double);

    double getGorduras();
    void setGorduras(double);

    double getProteinas();
    void setProteinas(double);

    double getQuantidade();
    void setQuantidade(double);

    //calcula o total de calorias do alimento
    double totalCalorico();

    //metodo que vai sofrer polimorfismo
    virtual void descricao() = 0;
    
};

#endif