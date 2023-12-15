#include "mat.h"

int main(){
    mat_tipo a, b, c;
    int optx = 8;
    int opty = 8;

    criaMatriz(&a,optx,opty,0);
    inicializaMatrizAleatoria(&a);
    criaMatriz(&b,opty,optx,1);
    inicializaMatrizAleatoria(&b);
    criaMatriz(&c,optx,optx,2);
    inicializaMatrizNula(&c);
    multiplicaMatrizes(&a,&b,&c);
    imprimeMatriz(&c);
    destroiMatriz(&a);
    destroiMatriz(&b);
    destroiMatriz(&c);
}
