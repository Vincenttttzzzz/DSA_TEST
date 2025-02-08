#pragma once
#include <iostream>
#include "LinkedList.h"
#include "Movie.h"
#include "Actor.h"
#include "HashTable.h"
#include "Rating.h"

template class LinkedList<std::weak_ptr<Movie>>;
//template struct HashNode<std::shared_ptr<Movie>>;
//template struct HashNode<std::shared_ptr<Actor>>;
template class LinkedList<std::shared_ptr<Movie>>;
template class LinkedList<std::shared_ptr<Actor>>;
template class LinkedList<Rating>;
//template class LinkedList<HashNode<std::shared_ptr<Movie>>*>;
//template class LinkedList<HashNode<std::shared_ptr<Actor>>*>;
//template struct Node<Movie>;       // For Node<Movie> if n;eeded

using namespace std;

// Constructor
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0) {}

// Destructor: delete all nodes to avoid memory leaks
template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
}

// Add an element at the front of the list (O(1) insertion)
template <typename T>
void LinkedList<T>::add(const T& data) {
    Node<T>* newHead = new Node<T>(data);  // Specify Node<T> instead of just Node
    newHead->next = head;  // Correctly link the new node to the current head
    head = newHead;        // Update the head to the new node
    size++;
}

// Retrieve the element at the specified index (throws exception if out of range)
template <typename T>
T LinkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range in LinkedList::get()");
    }
    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->item;
}

// Return a pointer to the first node (allows iteration)
//template <typename T>
template <typename T>
Node<T>* LinkedList<T>::getFirstNode() const {
    // Explicit null check
    if (head == nullptr) {
        return nullptr;  // Safe return instead of undefined behavior
    }
    return head;
}

// Check if the list is empty
template <typename T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

// Get the number of elements in the list
template <typename T>
int LinkedList<T>::getLength() const {
    return size;
}

// Print all elements in the list (assumes T supports operator<<)
//template <typename T>
//void LinkedList<T>::print() const {
//    Node* current = head;
//    while (current) {
//        // Handle weak_ptr special cases first
//        if constexpr (std::is_same_v<T, std::weak_ptr<Movie>> ||
//            std::is_same_v<T, std::weak_ptr<Actor>>) {
//            // Try to lock the weak_ptr to get access to the object
//            if (auto ptr = current->item.lock()) {
//                // Call the object's print method
//                ptr->print();
//                std::cout << " ";
//            }
//            else {
//                std::cout << "[Expired] ";
//            }
//        }
//        // Handle shared_ptr cases
//        else if constexpr (std::is_pointer_v<T> ||
//            is_smart_pointer_v<T>) {
//            // For pointers (both raw and smart), dereference and call print
//            if (current->item) {  // Check for null
//                current->item->print();
//                std::cout << " ";
//            }
//            else {
//                std::cout << "[Null] ";
//            }
//        }
//        // Handle regular objects that have a print method
//        else {
//            current->item.print();
//            std::cout << " ";
//        }
//        current = current->next;
//    }
//    std::cout << std::endl;
//}

//// Add an element at the end of the list
//void add(const T& data) {
//    if (!head) {
//        head = new Node(data);
//    }
//    else {
//        Node* current = head;
//        while (current->next != nullptr) {
//            current = current->next;
//        }
//        current->next = new Node(data);
//    }
//    size++;
//}

// Add an element at a specified index (0-indexed)
//bool add(int index, const T& data) {
//    if (index < 0 || index > size) {
//        return false; // Out of bounds
//    }
//    if (index == 0) {
//        addFront(data);
//        return true;
//    }
//    Node* current = head;
//    for (int i = 0; i < index - 1; i++) {
//        current = current->next;
//    }
//    current->next = new Node(data, current->next);
//    size++;
//    return true;
//}











