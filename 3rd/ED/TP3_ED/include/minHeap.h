#ifndef MINHEAP_H
#define MINHEAP_H

#include "vector.h"
#include <iostream>
using std::cout;

class MinHeapNode {
public:
    char data;
    unsigned freq;
    MinHeapNode* left;
    MinHeapNode* right;

    MinHeapNode(char data, unsigned freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }

    MinHeapNode(){
        left = right = nullptr;
    }
};

// Utility function to check if this node is leaf
int isLeaf(MinHeapNode* root)
{
	return !(root->left) && !(root->right);
}

class MinHeap {
public:
    unsigned size;
    unsigned capacity;
    Vector<MinHeapNode*>* array;

    MinHeap(unsigned capacity) {
        size = 0;
        this->capacity = capacity;
        this->array = new Vector<MinHeapNode*>(capacity);
    }

    MinHeap() {
        size = 0;
        this->capacity = 2;
    }

    void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b) {
        MinHeapNode* t = *a;
        *a = *b;
        *b = t;
    }

    void minHeapify(int idx) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && array->at(left)->freq < array->at(smallest)->freq)
            smallest = left;

        if (right < size && array->at(right)->freq < array->at(smallest)->freq)
            smallest = right;

        if (smallest != idx) {
            swapMinHeapNode(&array->at(smallest), &array->at(idx));
            minHeapify(smallest);
        }
    }

    bool isSizeOne() {
        return (size == 1);
    }

    MinHeapNode* extractMin() {
        MinHeapNode* temp = array->at(0);
        array->at(0) = array->at(size - 1);

        --size;
        minHeapify(0);

        return temp;
    }

    void insertMinHeap(MinHeapNode* minHeapNode) {
        ++size;
        int i = size - 1;

        while (i && minHeapNode->freq < array->at((i - 1) / 2)->freq) {
            array->at(i) = array->at((i - 1) / 2);
            i = (i - 1) / 2;
        }

        array->at(i) = minHeapNode;
    }

    void buildMinHeap() {
        int n = size - 1;

        for (int i = (n - 1) / 2; i >= 0; --i)
            minHeapify(i);
    }

    static MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
        MinHeap* minHeap = new MinHeap(size);

        for (int i = 0; i < size; ++i){
            minHeap->array->at(i) = new MinHeapNode(data[i], freq[i]);
        }
        minHeap->size = size;
        minHeap->buildMinHeap();

        return minHeap;
    }
};

#endif
