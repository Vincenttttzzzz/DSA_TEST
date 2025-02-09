#include "AVLTree.h"


// ===== AVLNode Constructor =====
template <typename T>
AVLTree<T>::AVLNode::AVLNode(int k, int i, T d)
    : key(k), item(i), data(d), left(nullptr), right(nullptr), height(1) {
}

// ===== Constructor / Destructor =====
template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
AVLTree<T>::~AVLTree() {
    destroyTree(root);
}

// ===== Helper Functions =====
template <typename T>
int AVLTree<T>::height(AVLNode* node) const {
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::balanceFactor(AVLNode* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

template <typename T>
void AVLTree<T>::updateHeight(AVLNode* node) {
    if (node) {
        int hl = height(node->left);
        int hr = height(node->right);
        node->height = 1 + (hl > hr ? hl : hr);
    }
}

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::balance(AVLNode* node) {
    if (!node) return node;

    updateHeight(node);
    int bf = balanceFactor(node);

    // Left heavy
    if (bf > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Right heavy
    if (bf < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

// ===== Insertion =====
// Use a separate template parameter U to avoid shadowing the class template parameter.
template <typename T>
template <typename U>
typename AVLTree<T>::AVLNode* AVLTree<T>::insertNode(AVLNode* node, int key, int item, U data) {
    if (!node)
        return new AVLNode(key, item, data);

    if (item < node->item)
        node->left = insertNode(node->left, key, item, data);
    else if (item > node->item)
        node->right = insertNode(node->right, key, item, data);
    else { // item equals node->item; break ties by key.
        if (key < node->key)
            node->left = insertNode(node->left, key, item, data);
        else if (key > node->key)
            node->right = insertNode(node->right, key, item, data);
        else
            return node; // Duplicate key and item; do nothing.
    }

    return balance(node);
}

template <typename T>
template <typename U>
void AVLTree<T>::insert(int key, int item, U data) {
    root = insertNode(root, key, item, data);
}

// ===== Removal =====
template <typename T>
typename AVLTree<T>::AVLNode* AVLTree<T>::removeNode(AVLNode* node, int key) {
    if (!node) return node;

    if (key < node->key) {
        node->left = removeNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = removeNode(node->right, key);
    }
    else {
        // Node with matching key found.
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                // No child case.
                temp = node;
                node = nullptr;
            }
            else {
                // One child case.
                *node = *temp;
            }
            delete temp;
        }
        else {
            // Node with two children: get the inorder successor (smallest in the right subtree)
            AVLNode* temp = node->right;
            while (temp->left != nullptr)
                temp = temp->left;
            // Copy the inorder successor's data to this node.
            node->key = temp->key;
            node->item = temp->item;
            node->data = temp->data;
            // Delete the inorder successor.
            node->right = removeNode(node->right, temp->key);
        }
    }

    // If the tree had only one node, then return.
    if (!node)
        return node;

    return balance(node);
}

template <typename T>
void AVLTree<T>::remove(int key) {
    root = removeNode(root, key);
}

// ===== Destroy Tree =====
template <typename T>
void AVLTree<T>::destroyTree(AVLNode* node) {
    if (!node)
        return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// ===== In-Order Range Query =====
template <typename T>
template <typename Callback>
void AVLTree<T>::inOrderRange(AVLNode* node, int low, int high, Callback cb) const {
    if (!node)
        return;
    // Traverse left if there is a chance of finding a valid node
    if (node->item > low || (node->item == low && node->key > low))
        inOrderRange(node->left, low, high, cb);

    // Process the node if it's within the range
    if (node->item >= low && node->item <= high)
        cb(node->data);

    // Traverse right if there is a chance of finding a valid node
    if (node->item < high || (node->item == high && node->key < high))
        inOrderRange(node->right, low, high, cb);
}

template <typename T>
template <typename Callback>
void AVLTree<T>::rangeQuery(int low, int high, Callback callback) const {
    inOrderRange(root, low, high, callback);
}

// =====================================================
// Explicit instantiation can be provided in a separate file
// if desired. Otherwise, users must include the full template
// definition in the header.
// =====================================================
