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
