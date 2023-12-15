#include <iostream>
#include <cmath>
#include <vector>
#include "problema_dieta.hpp"
#include "diario.hpp"


/*
    Basicamente, a ideia desse algoritmo é transformar o problema de otimização em um sistema linear.
    Tem uma função õbjetivo f(x) = Cx, que é a função que é maximizada, ou minimizada no nosso caso,
    e as restrições, no caso a quantidade de calorias, são o sistema Ax = B.

    O vetor x é o vetor das variáveis, que no nosso caso são os alimentos; o vetor C tem os coeficientes
    constantes que multiplicam as variáveis na função objetivo, que no nosso caso são os preços; na matriz
    A, cada linha representa uma restrição, que fica igualada a uma constante do vetor B, e cada coluna de
    A tem os coeficientes que representam o quanto cada variável (alimento) contribui para aquela restrição,
    no nosso caso, apesar de funcionar para qualquer número de restrições, para simplificar só vamos utilizar
    uma restrição que é a quantidade de calorias.

    O funcionamento do algoritmo gira em torno de operações elementares em matrizes (escalonamento) para 
    encontrar a matriz A otimizada, os valores ideais das variáveis do vetor x e o valor ótimo da função.
    No nosso caso, é um algoritmo simplificado, que encontra só os valores ideais das variáveis, que é o
    que nos interessa, mas poderia ser extendido para uma versão mais complexa caso necessário.
*/

