#ifndef HCODING_H
#define HCODING_H

#include <iostream>
#include "minHeap.h"
#include "hTree.h"
#include "codeMap.h"
#include "freqMap.h"

using std::cout;
using std::endl;

void assignCodes(MinHeapNode* node, const string& code, CodeMap& codes)
{
    if (isLeaf(node)) {
        codes.insert(node->data, code);
    }
    else {
        if (node->left) {
            assignCodes(node->left, code + "0", codes);
        }
        if (node->right) {
            assignCodes(node->right, code + "1", codes);
        }
    }
}

string huffmanCodes(const string& input, MinHeapNode& root)
{
    FrequencyMap freqMap;
        
    for (char c : input) {
        freqMap.insert(c);
    }
    
    char* charArray;
    int* freqArray;
    
    freqMap.getCharFrequencyArrays(charArray, freqArray);
    
    int size = freqMap.getSize();

    // Construct Huffman Tree
    root = *buildHuffmanTree(charArray, freqArray, size);

    // Create a CodeMap to store the codes for each character
    CodeMap codes;

    // Assign codes recursively
    assignCodes(&root, "", codes);

    // Return the codes as a string (optional)
    string codesString;
    for (char ch : input) {
        codesString += codes.getCode(ch);
    }

    // Clean up memory
    delete[] charArray;
    delete[] freqArray;

    return codesString;
}

string decodeFile(MinHeapNode& root, string s)
{
    string ans = "";
    MinHeapNode* curr = &root;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') {
            if (curr->left) {
                curr = curr->left;
            } else {
                // Handle case where the path doesn't exist in the Huffman tree
                cout << "Error: Invalid Huffman encoding." << endl;
                return "";
            }
        } else {
            if (curr->right) {
                curr = curr->right;
            } else {
                // Handle case where the path doesn't exist in the Huffman tree
                cout << "Error: Invalid Huffman encoding." << endl;
                return "";
            }
        }
 
        // reached leaf node
        if (isLeaf(curr)) {
            ans += curr->data;
            curr = &root;
        }
    }
    return ans;
}


#endif
