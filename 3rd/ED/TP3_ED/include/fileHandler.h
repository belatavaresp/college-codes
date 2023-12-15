#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <iostream>
#include <fstream>
#include <string>
#include "hCoding.h"

using std::cout;
using std::endl;

void compressFile(const std::string& inputFilename, const std::string& outputFilename, MinHeapNode& root) {
    // Abrir o arquivo de entrada
    std::ifstream inputFile(inputFilename);
    if (!inputFile) {
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return;
    }

    // Ler o conteúdo do arquivo de entrada
    std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

    // Fechar o arquivo de entrada
    inputFile.close();

    // Compactar o conteúdo usando o algoritmo de Huffman
    std::string compressedContent = huffmanCodes(content,root);

    // Abrir o arquivo de saída
    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
        return;
    }

    // Escrever o tamanho dos dados compactados
    size_t compressedSize = compressedContent.size();
    outputFile.write(reinterpret_cast<const char*>(&compressedSize), sizeof(size_t));

    // Escrever os dados compactados no arquivo de saída
    outputFile.write(compressedContent.c_str(), compressedSize);

    // Fechar o arquivo de saída
    outputFile.close();

    std::cout << "Compactação concluída com sucesso." << std::endl;
}

void decompressFile(const std::string& inputFilename, const std::string& outputFilename, MinHeapNode& root) {
    // Abrir o arquivo compactado binário
    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Erro ao abrir o arquivo compactado." << std::endl;
        return;
    }

    // Ler o tamanho dos dados compactados
    size_t compressedSize = 0;
    inputFile.read(reinterpret_cast<char*>(&compressedSize), sizeof(size_t));

    // Ler os dados compactados
    std::string compressedContent(compressedSize, '\0');
    inputFile.read(&compressedContent[0], compressedSize);

    // Fechar o arquivo compactado binário
    inputFile.close();

    // Descompactar o conteúdo usando o algoritmo de Huffman
    std::string decompressedContent = decodeFile(root, compressedContent);

    // Abrir o arquivo de saída (arquivo de texto)
    std::ofstream outputFile(outputFilename);
    if (!outputFile) {
        std::cerr << "Erro ao abrir o arquivo de saída." << std::endl;
        return;
    }

    // Escrever o conteúdo descompactado no arquivo de saída
    outputFile << decompressedContent;

    // Fechar o arquivo de saída
    outputFile.close();

    std::cout << "Descompactação concluída com sucesso." << std::endl;
}

#endif