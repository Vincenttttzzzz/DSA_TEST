#include "Graph.h"

// Constructor
Graph::Graph(bool directed) : isDirected(directed) {
}

// Add an edge between two actors
//
void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
    std::shared_ptr<Actor> lockedDest = destActor.lock(); // Declare before if statement

    std::cout << "DEBUG: Adding edge from Actor " << srcID << " to ";
    if (lockedDest) {
        std::cout << lockedDest->getActorID() << std::endl;
    }
    else {
        std::cout << "NULL (weak_ptr expired)" << std::endl;
        return;
    }

    // Ensure srcID exists in the adjacency list
    if (adjacencyList.get(srcID) == nullptr) {
        std::cout << "DEBUG: No existing list for " << srcID << ", creating new linked list.\n";
        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
    }

    // Retrieve linked list for srcID
    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
    if (!neighbors) {
        std::cerr << "ERROR: Could not retrieve adjacency list for Actor " << srcID << std::endl;
        return;
    }

    // Check if destActor already exists
    bool exists = false;
    for (int i = 0; i < neighbors->getLength(); ++i) {
        if (auto existing = neighbors->get(i).lock()) {
            if (existing->getActorID() == lockedDest->getActorID()) {
                exists = true;
                break;
            }
        }
    }

    if (!exists) {
        std::cout << "DEBUG: Inserting Actor " << lockedDest->getActorID() << " into adjacency list of " << srcID << std::endl;
        neighbors->add(destActor);
    }
    else {
        std::cout << "DEBUG: Actor " << lockedDest->getActorID() << " already exists in adjacency list of " << srcID << std::endl;
    }
}



// Add an edge between two actors
//void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
//    std::cout << "Adding edge from Actor " << srcID << " to Actor " << (destActor.lock() ? destActor.lock()->getActorID() : -1) << std::endl;
//    // Ensure srcID exists in the adjacency list
//    if (adjacencyList.get(srcID) == nullptr) {
//        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
//    }
//
//    // Get the linked list for srcID
//    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
//
//    // Add destActor to the adjacency list
//    if (neighbors) {
//        neighbors->add(destActor);
//        std::cout << "Added Actor " << (destActor.lock() ? destActor.lock()->getActorID() : -1) << " to adjacency list of Actor " << srcID << std::endl;
//    }
//
//    // If the graph is undirected, add the reverse edge
//    if (isDirected) {
//        if (auto strongDestActor = destActor.lock()) {
//            int destID = strongDestActor->getActorID();
//            if (adjacencyList.get(destID) == nullptr) {
//                adjacencyList.add(destID, new LinkedList<std::weak_ptr<Actor>>());
//            }
//            LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(destID);
//            if (reverseNeighbors) {
//                reverseNeighbors->add(std::weak_ptr<Actor>(strongDestActor));
//                std::cout << "Added reverse edge from Actor " << destID << " back to Actor " << srcID << std::endl;
//            }
//        }
//    }
//}

//void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
//    // Ensure srcID exists in the adjacency list
//    if (adjacencyList.get(srcID) == nullptr) {
//        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
//    }
//
//    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
//    if (neighbors) neighbors->add(destActor);
//
//    // Handle undirected graph with proper weak_ptr locking
//    if (!isDirected) {
//        if (auto strongDestActor = destActor.lock()) {
//            int destID = strongDestActor->getActorID();
//            if (adjacencyList.get(destID) == nullptr) {
//                adjacencyList.add(destID, new LinkedList<std::weak_ptr<Actor>>());
//            }
//            LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(destID);
//            if (reverseNeighbors) reverseNeighbors->add(std::weak_ptr<Actor>(destActor));
//        }
//    }
//}
//

//void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
//    if (adjacencyList.get(srcID) == nullptr) {
//        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
//    }
//
//    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
//    if (neighbors) neighbors->add(destActor);
//
//    if (!isDirected) {
//        auto strongDestActor = destActor.lock();
//        if (strongDestActor) {
//            int destID = strongDestActor->getActorID();
//            if (adjacencyList.get(destID) == nullptr) {
//                adjacencyList.add(destID, new LinkedList<std::weak_ptr<Actor>>());
//            }
//
//            LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(destID);
//            if (reverseNeighbors) reverseNeighbors->add(std::weak_ptr<Actor>(strongDestActor));
//        }
//    }
//}

