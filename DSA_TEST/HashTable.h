
// Latest ver
#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_SIZE = 10007; // Change from 101 to 1009 or 5003
typedef int KeyType;

template <typename T>
struct HashNode {
    int key;        // Search key
    T item;         // Data item
    HashNode* next;     // Pointer to the next node
};

template <typename T>
class HashTable {
private:
    std::vector<HashNode<T>*> items;
    int size;

public:
    HashTable();
    ~HashTable();
    void resize();
    int hash(KeyType key) const;
    size_t nextPrime(size_t n);
    bool isPrime(size_t n);
    bool add(KeyType newKey, T newItem);
    //void insertToLinkedList(int key, T item);
    //void remove(KeyType key);
    T get(KeyType key) const;
    bool isEmpty();
    int getLength();
    void print();
};


