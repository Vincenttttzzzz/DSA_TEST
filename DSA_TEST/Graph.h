#pragma once
#include <iostream>
#include <memory>
#include "HashTable.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Actor.h"
#include "Movie.h"

using namespace std;

class Graph {
private:
    // Main storage for actor-to-movie relationships.
    // Maps actor ID to a linked list of weak_ptr<Movie> that the actor starred in.
    HashTable<LinkedList<std::weak_ptr<Movie>>*> actorToMovie;

public:
    Graph();

    // Add an edge: here, insert the actor's movie list into actorToMovie.
    // If the actor's ID is not already in the table, add it.
    void insertActorRelationships(LinkedList<std::weak_ptr<Movie>>* movieList, const std::weak_ptr<Actor>& actor);

    // Display known actors:
    // 1. Use actorToMovie to get the list of movies for the source actor.
    // 2. For each movie, retrieve the vector of actors (stored in Movie).
    // 3. Use a Queue to perform BFS over these relationships while checking for duplicates.
    void displayKnownActors(const std::weak_ptr<Actor>& sourceActor) const;

    // Helper: Print connections from a vectorClass of weak_ptr<Actor>
    void printConnections(const vectorClass<std::weak_ptr<Actor>>& actorVector) const;
};
