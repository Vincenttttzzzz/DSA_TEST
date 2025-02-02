//// List.h - Specification of List ADT
//// Implementation of List is in List.h because of the use of template
//#pragma once
//#include <iostream>
//
//using namespace std;
//
//const int MAX_SIZE = 1;
//
//class List
//{
//private:
//    int items[MAX_SIZE];
//    int size;
//
//public:
//    // Constructor
//    List();
//    bool add(int item);
//    void print();
//    void rotate(int num);
//
//};



// version 2
//#pragma once
//#include <iostream>
//
//using namespace std;
//
//class List {
//private:
//    int* items;       // Dynamically allocated array
//    int maxSize;      // Maximum capacity
//    int size;         // Current number of elements
//
//    void resize(int newSize); // Function to resize the array
//
//public:
//    // Constructor
//    List(int initialSize = 10); // Start with a small default size
//
//    // Destructor
//    ~List();
//
//    // Add an item to the list
//    bool add(int item);
//
//    // Get an item at a specified index
//    int get(int index) const;
//
//    // Get the size of the list
//    int getLength() const;
//
//    // Print the list
//    void print() const;
//
//    // Clear all items from the list
//    void clear();
//};





// version 3
#pragma once
#include <iostream>

using namespace std;

template <typename T>
class List {
private:
    T* items;       // Dynamically allocated array
    int maxSize;    // Maximum capacity
    int size;       // Current number of elements

    void resize(int newSize);

public:
    // Constructor
    List(int initialSize = 10);

    // Destructor
    ~List();

    // Add an item to the list
    bool add(T item);

    // Get an item at a specified index
    T get(int index) const;

    // Get the size of the list
    int getLength() const;

    // Print the list
    void print() const;

    // Clear all items from the list
    void clear();
};

// Constructor
template <typename T>
List<T>::List(int initialSize) : maxSize(initialSize), size(0) {
    items = new T[maxSize];
}

// Destructor
template <typename T>
List<T>::~List() {
    delete[] items;
}

// Resize the array
template <typename T>
void List<T>::resize(int newSize) {
    T* newItems = new T[newSize];
    for (int i = 0; i < size; i++) {
        newItems[i] = items[i];
    }
    delete[] items;
    items = newItems;
    maxSize = newSize;
}

// Add an item to the list
template <typename T>
bool List<T>::add(T item) {
    if (size >= maxSize) {
        resize(maxSize * 2);  // Double the size when full
    }
    items[size++] = item;
    return true;
}

// Get an item at a specified index
template <typename T>
T List<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of bounds");
    }
    return items[index];
}

// Get the size of the list
template <typename T>
int List<T>::getLength() const {
    return size;
}

// Print the list
template <typename T>
void List<T>::print() const {
    for (int i = 0; i < size; i++) {
        cout << items[i] << " ";
    }
    cout << endl;
}

// Clear all items from the list
template <typename T>
void List<T>::clear() {
    size = 0;
}
