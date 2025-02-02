//#include "HashTable.h"
//#include "List.h"
//
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
//        Node* current = items[i];
//        while (current != nullptr) {
//            Node* toDelete = current;
//            current = current->next;
//            delete toDelete;
//        }
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
//template <typename T>
//int HashTable<T>::hash(KeyType key) {
//    int hashValue = 0;
//    for (char c : key) {
//        hashValue = (hashValue * 37 + c) % MAX_SIZE;
//    }
//    return hashValue;
//
//}
//
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
//T HashTable<T>::get(KeyType key) {
//    /* int index = hash(key);
//
//     if (items[index] == nullptr) {
//         return items[index]->item;
//     }
//     return nullptr;*/
//
//    int index = hash(key);
//
//    Node* current = items[index];
//    while (current != nullptr) {
//        if (current->key == key) {
//            return current->item;
//        }
//        current = current->next;
//    }
//
//    return nullptr; // Key not found
//}
//
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
//        Node* current = items[i];
//        while (current != nullptr) {
//            std::cout << "Key: " << current->key << ", Item: " << current->item << std::endl;
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