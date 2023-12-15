#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include "point.h"

// ---------------------------------------------
// THIS HEADER HAS ALL THE SORTING FUNCTIONS
// THAT SORT VECTORS'S POINT DATA
// ---------------------------------------------

// MERGE SORT ------------------------------------------------------------------------------------

// COMPARING Y COORDINATES FIRST

// function used in merge sort to merge subvectors
void mergeY(point vec[], int ini, int mid, int end, point vecAux[])
{
    int left = ini;
    int right = mid;
    for (int i = ini; i < end; ++i)
    {
        if ((left < mid) && ((right >= end) || (vec[left].y < vec[right].y) || (vec[left].y == vec[right].y && vec[left].y < vec[right].y)))
        {
            vecAux[i] = vec[left];
            ++left;
        }
        else
        {
            vecAux[i] = vec[right];
            ++right;
        }
    }
    for (int i = ini; i < end; ++i)
    {
        vec[i] = vecAux[i];
    }
}

void mergeSortY(point vec[], int begin, int end, point vecAux[])
{
    if ((end - begin) < 2)
        return;

    int mid = ((begin + end) / 2);
    mergeSortY(vec, begin, mid, vecAux);
    mergeSortY(vec, mid, end, vecAux);
    mergeY(vec, begin, mid, end, vecAux);
}

void mergeSortY(point vec[], int size)
{
    point vecAux[size];
    mergeSortY(vec, 0, size, vecAux);
}

// COMPARING BY POLAR ANGLE

// function used in merge sort to merge subvectors
void mergeP(Vector<point> &points, int start, int mid, int end, point reference)
{
    int leftSize = mid - start + 1;
    int rightSize = end - mid;

    Vector<point> leftSubvector, rightSubvector;
    for (int i = 0; i < leftSize; i++)
    {
        leftSubvector.push(points.at(start + i));
    }
    for (int j = 0; j < rightSize; j++)
    {
        rightSubvector.push(points.at(mid + 1 + j));
    }

    int leftIndex = 0, rightIndex = 0;
    for (int i = start; i <= end; i++)
    {
        if (leftIndex == leftSize)
        {
            points.at(i) = rightSubvector.at(rightIndex);
            rightIndex++;
        }
        else if (rightIndex == rightSize)
        {
            points.at(i) = leftSubvector.at(leftIndex);
            leftIndex++;
        }
        else if (comparePolar(reference, leftSubvector.at(leftIndex), rightSubvector.at(rightIndex)) < 0)
        {
            points.at(i) = leftSubvector.at(leftIndex);
            leftIndex++;
        }
        else
        {
            points.at(i) = rightSubvector.at(rightIndex);
            rightIndex++;
        }
    }
}

void mergePolar(Vector<point> &points, int start, int end,
                point reference)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergePolar(points, start, mid, reference);   // first half
        mergePolar(points, mid + 1, end, reference); // second half
        mergeP(points, start, mid, end, reference);
    }
}

// INSERTION SORT -----------------------------------------------------------------------------------------

// COMPARING Y COORDINATES FIRST

void insertionSortY(point vec[], int size)
{
    int i, j;
    point key;
    for (i = 1; i < size; i++)
    {
        key = vec[i];
        j = i - 1;

        // Compare points based on x and y values
        while (j >= 0 && (vec[j].y > key.y || (vec[j].y == key.y && vec[j].x > key.x)))
        {
            vec[j + 1] = vec[j];
            j = j - 1;
        }

        vec[j + 1] = key;
    }
}

// COMPARING BY POLAR ANGLE

void insertionSortPolar(point vec[], int size)
{
    int i, j;
    point key;
    for (i = 1; i < size; i++)
    {
        key = vec[i];
        j = i - 1;

        // Compare points using the provided compare function
        while (j >= 0 && compare(&vec[j], &key) > 0)
        {
            vec[j + 1] = vec[j];
            j = j - 1;
        }

        vec[j + 1] = key;
    }
}

// RADIX SORT -----------------------------------------------------------------------------------------

// COMPARING Y COORDINATES FIRST

void radixSortY(point vec[], int size)
{
    int i;
    point *b = new point;
    point big = vec[0];
    int exp = 1;

    b = new point[size];

    for (i = 0; i < size; i++)
    {
        if (vec[i].y > big.y)
            big = vec[i];
    }

    while (big.y / exp > 0)
    {
        int bucket[10] = {0};
        for (i = 0; i < size; i++)
            bucket[(vec[i].y / exp) % 10]++;
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (i = size - 1; i >= 0; i--)
            b[--bucket[(vec[i].y / exp) % 10]] = vec[i];
        for (i = 0; i < size; i++)
            vec[i] = b[i];
        exp *= 10;
    }

    delete b;
}

// COMPARING BY POLAR ANGLE (USING COUNTING SORT AS AUXILIARY)

// Counting sort based on a specific digit of the polar angle
void countingSortByDigit(point *points, int size, int exp)
{
    const int n = size;
    point *output = new point[n];
    Vector<int> count(10);

    // Calculate the count of points based on the current digit
    for (int i = 0; i < n; i++)
    {
        double polarAngle = calculatePolarAngle(points[i]);
        int digit = static_cast<int>(std::round(polarAngle / exp)) % 10;
        count.at(digit)++;
    }

    // Adjust the count array to store the actual position of the points in the output array
    for (int i = 1; i < 10; i++)
    {
        count.at(i) += count.at(i - 1);
    }

    // Build the output array based on the count array and the current digit
    for (int i = n - 1; i >= 0; i--)
    {
        double polarAngle = calculatePolarAngle(points[i]);
        int digit = static_cast<int>(std::round(polarAngle / exp)) % 10;
        output[count.at(digit) - 1] = points[i];
        count.at(digit)--;
    }

    // Copy the sorted points from the output array back to the original array
    for (int i = 0; i < n; i++)
    {
        points[i] = output[i];
    }

    delete[] output;
}

void radixSortPolar(point *points, int size)
{
    // Find the maximum value of the polar angle
    double maxPolarAngle = -1;
    for (int i = 0; i < size; i++)
    {
        double polarAngle = calculatePolarAngle(points[i]);
        maxPolarAngle = std::max(maxPolarAngle, polarAngle);
    }

    // Perform counting sort for each digit of the polar angle
    for (int exp = 1; maxPolarAngle / exp > 0; exp *= 10)
    {
        countingSortByDigit(points, size, exp);
    }
}

//-----------------------------------------------------------------------------------------

#endif