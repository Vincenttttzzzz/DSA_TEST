//#include "Queue.h"
//
//// Constructor
//template <typename T>
//Queue<T>::Queue() {
//    frontNode = nullptr;
//    backNode = nullptr;
//    size = 0; // Initialize size
//}
//
//// Destructor
//template <typename T>
//Queue<T>::~Queue() {
//    while (!isEmpty()) {
//        dequeue();
//    }
//}
//
//// Enqueue operation: Add an item to the back of the queue
//template <typename T>
//bool Queue<T>::enqueue(const T& item) {
//    Node* newNode = new Node();
//    newNode->item = item;
//    newNode->next = nullptr;
//
//    if (isEmpty()) {
//        frontNode = newNode;
//    }
//    else {
//        backNode->next = newNode;
//    }
//    backNode = newNode;
//    size++; // Increment size
//    return true;
//}
//
//// Dequeue operation: Remove item from front of queue
//template <typename T>
//T Queue<T>::dequeue() {
//    if (isEmpty()) {
//        throw runtime_error("Queue is empty");
//    }
//
//    Node* temp = frontNode;
//    T item = temp->item; // Store the item to return
//
//    if (frontNode == backNode) {
//        frontNode = nullptr;
//        backNode = nullptr;
//    }
//    else {
//        frontNode = frontNode->next;
//    }
//
//    delete temp;
//    size--; // Decrement size
//    return item;
//}
//
//// Dequeue operation: Remove item and retrieve it
//template <typename T>
//T Queue<T>::dequeue(T& item) {
//    if (isEmpty()) {
//        return false;
//    }
//
//    Node* temp = frontNode;
//    item = temp->item; // Store the item via reference
//
//    if (frontNode == backNode) {
//        frontNode = nullptr;
//        backNode = nullptr;
//    }
//    else {
//        frontNode = frontNode->next;
//    }
//
//    delete temp;
//    size--; // Decrement size
//    return true;
//}
//
//// Get front item without removing it
//template <typename T>
//bool Queue<T>::getFront(T& item) const {
//    if (isEmpty()) {
//        return false;
//    }
//    item = frontNode->item;
//    return true;
//}
//
//// Check if the queue is empty
//template <typename T>
//bool Queue<T>::isEmpty() const {
//    return frontNode == nullptr;
//}
//
//// Display items in queue from front to back
//template <typename T>
//void Queue<T>::displayItems() const {
//    Node* temp = frontNode;
//    while (temp != nullptr) {
//        cout << temp->item << " ";
//        temp = temp->next;
//    }
//    cout << endl;
//}
//
//// Reverse the queue recursively
//template <typename T>
//void Queue<T>::reverse() {
//    if (isEmpty()) {
//        return; // Base case: if queue is empty, do nothing
//    }
//
//    // Step 1: Dequeue the front item
//    T frontItem;
//    dequeue(frontItem);
//
//    // Step 2: Recursively reverse the rest of the queue
//    reverse();
//
//    // Step 3: Enqueue the front item back to the queue
//    enqueue(frontItem);
//}
//
//template <typename T>
//int Queue<T>::getSize() const {
//    return size;
//}