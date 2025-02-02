//// BST.h - Specification of BST (Binary Search Tree)
//#pragma once
//#include <iostream>
////#include "BinaryNode.h"
//using namespace std;
//
//
//template <typename int>
//struct BinaryNode {
//	int id;
//	int item;
//	BinaryNode* left;
//	BinaryNode* right;
//};
//
//template <typename int>
//class BST
//{
//private:
//
//	//struct BinaryNode {
//	//	int id;
//	//	int item;
//	//	BinaryNode* left;
//	//	BinaryNode* right;
//	//};
//	//BinaryNode* root;		// root of the BST
//
//	// Alias for the templated BinaryNode
//	BinaryNode<int>* root;           // Root of the BST
//
//public:
//	// constructor
//	BST();
//
//	// search an item in the binary search tree
//	BinaryNode<int>* search(int target);
//	BinaryNode<int>* search(BinaryNode<int>* root, int target);
//
//	// insert an item to the binary search tree
//	void insert(int item);
//	void insert(BinaryNode<int>*& root, int item);
//
//	// delete an item from the binary search tree
//	void remove(int target);
//	void remove(BinaryNode<int>*& root, int target);
//
//	// traverse the binary search tree in inorder
//	void inorder();
//	void inorder(BinaryNode<int>* t);
//
//	// traverse the binary search tree in preorder
//	void preorder();
//	void preorder(BinaryNode<int>* t);
//
//	// traverse the binary search tree in postorder
//	void postorder();
//	void postorder(BinaryNode<int>* t);
//
//	// check if the binary search tree is empty
//	bool isEmpty();
//
//	// ----------------- to be implemented ------------------
//  // count the number of nodes in the binary search tree
//	int countNodes();
//	int countNodes(BinaryNode<int>* t);
//
//	// compute the height of the binary search tree
//	int getHeight();
//	int getHeight(BinaryNode<int>* t);
//
//
//	// check if the binary search tree is balanced
//	bool isBalanced();
//	bool isBalanced(BinaryNode<int>* t);
//};
//
//// Constructor
//template <typename int>
//BST<int>::BST() : root(nullptr) {}
//
//// Search
//template <typename int>
//BinaryNode<int>* BST<int>::search(int target) {
//    return search(root, target);
//}
//
//template <typename int>
//BinaryNode<int>* BST<int>::search(BinaryNode<int>* t, int target) {
//    if (t == nullptr || t->item == target) {
//        return t;
//    }
//    return (target < t->item) ? search(t->left, target) : search(t->right, target);
//}
//
//// Insert
//template <typename int>
//void BST<int>::insert(int item) {
//    insert(root, item);
//}
//
//template <typename int>
//void BST<int>::insert(BinaryNode<int>*& t, int item) {
//    if (t == nullptr) {
//        t = new BinaryNode<int>{ 0, item, nullptr, nullptr };
//    }
//    else if (item < t->item) {
//        insert(t->left, item);
//    }
//    else {
//        insert(t->right, item);
//    }
//}
//
//// Remove
//template <typename int>
//void BST<int>::remove(int target) {
//    remove(root, target);
//}
//
//template <typename int>
//void BST<int>::remove(BinaryNode<int>*& t, int target) {
//    if (t == nullptr) {
//        return;
//    }
//
//    if (target < t->item) {
//        remove(t->left, target);
//    }
//    else if (target > t->item) {
//        remove(t->right, target);
//    }
//    else {
//        if (t->left == nullptr || t->right == nullptr) {
//            BinaryNode<int>* temp = t;
//            t = (t->left != nullptr) ? t->left : t->right;
//            delete temp;
//        }
//        else {
//            BinaryNode<int>* successor = t->left;
//            while (successor->right != nullptr) {
//                successor = successor->right;
//            }
//            t->item = successor->item;
//            remove(t->left, successor->item);
//        }
//    }
//}
//
//// Traversals
//template <typename int>
//void BST<int>::inorder() {
//    if (isEmpty()) {
//        cout << "No item found" << endl;
//    }
//    else {
//        inorder(root);
//    }
//}
//
//template <typename int>
//void BST<int>::inorder(BinaryNode<int>* t) {
//    if (t != nullptr) {
//        inorder(t->left);
//        cout << t->item << endl;
//        inorder(t->right);
//    }
//}
//
//template <typename int>
//void BST<int>::preorder() {
//    if (isEmpty()) {
//        cout << "No item found" << endl;
//    }
//    else {
//        preorder(root);
//    }
//}
//
//template <typename int>
//void BST<int>::preorder(BinaryNode<int>* t) {
//    if (t != nullptr) {
//        cout << t->item << endl;
//        preorder(t->left);
//        preorder(t->right);
//    }
//}
//
//template <typename int>
//void BST<int>::postorder() {
//    if (isEmpty()) {
//        cout << "No item found" << endl;
//    }
//    else {
//        postorder(root);
//    }
//}
//
//template <typename int>
//void BST<int>::postorder(BinaryNode<int>* t) {
//    if (t != nullptr) {
//        postorder(t->left);
//        postorder(t->right);
//        cout << t->item << endl;
//    }
//}
//
//// Utility
//template <typename int>
//bool BST<int>::isEmpty() {
//    return root == nullptr;
//}
//
//template <typename int>
//int BST<int>::countNodes() {
//    return countNodes(root);
//}
//
//template <typename int>
//int BST<int>::countNodes(BinaryNode<int>* t) {
//    return (t == nullptr) ? 0 : 1 + countNodes(t->left) + countNodes(t->right);
//}
//
//template <typename int>
//int BST<int>::getHeight() {
//    return getHeight(root);
//}
//
//template <typename int>
//int BST<int>::getHeight(BinaryNode<int>* t) {
//    return (t == nullptr) ? 0 : 1 + max(getHeight(t->left), getHeight(t->right));
//}
//
//template <typename int>
//bool BST<int>::isBalanced() {
//    return isBalanced(root);
//}
//
//template <typename int>
//bool BST<int>::isBalanced(BinaryNode<int>* t) {
//    if (t == nullptr) {
//        return true;
//    }
//    int leftHeight = getHeight(t->left);
//    int rightHeight = getHeight(t->right);
//    return abs(leftHeight - rightHeight) <= 1 && isBalanced(t->left) && isBalanced(t->right);
//}

 
// BST.h - Specification of BST (Binary Search Tree)
#pragma once
#include <iostream>
#include <vector>
#include "HashTable.h"
using namespace std;


