#include "Queue.h"

template class Queue<ActorLevel>;

// Queue.hpp (implementation header)
template <typename T>
Queue<T>::Queue() : frontNode(nullptr), backNode(nullptr), size(0) {}

template <typename T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

template <typename T>
bool Queue<T>::enqueue(const T& item) {
    Node* newNode = new Node();
    newNode->item = item;
    newNode->next = nullptr;
    if (isEmpty()) {
        frontNode = newNode;
    }
    else {
        backNode->next = newNode;
    }
    backNode = newNode;
    size++;
    return true;
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    Node* temp = frontNode;
    T item = temp->item;
    if (frontNode == backNode) {
        frontNode = backNode = nullptr;
    }
    else {
        frontNode = frontNode->next;
    }
    delete temp;
    size--;
    return item;
}

template <typename T>
bool Queue<T>::dequeue(T& item) {
    if (isEmpty()) return false;
    Node* temp = frontNode;
    item = temp->item;
    if (frontNode == backNode) {
        frontNode = backNode = nullptr;
    }
    else {
        frontNode = frontNode->next;
    }
    delete temp;
    size--;
    return true;
}

template <typename T>
bool Queue<T>::getFront(T& item) const {
    if (isEmpty()) return false;
    item = frontNode->item;
    return true;
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return frontNode == nullptr;
}

template <typename T>
int Queue<T>::getSize() const {
    return size;
}

template <typename T>
void Queue<T>::reverse() {
    if (isEmpty()) return;
    T frontItem;
    dequeue(frontItem);
    reverse();
    enqueue(frontItem);
}

