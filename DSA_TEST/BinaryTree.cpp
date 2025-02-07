//#include <iostream>
//#include "BinaryTree.h"
//#include <cmath>
//using namespace std;
//
//// Constructor
// 
//BST::BST() : root(nullptr) {}
//
//// Search
// 
//BinaryNode** BST::search(int target) {
//    return search(root, target);
//}
//
// 
//BinaryNode** BST::search(BinaryNode** t, int target) {
//    if (t == nullptr || t->item == target) {
//        return t;
//    }
//    return (target < t->item) ? search(t->left, target) : search(t->right, target);
//}
//
//// Insert
// 
//void BST::insert(int item) {
//    insert(root, item);
//}
//
// 
//void BST::insert(BinaryNode**& t, int item) {
//    if (t == nullptr) {
//        t = new BinaryNode*{ 0, item, nullptr, nullptr };
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
// 
//void BST::remove(int target) {
//    remove(root, target);
//}
//
// 
//void BST::remove(BinaryNode**& t, int target) {
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
//            BinaryNode** temp = t;
//            t = (t->left != nullptr) ? t->left : t->right;
//            delete temp;
//        }
//        else {
//            BinaryNode** successor = t->left;
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
// 
//void BST::inorder() {
//    if (isEmpty()) {
//        cout << "No item found" << endl;
//    }
//    else {
//        inorder(root);
//    }
//}
//
// 
//void BST::inorder(BinaryNode** t) {
//    if (t != nullptr) {
//        inorder(t->left);
//        cout << t->item << endl;
//        inorder(t->right);
//    }
//}
//
// 
//void BST::preorder() {
//    if (isEmpty()) {
//        cout << "No item found" << endl;
//    }
//    else {
//        preorder(root);
//    }
//}
//
// 
//void BST::preorder(BinaryNode** t) {
//    if (t != nullptr) {
//        cout << t->item << endl;
//        preorder(t->left);
//        preorder(t->right);
//    }
//}
//
// 
//void BST::postorder() {
//    if (isEmpty()) {
//        cout << "No item found" << endl;
//    }
//    else {
//        postorder(root);
//    }
//}
//
// 
//void BST::postorder(BinaryNode** t) {
//    if (t != nullptr) {
//        postorder(t->left);
//        postorder(t->right);
//        cout << t->item << endl;
//    }
//}
//
//// Utility
// 
//bool BST::isEmpty() {
//    return root == nullptr;
//}
//
// 
//int BST::countNodes() {
//    return countNodes(root);
//}
//
// 
//int BST::countNodes(BinaryNode** t) {
//    return (t == nullptr) ? 0 : 1 + countNodes(t->left) + countNodes(t->right);
//}
//
// 
//int BST::getHeight() {
//    return getHeight(root);
//}
//
// 
//int BST::getHeight(BinaryNode** t) {
//    return (t == nullptr) ? 0 : 1 + max(getHeight(t->left), getHeight(t->right));
//}
//
// 
//bool BST::isBalanced() {
//    return isBalanced(root);
//}
//
// 
//bool BST::isBalanced(BinaryNode** t) {
//    if (t == nullptr) {
//        return true;
//    }
//    int leftHeight = getHeight(t->left);
//    int rightHeight = getHeight(t->right);
//    return abs(leftHeight - rightHeight) <= 1 && isBalanced(t->left) && isBalanced(t->right);
//}


#include <iostream>
#include "BinaryTree.h"
#include "HashTable.h"
#include <vector>
#include <cmath>

using namespace std;

// Constructor
BST::BST() : root(nullptr) {}

// Search
 
BinaryNode* BST::search(int id, int target) {
    return search(root, id, target);
}

 
BinaryNode* BST::search(BinaryNode* t, int id, int target) {
    if (t == nullptr || t->item == target) {
        return t;
    }
    return (target < t->item) ? search(t->left, id, target) : search(t->right, id, target);
}

// Insert
 
void BST::insert(int id, int item) {
    insert(root, id, item);
}

 
void BST::insert(BinaryNode*& t, int id, int item) {
    if (t == NULL) {
        BinaryNode* newNode = new BinaryNode;
        newNode->id = id;
        newNode->item = item;
        newNode->left = NULL;
        newNode->right = NULL;
        t = newNode;
    }
    else {
        if (item < t->item) {
            insert(t->left, id, item);
        }
        else {
            insert(t->right, id, item);
        }
    }
}

// Remove
 