struct BinaryNode {
	int id;
	int item;
	BinaryNode* left;
	BinaryNode* right;
};

class BST
{
private:

	//struct BinaryNode {
	//	int id;
	//	int item;
	//	BinaryNode* left;
	//	BinaryNode* right;
	//};
	//BinaryNode* root;		// root of the BST

	// Alias for the templated BinaryNode
	BinaryNode* root;           // Root of the BST

public:
	// constructor
	BST();

	// search an item in the binary search tree
	BinaryNode* search(int id, int target);
	BinaryNode* search(BinaryNode* root, int id, int target);

	// insert an item to the binary search tree
	void insert(int id, int item);
	void insert(BinaryNode*& root, int id, int item);

	// delete an item from the binary search tree
	void remove(int target);
	void remove(BinaryNode*& root, int target);

	// traverse the binary search tree in inorder
	void inorder();
	void inorder(BinaryNode* t);

	// traverse the binary search tree in preorder
	void preorder();
	void preorder(BinaryNode* t);

	// traverse the binary search tree in postorder
	void postorder();
	void postorder(BinaryNode* t);

	// Method 1
	/*template <typename T>
	void displayByRange(int, int, const HashTable<T>&) const;

	template <typename T>
	void displayByRange(BinaryNode*, int, int, const HashTable<T>&) const;*/
	

	// Method 2
	/*vector<int> displayByRange(int, int) const;
	void displayByRange(BinaryNode*, int, int, vector<int>&) const;*/
	template <typename Callback>
	void displayByRange(int value1, int value2, Callback callback) const;

	template <typename Callback>
	void displayByRange(BinaryNode*, int value1, int value2, Callback callback) const;

	// check if the binary search tree is empty
	bool isEmpty();

	// ----------------- to be implemented ------------------
  // count the number of nodes in the binary search tree
	int countNodes();
	int countNodes(BinaryNode* t);

	// compute the height of the binary search tree
	int getHeight();
	int getHeight(BinaryNode* t);


	// check if the binary search tree is balanced
	bool isBalanced();
	bool isBalanced(BinaryNode* t);
};


//template <typename T>
//void BST::displayByRange(int value1, int value2, const HashTable<T>& table) const {
//	displayByRange(root, value1, value2, table);
//}
//
//template <typename T>
//void BST::displayByRange(BinaryNode* root, int value1, int value2, const HashTable<T>& table) const {
//	if (root == NULL) {
//		return; // Base case: empty tree or end of branch
//	}	
//
//	// Traverse the left subtree if it may contain values in the range
//	if (value1 < root->item) {
//		displayByRange(root->left, value1, value2, table);
//	}
//
//	// Process the current node if it's within the range
//	if (root->item >= value1 && root->item <= value2) {
//		// Lookup in the hashtable using actorID
//		T item = table.get(root->id); // Assuming `get` retrieves the object by key
//		item->print();
//		/*std::cout << "Actor ID: " << root->item << ", Name: " << actor.name
//			<< ", Birth Year: " << actor.birthYear << std::endl;*/
//	}
//
//	// Traverse the right subtree if it may contain values in the range
//	if (value2 > root->item) {
//		displayByRange(root->right, value1, value2, table);
//	}
//}

template <typename Callback>
void BST::displayByRange(int value1, int value2, Callback callback) const {
	displayByRange(root, value1, value2, callback);
}

template <typename Callback>
void BST::displayByRange(BinaryNode* root, int value1, int value2, Callback callback) const {
	if (root == nullptr) {
		return; // Base case: empty tree or end of branch
	}

	// Traverse the left subtree if it may contain values in the range
	if (value1 < root->item) {
		displayByRange(root->left, value1, value2, callback);
	}

	// Process the current node if it's within the range
	if (root->item >= value1 && root->item <= value2) {
		callback(root->id); // Pass the actor ID to the callback
	}

	// Traverse the right subtree if it may contain values in the range
	if (value2 >= root->item) {
		displayByRange(root->right, value1, value2, callback);
	}
}