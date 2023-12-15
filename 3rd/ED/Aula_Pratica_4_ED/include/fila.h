#ifndef CIRCULARQUEUE_HPP
#define CIRCULARQUEUE_HPP

const int MAX_SIZE = 10;

class CircularQueue {
public:
    int arr[MAX_SIZE];
    int front;
    int rear;
    
    CircularQueue();
    bool isEmpty();
    bool isFull();
    void enqueue(int value);
    void dequeue();
    int getFront();
    void print();
};

#endif
