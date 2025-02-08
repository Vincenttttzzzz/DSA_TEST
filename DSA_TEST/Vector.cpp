#include "Vector.h"
//#include "HashTable.h"

// Note: Because vectorClass is a template, all definitions must be visible
// at compile time. You can either include this file in Vector.h or use explicit
// template instantiation for the types you need.


template class vectorClass<std::weak_ptr<Actor>>;
template class vectorClass<std::weak_ptr<Movie>>;



template <typename T>
vectorClass<T>::vectorClass() : arr(new T[1]), capacity(1), current(0) {}

// Destructor
template <typename T>
vectorClass<T>::~vectorClass() {
    delete[] arr;
}

// Copy constructor
template <typename T>
vectorClass<T>::vectorClass(const vectorClass<T>& other)
    : capacity(other.capacity), current(other.current) {
    arr = new T[capacity];
    for (int i = 0; i < current; i++) {
        arr[i] = other.arr[i];
    }
}

// Assignment operator
template <typename T>
vectorClass<T>& vectorClass<T>::operator=(const vectorClass<T>& other) {
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

// push (append at the end)
template <typename T>
void vectorClass<T>::push(const T& data) {
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

// push at a specific index
template <typename T>
void vectorClass<T>::push(const T& data, int index) {
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

// Const version of get
template <typename T>
const T& vectorClass<T>::get(int index) const {
    if (index < 0 || index >= current) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

// Non-const version of get
template <typename T>
T& vectorClass<T>::get(int index) {
    if (index < 0 || index >= current) {
        throw std::out_of_range("Index out of bounds");
    }
    return arr[index];
}

// pop: remove the last element
template <typename T>
void vectorClass<T>::pop() {
    if (current > 0) {
        current--;
    }
}

// Return the current number of elements
template <typename T>
int vectorClass<T>::size() const {
    return current;
}

// Return the capacity of the vector
template <typename T>
int vectorClass<T>::getcapacity() const {
    return capacity;
}

// Print the elements of the vector
template <typename T>
void vectorClass<T>::print() const {
    for (int i = 0; i < current; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Return a pointer to the underlying array
template <typename T>
T* vectorClass<T>::data() {
    return arr;
}

// ----- Explicit Instantiation -----
// If you know which types you'll be using, you can explicitly instantiate them here.
// For example:
// template class vectorClass<int>;
// template class vectorClass<std::weak_ptr<Actor>>;
// template class vectorClass<Movie>;
// 
// If you don't do this, you'll need to include this .cpp file in your build via the header.