// Algoritmo simplex é um algoritmo de otimização linear que maximiza ou minimiza
// o valor de uma função objetivo com restrições para as variáveis dessa função
        // Construtor
        Simplex::Simplex(std::vector <std::vector<float>> matrix,std::vector<float> b ,std::vector<float> c){
            custoMin = 0;
            ilimitada = false;
            linhas = matrix.size();
            colunas = matrix[0].size();
            A.resize( linhas , std::vector<float>( colunas , 0 ));
            B.resize(b.size());
            C.resize(c.size());

            // Copia os valores de matrix para A
            for(int i= 0;i<linhas;i++){             
                for(int j= 0; j< colunas;j++ ){
                    A[i][j] = matrix[i][j];

                }
            }

            // Copia os valores de b para B
            for(int i=0; i< b.size();i++ ){      
                B[i] = b[i];
            }
            
            // Copia os valores de c para C
            for(int i=0; i< c.size() ;i++ ){      
                C[i] = c[i] ;
            }
            
        }
        
        // Algoritmo Simplex
        bool Simplex::calculoAlgoritmoSimplex(){
            
            // Verifica se a tabela já está otimizada, se estiver não tem necessidade de calcular
            if(verificaOtimizacao() == true){
			    return true;
            }

            // Encontra qual coluna da matriz tem pivô
            int colunaPivo = encontraColunaPivo();

            // Alerta de um erro caso a função seja ilimitada
            if(ilimitada == true){
                std::cout << "Erro: função ilimitada" << std::endl;
			    return true;
            }

            // Encontra a linha em que o pivô da coluna está 
            int linhaPivo = encontraLinhaPivo(colunaPivo);

            // Atualiza a tabela de acordo com o valor do pivô
            escalonamento(linhaPivo,colunaPivo);

            return false;
        }
        
        // Verifica se a tabela está otimizada
        // Se a função objetivo tiver mais coeficientes negativos que positivos, então não está otimizada
        bool Simplex::verificaOtimizacao(){
             
            bool otimizada = false;
            int contValoresPositivos = 0;

            // Verifica se os coeficientes da função objetivo são negativos
            for(int i=0; i<C.size();i++){
                float valor = C[i];
                if(valor >= 0){
                    contValoresPositivos++;
                }
            }
            // Se todos os coeficientes forem positivos, a tabela está otimizada
            if(contValoresPositivos == C.size()){
                otimizada = true;
            }
            return otimizada;
        }
        
        // Escalona a matriz
        void Simplex::escalonamento(int linhaPivo, int colunaPivo){

            float valorPivo = A[linhaPivo][colunaPivo]; // Armazena o valor do pivô

            float valLinhaPivo[colunas]; // Coluna com pivô

            float valColunaPivo[linhas]; // Linha com pivô

            float novaLinha[colunas]; // Linha após processar o valor do pivô
             
             custoMin = custoMin - (C[colunaPivo]*(B[linhaPivo]/valorPivo));  //Calcula o custo mínimo em reais

             // Encontra a linha com o pivô e armazena o valor
             for(int i=0;i<colunas;i++){
                valLinhaPivo[i] = A[linhaPivo][i];
             }
             // Encontra a coluna com o pivô e armazena o valor
             for(int j=0;j<linhas;j++){
                valColunaPivo[j] = A[j][colunaPivo];
            }

            // Divide o valor da linha com o pivô pelo pivô e armazena na nova linha
             for(int k=0;k<colunas;k++){
                novaLinha[k] = valLinhaPivo[k]/valorPivo;
             }

            B[linhaPivo] = B[linhaPivo]/valorPivo;


             // Processa os outros coeficientes da matriz subtraindo múltiplos,
             // ignorando a linha com o pivô que já foi calculada
             for(int m=0;m<linhas;m++){
                
                if(m !=linhaPivo){
                    for(int p=0;p<colunas;p++){
                        float valorMultiplo = valColunaPivo[m];
                        A[m][p] = A[m][p] - (valorMultiplo*novaLinha[p]);
                    }
                }
             }

            // Processa os valores do vetor B da mesma maneira
            for(int i=0;i<B.size();i++){
                if(i != linhaPivo){
                    float valorMultiplo = valColunaPivo[i];
                    B[i] = B[i] - (valorMultiplo*B[linhaPivo]);

                }
            }
                // Menor coeficiente das restrições da função objetivo
                float valorMultiplo = C[colunaPivo];
                
                //Processa o vetor C subtraindo múltiplos
                 for(int i=0;i<C.size();i++){
                    C[i] = C[i] - (valorMultiplo*novaLinha[i]);

                }


             // Substitui a linha com o pivô na matriz A
             for(int i=0;i<colunas;i++){
                A[linhaPivo][i] = novaLinha[i];
             }


        }

        // Encontra os menores coeficientes das restrições na respectiva posição da função objetivo
        int Simplex::encontraColunaPivo(){

            int localizacao = 0;
            float minimo = C[0];



            for(int i=1;i<C.size();i++){
                if(C[i]<minimo){
                    minimo = C[i];
                    localizacao = i;
                }
            }

            return localizacao;

        }

        // Encontra a linha com o valor do pivô
        int Simplex::encontraLinhaPivo(int colunaPivo){
            float valoresPositivos[linhas];
            std::vector<float> resultado(linhas,0);
            int contValoresNegativos = 0;

            for(int i=0;i<linhas;i++){
                if(A[i][colunaPivo]>0){
                    valoresPositivos[i] = A[i][colunaPivo];
                }
                else{
                    valoresPositivos[i]=0;
                    contValoresNegativos+=1;
                }
            }
            
            //Se todos os valores forem negativos a função é ilimitada
            if(contValoresNegativos == linhas){
                ilimitada = true;
            }
            else{
                for(int i=0;i<linhas;i++){
                    float valor = valoresPositivos[i];
                    if(valor>0){
                        resultado[i] = B[i]/valor;

                    }
                    else{
                        resultado[i] = 0;
                    }
                }
            }
            // Encontra a localização do menor item da matriz B
            float min = 99999999;
            int localizacao = 0;
            for(int i=0;i<sizeof(resultado)/sizeof(resultado[0]);i++){
                if(resultado[i]>0){
                    if(resultado[i]<min){
                        min = resultado[i];

                        localizacao = i;
                    }
                }

            }

            return localizacao;

        }

        void Simplex::calculaSimplex(){
            bool fim = false;

            while(!fim){

                bool resultado = calculoAlgoritmoSimplex();

                if(resultado==true){
                    fim = true;
                }
            }

            for(int i=0;i < A.size(); i++){  // Os valores procurados estão nas colunas básicas da matriz
                int cont = 0;
                int indice = 0;
                for(int j=0; j < linhas; j++){
                    if(A[j][i]==0.0){
                        cont += 1;
                    }
                    else if(A[j][i]==1){
                        indice = j;
                    }

                }

                if(cont == linhas - 1){
                    std::cout << std::fixed;
                    std::cout.precision(0);
                    std::cout << "\nAlimento " << indice+8 << ": " << B[indice] << " unidades" << std::endl;
                }

            }

            std::cout << std::fixed;
            std::cout.precision(2);
            std::cout<<"\nValor em reais: R$ " << custoMin << std::endl;

        }


