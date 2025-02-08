// HashTable.h - - Specification of HashTable ADT
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
//struct HashNode {
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
//	HashNode<T>* items[MAX_SIZE];
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

//#pragma once
//
//#include "LinkedList.h"  // This must define LinkedList and its getFirstNode() method.
//#include <iostream>
//#include <cstdlib>
//#include <type_traits>
//#include "Actor.h"
//#include "Movie.h"
//
//const int MAX_SIZE = 101;
//typedef int KeyType;
//
////template <typename T>
////struct HashNode {
////    KeyType key;
////    T item;
////
////    HashNode(KeyType k, const T& i) : key(k), item(i) {}
////
////    bool operator==(const HashNode& other) const {
////        return key == other.key;
////    }
////};
//
//template <typename T>
//class HashTable {
//private:
//    struct HashNode {
//        KeyType key;
//        T item;
//
//        HashNode(KeyType k, const T& i) : key(k), item(i) {}
//
//        bool operator==(const HashNode& other) const {
//            return key == other.key;
//        }
//    };
//
//    // Each bucket is a pointer to a LinkedList of HashNode<T>
//    LinkedList<HashNode>* items[MAX_SIZE];
//    int size;
//
//    int hash(KeyType key) const;
//
//public:
//    HashTable();
//    ~HashTable();
//
//    // Adds an item with the given key to the table.
//    //bool add(KeyType newKey, const T& newItem);
//
//    bool add(KeyType newKey, const T& newItem);
//    //bool addActor(KeyType newKey, const std::shared_ptr<Actor>& newItem);
//    //bool addMovie(KeyType newKey, const std::shared_ptr<Movie>& newItem);
//    //bool markVisited(KeyType key);
//    //bool addMovieCollection(KeyType actorId, LinkedList<std::weak_ptr<Movie>>* movieCollection);
//
//    // Retrieves the value associated with the key; returns a default T if not found.
//    T get(KeyType key);
//    const T get(KeyType key) const;
//
//    bool isEmpty() const;
//    int getLength() const;
//    void print() const;
//};









// __________________________________________________________________________________________

//#pragma once
//
//#include <iostream>
//#include <cstdlib>   // For abs()
//#include "LinkedList.h"
//
//using namespace std;
//
//const int MAX_SIZE = 101; // A prime number is often a good choice.
//typedef int KeyType;
//
//template <typename T>
//struct HashNode {
//
//    KeyType key;
//    T item;
//
//    // Constructor for HashNode.
//    HashNode(KeyType k, const T& i) : key(k), item(i) {}
//
//};
//
//template <typename T>
//class HashTable {
//private:
//    // Nested HashNode class used to store key-value pairs.
//
//
//    // Array of pointers to LinkedList of HashNode objects.
//    // Each bucket uses separate chaining to handle collisions.
//    LinkedList<HashNode<T>>* items[MAX_SIZE];
//    int size; // Number of elements stored.
//
//public:
//    HashTable();
//    ~HashTable();
//
//    // Computes a hash value for a given key.
//    int hash(KeyType key) const;
//
//    // Adds a new key-value pair. If key exists, update value and return false.
//    bool add(KeyType newKey, const T& newItem);
//
//    // Retrieves the value associated with the key; returns default T if not found.
//    T get(KeyType key);
//    const T get(KeyType key) const;
//
//    // Checks if the hash table is empty.
//    bool isEmpty() const;
//
//    // Returns the number of elements stored.
//    int getLength() const;
//
//    // Prints the hash table's contents.
//    void print() const;
//};

///////////////////////
// Implementation
///////////////////////

