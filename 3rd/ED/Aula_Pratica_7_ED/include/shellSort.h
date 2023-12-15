#include <iostream>
#include "randVector.h"

int shellSort(int vec[],int n)
{
    //using Sedgewick's Gap Sequence to iterate h
    int gaps[] = {1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305, 260609};

	// Start with a big h, then reduce the h
	for (int i = sizeof(gaps) / sizeof(gaps[0]) - 1; i >= 0; i--)
	{
        int h = gaps[i];

		for (int i = h; i < n; i++)
		{
			// add a[i] to the elements that have been h sorted
			// save a[i] in temp and make a hole at position i
			int temp = vec[i];

			// shift earlier h-sorted elements up until the correct
			// location for a[i] is found
			int j;			
			for (j = i; j >= h && vec[j - h] > temp; j -= h)
				vec[j] = vec[j - h];
			
			// put temp (the original a[i]) in its correct location
			vec[j] = temp;
		}
	}
	return 0;
}

void printvec(int vec[], int n)
{
	for (int i=0; i<n; i++)
		std::cout << vec[i] << " ";
}

