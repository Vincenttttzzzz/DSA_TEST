#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

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
    // Constructor
    Queue() : frontNode(nullptr), backNode(nullptr), size(0) {}

    // Destructor (MUST BE IN HEADER FOR TEMPLATE CLASSES)
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Enqueue item
    bool enqueue(const T& item) {
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

    // Dequeue and return item (throws if empty)
    T dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
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

    // Dequeue and retrieve via reference (returns success)
    T dequeue(T& item) {
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

    // Other methods (getFront, isEmpty, getSize, etc.) 
    bool getFront(T& item) const {
        if (isEmpty()) return false;
        item = frontNode->item;
        return true;
    }

    bool isEmpty() const { return frontNode == nullptr; }
    int getSize() const { return size; }

    void displayItems() const {
        Node* temp = frontNode;
        while (temp != nullptr) {
            cout << temp->item << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void reverse() {
        if (isEmpty()) return;

        T frontItem;
        dequeue(frontItem);
        reverse();
        enqueue(frontItem);
    }
};