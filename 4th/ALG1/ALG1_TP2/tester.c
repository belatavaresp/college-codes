#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define NTESTS 1
#define N 1000000
#define M 1000000
#define MAXX 100000

// Gera um grafo conexo com N vértices e M arestas
// Logo, M deve ser pelo menos N-1 se não dá merda.

// Esse programa não garante que as arestas do grafo 
// sejam sempre distintas


int main(){
	
	assert(M>=N-1);
	
	srand(time(0));
	
	for(int k=0;k<NTESTS;k++){
		
		printf("%d %d\n", N, M);
		
		for(int i=0;i<N-1;i++){
			
			int a = rand()%MAXX;
			int t = rand()%MAXX;
			int c = rand()%MAXX;
			int v = i+2;
			int w = (rand()%(i+1))+1;
			printf("%d %d %d %d %d\n", v, w, a, t, c);
			
		}
		for(int i=0;i<M-(N-1);i++){
			int a = rand()%MAXX;
			int t = rand()%MAXX;
			int c = rand()%MAXX;
			int v = (rand()%N)+1;
			int w;
			do{
				w = (rand()%N)+1;
			}while(w==v);
			
			printf("%d %d %d %d %d\n", v, w, a, t, c);
		}
		
		printf("\n");
		
	}
	
	
}		
