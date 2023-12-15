#include <time.h>
#include <stdlib.h>

//creates a random vector with numbers 1-80
void randVector(int vec[], int n){
    srand (time(NULL));
    for(int i = 0; i<n; i++){
        vec[i] = (rand() % 81);
    }
} 
