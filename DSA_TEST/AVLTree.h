#pragma once
#include <iostream>
#include <functional>
#include <memory>

// Forward declaration for Movie (if needed)
class Movie;

template <typename T>
class AVLTree {
private:
    // Nested AVLNode structure
    struct AVLNode {
        int key;      // Unique identifier (e.g., actor/movie ID)
        int item;     // Value for sorting (e.g., year/age)
        T data;       // Pointer to Actor/Movie object (or object itself)
        AVLNode* left;
        AVLNode* right;
        int height;

        AVLNode(int k, int i, T d);
    };

    AVLNode* root;

    // Helper function declarations
    int height(AVLNode* node) const;
    int balanceFactor(AVLNode* node) const;
    void updateHeight(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* balance(AVLNode* node);

    // We rename the inner template parameter for insertion to U to avoid hiding the class template parameter.
    template <typename U>
    AVLNode* insertNode(AVLNode* node, int key, int item, U data);

    AVLNode* removeNode(AVLNode* node, int key);
    void destroyTree(AVLNode* node);

    template <typename Callback>
    void inOrderRange(AVLNode* node, int low, int high, Callback cb) const;

public:
    AVLTree();
    ~AVLTree();

    // Public insertion: note the inner template parameter is now U.
    template <typename U>
    void insert(int key, int item, U data);

    void remove(int key);

    // Range query: call a callback for each data in the given range.
    template <typename Callback>
    void rangeQuery(int low, int high, Callback callback) const;
};

// Include the implementation file. (An alternative is to put the definitions here.)
#include "AVLTree.cpp"