//#include "LinkedList.h"
//
////do i need to set pointer to nullptr when they are declared?
//LinkedList::LinkedList() {
//	//is this correct way of initialising? (or nullptr?)
//	firstNode = NULL;
//	size = 0;
//}
//
//LinkedList::~LinkedList() {
//	//what do i put here for destructor?
//	Node* current = firstNode;
//	while (current != nullptr) {
//		Node* toDelete = current;
//		current = current->next;
//		delete toDelete;
//	}
//}
//
//bool LinkedList::add(ItemType n) {
//	Node* newNode = new Node;
//	newNode->item = n;
//	newNode->next = NULL;
//
//	if (size == 0) {
//		firstNode = newNode;
//	}
//	else {
//		Node* temp = firstNode;
//		while (temp->next != NULL) {
//			temp = temp->next;
//		}
//		temp->next = newNode;
//	}
//	size += 1;
//	return true;
//}
//
//bool LinkedList::add(int index, ItemType n) {
//	bool success = (index >= 0 && index <= size);
//
//	if (!success) {
//		return false;
//	}
//
//	Node* newNode = new Node;
//	newNode->item = n;
//	newNode->next = NULL;
//
//	if (index == 0) {
//		newNode->next = firstNode;
//		firstNode = newNode;
//	}
//	else {
//		Node* temp = firstNode;
//		for (int i = 0; i < (index - 1); i++) {
//			temp = temp->next;
//		}
//		newNode->next = temp->next;
//		temp->next = newNode;
//	}
//	size += 1;
//	return true;
//}
//
////is this correct implementation of the remove method?
//void LinkedList::remove(int index) {
//	bool success = (index >= 0 && index < size);
//	Node* temp = firstNode;
//
//	if (!success) {
//		return;
//	}
//
//	if (index == 0) {
//		firstNode = firstNode->next;
//	}
//	else {
//		for (int i = 0; i < (index - 1); i++) {
//			temp = temp->next;
//		}
//
//		Node* nodeToDelete = temp->next;
//		temp->next = nodeToDelete->next;
//		delete nodeToDelete;
//		/*if (index + 1 < size) {
//			temp->next = temp->next->next;
//		}
//		else {
//			temp->next = NULL;
//		}*/
//	}
//	size -= 1;
//}
//
//int LinkedList::get(int index) {
//	bool success = (index < size);
//	Node* temp = firstNode;
//
//	if (!success) {
//		return NULL;
//	}
//
//	for (int i = 0; i < index; i++) {
//		temp = temp->next;
//	}
//	return temp->item;
//}
//
//bool LinkedList::isEmpty() {
//	if (size == 0) {
//		return true;
//	}
//	return false;
//}
//
//int LinkedList::getLength() {
//	return size;
//}
//
//void LinkedList::print() {
//	Node* temp = firstNode;
//
//	//cout << "LinkedList Of Actors: " << endl;
//	for (int i = 0; i < size; i++) {
//		cout << i + 1 << temp->item << endl;
//		temp = temp->next;
//	}
//}
//
//void LinkedList::replace(int index, ItemType item) {
//	if (index >= 0 && index < size) {
//		Node* temp = firstNode;
//		for (int i = 0; i < index; i++) {
//			temp = temp->next;
//		}
//		temp->item = item;
//	}
//	else {
//		std::cout << "Index out of range." << std::endl;
//	}
//}
//
//int LinkedList::search(ItemType item) {
//	Node* temp = firstNode;
//	int index = 0;
//	while (temp != nullptr) {
//		if (temp->item == item) {
//			return index; // Found, return index
//		}
//		temp = temp->next;
//		index++;
//	}
//	return -1; // Not found
//}
//
//void LinkedList::reverse() {
//	if (size <= 1) return; // No need to reverse if list is empty or has one item
//
//	Node* prev = nullptr;
//	Node* current = firstNode;
//	Node* next = nullptr;
//
//	while (current != nullptr) {
//		next = current->next; // Save the next node
//		current->next = prev; // Reverse the link
//		prev = current;       // Move prev to current
//		current = next;       // Move current to next
//	}
//
//	firstNode = prev; // Update the head of the list
//}
//
//
//
//
//// version 2.0
////#include "LinkedList.h"
////
////// Constructor
////template <typename T>
////LinkedList<T>::LinkedList() {
////    firstNode = nullptr;
////    size = 0;
////}
////
////// Destructor
////template <typename T>
////LinkedList<T>::~LinkedList() {
////    Node* current = firstNode;
////    while (current != nullptr) {
////        Node* toDelete = current;
////        current = current->next;
////        delete toDelete;
////    }
////}
////
////// Add an item to the back of the list
////template <typename T>
////bool LinkedList<T>::add(T item) {
////    Node* newNode = new Node;
////    newNode->item = item;
////    newNode->next = nullptr;
////
////    if (size == 0) {
////        firstNode = newNode;
////    }
////    else {
////        Node* temp = firstNode;
////        while (temp->next != nullptr) {
////            temp = temp->next;
////        }
////        temp->next = newNode;
////    }
////    size++;
////    return true;
////}
////
////// Add an item at a specific position
////template <typename T>
////bool LinkedList<T>::add(int index, T item) {
////    if (index < 0 || index > size) {
////        return false;
////    }
////
////    Node* newNode = new Node;
////    newNode->item = item;
////    newNode->next = nullptr;
////
////    if (index == 0) {
////        newNode->next = firstNode;
////        firstNode = newNode;
////    }
////    else {
////        Node* temp = firstNode;
////        for (int i = 0; i < index - 1; i++) {
////            temp = temp->next;
////        }
////        newNode->next = temp->next;
////        temp->next = newNode;
////    }
////    size++;
////    return true;
////}
////
////// Remove an item at a specified position
////template <typename T>
////void LinkedList<T>::remove(int index) {
////    if (index < 0 || index >= size) {
////        return;
////    }
////
////    Node* temp = firstNode;
////
////    if (index == 0) {
////        firstNode = firstNode->next;
////    }
////    else {
////        for (int i = 0; i < index - 1; i++) {
////            temp = temp->next;
////        }
////        Node* nodeToDelete = temp->next;
////        temp->next = nodeToDelete->next;
////        delete nodeToDelete;
////    }
////    size--;
////}
////
////// Retrieve an item from a specified position
////template <typename T>
////T LinkedList<T>::get(int index) const {
////    if (index < 0 || index >= size) {
////        throw out_of_range("Index out of range");
////    }
////
////    Node* temp = firstNode;
////    for (int i = 0; i < index; i++) {
////        temp = temp->next;
////    }
////    return temp->item;
////}
////
////// Check if the list is empty
////template <typename T>
////bool LinkedList<T>::isEmpty() const {
////    return size == 0;
////}
////
////// Get the size of the list
////template <typename T>
////int LinkedList<T>::getLength() const {
////    return size;
////}
////
////// Print the list elements
////template <typename T>
////void LinkedList<T>::print() const {
////    Node* temp = firstNode;
////    for (int i = 0; temp != nullptr; i++) {
////        cout << i + 1 << ". " << temp->item << endl;
////        temp = temp->next;
////    }
////}
////
////// Replace an item at a specified index
////template <typename T>
////void LinkedList<T>::replace(int index, T item) {
////    if (index < 0 || index >= size) {
////        cout << "Index out of range." << endl;
////        return;
////    }
////
////    Node* temp = firstNode;
////    for (int i = 0; i < index; i++) {
////        temp = temp->next;
////    }
////    temp->item = item;
////}
////
////// Search for an item in the list and return the index, or -1 if not found
////template <typename T>
////int LinkedList<T>::search(T item) const {
////    Node* temp = firstNode;
////    int index = 0;
////    while (temp != nullptr) {
////        if (temp->item == item) {
////            return index;
////        }
////        temp = temp->next;
////        index++;
////    }
////    return -1;
////}
////
////// Reverse the order of the list
////template <typename T>
////void LinkedList<T>::reverse() {
////    if (size <= 1) return;
////
////    Node* prev = nullptr;
////    Node* current = firstNode;
////    Node* next = nullptr;
////
////    while (current != nullptr) {
////        next = current->next;
////        current->next = prev;
////        prev = current;
////        current = next;
////    }
////    firstNode = prev;
////}
////
////// Convert the list to a vector for easier manipulation
////template <typename T>
////std::vector<T> LinkedList<T>::toVector() const {
////    std::vector<T> result;
////    Node* current = firstNode;
////    while (current) {
////        result.push_back(current->item);
////        current = current->next;
////    }
////    return result;
////}