//template <typename T>
//HashTable<T>::HashTable() : size(0) {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        // Create a new LinkedList for each bucket.
//        items[i] = new LinkedList<HashNode>();
//    }
//}
//
//template <typename T>
//HashTable<T>::~HashTable() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        delete items[i];
//    }
//}
//
//template <typename T>
//int HashTable<T>::hash(int key) const {
//    const double A = 0.6180339887;  // Fractional part of the golden ratio
//    double fractionalPart = key * A - static_cast<int>(key * A);
//    return static_cast<int>(size * fractionalPart);
//}
//
////int HashTable<T>::hash(KeyType key) const {
////    const int PRIME = 31;
////    long long hashVal = key;
////    hashVal = abs(hashVal * PRIME) % MAX_SIZE;
////    return static_cast<int>(hashVal);
////}
//
//template <typename T>
//bool HashTable<T>::add(KeyType newKey, const T& newItem) {
//    int index = hash(newKey);
//    cout << "[DEBUG] Hash index for key " << newKey << " is " << index << endl;
//
//    // Create a new node with the key and value.
//    HashNode newNode(newKey, newItem);
//    cout << "[DEBUG] Created new node with key: " << newKey << endl;
//
//    // Iterate over the linked list in this bucket.
//    auto* current = items[index]->getFirstNode();
//    while (current != nullptr) {
//        cout << "[DEBUG] Checking node with key: " << current->item.key << endl;
//
//        // If current->item is a pointer, check for nullptr correctly
//        if constexpr (std::is_pointer_v<decltype(current->item)>) {
//            if (current->item == nullptr) {
//                cout << "[DEBUG] Found a null item in the list!" << endl;
//            }
//        }
//
//        // Compare keys properly
//        if (current->item.key == newKey) {
//            cout << "[DEBUG] Key " << newKey << " already exists. Not adding." << endl;
//            return false;
//        }
//        current = current->next;
//    }
//
//    // Key not found: add the new node at the front.
//    cout << "[DEBUG] Key " << newKey << " not found, adding to bucket " << index << endl;
//    items[index]->add(newNode);
//    size++;
//    return true;
//}
//
//
//template <typename T>
//void HashTable<T>::remove(KeyType key) {
//    int index = hash(key);
//    auto* current = items[index]->getFirstNode();
//    int position = 0;
//    while (current != nullptr) {
//        if (current->item.key == key) {
//            items[index]->remove(position);
//            size--;
//            return;
//        }
//        current = current->next;
//        position++;
//    }
//}
//
//template <typename T>
//T HashTable<T>::get(KeyType key) {
//    int index = hash(key);
//    auto* current = items[index]->getFirstNode();
//    while (current != nullptr) {
//        if (current->item.key == key) {
//            return current->item.item;
//        }
//        current = current->next;
//    }
//    return T{};  // Return a default-constructed T if key is not found.
//}
//
//template <typename T>
//const T HashTable<T>::get(KeyType key) const {
//    int index = hash(key);
//    auto* current = items[index]->getFirstNode();
//    while (current != nullptr) {
//        if (current->item.key == key) {
//            return current->item.item;
//        }
//        current = current->next;
//    }
//    return T{};
//}
//
//template <typename T>
//bool HashTable<T>::isEmpty() const {
//    return size == 0;
//}
//
//template <typename T>
//int HashTable<T>::getLength() const {
//    return size;
//}
//
//template <typename T>
//void HashTable<T>::print() const {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        if (!items[i]->isEmpty()) {
//            std::cout << "Bucket " << i << ": ";
//            auto* current = items[i]->getFirstNode();
//            while (current != nullptr) {
//                std::cout << "[" << current->item.key << ":" << current->item.item << "] ";
//                current = current->next;
//            }
//            std::cout << std::endl;
//        }
//    }
//}









