#include "HashTable.h"
#include "Actor.h"       // For shared_ptr<Actor>
#include "Movie.h"       // For shared_ptr<Movie>
#include "LinkedList.h"  // For LinkedList
#include "Rating.h"      // For Rating
#include "RatingSystem.h"   

using namespace std;

template struct HashNode<std::shared_ptr<Movie>>;
template struct HashNode<std::shared_ptr<Actor>>;
template struct HashNode<LinkedList<std::weak_ptr<Movie>>*>;
template struct HashTable<EntityRatings*>;

template <typename T>
HashTable<T>::HashTable() {
    items.resize(MAX_SIZE, nullptr);
    size = 0;
}

template <typename T>
HashTable<T>::~HashTable() {
    // Delete all nodes in each chain
    for (int i = 0; i < MAX_SIZE; i++) {
        HashNode<T>* current = items[i];
        while (current != nullptr) {
            HashNode<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

template <typename T>
void HashTable<T>::resize() {
    size_t oldCapacity = items.size();
    // Find next prime number for new size instead of just doubling
    size_t newCapacity = nextPrime(oldCapacity * 2);

    // Reserve space for the new vector before copying
    std::vector<HashNode<T>*> oldItems;
    oldItems.swap(items);  // Efficient swap instead of copy

    items.resize(newCapacity, nullptr);
    size = 0;

    // Batch rehashing for better cache utilization
    for (size_t i = 0; i < oldCapacity; i++) {
        HashNode<T>* current = oldItems[i];
        while (current != nullptr) {
            HashNode<T>* next = current->next;  // Save next pointer before rehashing

            // Inline the add operation instead of calling add()
            int newIndex = hash(current->key);
            current->next = items[newIndex];
            items[newIndex] = current;
            size++;

            current = next;
        }
    }
}

template <typename T>
int HashTable<T>::hash(KeyType key) const {
    // Improved hash function using multiplicative hashing
    const double A = 0.6180339887; // (sqrt(5)-1)/2
    double product = key * A;
    double fractional = product - floor(product);
    return static_cast<int>(items.size() * fractional);
}

// Helper function to find next prime number
template <typename T>
size_t HashTable<T>::nextPrime(size_t n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

// Helper function to check if number is prime
template <typename T>
bool HashTable<T>::isPrime(size_t n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (size_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

template <typename T>
bool HashTable<T>::add(KeyType newKey, T newItem) {
    // Compute load factor: (# elements) / (# buckets)
    float loadFactor = static_cast<float>(size) / items.size();
    if (loadFactor >= 0.7f) {
        resize();
    }

    int index = hash(newKey);

    // Create new node
    HashNode<T>* newNode = new HashNode<T>;
    newNode->key = newKey;
    newNode->item = newItem;
    newNode->next = nullptr;

    // If bucket is empty
    if (items[index] == nullptr) {
        items[index] = newNode;
        size++;
        return true;
    }

    // Check if key already exists
    HashNode<T>* current = items[index];
    while (current != nullptr) {
        if (current->key == newKey) {
            // Key already exists, update value
            current->item = newItem;
            delete newNode;  // Clean up unused node
            return false;
        }
        current = current->next;
    }

    // Add to front of chain (could also add to end if preferred)
    newNode->next = items[index];
    items[index] = newNode;
    size++;
    return true;
}

template <typename T>
T HashTable<T>::get(KeyType key) const {
    int index = hash(key);
    HashNode<T>* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current->item;
        }
        current = current->next;
    }

    // If key not found, throw exception or return default value
    return T{};
}

template <typename T>
bool HashTable<T>::isEmpty() {
    return size == 0;
}

template <typename T>
int HashTable<T>::getLength() {
    return size;
}

template <typename T>
void HashTable<T>::print() {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (items[i] != nullptr) {
            std::cout << "Bucket " << i << ": ";
            HashNode<T>* current = items[i];
            while (current != nullptr) {
                std::cout << "(" << current->key << "," << current->item << ") ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
}
