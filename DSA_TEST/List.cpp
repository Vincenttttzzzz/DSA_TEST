//#include "List.h"
//
//
//List::List() {
//    size = 0;
//}
//
//// Add an item to the back of the list (append)
//bool List::add(int item)
//{
//    bool success = size < MAX_SIZE;
//    if (success)
//    {
//        items[size] = item;    // Add to the end of the list
//        size++;                // Increase the size by 1
//    }
//    return success;
//}
//
//
//// Display the items in the list
//void List::print()
//{
//    for (int i = 0; i < size; i++) {
//        std::cout << items[i] << ". ";
//    }
//    std::cout << endl;
//}
//
//void List::rotate(int num)
//{
//
//    int m = 0;
//
//    for (int i = 0; i < num; i++) {
//        /* Node* newNode = new Node;
//         newNode->item = firstNode->item;
//         newNode->next = NULL;*/
//
//        for (int pos = 0; pos < size; pos++) {
//            items[pos] = items[pos + 1];
//        }
//
//        items[size] = num;
//
//    }
//
//    return;
//}






// version 2
//#include "List.h"
//
//// Constructor
//List::List(int initialSize) : maxSize(initialSize), size(0) {
//    items = new int[maxSize]; // Allocate memory for the array
//}
//
//// Destructor
//List::~List() {
//    delete[] items; // Free the allocated memory
//}
//
//// Resize the array
//void List::resize(int newSize) {
//    int* temp = new int[newSize]; // Allocate new memory
//    for (int i = 0; i < size; ++i) {
//        temp[i] = items[i]; // Copy existing elements
//    }
//    delete[] items; // Free old memory
//    items = temp;   // Point to the new array
//    maxSize = newSize;
//}
//
//// Add an item to the list
//bool List::add(int item) {
//    if (size >= maxSize) {
//        resize(maxSize * 2); // Double the size when full
//    }
//    items[size++] = item;
//    return true;
//}
//
//// Get an item at a specified index
//int List::get(int index) const {
//    if (index < 0 || index >= size) {
//        throw out_of_range("Index out of range");
//    }
//    return items[index];
//}
//
//// Get the size of the list
//int List::getLength() const {
//    return size;
//}
//
//// Print the list
//void List::print() const {
//    for (int i = 0; i < size; ++i) {
//        cout << items[i] << " ";
//    }
//    cout << endl;
//}
//
//// Clear the list
//void List::clear() {
//    size = 0; // Just reset the size (memory stays allocated)
//}
