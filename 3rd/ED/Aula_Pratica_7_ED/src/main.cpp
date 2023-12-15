#include "shellSort.h"
#include "heapSort.h"
#include "fstream"
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    int n = 1;
    fstream f;
    f.open("vecSizes.txt");
    if (f.is_open())
    {
        while (f >> n)
        {
            cout << "TAMANHO: " << n << endl;

            int* vec = static_cast<int*>(calloc(n, sizeof(int))); // Allocate memory for vec
            int* vecAux = static_cast<int*>(calloc(n, sizeof(int))); // Allocate memory for vecAux

            if (vec == nullptr || vecAux == nullptr)
            {
                cout << "ERRO: FALHA NA ALOCAÇÃO DE MEMÓRIA" << endl;
                free(vec);
                free(vecAux);
                return 1;
            }

            randVector(vec, n); // Assign random values to the vector

            cout << "VETOR ALEATÓRIO: ";
            printvec(vec, n);

            clock_t start, end;
            double heapSortTime, shellSortTime;

            // Measure execution time for Heap Sort
            start = clock();
            heapSort(vec, n);
            end = clock();
            heapSortTime = double(end - start) / CLOCKS_PER_SEC;
            heapSortTime = heapSortTime * 1000000;

            cout << endl << "VETOR APÓS HEAPSORT: ";
            printvec(vec, n);
            cout << endl <<  "TEMPO DE EXECUÇÃO (HEAPSORT): " << heapSortTime << " MICROSSEGUNDOS" << endl;

            memcpy(vecAux, vec, n * sizeof(int)); // Copy elements from vec to vecAux

            // Measure execution time for Shell Sort
            start = clock();
            shellSort(vecAux, n);
            end = clock();
            shellSortTime = double(end - start) / CLOCKS_PER_SEC;
            shellSortTime = shellSortTime * 1000000;

            cout << "VETOR APÓS SHELLSORT: ";
            printvec(vecAux, n);
            cout << endl << "TEMPO DE EXECUÇÃO (SHELLSORT): " << shellSortTime << " MICROSSEGUNDOS" << endl;

            // Free the allocated memory
            free(vec);
            free(vecAux);
            cout << endl << endl;
        }
        f.close();
    }
    else
    {
        cout << "ERRO: FALHA NA LEITURA DO ARQUIVO" << endl;
        return 1;
    }
    return 0;
}