// LATESTTTTTTTTTTTTTTT COMMITTTTTTTTTTTTTTTTTTTTT
//#pragma once
//#include <string>
//#include <iostream>
//#include "LinkedList.h"
//using namespace std;
//const int MAX_SIZE = 1009;
//typedef int KeyType;
//
//template <typename T>
//class HashTable {
//private:
//    struct HashNode {
//        KeyType key;
//        T item;
//
//        // Add constructor for convenience
//        HashNode(KeyType k = KeyType(), T i = T()) : key(k), item(i) {}
//    };
//    LinkedList<HashNode>* items[MAX_SIZE];
//    int size;
//
//public:
//    HashTable();  // Constructor
//    ~HashTable(); // Destructor
//    int hash(KeyType key) const;
//    bool add(KeyType newKey, const T& newItem);
//    void remove(KeyType key);
//    T get(KeyType key);
//    const T get(KeyType key) const;
//    bool isEmpty() const;
//    int getLength() const;
//    void print() const;
//};
//
//// Constructor: Initialize empty LinkedLists for each bucket
//template <typename T>
//HashTable<T>::HashTable() : size(0) {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        items[i] = new LinkedList<HashNode>();
//    }
//}
//
//// Destructor: Clean up all LinkedLists
//template <typename T>
//HashTable<T>::~HashTable() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        delete items[i];
//    }
//}
//    
//// Hash function using prime number for better distribution
//template <typename T>
//int HashTable<T>::hash(KeyType key) const {
//    const int PRIME1 = 31;
//    const int PRIME2 = 17;
//    long long hash = key;
//    hash = abs((hash * PRIME1 + PRIME2)) % MAX_SIZE;
//    return static_cast<int>(hash);
//}
//
//// Add a new key-item pair to the hash table
//template <typename T>
//bool HashTable<T>::add(KeyType newKey, const T& newItem) {
//    int index = hash(newKey);
//
//    // Create new node
//    HashNode newNode(newKey, newItem);
//
//    // Check if key already exists
//    for (int i = 0; i < items[index]->getLength(); i++) {
//        HashNode currentNode = items[index]->get(i);
//        if (currentNode.key == newKey) {
//            return false;  // Key already exists
//        }
//    }
//
//    // Add new node to the front of the list
//    items[index]->add(0, newNode);
//    size++;
//    return true;
//}
//
//// Remove an item with the given key
//template <typename T>
//void HashTable<T>::remove(KeyType key) {
//    int index = hash(key);
//    auto* current = items[index]->getFirstNode();
//    int position = 0;
//
//    while (current != nullptr) {
//        if (current->item.key == key) {
//            items[index]->remove(position);
//            size--;
//            return;
//        }
//        current = current->next;
//        position++;
//    }
//}
//
//// Get item associated with key (non-const version)
//template <typename T>
//T HashTable<T>::get(KeyType key) {
//    int index = hash(key);
//
//    for (int i = 0; i < items[index]->getLength(); i++) {
//        HashNode node = items[index]->get(i);
//        if (node.key == key) {
//            return node.item;
//        }
//    }
//
//    throw std::runtime_error("Key not found");
//}
////T HashTable<T>::get(KeyType key) {
////    int index = hash(key);
////    auto* current = items[index]->getFirstNode();
////
////    while (current != nullptr) {
////        if (current->item.key == key) {
////            return current->item.item;
////        }
////        current = current->next;
////    }
////    return T{};  // Return default-constructed T if not found
////}
//
//// Get item associated with key (const version)
//template <typename T>
//const T HashTable<T>::get(KeyType key) const {
//    int index = hash(key);
//
//    for (int i = 0; i < items[index]->getLength(); i++) {
//        HashNode node = items[index]->get(i);
//        if (node.key == key) {
//            return node.item;
//        }
//    }
//
//    throw std::runtime_error("Key not found");
//}
////const T HashTable<T>::get(KeyType key) const {
////    int index = hash(key);
////    auto* current = items[index]->getFirstNode();
////
////    while (current != nullptr) {
////        if (current->item.key == key) {
////            return current->item.item;
////        }
////        current = current->next;
////    }
////    return T{};  // Return default-constructed T if not found
////}
//
//// Check if hash table is empty
//template <typename T>
//bool HashTable<T>::isEmpty() const {
//    return size == 0;
//}
//
//// Get number of items in hash table
//template <typename T>
//int HashTable<T>::getLength() const {
//    return size;
//}
//
//// Print all items in hash table
//template <typename T>
//void HashTable<T>::print() const {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        if (!items[i]->isEmpty()) {
//            cout << "Bucket " << i << ": ";
//            auto* current = items[i]->getFirstNode();
//            while (current != nullptr) {
//                cout << "[Key: " << current->item.key
//                    << ", Item: " << current->item.item << "] ";
//                current = current->next;
//            }
//            cout << endl;
//        }
//    }
//    cout << "Total items: " << size << endl;
//}



















