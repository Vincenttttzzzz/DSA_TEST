


#pragma once
 
#include <iostream>


using namespace std;

template <typename T>
struct Node {
    T item;          // The data stored in the node
    Node* next;      // Pointer to the next node

    // Constructor for a node, defaulting next to nullptr
    Node(const T& item, Node* next = nullptr)
        : item(item), next(next) {
    }
};

template <typename T>
class LinkedList {

private:
    Node<T>* head;     // Pointer to the first node in the list
    int size;       // Number of elements in the list

public:
    // Constructor
    LinkedList();

    // Destructor: delete all nodes to avoid memory leaks
    ~LinkedList();

    // Add an element at the front of the list (O(1) insertion)
    void add(const T& data);

    // Retrieve the element at the specified index (throws exception if out of range)
    T get(int index) const;

    // Return a pointer to the first node (allows iteration)
    Node<T>* getFirstNode() const;

    // Check if the list is empty
    bool isEmpty() const;
    // Get the number of elements in the list
    int getLength() const;

    // Print all elements in the list (assumes T supports operator<<)
    //void prinz`t() const;
};


// template
//#pragma once
//class Actor;  // Forward declaration of Actor
//class Movie;  // Forward declaration of Movie
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//template <typename T>
//struct LinkedListNode {
//    T item;                   // data item of generic type T
//    LinkedListNode* next;     // pointer pointing to next item
//
//    LinkedListNode(const T& item, LinkedListNode* next = nullptr)
//        : item(item), next(next) {}
//};
//
//template <typename T>
//class LinkedList {
//private:
//    LinkedListNode<T>* firstNode; // points to the first item
//    int size;                     // number of items in the list
//
//public:
//    LinkedList();  // constructor
//    ~LinkedList(); // destructor
//
//    bool add(T item);
//    bool add(int index, T item);
//    void remove(int index);
//    T get(int index) const;
//    bool isEmpty() const;
//    int getLength() const;
//    void print() const;
//    void replace(int index, T item);
//    int search(T item) const;
//    void reverse();
//    std::vector<T> toVector() const;
//
//    // Getter for firstNode
//    LinkedListNode<T>* getFirstNode() const {
//        return firstNode;
//    }
//};
//
//// Implementation of templated functions
//
//template <typename T>
//LinkedList<T>::LinkedList() {
//    firstNode = nullptr;
//    size = 0;
//}
//
//// Destructor
//template <typename T>
//LinkedList<T>::~LinkedList() {
//    LinkedListNode<T>* current = firstNode;
//    while (current != nullptr) {
//        LinkedListNode<T>* toDelete = current;
//        current = current->next;
//        delete toDelete;
//    }
//}
//
//// Add an item to the back of the list
//template <typename T>
//bool LinkedList<T>::add(T item) {
//    LinkedListNode<T>* newNode = new LinkedListNode<T>(item);
//    if (size == 0) {
//        firstNode = newNode;
//    }
//    else {
//        LinkedListNode<T>* temp = firstNode;
//        while (temp->next != nullptr) {
//            temp = temp->next;
//        }
//        temp->next = newNode;
//    }
//    size++;
//    return true;
//}
//
//// Add an item at a specific position
//template <typename T>
//bool LinkedList<T>::add(int index, T item) {
//    if (index < 0 || index > size) {
//        return false;
//    }
//
//    LinkedListNode<T>* newNode = new LinkedListNode<T>(item);
//
//    if (index == 0) {
//        newNode->next = firstNode;
//        firstNode = newNode;
//    }
//    else {
//        LinkedListNode<T>* temp = firstNode;
//        for (int i = 0; i < index - 1; i++) {
//            temp = temp->next;
//        }
//        newNode->next = temp->next;
//        temp->next = newNode;
//    }
//    size++;
//    return true;
//}
//
//// Remove an item at a specified position
//template <typename T>
//void LinkedList<T>::remove(int index) {
//    if (index < 0 || index >= size) {
//        return;
//    }
//
//    LinkedListNode<T>* temp = firstNode;
//
//    if (index == 0) {
//        firstNode = firstNode->next;
//    }
//    else {
//        for (int i = 0; i < index - 1; i++) {
//            temp = temp->next;
//        }
//        LinkedListNode<T>* nodeToDelete = temp->next;
//        temp->next = nodeToDelete->next;
//        delete nodeToDelete;
//    }
//    size--;
//}
//
//// Retrieve an item from a specified position
//template <typename T>
//T LinkedList<T>::get(int index) const {
//    if (index < 0 || index >= size) {
//        throw out_of_range("Index out of range");
//    }
//
//    LinkedListNode<T>* temp = firstNode;
//    for (int i = 0; i < index; i++) {
//        temp = temp->next;
//    }
//    return temp->item;
//}
//
//// Check if the list is empty
//template <typename T>
//bool LinkedList<T>::isEmpty() const {
//    return size == 0;
//}
//
//// Get the size of the list
//template <typename T>
//int LinkedList<T>::getLength() const {
//    return size;
//}
//
//// Print the list elements
//template <typename T>
//void LinkedList<T>::print() const {
//    /*LinkedListNode<T>* temp = firstNode;
//    for (int i = 0; temp != nullptr; i++) {
//        cout << i + 1 << ". " << temp->item << endl;
//        temp = temp->next;
//    }*/
//
//    LinkedListNode<T>* temp = firstNode;
//    int i = 0;
//
//    while (temp != nullptr) {
//        cout << i + 1 << ". ";
//
//        if constexpr (std::is_same_v<T, std::weak_ptr<Actor>> || std::is_same_v<T, std::weak_ptr<Movie>>) {
//            // Handle weak pointers (Actor or Movie)
//            if (auto sharedPtr = temp->item.lock()) {
//                cout << *sharedPtr << endl; // Use operator<< for Actor or Movie
//            }
//            else {
//                cout << "[Expired Pointer]" << endl;
//            }
//        }
//        else {
//            // For other types
//            cout << temp->item << endl;
//        }
//
//        temp = temp->next;
//        ++i;
//    }
//}
//
//// Replace an item at a specified index
//template <typename T>
//void LinkedList<T>::replace(int index, T item) {
//    if (index < 0 || index >= size) {
//        cout << "Index out of range." << endl;
//        return;
//    }
//
//    LinkedListNode<T>* temp = firstNode;
//    for (int i = 0; i < index; i++) {
//        temp = temp->next;
//    }
//    temp->item = item;
//}
//
//// Search for an item in the list and return the index, or -1 if not found
//template <typename T>
//int LinkedList<T>::search(T item) const {
//    LinkedListNode<T>* temp = firstNode;
//    int index = 0;
//    while (temp != nullptr) {
//        if (temp->item == item) {
//            return index;
//        }
//        temp = temp->next;
//        index++;
//    }
//    return -1;
//}
//
//// Reverse the order of the list
//template <typename T>
//void LinkedList<T>::reverse() {
//    if (size <= 1) return;
//
//    LinkedListNode<T>* prev = nullptr;
//    LinkedListNode<T>* current = firstNode;
//    LinkedListNode<T>* next = nullptr;
//
//    while (current != nullptr) {
//        next = current->next;
//        current->next = prev;
//        prev = current;
//        current = next;
//    }
//    firstNode = prev;
//}
//
//// Convert the list to a vector for easier manipulation
//template <typename T>
//std::vector<T> LinkedList<T>::toVector() const {
//    std::vector<T> result;
//    LinkedListNode<T>* current = firstNode;
//    while (current) {
//        result.push_back(current->item);
//        current = current->next;
//    }
//    return result;
//}
