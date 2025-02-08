#include "HashTable.h"
#include "Actor.h"       // For shared_ptr<Actor>
#include "Movie.h"       // For shared_ptr<Movie>
#include "LinkedList.h"  // For LinkedList
#include "Rating.h"      // For Rating
#include "RatingSystem.h"   

using namespace std;

// Explicit instantiations for the types we use:
//template class HashTable<std::shared_ptr<Actor>>;
//template class HashTable<std::shared_ptr<Movie>>;
//template class HashTable<LinkedList<std::weak_ptr<Movie>>*>;
//template class HashTable<bool>;
//
template struct HashNode<std::shared_ptr<Movie>>;
template struct HashNode<std::shared_ptr<Actor>>;
template struct HashNode<LinkedList<std::weak_ptr<Movie>>*>;
template struct HashTable<EntityRatings*>;

////// Now, explicitly instantiate the LinkedList for the needed specializations:
////template class LinkedList<HashNode<std::shared_ptr<Movie>>>;
////template class LinkedList<HashNode<std::shared_ptr<Actor>>>;
//
//
//
//// Constructor: Initialize size to 0 and create a new LinkedList for each bucket.
//template <typename T>
//HashTable<T>::HashTable() : size(0) {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        items[i] = nullptr;
//    }
//}
//
//// Destructor: Delete all buckets.
//template <typename T>
//HashTable<T>::~HashTable() {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        delete items[i];
//    }
//}
//
//// Hash function: uses a fractional part method based on the golden ratio.
//template <typename T>
//int HashTable<T>::hash(KeyType key) const {
//    const double A = 0.6180339887;  // Fractional part of the golden ratio
//    double fractionalPart = key * A - static_cast<int>(key * A);
//    return static_cast<int>(size * fractionalPart);
//}
//
//
//// Generic add method for basic types
//template <typename T>
//bool HashTable<T>::add(KeyType newKey, const T& newItem) {
//    int index = hash(newKey);
//
//    // Safety check
//    if (items[index] == nullptr) {
//        items[index] = new LinkedList<HashNode>();
//    }
//
//    // Check for existing entry
//    auto* current = items[index]->getFirstNode();
//    while (current != nullptr) {
//        if (current->item.key == newKey) {
//            return false; // Key already exists
//        }
//        current = current->next;
//    }
//
//    // Create and add new node
//    HashNode newNode(newKey, newItem);
//    items[index]->add(newNode);
//    size++;
//    return true;
//}
//
//
////// Specialized method for shared_ptr<Actor>
////template <typename T>
////bool HashTable<T>::addActor(KeyType newKey, const std::shared_ptr<Actor>& newItem) {
////    int index = hash(newKey);
////
////    // Safety check
////    if (items[index] == nullptr) {
////        items[index] = new LinkedList<HashNode<std::shared_ptr<Actor>>>();
////    }
////
////    // Check for existing entry
////    auto* current = items[index]->getFirstNode();
////    while (current != nullptr) {
////        if (current->item.key == newKey) {
////            return false; // Actor already exists
////        }
////        current = current->next;
////    }
////
////    // Create and add new node
////    HashNode<std::shared_ptr<Actor>> newNode(newKey, newItem);
////    items[index]->add(newNode);
////    size++;
////    return true;
////}
////
////template <typename T>
////bool HashTable<T>::addMovie(KeyType newKey, const std::shared_ptr<Movie>& newItem) {
////    int index = hash(newKey);
////
////    // Safety check
////    if (items[index] == nullptr) {
////        items[index] = new LinkedList<HashNode<std::shared_ptr<Movie>>>();
////    }
////
////    // Check for existing entry
////    auto* current = items[index]->getFirstNode();
////    while (current != nullptr) {
////        if (current->item.key == newKey) {
////            return false; // Actor already exists
////        }
////        current = current->next;
////    }
////
////    // Create and add new node
////    HashNode<std::shared_ptr<Movie>> newNode(newKey, newItem);
////    items[index]->add(newNode);
////    size++;
////    return true;
////}
////
////
////// Specialized visited tracking method
////template <typename T>
////bool HashTable<T>::markVisited(KeyType key) {
////    int index = hash(key);
////
////    // Safety check
////    if (items[index] == nullptr) {
////        items[index] = new LinkedList<HashNode<bool>>();
////    }
////
////    // Check for existing entry
////    auto* current = items[index]->getFirstNode();
////    while (current != nullptr) {
////        if (current->item.key == key) {
////            return false; // Already visited
////        }
////        current = current->next;
////    }
////
////    // Create and add new node
////    HashNode<bool> newNode(key, true);
////    items[index]->add(newNode);
////    size++;
////    return true;
////}
////
////// Specialized method for actor-to-movie mapping
////template <typename T>
////bool HashTable<T>::addMovieCollection(
////    KeyType actorId,
////    LinkedList<std::weak_ptr<Movie>>* movieCollection
////) {
////    int index = hash(actorId);
////
////    // Safety check
////    if (items[index] == nullptr) {
////        items[index] = new LinkedList<HashNode<LinkedList<std::weak_ptr<Movie>>*>>();
////    }
////
////    // Check for existing entry
////    auto* current = items[index]->getFirstNode();
////    while (current != nullptr) {
////        if (current->item.key == actorId) {
////            return false; // Collection already exists
////        }
////        current = current->next;
////    }
////
////    // Create and add new node
////    HashNode<LinkedList<std::weak_ptr<Movie>>*> newNode(actorId, movieCollection);
////    items[index]->add(newNode);
////    size++;
////    return true;
////}
//
//
//// Add an item with key newKey and value newItem.
////template <typename T>
////bool HashTable<T>::add(KeyType newKey, const T& newItem) {
////    int index = hash(newKey);
////    cout << "[DEBUG] Hash index for key " << newKey << " is " << index << endl;
////
////    // Create a new HashNode with the given key and item.
////    HashNode<T> newNode(newKey, newItem);
////    cout << "[DEBUG] Created new node with key: " << newKey << endl;
////
////    // Iterate over the linked list at this bucket.
////    auto* current = items[index]->getFirstNode();
////    while (current != nullptr) {
////        cout << "[DEBUG] Checking node with key: " << current->item.key << endl;
////        if (current->item.key == newKey) {
////            cout << "[DEBUG] Key " << newKey << " already exists. Not adding." << endl;
////            return false;
////        }
////        current = current->next;
////    }
////
////    // Key not found: add the new node at the front of the list.
////    cout << "[DEBUG] Key " << newKey << " not found, adding to bucket " << index << endl;
////    items[index]->add(newNode);
////    size++;
////    return true;
////}
//
//// Retrieve the item for the given key; return a default-constructed T if not found.
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
//    return T{};
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
//            cout << "Bucket " << i << ": ";
//            auto* current = items[i]->getFirstNode();
//            while (current != nullptr) {
//                cout << "[" << current->item.key << ":" << current->item.item << "] ";
//                current = current->next;
//            }
//            cout << endl;
//        }
//    }
//}





