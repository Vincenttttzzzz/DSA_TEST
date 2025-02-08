#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include <iostream>
#include "Actor.h"


template <typename T>
class vectorClass {
private:
    T* arr;
    int capacity;
    int current;

public:
    // Constructor
    vectorClass() : arr(new T[1]), capacity(1), current(0) {}

    // Destructor
    ~vectorClass() { delete[] arr; }

    // Copy constructor (important to prevent double deletion)
    vectorClass(const vectorClass& other) : capacity(other.capacity), current(other.current) {
        arr = new T[capacity];
        for (int i = 0; i < current; i++) {
            arr[i] = other.arr[i];
        }
    }

    // Assignment operator
    vectorClass& operator=(const vectorClass& other) {
        if (this != &other) {
            delete[] arr;
            capacity = other.capacity;
            current = other.current;
            arr = new T[capacity];
            for (int i = 0; i < current; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    void push(const T& data) {
        if (current == capacity) {
            T* temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            capacity *= 2;
            arr = temp;
        }
        arr[current] = data;
        current++;
    }

    void push(const T& data, int index) {
        if (index < 0 || index > current) {
            throw std::out_of_range("Index out of bounds");
        }
        if (index == current) {
            push(data);
        }
        else {
            arr[index] = data;
        }
    }

    // Fixed get function with const correctness
    const T& get(int index) const {
        if (index < 0 || index >= current) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    // Non-const version of get
    T& get(int index) {
        if (index < 0 || index >= current) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    void pop() {
        if (current > 0) {
            current--;
        }
    }

    int size() const { return current; }
    int getcapacity() const { return capacity; }

    void print() const {
        for (int i = 0; i < current; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    T* data() { return arr; }

};

#endif // VECTOR_CLASS_H
