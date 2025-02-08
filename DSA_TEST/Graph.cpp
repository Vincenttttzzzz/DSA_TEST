#include "Graph.h"
#include "Actor.h"
#include "Movie.h"
#include "LinkedList.h"
#include "HashTable.h"
#include "HashTable.cpp"
#include "LinkedList.cpp"
#include <iostream>


// Constructor: default constructs the internal hash tables.
Graph::Graph() {
    // actorTable and actorToMovie are default-constructed.
	actorTable = HashTable<std::shared_ptr<Actor>>();
	movieTable = HashTable<std::shared_ptr<Movie>>();
	actorToMovie = HashTable<LinkedList<std::weak_ptr<Movie>>*>();
}

// Get the actor with the given ID.
// Returns a weak pointer to the actor if found, an expired weak pointer otherwise.
std::shared_ptr<Actor> Graph::getActor(int id) const {
	return actorTable.get(id);
}

// Get the movie with the give  n ID.
// Returns a weak pointer to the movie if found, an expired weak pointer otherwise.
std::shared_ptr<Movie> Graph::getMovie(int id) const {
	return movieTable.get(id);
}

// Get the list of movies for the actor with the given ID.
// Returns a pointer to the list of movies if found, nullptr otherwise.
LinkedList<std::weak_ptr<Movie>>* Graph::getMovies(int actorId) const {
	return actorToMovie.get(actorId);
}

// Insert an actor into the graph.
// Insert an actor into the graph.
// Returns true if the actor was successfully inserted, false otherwise.
bool Graph::insertNewActor(int id, std::shared_ptr<Actor>& actor) {

    //cout << " Inserting 1" << endl;
	// Check if the actor is valid
	//if (actorTable.get(id)) {
	//	return false; // Actor already exists, insertion failed
	//}

    // Add the actor to the actorTable
    //cout << "Inserting 2" << endl;
    actorTable.add(id, actor);

    // Add an empty movie list for the actor in actorToMovie
    actorToMovie.add(id, new LinkedList<std::weak_ptr<Movie>>);

    return true; // Insertion successful
}

bool Graph::insertNewMovie(int id, std::shared_ptr<Movie>& movie) {
	// Check if the movie is valid
	//if (movieTable.get(id)) {
	//	return false; // Movie already exists, insertion failed
	//}

    // Add the actor to the actorTable
    movieTable.add(id, movie);

    return true; // Insertion successful
}

bool Graph::insertActorToMovie(int actorId, int movieId) {
    // Get Actor weak pointer
    auto actor = actorTable.get(actorId);
	if (!actor) {
		//cout << "Actor with ID " << actorId << " not found." << endl;
		return false;
	}

    auto movie = movieTable.get(movieId);
	if (!movie) {
		//cout << "Movie with ID " << movieId << " not found." << endl;
		return false;
	}

    // Add the actor to the movie's list of actors
    movie->addActor(actor);

    // Retrieve the list of movies for the actor
    LinkedList<weak_ptr<Movie>>* listOfMovies = actorToMovie.get(actorId);
    listOfMovies->add(movie);

    return true;
}
// Insert actor-to-movie relationship: associate the given movie list with the actor.
// If the actor’s entry is not present in actorToMovie, add it.
//void Graph::insertActorRelationships(LinkedList<weak_ptr<Movie>>* movieList, const weak_ptr<Actor>& actor) {
//    auto lockedActor = actor.lock();
//    if (!lockedActor) {
//        cout << "Actor expired; cannot insert relationships." << endl;
//        return;
//    }
//    int actorID = lockedActor->getActorID();
//    if (!actorToMovie.get(actorID)) {
//        actorToMovie.add(actorID, movieList);
//    }
//    // Optionally, if an entry exists, you might merge or update the movie list.
//}


