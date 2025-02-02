//// HashTable.h - - Specification of HashTable ADT
//#include<string>
//#include<iostream>
//using namespace std;
//
//const int MAX_SIZE = 101;
//typedef int KeyType;
////typedef string ItemType;
//
//
//template <typename T>
//struct Node {
//	int key;        // search key
//	T item;         // data item (Actor, Movie, LinkedList, etc.)
//	Node* next;     // pointer to the next node
//};
//
//
//template <typename T>
//class HashTable
//{
//private:
//	Node<T>* items[MAX_SIZE];
//	int  size;			// number of items in the HashTable
//
//public:
//	// constructor
//	HashTable();
//
//	// destructor
//	~HashTable();
//
//	int hash(KeyType key);
//
//	// add a new item with the specified key to the HashTable	
//	bool add(KeyType newKey, T newItem);
//
//	// Specialized insert for LinkedList<T>
//	void insertToLinkedList(int key, T item);
//
//	// remove an item with the specified key in the HashTable
//	void remove(KeyType key);
//
//	// get an item with the specified key in the HashTable (retrieve)
//	T get(KeyType key);
//
//	// check if the HashTable is empty
//	bool isEmpty();
//
//	// check the size of the HashTable
//	int getLength();
//
//	//------------------- Other useful functions -----------------
//	// display the items in the HashTable
//	void print();  // print all elements in array
//};
//
//




// Latest ver
#pragma once
#include <string>
#include <iostream>
#include "List.h"

using namespace std;

const int MAX_SIZE = 1009; // Change from 101 to 1009 or 5003
typedef int KeyType;

template <typename T>
struct Node {
    int key;        // Search key
    T item;         // Data item
    Node* next;     // Pointer to the next node
};

template <typename T>
class HashTable {
private:
    Node<T>* items[MAX_SIZE];
    int size;

public:
    HashTable();
    ~HashTable();
    int hash(KeyType key) const;
    bool add(KeyType newKey, T newItem);
    void insertToLinkedList(int key, T item);
    void remove(KeyType key);
    T get(KeyType key) const;
    bool isEmpty();
    int getLength();
    void print();
};



template <typename T>
HashTable<T>::HashTable() {
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;
    }
    size = 0;
}


template <typename T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node<T>* current = items[i];
        while (current != nullptr) {
            Node<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        items[i] = nullptr;
    }
}


//template <typename T>
//int HashTable<T>::hash(KeyType newKey) {
//    int hashValue = 0;
//
//    for (char c : newKey) {
//        if (isalpha(c))
//        {
//            if (isupper(c))
//                return (int)c - (int)'A';
//            else
//                return (int)c - (int)'a' + 26;
//        }
//        else
//            return -1;
//    }
//
//    std::cout << "Hashed key: " << hashValue;
//
//    // Modulo operation to ensure hash value is within array bounds
//    return hashValue % MAX_SIZE;
//}

//template <typename T>
//int HashTable<T>::hash(KeyType key) {
//    int hashValue = 0;
//    for (char c : key) {
//        hashValue = (hashValue * 37 + c) % MAX_SIZE;
//    }
//    return hashValue;
//
//}


//template <typename T>
//int HashTable<T>::hash(KeyType key) const {
//    // A prime number multiplier to reduce clustering
//    const int primeMultiplier = 31;
//    unsigned int hashValue = 0;
//
//    while (key > 0) {
//        // XOR the lower bits of the key and multiply by the prime
//        hashValue = (hashValue ^ (key & 0xFF)) * primeMultiplier;
//
//        // Shift the key to process the next part
//        key >>= 8; // Move to the next byte
//    }
//
//    // Modulo operation to ensure hash value fits within the hash table size
//    return hashValue % MAX_SIZE;
//}

template <typename T>
int HashTable<T>::hash(KeyType key) const {
    const int primeMultiplier = 31;
    unsigned int hashValue = 0;

    while (key > 0) {
        hashValue = hashValue * primeMultiplier + (key % 10); // Use digits for hashing
        key /= 10;
    }

    return hashValue % MAX_SIZE;
}

//template <typename T>
//int HashTable<T>::hash(KeyType key) const {
//    unsigned int unsignedKey = static_cast<unsigned int>(key);
//
//    const int primeMultiplier = 31;
//    unsigned int hashValue = 0;
//
//    //std::cout << "Hashing key: " << unsignedKey << std::endl;
//
//    while (unsignedKey > 0) {
//        hashValue = (hashValue ^ (unsignedKey & 0xFF)) * primeMultiplier;
//        unsignedKey >>= 8;
//    }
//
//    //std::cout << "Computed hash: " << hashValue % MAX_SIZE << std::endl;
//
//    return hashValue % MAX_SIZE;
//}