// latest ver with chaining
// #pragma once
//#pragma once
//#include <string>
//#include <iostream>
//#include "LinkedList.h"
//
//using namespace std;
//
//const int MAX_SIZE = 1009;
//typedef int KeyType;
//
//template <typename T>
//struct HashNode {
//    KeyType key;
//    T item;
//
//    HashNode(KeyType k, T i) : key(k), item(i) {}
//
//    bool operator==(const HashNode& other) const {
//        return key == other.key;
//    }
//};
//
//template <typename T>
//class HashTable {
//private:
//    LinkedList<HashNode<T>>* items[MAX_SIZE];
//    int size;
//
//public:
//    HashTable();
//    ~HashTable();
//    int hash(KeyType key) const;
//    bool add(KeyType newKey, const T& newItem);  // Changed to take const reference
//    void remove(KeyType key);
//    T get(KeyType key);  // Non-const version for modification
//    const T get(KeyType key) const;  // Const version for reading
//    bool isEmpty() const;
//    int getLength() const;
//    void print() const;
//};
//
//// Latest ver
////#pragma once
////#include <string>
////#include <iostream>
////#include "LinkedList.h"
////#include "List.h"
////
////using namespace std;
////
////const int MAX_SIZE = 1009; // Change from 101 to 1009 or 5003
////typedef int KeyType;
////
////template <typename T>
////struct Node {
////    int key;        // Search key
////    T item;         // Data item
////    Node* next;     // Pointer to the next node
////};
////
////template <typename T>
////class HashTable {
////private:
////    Node<T>* items[MAX_SIZE];
////    int size;
////
////public:
////    HashTable();
////    ~HashTable();
////    int hash(KeyType key) const;
////    bool add(KeyType newKey, T newItem);
////    void insertToLinkedList(int key, T item);
////    void remove(KeyType key);
////    T get(KeyType key) const;
////    bool isEmpty();
////    int getLength();
////    void print();
////};
//
//
//
//
//
//// Latest ver for chaining
//template <typename T>
//HashTable<T>::HashTable() {
//    size = 0;
//    for (int i = 0; i < MAX_SIZE; i++) {
//        items[i] = new LinkedList<HashNode<T>>();
//    }
//}
//
//template <typename T>
//HashTable<T>::~HashTable() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        delete items[i];
//    }
//}
//
//template <typename T>
//int HashTable<T>::hash(KeyType key) const {
//    return abs(key) % MAX_SIZE;
//}
//
//template <typename T>
//bool HashTable<T>::add(KeyType newKey, const T& newItem) {
//    int index = hash(newKey);
//    HashNode<T> newNode(newKey, newItem);
//
//    LinkedListNode<HashNode<T>>* current = items[index]->getFirstNode();
//    while (current != nullptr) {
//        if (current->item.key == newKey) {
//            current->item.item = newItem;
//            return false;
//        }
//        current = current->next;
//    }
//
//    items[index]->add(0, newNode);
//    size++;
//    return true;
//}
//
//template <typename T>
//void HashTable<T>::remove(KeyType key) {
//    int index = hash(key);
//    LinkedListNode<HashNode<T>>* current = items[index]->getFirstNode();
//    int position = 0;
//
//    while (current != nullptr) {
//        if (current->item.key == key) {
//            items[index]->remove(position);
//            size--;
//            return;
//        }
//        current = current->next;
//        position++;
//    }
//}
//
//// Non-const version for modification
//template <typename T>
//T HashTable<T>::get(KeyType key) {
//    int index = hash(key);
//    LinkedListNode<HashNode<T>>* current = items[index]->getFirstNode();
//
//    while (current != nullptr) {
//        if (current->item.key == key) {
//            return current->item.item;
//        }
//        current = current->next;
//    }
//
//    return T{};
//}
//
//// Const version for reading
//template <typename T>
//const T HashTable<T>::get(KeyType key) const {
//    int index = hash(key);
//    LinkedListNode<HashNode<T>>* current = items[index]->getFirstNode();
//
//    while (current != nullptr) {
//        if (current->item.key == key) {
//            return current->item.item;
//        }
//        current = current->next;
//    }
//
//    return T{};
//}
//
//template <typename T>
//bool HashTable<T>::isEmpty() const {
//    return size == 0;
//}
//
//template <typename T>
//int HashTable<T>::getLength() const {
//    return size;
//}
//
//template <typename T>
//void HashTable<T>::print() const {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        if (!items[i]->isEmpty()) {
//            std::cout << "Bucket " << i << ": ";
//            LinkedListNode<HashNode<T>>* current = items[i]->getFirstNode();
//            while (current != nullptr) {
//                std::cout << "[" << current->item.key << ":" << current->item.item << "] ";
//                current = current->next;
//            }
//            std::cout << std::endl;
//        }
//    }
//}