// Display known actors for the given source actor using BFS over movies.
// The process is as follows:
// 1. Retrieve the actor's movie list from actorToMovie.
// 2. For each movie, get the list of actors (stored as a LinkedList of weak_ptr<Actor>) from the Movie object.
// 3. Use a Queue (BFS) and a HashTable (visited) to avoid duplicates.
//void Graph::displayKnownActors(const weak_ptr<Actor>& sourceActor) const {
//    auto lockedSource = sourceActor.lock();
//    if (!lockedSource) {
//        cout << "Source actor expired." << endl;
//        return;
//    }
//    int sourceID = lockedSource->getActorID();
//
//    // Retrieve the LinkedList of movies for the source actor.
//    LinkedList<weak_ptr<Movie>>* movieList = actorToMovie.get(sourceID);
//    if (!movieList) {
//        cout << "No movie relationships found for actor " << lockedSource->getName() << "." << endl;
//        return;
//    }
//
//    // Queue for BFS (storing weak_ptr<Actor>).
//    Queue<weak_ptr<Actor>> queue;
//    // HashTable to track visited actor IDs to avoid duplicates.
//    HashTable<bool> visited;
//
//    // Mark the source actor as visited.
//    visited.add(sourceID, true);
//
//    // For each movie in which the source actor appeared, enqueue its actors.
//    int numMovies = movieList->getLength();
//    for (int i = 0; i < numMovies; i++) {
//        weak_ptr<Movie> weakMovie = movieList->get(i);
//        auto lockedMovie = weakMovie.lock();
//        if (!lockedMovie)
//            continue;
//
//        // Assume Movie::getListOfActors() returns a LinkedList<weak_ptr<Actor>>&.
//        vectorClass<std::weak_ptr<Actor>> actorList = lockedMovie->getListOfActors();
//        int numActors = actorList.size();
//        for (int j = 0; j < numActors; j++) {
//            weak_ptr<Actor> neighborWeak = actorList.get(j);
//            auto lockedNeighbor = neighborWeak.lock();
//            if (!lockedNeighbor)
//                continue;
//            int neighborID = lockedNeighbor->getActorID();
//            if (neighborID == sourceID)
//                continue; // Skip the source actor.
//            if (!visited.get(neighborID)) {
//                visited.add(neighborID, true);
//                queue.enqueue(neighborWeak);
//            }
//        }
//    }
//
//    // Process the BFS queue and print the actors.
//    cout << "Known actors for " << lockedSource->getName() << ":" << endl;
//    while (!queue.isEmpty()) {
//        weak_ptr<Actor> weakActor;
//        queue.dequeue(weakActor);
//        if (auto lockedActor = weakActor.lock()) {
//            cout << lockedActor->getName() << " (ID: " << lockedActor->getActorID() << ")" << endl;
//        }
//    }
//}





// A helper structure to hold an actor and its level in the BFS.
struct ActorLevel {
    std::weak_ptr<Actor> actor;
    int level;  // 0 = source, 1 = direct, 2 = indirect
};

void Graph::displayKnownActors(const std::weak_ptr<Actor>& sourceActor) const {
    // Lock source actor.
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

    // Create a queue for BFS that stores ActorLevel.
    // (Assume you have a Queue<ActorLevel> implementation.)
    Queue<ActorLevel> queue;

    // Hash table to track visited actor IDs.
    // Here, visited.add(actorID, true) marks an actor as seen.
    HashTable<bool> visited;

    // Mark the source actor as visited at level 0 and enqueue it.
    visited.add(sourceID, true);
    queue.enqueue({ sourceActor, 0 });

    cout << "Known actors for " << lockedSource->getName() << ":" << endl;

    // Process the BFS queue.
    while (!queue.isEmpty()) {
        ActorLevel current;
        if (!queue.dequeue(current))
            break;

        int currentLevel = current.level;
        // Do not expand actors beyond level 2.
        if (currentLevel >= 2)
            continue;

        // Lock the current actor.
        auto lockedCurrent = current.actor.lock();
        if (!lockedCurrent)
            continue;
        int currentID = lockedCurrent->getActorID();

        // Retrieve the movie list for the current actor.
        LinkedList<weak_ptr<Movie>>* currMovieList = actorToMovie.get(currentID);
        if (!currMovieList)
            continue;

        int numMovies = currMovieList->getLength();
        for (int i = 0; i < numMovies; i++) {
            weak_ptr<Movie> weakMovie = currMovieList->get(i);
            auto lockedMovie = weakMovie.lock();
            if (!lockedMovie)
                continue;

            // Assume Movie::getListOfActors() returns a vectorClass<weak_ptr<Actor>>.
            vectorClass<weak_ptr<Actor>> actorVector = lockedMovie->getListOfActors();
            int numActors = actorVector.size();
            for (int j = 0; j < numActors; j++) {
                weak_ptr<Actor> neighborWeak = actorVector.get(j);
                auto neighbor = neighborWeak.lock();
                if (!neighbor)
                    continue;
                int neighborID = neighbor->getActorID();
                if (neighborID == sourceID)
                    continue; // Skip the source actor.

                // If the neighbor hasn't been visited, mark and enqueue.
                if (!visited.get(neighborID)) {
                    visited.add(neighborID, true);
                    int newLevel = currentLevel + 1;
                    queue.enqueue({ neighborWeak, newLevel });
                    // Print the neighbor immediately (if level 1 or 2)
                    cout << neighbor->getName() << " (ID: " << neighborID << ")" << endl;
                }
            }
        }
    }
}


