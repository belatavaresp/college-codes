#include <cstdlib>
#include <iostream>
#include "fileHandler.h"
#include "fileMap.h"
using namespace std;

int main() {
    string flag, inputFile, outputFile;
    MinHeapNode* root = nullptr;
    FileMap outputs;
    cout << "Insira a flag e os arquivos (-flag <entrada> <saida>):\n";

    while (true) {
        cin >> flag;
        if (flag == "eof" || flag == "exit") {
            break;
        }
        if (cin >> inputFile >> outputFile) {
            if (flag == "-c") {
                root = new MinHeapNode();
                // Compactação do arquivo de entrada
                compressFile(inputFile, outputFile, *root);
                outputs.insert(outputFile, root);
            } else if (flag == "-d") {
                root = outputs.getValue(inputFile);
                if (root != nullptr) {
                    // Descompactação do arquivo binário e reescrita no arquivo de saída de texto
                    decompressFile(inputFile, outputFile, *root);
                    delete root;
                } else {
                    cerr << "Arquivo binário não encontrado." << endl;
                }
            } else {
                cerr << "Flag inválida. Use -c para compactar ou -d para descompactar." << endl;
                cout << "Insira a flag e os arquivos (-flag <entrada> <saida>):\n";
            }
        } else {
            cerr << "Insira dois nomes de arquivo." << endl;
        }
    }

    return 0;
}