// Most latest

// 
// template <typename T>
//HashTable<T>::HashTable() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        items[i] = nullptr;
//    }
//    size = 0;
//}
//
//
//template <typename T>
//HashTable<T>::~HashTable() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        Node<T>* current = items[i];
//        while (current != nullptr) {
//            Node<T>* toDelete = current;
//            current = current->next;
//            delete toDelete;
//        }
//        items[i] = nullptr;
//    }
//}
//
//
////template <typename T>
////int HashTable<T>::hash(KeyType newKey) {
////    int hashValue = 0;
////
////    for (char c : newKey) {
////        if (isalpha(c))
////        {
////            if (isupper(c))
////                return (int)c - (int)'A';
////            else
////                return (int)c - (int)'a' + 26;
////        }
////        else
////            return -1;
////    }
////
////    std::cout << "Hashed key: " << hashValue;
////
////    // Modulo operation to ensure hash value is within array bounds
////    return hashValue % MAX_SIZE;
////}
//
////template <typename T>
////int HashTable<T>::hash(KeyType key) {
////    int hashValue = 0;
////    for (char c : key) {
////        hashValue = (hashValue * 37 + c) % MAX_SIZE;
////    }
////    return hashValue;
////
////}
//
//
////template <typename T>
////int HashTable<T>::hash(KeyType key) const {
////    // A prime number multiplier to reduce clustering
////    const int primeMultiplier = 31;
////    unsigned int hashValue = 0;
////
////    while (key > 0) {
////        // XOR the lower bits of the key and multiply by the prime
////        hashValue = (hashValue ^ (key & 0xFF)) * primeMultiplier;
////
////        // Shift the key to process the next part
////        key >>= 8; // Move to the next byte
////    }
////
////    // Modulo operation to ensure hash value fits within the hash table size
////    return hashValue % MAX_SIZE;
////}
//
//template <typename T>
//int HashTable<T>::hash(KeyType key) const {
//    const int primeMultiplier = 31;
//    unsigned int hashValue = 0;
//
//    while (key > 0) {
//        hashValue = hashValue * primeMultiplier + (key % 10); // Use digits for hashing
//        key /= 10;
//    }
//
//    return hashValue % MAX_SIZE;
//}
//
////template <typename T>
////int HashTable<T>::hash(KeyType key) const {
////    unsigned int unsignedKey = static_cast<unsigned int>(key);
////
////    const int primeMultiplier = 31;
////    unsigned int hashValue = 0;
////
////    //std::cout << "Hashing key: " << unsignedKey << std::endl;
////
////    while (unsignedKey > 0) {
////        hashValue = (hashValue ^ (unsignedKey & 0xFF)) * primeMultiplier;
////        unsignedKey >>= 8;
////    }
////
////    //std::cout << "Computed hash: " << hashValue % MAX_SIZE << std::endl;
////
////    return hashValue % MAX_SIZE;
////}
//
//
//template <typename T>
//bool HashTable<T>::add(KeyType newKey, T newItem) {
//
//    int index = hash(newKey);
//
//    // Traverse the chain at the hash index to check for duplicate keys
//    Node<T>* current = items[index];
//    while (current != nullptr) {
//        if (current->key == newKey) {
//            // Duplicate key found, reject the new entry
//            return false;
//        }
//        current = current->next;
//    }
//
//    // Create and initialize a new node
//    Node<T>* newNode = new Node<T>();
//    newNode->key = newKey;
//    newNode->item = newItem;
//    newNode->next = nullptr;
//
//    // Add the new node at the front of the chain
//    newNode->next = items[index];
//    items[index] = newNode;
//
//    size++;
//    return true;
//}
//
//
//template <typename T>
//void HashTable<T>::insertToLinkedList(int key, T item) {
//    int index = hash(key);
//    Node<List>* current = items[index];
//
//    // Find the node with the given key
//    while (current != nullptr) {
//        if (current->key == key) {
//            current->item.add(item); // Add to the linked list
//            return;
//        }
//        current = current->next;
//    }
//
//    // If key not found, create a new linked list and insert
//    List newList;
//    newList.add(item);
//    Node<List>* newNode = new Node<List>(key, newList, items[index]);
//    items[index] = newNode;
//    size++;
//}
//
//
//template <typename T>
//void HashTable<T>::remove(KeyType key) {
//    //int index = hash(key);
//
//    //if (items[index] == nullptr) {
//
//    //    bool success = (index >= 0) && (index < MAX_SIZE);
//    //    if (success)
//    //    {
//    //        // Delete item by shifting all items at positions >
//    //        // index toward the beginning of the list
//    //        for (int pos = index; pos < MAX_SIZE - 1; pos++)
//    //            items[pos] = items[pos + 1];
//    //        size--;  // Decrease the size by 1
//    //    }
//
//    //}
//    int index = hash(key);
//
//    Node* current = items[index];
//    Node* previous = nullptr;
//
//    while (current != nullptr) {
//        if (current->key == key) {
//            // Found the key, remove the node
//            if (previous == nullptr) {
//                items[index] = current->next; // Removing the first node in the chain
//            }
//            else {
//                previous->next = current->next; // Bypass the node
//            }
//            delete current;
//            size--;
//            return;
//        }
//        previous = current;
//        current = current->next;
//    }
//}
//
//
//
//template <typename T>
//T HashTable<T>::get(KeyType key) const {
//    int index = hash(key);
//    Node<T>* current = items[index];
//
//    //std::cout << "DEBUG: Searching for key " << key << " at index " << index << std::endl;
//
//    while (current != nullptr) {
//        //std::cout << "DEBUG: Checking node with key " << current->key << std::endl;
//        if (current->key == key) {
//            //std::cout << "DEBUG: Found key " << key << " in hash table." << std::endl;
//            return current->item;
//        }
//        current = current->next;
//    }
//
//    //std::cout << "ERROR: Key " << key << " not found in hash table!" << std::endl;
//    return T{};
//}
//
////template <typename T>
////T HashTable<T>::get(KeyType key) const {
////    /* int index = hash(key);
////
////     if (items[index] == nullptr) {
////         return items[index]->item;
////     }
////     return nullptr;*/
////
////    int index = hash(key);
////
////    Node<T>* current = items[index];
////    while (current != nullptr) {
////        if (current->key == key) {
////            return current->item;
////        }
////        current = current->next;
////    }
////
////    //return nullptr; // Key not found
////    // Return a default-constructed T if the key is not found
////    return T{};
////}
//
////template <typename T>
////T HashTable<T>::get(KeyType key) {
////    int index = hash(key);
////
////    Node<T>* current = items[index];
////    while (current != nullptr) {
////        if (current->key == key) {
////            return current->item; // Return the found item
////        }
////        current = current->next;
////    }
////
////    // If the key is not found, return a default-constructed object of type T
////    return T(); 
////}
//
//
//template <typename T>
//bool HashTable<T>::isEmpty() {
//    return size == 0;
//}
//
//
//
//template <typename T>
//int HashTable<T>::getLength() {
//    return size;
//}
//
//
//
//template <typename T>
//void HashTable<T>::print() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        Node<T>* current = items[i];
//        while (current != nullptr) {
//            std::cout << "Key: " << current->key << ", Item: ";
//
//            // Check if the item has a print method
//            // Assuming T is a class with a print() method
//            current->item->print(); // Call the print method of the item
//
//            std::cout << std::endl;
//            current = current->next;
//        }
//    }
//    std::cout << endl;
//}
//
//
//
////template <typename T>
////int HashTable<T>::hash(KeyType key) {
////    int hashValue = 0;
////    for (char c : key) {
////        hashValue = (hashValue * 37 + c) % MAX_SIZE;
////    }
////    return hashValue;
////
////}
























