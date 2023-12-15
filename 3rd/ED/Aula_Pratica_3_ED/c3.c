#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int i;
  int *a;

  for (i=0; i < 10; i++){
    a = malloc(sizeof(int) * 100);
  }

  //nao libera a memoria do a corretamente pois está fora do for
  free(a);
  return 0;
}