// Add an edge between two actors
//void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
//    // Ensure srcID exists in the adjacency list
//    if (adjacencyList.get(srcID) == nullptr) {
//        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
//    }
//
//    // Get the linked list for srcID
//    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
//
//    // Add destActor to the adjacency list
//    if (neighbors) neighbors->add(destActor);
//
//    // If the graph is undirected, add the reverse edge
//    if (!isDirected) {
//        if (auto strongDestActor = destActor.lock()) {
//            if (adjacencyList.get(strongDestActor->getActorID()) == nullptr) {
//                adjacencyList.add(strongDestActor->getActorID(), new LinkedList<std::weak_ptr<Actor>>());
//            }
//
//            LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(strongDestActor->getActorID());
//            if (reverseNeighbors) reverseNeighbors->add(destActor);
//        }
//
//        LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(destActor->getActorID());
//        if (reverseNeighbors) reverseNeighbors->add(destActor);
//    }
//}





// Print the adjacency list of the graph
//void Graph::printGraph() const {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(i);
//        if (neighbors == nullptr) continue;
//
//        std::cout << "Actor " << i << " knows: ";
//
//        for (const auto& actorWeakPtr : neighbors->toVector()) {
//            if (auto actorPtr = actorWeakPtr.lock()) {
//                std::cout << actorPtr->getName() << " (ID: " << actorPtr->getActorID() << ") ";
//            }
//        }
//
//        std::cout << std::endl;
//    }
//}

void Graph::printGraph() const {
    for (int i = 0; i < MAX_SIZE; i++) {
        LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(i);
        if (neighbors == nullptr) continue;

        std::cout << "Actor " << i << " knows: ";

        for (LinkedListNode<std::weak_ptr<Actor>>* node = neighbors->getFirstNode(); node != nullptr; node = node->next) {
            if (auto actorPtr = node->item.lock()) {
                std::cout << actorPtr->getName() << " (ID: " << actorPtr->getActorID() << ") ";
            }
        }

        std::cout << std::endl;
    }
}


// Display actors that a given actor knows (direct and indirect up to 2 levels)
//void Graph::displayKnownActors(int actorID) const {
//    LinkedList<std::weak_ptr<Actor>>* firstLevel = adjacencyList.get(actorID);
//
//    if (firstLevel == nullptr) {
//        std::cout << "Actor with ID " << actorID << " not found or has no connections." << std::endl;
//        return;
//    }
//
//    std::cout << "Directly knows: ";
//    for (const auto& actorWeakPtr : firstLevel->toVector()) {
//        if (auto actorPtr = actorWeakPtr.lock()) {
//            std::cout << actorPtr->getName() << " (ID: " << actorPtr->getActorID() << ") ";
//        }
//    }
//
//    std::cout << "\nIndirectly knows: ";
//    for (const auto& actorWeakPtr : firstLevel->toVector()) {
//        if (auto actorPtr = actorWeakPtr.lock()) {
//            LinkedList<std::weak_ptr<Actor>>* secondLevel = adjacencyList.get(actorPtr->getActorID());
//            if (secondLevel == nullptr) continue;
//
//            for (const auto& indirectActorWeakPtr : secondLevel->toVector()) {
//                if (auto indirectActorPtr = indirectActorWeakPtr.lock()) {
//                    if (indirectActorPtr->getActorID() != actorID) {
//                        std::cout << indirectActorPtr->getName() << " (ID: " << indirectActorPtr->getActorID() << ") ";
//                    }
//                }
//            }
//        }
//    }
//
//    std::cout << std::endl;
//}