//github
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



//template <typename T>
//HashTable<T>::HashTable() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        items[i] = nullptr;
//    }
//    size = 0;
//}
//
//
//template <typename T>
//HashTable<T>::~HashTable() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        Node<T>* current = items[i];
//        while (current != nullptr) {
//            Node<T>* toDelete = current;
//            current = current->next;
//            delete toDelete;
//        }
//        items[i] = nullptr;
//    }
//}
//
//
////template <typename T>
////int HashTable<T>::hash(KeyType newKey) {
////    int hashValue = 0;
////
////    for (char c : newKey) {
////        if (isalpha(c))
////        {
////            if (isupper(c))
////                return (int)c - (int)'A';
////            else
////                return (int)c - (int)'a' + 26;
////        }
////        else
////            return -1;
////    }
////
////    std::cout << "Hashed key: " << hashValue;
////
////    // Modulo operation to ensure hash value is within array bounds
////    return hashValue % MAX_SIZE;
////}
//
////template <typename T>
////int HashTable<T>::hash(KeyType key) {
////    int hashValue = 0;
////    for (char c : key) {
////        hashValue = (hashValue * 37 + c) % MAX_SIZE;
////    }
////    return hashValue;
////
////}
//
//
////template <typename T>
////int HashTable<T>::hash(KeyType key) const {
////    // A prime number multiplier to reduce clustering
////    const int primeMultiplier = 31;
////    unsigned int hashValue = 0;
////
////    while (key > 0) {
////        // XOR the lower bits of the key and multiply by the prime
////        hashValue = (hashValue ^ (key & 0xFF)) * primeMultiplier;
////
////        // Shift the key to process the next part
////        key >>= 8; // Move to the next byte
////    }
////
////    // Modulo operation to ensure hash value fits within the hash table size
////    return hashValue % MAX_SIZE;
////}
//
//template <typename T>
//int HashTable<T>::hash(KeyType key) const {
//    const int primeMultiplier = 31;
//    unsigned int hashValue = 0;
//
//    while (key > 0) {
//        hashValue = hashValue * primeMultiplier + (key % 10); // Use digits for hashing
//        key /= 10;
//    }
//
//    return hashValue % MAX_SIZE;
//}
//
////template <typename T>
////int HashTable<T>::hash(KeyType key) const {
////    unsigned int unsignedKey = static_cast<unsigned int>(key);
////
////    const int primeMultiplier = 31;
////    unsigned int hashValue = 0;
////
////    //std::cout << "Hashing key: " << unsignedKey << std::endl;
////
////    while (unsignedKey > 0) {
////        hashValue = (hashValue ^ (unsignedKey & 0xFF)) * primeMultiplier;
////        unsignedKey >>= 8;
////    }
////
////    //std::cout << "Computed hash: " << hashValue % MAX_SIZE << std::endl;
////
////    return hashValue % MAX_SIZE;
////}
//
//
//template <typename T>
//bool HashTable<T>::add(KeyType newKey, T newItem) {
//
//    int index = hash(newKey);
//
//    // Traverse the chain at the hash index to check for duplicate keys
//    Node<T>* current = items[index];
//    while (current != nullptr) {
//        if (current->key == newKey) {
//            // Duplicate key found, reject the new entry
//            return false;
//        }
//        current = current->next;
//    }
//
//    // Create and initialize a new node
//    Node<T>* newNode = new Node<T>();
//    newNode->key = newKey;
//    newNode->item = newItem;
//    newNode->next = nullptr;
//
//    // Add the new node at the front of the chain
//    newNode->next = items[index];
//    items[index] = newNode;
//
//    size++;
//    return true;
//}
//
//
////template <typename T>
////void HashTable<T>::insertToLinkedList(int key, T item) {
////    int index = hash(key);
////    Node<List>* current = items[index];
////
////    // Find the node with the given key
////    while (current != nullptr) {
////        if (current->key == key) {
////            current->item.add(item); // Add to the linked list
////            return;
////        }
////        current = current->next;
////    }
////
////    // If key not found, create a new linked list and insert
////    List newList;
////    newList.add(item);
////    Node<List>* newNode = new Node<List>(key, newList, items[index]);
////    items[index] = newNode;
////    size++;
////}
//
//
//template <typename T>
//void HashTable<T>::remove(KeyType key) {
//    //int index = hash(key);
//
//    //if (items[index] == nullptr) {
//
//    //    bool success = (index >= 0) && (index < MAX_SIZE);
//    //    if (success)
//    //    {
//    //        // Delete item by shifting all items at positions >
//    //        // index toward the beginning of the list
//    //        for (int pos = index; pos < MAX_SIZE - 1; pos++)
//    //            items[pos] = items[pos + 1];
//    //        size--;  // Decrease the size by 1
//    //    }
//
//    //}
//    int index = hash(key);
//
//    Node* current = items[index];
//    Node* previous = nullptr;
//
//    while (current != nullptr) {
//        if (current->key == key) {
//            // Found the key, remove the node
//            if (previous == nullptr) {
//                items[index] = current->next; // Removing the first node in the chain
//            }
//            else {
//                previous->next = current->next; // Bypass the node
//            }
//            delete current;
//            size--;
//            return;
//        }
//        previous = current;
//        current = current->next;
//    }
//}
//
//
//
//template <typename T>
//T HashTable<T>::get(KeyType key) const {
//    int index = hash(key);
//    Node<T>* current = items[index];
//
//    //std::cout << "DEBUG: Searching for key " << key << " at index " << index << std::endl;
//
//    while (current != nullptr) {
//        //std::cout << "DEBUG: Checking node with key " << current->key << std::endl;
//        if (current->key == key) {
//            //std::cout << "DEBUG: Found key " << key << " in hash table." << std::endl;
//            return current->item;
//        }
//        current = current->next;
//    }
//
//    //std::cout << "ERROR: Key " << key << " not found in hash table!" << std::endl;
//    return T{};
//}
//
////template <typename T>
////T HashTable<T>::get(KeyType key) const {
////    /* int index = hash(key);
////
////     if (items[index] == nullptr) {
////         return items[index]->item;
////     }
////     return nullptr;*/
////
////    int index = hash(key);
////
////    Node<T>* current = items[index];
////    while (current != nullptr) {
////        if (current->key == key) {
////            return current->item;
////        }
////        current = current->next;
////    }
////
////    //return nullptr; // Key not found
////    // Return a default-constructed T if the key is not found
////    return T{};
////}
//
////template <typename T>
////T HashTable<T>::get(KeyType key) {
////    int index = hash(key);
////
////    Node<T>* current = items[index];
////    while (current != nullptr) {
////        if (current->key == key) {
////            return current->item; // Return the found item
////        }
////        current = current->next;
////    }
////
////    // If the key is not found, return a default-constructed object of type T
////    return T(); 
////}
//
//
//template <typename T>
//bool HashTable<T>::isEmpty() {
//    return size == 0;
//}
//
//
//
//template <typename T>
//int HashTable<T>::getLength() {
//    return size;
//}
//
//
//
//template <typename T>
//void HashTable<T>::print() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        Node<T>* current = items[i];
//        while (current != nullptr) {
//            std::cout << "Key: " << current->key << ", Item: ";
//
//            // Check if the item has a print method
//            // Assuming T is a class with a print() method
//            current->item->print(); // Call the print method of the item
//
//            std::cout << std::endl;
//            current = current->next;
//        }
//    }
//    std::cout << endl;
//}