#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <iostream>

// ---------------------------------------------
// THIS HEADER CONTAINS A IMPLEMENTATION OF
// A STANDARD VECTOR STRUCTURE USING TEMPLATES
// ---------------------------------------------

template <typename T>
class Vector
{
private:
    T *vec;       // address for data
    int capacity; // total number of elements that fit the vector
    int size;     // total of elements currently in the vector

public:
    // constructors
    Vector()
    {
        vec = new T[1]();
        capacity = 1;
        size = 0;
    }

    Vector(int n)
    {
        vec = new T[n]();
        capacity = n;
        size = n;
    }

    // destructor
    ~Vector()
    {
        delete[] vec;
    }

    // clears data inside of vector
    void clear()
    {
        delete[] vec;
        vec = new T[1]();
        capacity = 1;
        size = 0;
    }

    // push elements into the vector
    void push(T data)
    {
        // vector full
        if (capacity == size)
        {
            T *temp = new T[2 * capacity];

            for (int i = 0; i < capacity; i++)
            {
                temp[i] = vec[i];
            }

            delete[] vec;
            capacity *= 2;
            vec = temp;
        }

        vec[size] = data;
        size++;
    }

    // remove last element
    void pop()
    {
        size--;
    }

    // return current size of vector
    int getSize()
    {
        return size;
    }

    // access element at index
    T& at(int index)
    {
        if (index >= 0 && index < size)
        {
            return vec[index];
        }
        else
        {
            throw std::out_of_range("Index out of range");
        }
    }

    // get the data address
    T* getData()
    {
        return vec;
    }

    // get the top element of the vector
    T top()
    {
        if (size > 0)
        {
            return vec[size - 1];
        }
        else
        {
            throw std::out_of_range("Vector is empty");
        }
    }

    // copies a vector data to another vector
    void copy(Vector<T> &copy)
    {
        for (int i = 0; i < size; i++)
        {
            copy.vec[i] = vec[i];
        }
    }

};

#endif