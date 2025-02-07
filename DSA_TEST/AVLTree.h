#pragma once
#include <iostream>
#include <functional>

template <typename T>
class AVLTree {
private:
    struct AVLNode {
        int key;     // Unique identifier (e.g., actor/movie ID)
        int item;    // Value for sorting (e.g., year/age)
        T data;      // Pointer to Actor/Movie object
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(int k, int i, T d)
            : key(k), item(i), data(d), left(nullptr), right(nullptr), height(1) {}
    };

    AVLNode* root;

    // Helper functions for AVL operations
    int height(AVLNode* node) const {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) const {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* balance(AVLNode* node) {
        if (!node) return nullptr;

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

    AVLNode* insert(AVLNode* node, int key, int item, T data) {
        if (!node) return new AVLNode(key, item, data);

        if (item < node->item) {
            node->left = insert(node->left, key, item, data);
        }
        else if (item > node->item) {
            node->right = insert(node->right, key, item, data);
        }
        else {
            // Handle equal items using key for uniqueness
            if (key < node->key) {
                node->left = insert(node->left, key, item, data);
            }
            else if (key > node->key) {
                node->right = insert(node->right, key, item, data);
            }
            else {
                return node; // Duplicate key
            }
        }

        return balance(node);
    }

    AVLNode* remove(AVLNode* node, int key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else {
                AVLNode* successor = node->right;
                while (successor->left)
                    successor = successor->left;
                node->key = successor->key;
                node->item = successor->item;
                node->data = successor->data;
                node->right = remove(node->right, successor->key);
            }
        }

        return balance(node);
    }

    template <typename Callback>
    void inOrderRange(AVLNode* node, int low, int high, Callback cb) const {
        if (!node) return;

        if (node->item > low)
            inOrderRange(node->left, low, high, cb);

        if (node->item >= low && node->item <= high)
            cb(node->data);

        if (node->item <= high)
            inOrderRange(node->right, low, high, cb);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key, int item, T data) {
        root = insert(root, key, item, data);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    template <typename Callback>
    void rangeQuery(int low, int high, Callback callback) const {
        inOrderRange(root, low, high, callback);
    }

    // Destructor and other methods needed
};