void Graph::displayKnownActors(int actorID) const {
    LinkedList<std::weak_ptr<Actor>>* firstLevel = adjacencyList.get(actorID);

    if (firstLevel == nullptr) {
        std::cout << "Actor with ID " << actorID << " not found or has no connections." << std::endl;
        return;
    }

    std::cout << "Directly knows: ";
    for (LinkedListNode<std::weak_ptr<Actor>>* node = firstLevel->getFirstNode(); node != nullptr; node = node->next) {
        if (auto actorPtr = node->item.lock()) {
            std::cout << actorPtr->getName() << " (ID: " << actorPtr->getActorID() << ") ";
        }
    }

    std::cout << "\nIndirectly knows: ";
    for (LinkedListNode<std::weak_ptr<Actor>>* node = firstLevel->getFirstNode(); node != nullptr; node = node->next) {
        if (auto actorPtr = node->item.lock()) {
            LinkedList<std::weak_ptr<Actor>>* secondLevel = adjacencyList.get(actorPtr->getActorID());
            if (secondLevel == nullptr) continue;

            for (LinkedListNode<std::weak_ptr<Actor>>* secondNode = secondLevel->getFirstNode(); secondNode != nullptr; secondNode = secondNode->next) {
                if (auto indirectActorPtr = secondNode->item.lock()) {
                    if (indirectActorPtr->getActorID() != actorID) {
                        std::cout << indirectActorPtr->getName() << " (ID: " << indirectActorPtr->getActorID() << ") ";
                    }
                }
            }
        }
    }

    std::cout << std::endl;
}


// Check if the graph is empty
bool Graph::isEmpty() const {
    return const_cast<HashTable<LinkedList<std::weak_ptr<Actor>>*>&>(adjacencyList).getLength() == 0;
}

// Get the number of vertices in the graph
int Graph::getVertexCount() const {
    return const_cast<HashTable<LinkedList<std::weak_ptr<Actor>>*>&>(adjacencyList).getLength(); // Ensure method compatibility with non-const context
}
// Insert actor relationships from actor-movie data into the graph
// 
void Graph::insertActorRelationships(LinkedList<std::weak_ptr<Actor>>* actorList, int actorId) {
    std::cout << "DEBUG: insertActorRelationships() called for Actor " << actorId << std::endl;

    if (!actorList) {
        std::cerr << "ERROR: Invalid actor list reference!" << std::endl;
        return;
    }

    // Print out the actors in actorList
    std::cout << "DEBUG: Actor list contains " << actorList->getLength() << " elements.\n";

    // Add edges between the actor and all other actors in the list
    for (LinkedListNode<std::weak_ptr<Actor>>* node = actorList->getFirstNode();
        node != nullptr;
        node = node->next) {

        std::cout << "DEBUG: Node at " << node << ", item (weak_ptr) exists: "
            << (node->item.expired() ? "NO" : "YES") << std::endl;

        if (auto coActor = node->item.lock()) {  // Convert weak_ptr to shared_ptr
            std::cout << "DEBUG: Actor ID in list: " << coActor->getActorID() << std::endl;
            if (coActor->getActorID() != actorId) {
                std::cout << "DEBUG: Connecting " << actorId << " with " << coActor->getActorID() << std::endl;
                addEdge(actorId, coActor);
            }
        }
        else {
            std::cout << "WARNING: Skipping expired weak_ptr\n";
        }
    }

}

// // Insert actor relationships from actor-movie data into the graph
//void Graph::insertActorRelationships(LinkedList<std::weak_ptr<Actor>>* actorList, int actorId) {
//    std::cout << "insert actor" << endl;
//    if (!actorList) {
//        std::cerr << "Invalid actor list reference!" << std::endl;
//        return;
//    }
//
//    // Add edges between the actor and all other actors in the list
//    for (LinkedListNode<std::weak_ptr<Actor>>* node = actorList->getFirstNode(); node != nullptr; node = node->next) {
//        if (auto coActor = node->item.lock()) {
//            if (coActor->getActorID() != actorId) {
//                std::cout << "Adding edge between Actor " << actorId << " and Actor " << coActor->getActorID() << std::endl;
//                addEdge(actorId, coActor);
//            }
//        }
//    }
//}
//void Graph::insertActorRelationships(const LinkedList<std::weak_ptr<Actor>>* actorList, int actorId) {
//    if (!actorList) {
//        std::cerr << "Invalid actor list reference!" << std::endl;
//        return;
//    }
//
//    // Add edges between the actor and all other actors in the list
//    for (LinkedListNode<std::weak_ptr<Actor>>* node = actorList->getFirstNode(); node != nullptr; node = node->next) {
//        if (auto coActor = node->item.lock()) {
//            if (coActor->getActorID() != actorId) {
//                std::cout << actorId << " " << coActor->getActorID() << endl;
//                addEdge(actorId, coActor);
//            }
//        }
//    }
//}
