#include <iostream>
#include "fila.h"
using namespace std;

CircularQueue::CircularQueue() {
    front = -1;
    rear = -1;
}

bool CircularQueue::isEmpty() {
    return front == -1 && rear == -1;
}

bool CircularQueue::isFull() {
    return (rear + 1) % MAX_SIZE == front;
}

void CircularQueue::enqueue(int value) {
    if (isFull()) {
        cout << "Error: Queue is full\n";
        return;
    }
    if (isEmpty()) {
        front = 0;
        rear = 0;
    } else {
        rear = (rear + 1) % MAX_SIZE;
    }
    arr[rear] = value;
}

void CircularQueue::dequeue() {
    if (isEmpty()) {
        cout << "Error: Queue is empty\n";
        return;
    } else if (front == rear) {
        front = -1;
        rear = -1;
    } else {
        front = (front + 1) % MAX_SIZE;
    }
}

int CircularQueue::getFront() {
    if (isEmpty()) {
        cout << "Error: Queue is empty\n";
        return -1;
    }
    return arr[front];
}

void CircularQueue::print() {
    if (isEmpty()) {
        cout << "Queue is empty\n";
        return;
    }
    cout << "Front: " << front << ", Rear: " << rear << ", Elements: ";
    int i = front;
    while (i != rear) {
        cout << arr[i] << " ";
        i = (i + 1) % MAX_SIZE;
    }
    cout << arr[rear] << endl;
}
