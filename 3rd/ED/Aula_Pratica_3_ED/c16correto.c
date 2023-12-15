#include <stdio.h>
#include <stdlib.h>

int actual_calc(int a, int b){
  int c;
  if (b != 0) {
    c = a/b;
    return c;
  } else {
    printf("Erro: divisão por zero\n");
    return 0;
  }
}

int calc(){
  int a;
  int b;
  a = 13;
  b = 0;
  actual_calc(a, b);
  return 0;
}

int main(){
  calc();
  return 0;
}
