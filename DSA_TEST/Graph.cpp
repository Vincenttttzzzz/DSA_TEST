#include "Graph.h"
#include "Actor.h"
#include "Movie.h"

// Constructor: default constructs the internal hash tables.
Graph::Graph() {
    // actorTable and actorToMovie are default-constructed.
}

// Insert actor-to-movie relationship: associate the given movie list with the actor.
// If the actor’s entry is not present in actorToMovie, add it.
void Graph::insertActorRelationships(LinkedList<weak_ptr<Movie>>* movieList, const weak_ptr<Actor>& actor) {
    auto lockedActor = actor.lock();
    if (!lockedActor) {
        cout << "Actor expired; cannot insert relationships." << endl;
        return;
    }
    int actorID = lockedActor->getActorID();
    if (!actorToMovie.get(actorID)) {
        actorToMovie.add(actorID, movieList);
    }
    // Optionally, if an entry exists, you might merge or update the movie list.
}

// Display known actors for the given source actor using BFS over movies.
// The process is as follows:
// 1. Get the movie list for the actor from actorToMovie.
// 2. For each movie, get the vector (vectorClass) of actors stored in the Movie object.
// 3. Use a Queue to perform BFS, using a HashTable to track visited actor IDs.
void Graph::displayKnownActors(const weak_ptr<Actor>& sourceActor) const {
    auto lockedSource = sourceActor.lock();
    if (!lockedSource) {
        cout << "Source actor expired." << endl;
        return;
    }
    int sourceID = lockedSource->getActorID();

    // Retrieve the list of movies for the source actor.
    LinkedList<weak_ptr<Movie>>* movieList = actorToMovie.get(sourceID);
    if (!movieList) {
        cout << "No movie relationships found for actor " << lockedSource->getName() << "." << endl;
        return;
    }

    // Queue for BFS (storing weak_ptr<Actor>)
    Queue<weak_ptr<Actor>> queue;
    // HashTable to track visited actor IDs (avoid duplicates)
    HashTable<bool> visited;

    // Mark the source actor as visited
    visited.add(sourceID, true);

    // Enqueue all actors from the movies in which the source actor appeared
    int numMovies = movieList->getLength();
    for (int i = 0; i < numMovies; i++) {
        weak_ptr<Movie> weakMovie = movieList->get(i);
        auto lockedMovie = weakMovie.lock();
        if (!lockedMovie) continue;

        // Assume Movie::getListOfActors() now returns a vectorClass<weak_ptr<Actor>>& 
        // (since you modified Movie to use a vector for actors)
        vectorClass<weak_ptr<Actor>>& actorVector = lockedMovie->getListOfActors();
        int numActors = actorVector.size();
        for (int j = 0; j < numActors; j++) {
            weak_ptr<Actor> neighborWeak = actorVector.get(j);
            auto lockedNeighbor = neighborWeak.lock();
            if (!lockedNeighbor) continue;
            int neighborID = lockedNeighbor->getActorID();
            if (neighborID == sourceID) continue; // Skip self

            if (!visited.get(neighborID)) {
                visited.add(neighborID, true);
                queue.enqueue(neighborWeak);
            }
        }
    }

    // Now, process the BFS queue and print the actors
    cout << "Known actors for " << lockedSource->getName() << ":" << endl;
    while (!queue.isEmpty()) {
        weak_ptr<Actor> weakActor;
        queue.dequeue(weakActor);
        auto lockedActor = weakActor.lock();
        if (lockedActor) {
            cout << lockedActor->getName() << " (ID: " << lockedActor->getActorID() << ")" << endl;
        }
    }
}

// Helper: print connections stored in a vectorClass of weak_ptr<Actor>
void Graph::printConnections(const vectorClass<weak_ptr<Actor>>& actorVector) const {
    int n = actorVector.size();
    for (int i = 0; i < n; i++) {
        weak_ptr<Actor> weakActor = actorVector.get(i);
        if (auto lockedActor = weakActor.lock()) {
            cout << lockedActor->getName() << " (ID: " << lockedActor->getActorID() << ") ";
        }
    }
    cout << endl;
}