template <typename T>
bool HashTable<T>::add(KeyType newKey, T newItem) {

    int index = hash(newKey);

    // Traverse the chain at the hash index to check for duplicate keys
    Node<T>* current = items[index];
    while (current != nullptr) {
        if (current->key == newKey) {
            // Duplicate key found, reject the new entry
            return false;
        }
        current = current->next;
    }

    // Create and initialize a new node
    Node<T>* newNode = new Node<T>();
    newNode->key = newKey;
    newNode->item = newItem;
    newNode->next = nullptr;

    // Add the new node at the front of the chain
    newNode->next = items[index];
    items[index] = newNode;

    size++;
    return true;
}


template <typename T>
void HashTable<T>::insertToLinkedList(int key, T item) {
    int index = hash(key);
    Node<List>* current = items[index];

    // Find the node with the given key
    while (current != nullptr) {
        if (current->key == key) {
            current->item.add(item); // Add to the linked list
            return;
        }
        current = current->next;
    }

    // If key not found, create a new linked list and insert
    List newList;
    newList.add(item);
    Node<List>* newNode = new Node<List>(key, newList, items[index]);
    items[index] = newNode;
    size++;
}


template <typename T>
void HashTable<T>::remove(KeyType key) {
    //int index = hash(key);

    //if (items[index] == nullptr) {

    //    bool success = (index >= 0) && (index < MAX_SIZE);
    //    if (success)
    //    {
    //        // Delete item by shifting all items at positions >
    //        // index toward the beginning of the list
    //        for (int pos = index; pos < MAX_SIZE - 1; pos++)
    //            items[pos] = items[pos + 1];
    //        size--;  // Decrease the size by 1
    //    }

    //}
    int index = hash(key);

    Node* current = items[index];
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            // Found the key, remove the node
            if (previous == nullptr) {
                items[index] = current->next; // Removing the first node in the chain
            }
            else {
                previous->next = current->next; // Bypass the node
            }
            delete current;
            size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}



template <typename T>
T HashTable<T>::get(KeyType key) const {
    int index = hash(key);
    Node<T>* current = items[index];

    //std::cout << "DEBUG: Searching for key " << key << " at index " << index << std::endl;

    while (current != nullptr) {
        //std::cout << "DEBUG: Checking node with key " << current->key << std::endl;
        if (current->key == key) {
            //std::cout << "DEBUG: Found key " << key << " in hash table." << std::endl;
            return current->item;
        }
        current = current->next;
    }

    //std::cout << "ERROR: Key " << key << " not found in hash table!" << std::endl;
    return T{};
}

//template <typename T>
//T HashTable<T>::get(KeyType key) const {
//    /* int index = hash(key);
//
//     if (items[index] == nullptr) {
//         return items[index]->item;
//     }
//     return nullptr;*/
//
//    int index = hash(key);
//
//    Node<T>* current = items[index];
//    while (current != nullptr) {
//        if (current->key == key) {
//            return current->item;
//        }
//        current = current->next;
//    }
//
//    //return nullptr; // Key not found
//    // Return a default-constructed T if the key is not found
//    return T{};
//}

//template <typename T>
//T HashTable<T>::get(KeyType key) {
//    int index = hash(key);
//
//    Node<T>* current = items[index];
//    while (current != nullptr) {
//        if (current->key == key) {
//            return current->item; // Return the found item
//        }
//        current = current->next;
//    }
//
//    // If the key is not found, return a default-constructed object of type T
//    return T(); 
//}


template <typename T>
bool HashTable<T>::isEmpty() {
    return size == 0;
}



template <typename T>
int HashTable<T>::getLength() {
    return size;
}



template <typename T>
void HashTable<T>::print() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node<T>* current = items[i];
        while (current != nullptr) {
            std::cout << "Key: " << current->key << ", Item: ";

            // Check if the item has a print method
            // Assuming T is a class with a print() method
            current->item->print(); // Call the print method of the item

            std::cout << std::endl;
            current = current->next;
        }
    }
    std::cout << endl;
}



//template <typename T>
//int HashTable<T>::hash(KeyType key) {
//    int hashValue = 0;
//    for (char c : key) {
//        hashValue = (hashValue * 37 + c) % MAX_SIZE;
//    }
//    return hashValue;
//
//}