// Helper function: print connections stored in a vectorClass of weak_ptr<Actor>.
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

// Display known actors for the given source actor using BFS over movies.
// The process is as follows:
// 1. Get the movie list for the actor from actorToMovie.
// 2. For each movie, get the vector (vectorClass) of actors stored in the Movie object.
// 3. Use a Queue to perform BFS, using a HashTable to track visited actor IDs.

//void Graph::displayKnownActors(const weak_ptr<Actor>& sourceActor) const {
//    auto lockedSource = sourceActor.lock();
//    if (!lockedSource) {
//        cout << "Source actor expired." << endl;
//        return;
//    }
//    int sourceID = lockedSource->getActorID();
//
//    // Retrieve the list of movies for the source actor.
//    LinkedList<weak_ptr<Movie>>* movieList = actorToMovie.get(sourceID);
//    if (!movieList) {
//        cout << "No movie relationships found for actor " << lockedSource->getName() << "." << endl;
//        return;
//    }
//
//    // Queue for BFS (storing weak_ptr<Actor>)
//    Queue<weak_ptr<Actor>> queue;
//    // HashTable to track visited actor IDs (avoid duplicates)
//    HashTable<bool> visited;
//
//    // Mark the source actor as visited
//    visited.add(sourceID, true);
//
//    // Enqueue all actors from the movies in which the source actor appeared
//    int numMovies = movieList->getLength();
//    for (int i = 0; i < numMovies; i++) {
//        weak_ptr<Movie> weakMovie = movieList->get(i);
//        auto lockedMovie = weakMovie.lock();
//        if (!lockedMovie) continue;
//
//        // Assume Movie::getListOfActors() now returns a vectorClass<weak_ptr<Actor>>& 
//        // (since you modified Movie to use a vector for actors)
//        vectorClass<weak_ptr<Actor>>& actorVector = lockedMovie->getListOfActors();
//        int numActors = actorVector.size();
//        for (int j = 0; j < numActors; j++) {
//            weak_ptr<Actor> neighborWeak = actorVector.get(j);
//            auto lockedNeighbor = neighborWeak.lock();
//            if (!lockedNeighbor) continue;
//            int neighborID = lockedNeighbor->getActorID();
//            if (neighborID == sourceID) continue; // Skip self
//
//            if (!visited.get(neighborID)) {
//                visited.add(neighborID, true);
//                queue.enqueue(neighborWeak);
//            }
//        }
//    }
//
//    // Now, process the BFS queue and print the actors
//    cout << "Known actors for " << lockedSource->getName() << ":" << endl;
//    while (!queue.isEmpty()) {
//        weak_ptr<Actor> weakActor;
//        queue.dequeue(weakActor);
//        auto lockedActor = weakActor.lock();
//        if (lockedActor) {
//            cout << lockedActor->getName() << " (ID: " << lockedActor->getActorID() << ")" << endl;
//        }
//    }
//}
//
//// Helper: print connections stored in a vectorClass of weak_ptr<Actor>
//void Graph::printConnections(const vectorClass<weak_ptr<Actor>>& actorVector) const {
//    int n = actorVector.size();
//    for (int i = 0; i < n; i++) {
//        weak_ptr<Actor> weakActor = actorVector.get(i);
//        if (auto lockedActor = weakActor.lock()) {
//            cout << lockedActor->getName() << " (ID: " << lockedActor->getActorID() << ") ";
//        }
//    }
//    cout << endl;
//}
