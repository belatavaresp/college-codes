#ifndef ALIMENTO_SOLIDO_H
#define ALIMENTO_SOLIDO_H

#include "alimento.hpp"

class AlimentoSolido : public Alimento
{
    public:
        //construtor
        AlimentoSolido(int,double,double,double,double,double);

        //poliformismo
        virtual void descricao() override;
};

#endif