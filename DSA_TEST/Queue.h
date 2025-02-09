// Queue.h
#pragma once
#include <iostream>
#include <stdexcept>
#include "Actor.h"
#include "Graph.h"

template <typename T>
class Queue {
private:
    struct Node {
        T item;
        Node* next;
    };
    Node* frontNode;
    Node* backNode;
    int size;

public:
    Queue();
    ~Queue();

    bool enqueue(const T& item);
    T dequeue();
    bool dequeue(T& item);
    bool getFront(T& item) const;
    bool isEmpty() const;
    int getSize() const;
    void reverse();
};
