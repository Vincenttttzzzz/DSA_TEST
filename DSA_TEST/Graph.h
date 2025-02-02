//#pragma once
//
//#include <iostream>
//#include "LinkedList.hx"
//
//using namespace std;
//
//template <typename T>
//class Graph {
//private:
//    LinkedList<T>* adjList;  // Array of LinkedList objects
//    int numVertices;
//    bool isDirected;
//
//public:
//    // Constructor
//    Graph(int vertices, bool directed = false);
//
//    // Destructor
//    ~Graph();
//
//    // Add an edge to the graph
//    void addEdge(int src, const T& dest);
//
//    // Print the adjacency list of the graph
//    void printGraph() const;
//};
//
//
//// Constructor to initialize the graph
//template <typename T>
//Graph<T>::Graph(int vertices, bool directed) {
//    numVertices = vertices;
//    isDirected = directed;
//
//    // Allocate memory for adjacency list array
//    adjList = new LinkedList<T>[numVertices];
//}
//
//// Destructor to free allocated memory
//template <typename T>
//Graph<T>::~Graph() {
//    delete[] adjList;
//}
//
//// Function to add an edge to the graph
//template <typename T>
//void Graph<T>::addEdge(int src, const T& dest) {
//    // Add destination to the source's adjacency list
//    adjList[src].add(dest);
//
//    // If undirected, add source to destination's list
//    if (!isDirected) {
//        adjList[dest].add(src);
//    }
//}
//
//// Function to print the adjacency list of the graph
//template <typename T>
//void Graph<T>::printGraph() const {
//    for (int i = 0; i < numVertices; i++) {
//        cout << i << ": ";
//        adjList[i].print();  // Using the print function from LinkedList
//        cout << "NULL" << endl;
//    }
//}







//#pragma once
//
//#include <iostream>
//#include <memory>
//#include "HashTable.h"
//#include "LinkedList.h"
//#include "Actor.h"
//
//using namespace std;
//
//class Graph {
//private:
//    // Outer hash table: maps actor ID to an inner hash table that acts as a hash set of neighbor actors.
//    // The inner hash table stores std::weak_ptr<Actor>, with both key and item being the neighbor's actor ID and weak pointer.
//    HashTable<HashTable<std::weak_ptr<Actor>>*> adjacencyList;
//    bool isDirected; // Whether the graph is directed
//
//public:
//    // Constructor
//    Graph(bool directed = false);
//
//    // Add an edge between two actors (by their IDs, using weak_ptr for neighbor)
//    void addEdge(int srcID, const std::weak_ptr<Actor>& destActor);
//
//    // Print the adjacency list of the graph
//    void printGraph() const;
//
//    // Display actors that a given actor knows (using actorTable for full details)
//    void displayKnownActors(int actorID, const HashTable<shared_ptr<Actor>>& actorTable) const;
//
//    // Check if the graph is empty
//    bool isEmpty() const;
//
//    // Get the number of vertices in the graph
//    int getVertexCount() const;
//
//    // Insert actor relationships from actor-movie data into the graph.
//    // Here, actorList is a linked list (of integers) of neighbor actor IDs.
//    void insertActorRelationships(const LinkedList<int>* actorList, int actorId);
//};


// Latest Version
#pragma once

#include <iostream>
#include <memory>
#include "HashTable.h"
#include "LinkedList.h"
#include "Actor.h"

using namespace std;

class Graph {
private:
    HashTable<LinkedList<std::weak_ptr<Actor>>*> adjacencyList; // Adjacency list using HashTable
    bool isDirected; // Whether the graph is directed

public:
    // Constructor
    Graph(bool directed = false);

    // Add an edge between two actors
    void addEdge(int srcID, const std::weak_ptr<Actor>& destActor);

    // Print the adjacency list of the graph
    void printGraph() const;

    // Display actors that a given actor knows
    void displayKnownActors(int actorID) const;

    // Check if the graph is empty
    bool isEmpty() const;

    // Get the number of vertices in the graph
    int getVertexCount() const;

    // Insert actor relationships from actor-movie data into the graph
    void insertActorRelationships(LinkedList<std::weak_ptr<Actor>>* actorList, std::weak_ptr<Actor> actor);
};
