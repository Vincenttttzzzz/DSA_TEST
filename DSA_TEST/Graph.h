#pragma once

#include <iostream>
#include <memory>
#include "HashTable.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Actor.h"
#include "Movie.h"
#include "vector.h"  // Your vectorClass implementation

using namespace std;

class Graph {
private:
    // Main storage for actors (shared pointers)
    HashTable<std::shared_ptr<Actor>> actorTable;

    HashTable<std::shared_ptr<Movie>> movieTable;

    // Mapping from actor ID to a list (LinkedList) of movies (stored as weak pointers)
    HashTable<LinkedList<std::weak_ptr<Movie>>*> actorToMovie;

public:
    Graph(); 

	std::shared_ptr<Actor> getActor(int id) const;

	std::shared_ptr<Movie> getMovie(int id) const;

	LinkedList<std::weak_ptr<Movie>>* getMovies(int actorId) const;

    bool insertNewActor(int id, shared_ptr<Actor>& actor);

    bool insertNewMovie(int id, shared_ptr<Movie>& movie);

    bool insertActorToMovie(int actorId, int movieId);

    // Insert actor-to-movie relationships:
    // Associates the given movie list with the actor in actorToMovie.
    //void insertActorRelationships(LinkedList<weak_ptr<Movie>>* movieList, const weak_ptr<Actor>& actor);

    // Display known actors for a given source actor.
    // 1. Get the actor’s movie list from actorToMovie.
    // 2. For each movie, get the movie’s vector (vectorClass) of actors.
    // 3. Use BFS (via a Queue) and a visited hash table to avoid duplicates.
    void displayKnownActors(const weak_ptr<Actor>& sourceActor) const;

    // Helper function to print a vectorClass of weak_ptr<Actor>
    void printConnections(const vectorClass<weak_ptr<Actor>>& actorVector) const;
};

struct ActorLevel {
    std::weak_ptr<Actor> actor;
    int level;  // 0 = source, 1 = direct, 2 = indirect
};