// Also, as requested, an explicit instantiation for List<Module>.
// (Make sure Module.h exists and defines the Module class.)
//#include "Module.h"
//template class List<Module>;


//#include "HashTable.h"
//#include <iostream>
//#include "Actor.h"
//#include "Movie.h"
//#include "LinkedList.h"
//
//using namespace std;
//
//template class HashTable<std::shared_ptr<Actor>>;
//template class HashTable<std::shared_ptr<Movie>>;
//template class HashTable<LinkedList<std::weak_ptr<Movie>>*>;
//
//
//template <typename T>
//HashTable<T>::HashTable() : size(0) {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        // Create a new LinkedList for each bucket.
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
//    HashNode<T> newNode(newKey, newItem);
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










#include "HashTable.h"
#include <iostream>
template <typename T>
HashTable<T>::HashTable() {
    items = new HashNode<T>*[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = NULL;
    }
    size = 0;
}


template <typename T>
HashTable<T>::~HashTable() {
    for (int i = 0; i < MAX_SIZE; i++) {
        HashNode<T>* p = items[i];
        if (p != NULL) {
            // Delete the chain if available
            HashNode<T>* chain = p->next;
            while (chain != NULL) {
                HashNode<T>* target = chain;
                chain = chain->next;
                delete target;
            }

            // Delete the table record
            delete p;
            items[i] = NULL;
        }
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

template <typename T>
int HashTable<T>::hash(KeyType key) const {
	return abs(key) % MAX_SIZE;
}



template <typename T>
bool HashTable<T>::add(KeyType newKey, T newItem) {

    int index = hash(newKey);

    // Traverse the chain at the hash index to check for duplicate keys
    //HashNode<T>* current = items[index];
    //while (current != nullptr) {
    //    if (current->key == newKey) {
    //        // Duplicate key found, reject the new entry
    //        return false;
    //    }
    //    current = current->next;
    //}

    // Create and initialize a new node
    HashNode<T>* newNode = new HashNode<T>();
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
T HashTable<T>::get(KeyType key) const {
    int index = hash(key);
    //HashNode<T>* current = items[index];

    //std::cout << "DEBUG: Searching for key " << key << " at index " << index << std::endl;

    //while (current != nullptr) {
    //    //std::cout << "DEBUG: Checking node with key " << current->key << std::endl;
    //    if (current->key == key) {
    //        //std::cout << "DEBUG: Found key " << key << " in hash table." << std::endl;
    //        return current->item;
    //    }
    //    current = current->next;
    //}

    for (HashNode<T>* p = items[index]; p != NULL; p = p->next) {
        if (p->key == key) {
            // Step 3. Return the node if the key matches any of the node. NULL otherwise.
            return p->item;
        }
    }
    //std::cout << "ERROR: Key " << key << " not found in hash table!" << std::endl;
    return T{};
}



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
        HashNode<T>* current = items[i];

        //while (current != nullptr) {
        //    std::cout << "Key: " << current->key << ", Item: ";

        //    // Check if the item has a print method
        //    // Assuming T is a class with a print() method
        //    current->item->print(); // Call the print method of the item

        //    std::cout << std::endl;
        //    current = current->next;
        //}
    }
    std::cout << endl;
}
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