void BST::remove(int target) {
    remove(root, target);
}

 
void BST::remove(BinaryNode*& t, int target) {
    if (t != NULL) {
        if (target < t->id) {
            remove(t->left, target);
        }
        else if (target > t->id) {
            remove(t->right, target);
        }
        else {
            if (t->left == NULL && t->right == NULL) {
                BinaryNode* temp = t;
                t = NULL;
                delete temp;
            }
            else if (t->left == NULL) {
                BinaryNode* temp = t;
                if (t == root) {
                    root = t->right;
                }
                else {
                    t = t->right;
                }
                delete temp;
            }
            else if (t->right == NULL) {
                BinaryNode* temp = t;
                if (t == root) {
                    root = t->left;
                }
                else {
                    t = t->left;
                }
                delete temp;
            }
            else {
                /*BinaryNode* temp = t;
                BinaryNode* tempRight = t->left;
                while (tempRight->right != NULL) {
                    tempRight = tempRight->right;
                }
                t = tempRight
                tempRight->left = t->left;*/
                BinaryNode* tempRight = t->left;
                while (tempRight->right != NULL) {
                    tempRight = tempRight->right;
                }
                int id = tempRight->id;
                remove(t->left, id);
                t->id = id;
            }
        }
    }
}
//void BST::remove(BinaryNode*& t, int target) {
//    if (t != NULL) {
//        if (target < t->item) {
//            remove(t->left, target);
//        }
//        else if (target > t->item) {
//            remove(t->right, target);
//        }
//        else {
//            if (t->left == NULL && t->right == NULL) {
//                BinaryNode* temp = t;
//                t = NULL;
//                delete temp;
//            }
//            else if (t->left == NULL) {
//                BinaryNode* temp = t;
//                if (t == root) {
//                    root = t->right;
//                }
//                else {
//                    t = t->right;
//                }
//                delete temp;
//            }
//            else if (t->right == NULL) {
//                BinaryNode* temp = t;
//                if (t == root) {
//                    root = t->left;
//                }
//                else {
//                    t = t->left;
//                }
//                delete temp;
//            }
//            else {
//                /*BinaryNode* temp = t;
//                BinaryNode* tempRight = t->left;
//                while (tempRight->right != NULL) {
//                    tempRight = tempRight->right;
//                }
//                t = tempRight   
//                tempRight->left = t->left;*/
//                BinaryNode* tempRight = t->left;
//                while (tempRight->right != NULL) {
//                    tempRight = tempRight->right;
//                }
//                int item = tempRight->item;
//                remove(t->left, item);
//                t->item = item;
//            }
//        }
//    }
//}

// Traversals
 
void BST::inorder() {
    if (isEmpty()) {
        cout << "No item found" << endl;
    }
    else {
        inorder(root);
    }
}

 
void BST::inorder(BinaryNode* t) {
    if (t != nullptr) {
        inorder(t->left);
        cout << t->item << endl;
        inorder(t->right);
    }
}

 
void BST::preorder() {
    if (isEmpty()) {
        cout << "No item found" << endl;
    }
    else {
        preorder(root);
    }
}

 
void BST::preorder(BinaryNode* t) {
    if (t != nullptr) {
        cout << t->item << endl;
        preorder(t->left);
        preorder(t->right);
    }
}

 
void BST::postorder() {
    if (isEmpty()) {
        cout << "No item found" << endl;
    }
    else {
        postorder(root);
    }
}

 
void BST::postorder(BinaryNode* t) {
    if (t != nullptr) {
        postorder(t->left);
        postorder(t->right);
        cout << t->item << endl;
    }
}

//template <typename T>
//void BST::displayByRange(int value1, int value2, HashTable<T>*) {
//    displayByRange(root, value1, value2);
//}
//
//template <typename T>
//void BST::displayByRange(BinaryNode* root, int value1, int value2, HashTable<T>* table) {
//    if (root == NULL) {
//        return; // Base case: empty tree or end of branch
//    }
//
//    // Traverse the left subtree if it may contain values in the range
//    if (value1 < root->item) {
//        displayByRange(root->left, value1, value2, table);
//    }
//
//    // Process the current node if it's within the range
//    if (root->item >= value1 && root->item <= value2) {
//        // Lookup in the hashtable using actorID
//        T actor = table->get(root->item); // Assuming `get` retrieves the object by key
//        std::cout << "Actor ID: " << root->item << ", Name: " << actor.name
//            << ", Birth Year: " << actor.birthYear << std::endl;
//    }
//
//    // Traverse the right subtree if it may contain values in the range
//    if (value2 > root->item) {
//        displayByRange(root->right, value1, value2, table);
//    }
//}

// Utility
 
bool BST::isEmpty() {
    return root == nullptr;
}

 
int BST::countNodes() {
    return countNodes(root);
}

 
int BST::countNodes(BinaryNode* t) {
    return (t == nullptr) ? 0 : 1 + countNodes(t->left) + countNodes(t->right);
}

 
int BST::getHeight() {
    return getHeight(root);
}

 
int BST::getHeight(BinaryNode* t) {
    return (t == nullptr) ? 0 : 1 + max(getHeight(t->left), getHeight(t->right));
}

 
bool BST::isBalanced() {
    return isBalanced(root);
}

 
bool BST::isBalanced(BinaryNode* t) {
    if (t == nullptr) {
        return true;
    }
    int leftHeight = getHeight(t->left);
    int rightHeight = getHeight(t->right);
    return abs(leftHeight - rightHeight) <= 1 && isBalanced(t->left) && isBalanced(t->right);
}




// other functions
//template <typename T>
//std::vector<int> BST::displayByRange(int value1, int value2) const {
//    std::vector<int> result;
//    displayByRange(root, value1, value2, result);
//    return result;
//}
//
//void BST::displayByRange(BinaryNode* root, int value1, int value2, std::vector<int>& result) const {
//    if (root == nullptr) {
//        return; // Base case: empty tree or end of branch
//    }
//
//    // Traverse the left subtree if it may contain values in the range
//    if (value1 < root->item) {
//        displayByRange(root->left, value1, value2, result);
//    }
//
//    // Process the current node if it's within the range
//    if (root->item >= value1 && root->item <= value2) {
//        result.push_back(root->id); // Add the actor ID to the result
//    }
//
//    // Traverse the right subtree if it may contain values in the range
//    if (value2 > root->item) {
//        displayByRange(root->right, value1, value2, result);
//    }
//}

