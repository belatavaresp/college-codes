#ifndef HTREE_H
#define HTREE_H

#include "minHeap.h"

MinHeapNode* buildHuffmanTree(char data[],int freq[], int size)
{   
	MinHeapNode *left, *right, *top;

	// Step 1: Create a min heap of capacity
	// equal to size. Initially, there are
	// modes equal to size.
	MinHeap* minHeap = new MinHeap();
    minHeap = minHeap->createAndBuildMinHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1
	while (!minHeap->isSizeOne()) {

		// Step 2: Extract the two minimum
		// freq items from min heap
		left = minHeap->extractMin();
		right = minHeap->extractMin();

		// Step 3: Create a new internal
		// node with frequency equal to the
		// sum of the two nodes frequencies.
		// Make the two extracted node as
		// left and right children of this new node.
		// Add this node to the min heap
		// '$' is a special value for internal nodes, not
		// used
		top = new MinHeapNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		minHeap->insertMinHeap(top);
	}

	// Step 4: The remaining node is the
	// root node and the tree is complete.
	return minHeap->extractMin();
}

int huffmanTreeSize(MinHeapNode* root) {
    // Base case: if the tree is empty (root is null), return 0
    if (root == nullptr) {
        return 0;
    }

    // Recursive case: calculate the height of the left and right subtrees
    int leftHeight = huffmanTreeSize(root->left);
    int rightHeight = huffmanTreeSize(root->right);

    // Return the maximum height among the left and right subtrees, plus 1 for the root node
    return 1 + std::max(leftHeight, rightHeight);
}


#endif
