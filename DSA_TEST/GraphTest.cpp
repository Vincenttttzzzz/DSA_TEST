//#include "Graph.h"
//
//// Constructor
//Graph::Graph(bool directed) : isDirected(directed) {
//    // The outer hash table (adjacencyList) is automatically initialized.
//}
//
//// Add an edge between two actors.
//// This function uses the inner hash table to store neighbors as weak pointers.
//void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
//    // Convert destActor to a shared_ptr so we can retrieve its ID.
//    std::shared_ptr<Actor> lockedDest = destActor.lock();
//    std::cout << "DEBUG: Adding edge from Actor " << srcID << " to ";
//    if (lockedDest) {
//        std::cout << lockedDest->getActorID() << std::endl;
//    }
//    else {
//        std::cout << "NULL (weak_ptr expired)" << std::endl;
//        return;
//    }
//    int destID = lockedDest->getActorID();
//
//    // Retrieve (or create) the inner hash table for srcID.
//    HashTable<std::weak_ptr<Actor>>* inner = adjacencyList.get(srcID);
//    if (inner == nullptr) {
//        std::cout << "DEBUG: No existing neighbor set for Actor " << srcID << ", creating new set." << std::endl;
//        inner = new HashTable<std::weak_ptr<Actor>>();
//        adjacencyList.add(srcID, inner);
//    }
//
//    // Check if destID already exists in the inner hash table.
//    // Here, inner->search(destID) should return -1 if destID is not found.
//    if (inner->search(destID) == -1) {
//        std::cout << "DEBUG: Inserting Actor " << destID << " into adjacency list of " << srcID << std::endl;
//        inner->add(destID, destActor);
//    }
//    else {
//        std::cout << "DEBUG: Edge from Actor " << srcID << " to Actor " << destID << " already exists." << std::endl;
//    }
//
//    // For undirected graphs, add the reverse edge.
//    if (!isDirected) {
//        HashTable<std::weak_ptr<Actor>>* reverse = adjacencyList.get(destID);
//        if (reverse == nullptr) {
//            reverse = new HashTable<std::weak_ptr<Actor>>();
//            adjacencyList.add(destID, reverse);
//        }
//        if (reverse->search(srcID) == -1) {
//            std::cout << "DEBUG: Inserting reverse edge from Actor " << destID << " to Actor " << srcID << std::endl;
//            // For reverse edge, we need a weak pointer for the source actor.
//            // However, if the source actor is not directly passed, we assume that the caller manages it.
//            // Here, for simplicity, we create a weak_ptr from a temporary shared_ptr retrieved from actorTable (if available).
//            // (Alternatively, you could pass the source actor's weak_ptr to addEdge.)
//            // For now, we'll simply call addEdge recursively with the same destActor (if graph is undirected).
//            // A more robust solution would require passing source actor's weak_ptr.
//            // We'll assume that when undirected, both directions are handled in the same call.
//            reverse->add(srcID, destActor); // Note: This is not ideal since destActor isn't the source.
//        }
//    }
//}
//
//// Print the adjacency list of the graph.
//void Graph::printGraph() const {
//    // Iterate over the outer hash table's buckets.
//    for (int i = 0; i < MAX_SIZE; i++) {
//        Node<HashTable<std::weak_ptr<Actor>>*>* node = adjacencyList.items[i]; // Access items array (assuming it's public or accessible).
//        while (node != nullptr) {
//            int actorID = node->key;
//            std::cout << "Actor " << actorID << " knows: ";
//            HashTable<std::weak_ptr<Actor>>* inner = node->item;
//            // Iterate over the inner hash table's buckets.
//            for (int j = 0; j < MAX_SIZE; j++) {
//                Node<std::weak_ptr<Actor>>* innerNode = inner->items[j];
//                while (innerNode != nullptr) {
//                    if (auto neighbor = innerNode->item.lock()) {
//                        std::cout << neighbor->getActorID() << " ";
//                    }
//                    innerNode = innerNode->next;
//                }
//            }
//            std::cout << std::endl;
//            node = node->next;
//        }
//    }
//}
//
//// Display actors that a given actor knows, retrieving full details from actorTable.
//void Graph::displayKnownActors(int actorID, const HashTable<shared_ptr<Actor>>& actorTable) const {
//    HashTable<std::weak_ptr<Actor>>* inner = adjacencyList.get(actorID);
//    if (!inner) {
//        std::cout << "Actor with ID " << actorID << " not found or has no connections." << std::endl;
//        return;
//    }
//
//    std::cout << "Directly knows: ";
//    // Iterate over inner hash table's buckets.
//    for (int i = 0; i < MAX_SIZE; i++) {
//        Node<std::weak_ptr<Actor>>* node = inner->items[i];
//        while (node != nullptr) {
//            if (auto neighbor = node->item.lock()) {
//                int neighborID = neighbor->getActorID();
//                shared_ptr<Actor> actorPtr = actorTable.get(neighborID);
//                if (actorPtr) {
//                    std::cout << actorPtr->getName() << " (ID: " << neighborID << ") ";
//                }
//            }
//            node = node->next;
//        }
//    }
//    std::cout << std::endl;
//}
//
//// Check if the graph is empty.
//bool Graph::isEmpty() const {
//    return getVertexCount() == 0;
//}
//
//// Get the number of vertices in the graph.
//int Graph::getVertexCount() const {
//    return adjacencyList.getLength();
//}
//
//// Insert actor relationships from actor-movie data into the graph.
//// Here, actorList is a LinkedList<int>* containing neighbor actor IDs.
//void Graph::insertActorRelationships(const LinkedList<int>* actorList, int actorId) {
//    if (!actorList) {
//        std::cerr << "ERROR: Invalid actor list reference!" << std::endl;
//        return;
//    }
//    std::cout << "DEBUG: Inserting actor relationships for Actor " << actorId << std::endl;
//    // Iterate over the linked list of neighbor actor IDs.
//    for (LinkedListNode<int>* node = actorList->getFirstNode(); node != nullptr; node = node->next) {
//        int neighborID = node->item;
//        if (neighborID != actorId) {
//            std::cout << "DEBUG: Adding edge from Actor " << actorId << " to Actor " << neighborID << std::endl;
//            addEdge(actorId, neighborID);  // We'll need an overloaded version of addEdge that takes two ints.
//        }
//    }
//}
//
//// Overloaded version of addEdge that takes two ints (used by insertActorRelationships)
//void Graph::addEdge(int srcID, int destID) {
//    // We need to create a weak_ptr for destID.
//    // Since we don't have a direct pointer here, we assume that the graph's design uses actorTable elsewhere.
//    // For now, we create a dummy weak_ptr.
//    // In practice, you should look up the shared_ptr for destID and then convert to weak_ptr.
//    // Here, we simply construct a weak_ptr from a shared_ptr constructed from destID,
//    // which is not ideal; proper implementation requires access to actorTable.
//    std::shared_ptr<Actor> dummyActor = std::make_shared<Actor>(destID, "Dummy", 0);
//    std::weak_ptr<Actor> weakDest = dummyActor;
//    addEdge(srcID, weakDest);
//}





// Latest ver
#include "Graph.h"

// Constructor
Graph::Graph(bool directed) : isDirected(directed) {
}

// Add an edge between two actors
//
void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
    std::shared_ptr<Actor> lockedDest = destActor.lock(); // Declare before if statement

    //std::cout << "DEBUG: Adding edge from Actor " << srcID << " to ";
    if (lockedDest) {   
        //std::cout << lockedDest->getActorID() << std::endl;
    }
    else {
        std::cout << "NULL (weak_ptr expired)" << std::endl;
        return;
    }

    // Ensure srcID exists in the adjacency list
    if (adjacencyList.get(srcID) == nullptr) {
        //std::cout << "DEBUG: No existing list for " << srcID << ", creating new linked list.\n";
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
        //std::cout << "DEBUG: Inserting Actor " << lockedDest->getActorID() << " into adjacency list of " << srcID << std::endl;
        neighbors->add(destActor);
    }
    else {
        //std::cout << "DEBUG: Actor " << lockedDest->getActorID() << " already exists in adjacency list of " << srcID << std::endl;
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

    if (!firstLevel) {
        std::cout << "Actor with ID " << actorID << " not found or has no connections.\n";
        return;
    }

    // Track direct and indirect actors using HashTable for O(1) checks
    HashTable<bool> directHash;   // Key: actorID, Value: unused (just needs existence)
    HashTable<bool> indirectHash; // Key: actorID, Value: unused

    // Direct connections (guaranteed unique)
    std::cout << "Directly knows: ";
    for (auto node = firstLevel->getFirstNode(); node != nullptr; node = node->next) {
        if (auto actor = node->item.lock()) {
            int id = actor->getActorID();
            directHash.add(id, true); // Mark as direct connection
            std::cout << actor->getName() << " (ID: " << id << ") ";
        }
    }

    // Indirect connections (friends-of-friends)
    std::cout << "\nIndirectly knows: ";
    for (auto node = firstLevel->getFirstNode(); node != nullptr; node = node->next) {
        if (auto directActor = node->item.lock()) {
            LinkedList<std::weak_ptr<Actor>>* secondLevel = adjacencyList.get(directActor->getActorID());
            if (!secondLevel) continue;

            for (auto secondNode = secondLevel->getFirstNode(); secondNode != nullptr; secondNode = secondNode->next) {
                if (auto indirectActor = secondNode->item.lock()) {
                    int indirectID = indirectActor->getActorID();

                    // Skip if self, direct, or already added
                    if (indirectID == actorID || directHash.get(indirectID) || indirectHash.get(indirectID)) {
                        continue;
                    }

                    // Mark as indirect and print
                    indirectHash.add(indirectID, true);
                    std::cout << indirectActor->getName() << " (ID: " << indirectID << ") ";
                }
            }
        }
    }

    std::cout << std::endl;
}


//void Graph::displayKnownActors(int actorID) const {
//    LinkedList<std::weak_ptr<Actor>>* firstLevel = adjacencyList.get(actorID);
//
//    if (firstLevel == nullptr) {
//        std::cout << "Actor with ID " << actorID << " not found or has no connections." << std::endl;
//        return;
//    }
//
//    // Track direct and indirect actors to avoid duplicates
//    std::unordered_set<int> directActors;
//    std::unordered_set<int> indirectActors;
//
//    // Collect direct connections
//    std::cout << "Directly knows: ";
//    for (LinkedListNode<std::weak_ptr<Actor>>* node = firstLevel->getFirstNode(); node != nullptr; node = node->next) {
//        if (auto actorPtr = node->item.lock()) {
//            int id = actorPtr->getActorID();
//            directActors.insert(id);
//            std::cout << actorPtr->getName() << " (ID: " << id << ") ";
//        }
//    }
//
//    // Collect indirect connections (friends-of-friends)
//    for (LinkedListNode<std::weak_ptr<Actor>>* node = firstLevel->getFirstNode(); node != nullptr; node = node->next) {
//        if (auto directActor = node->item.lock()) {
//            LinkedList<std::weak_ptr<Actor>>* secondLevel = adjacencyList.get(directActor->getActorID());
//            if (!secondLevel) continue;
//
//            for (LinkedListNode<std::weak_ptr<Actor>>* secondNode = secondLevel->getFirstNode(); secondNode != nullptr; secondNode = secondNode->next) {
//                if (auto indirectActor = secondNode->item.lock()) {
//                    int indirectID = indirectActor->getActorID();
//                    // Exclude self and direct connections
//                    if (indirectID != actorID && !directActors.count(indirectID)) {
//                        indirectActors.insert(indirectID);
//                    }
//                }
//            }
//        }
//    }
//
//    // Print indirect connections
//    std::cout << "\nIndirectly knows: ";
//    for (int id : indirectActors) {
//        if (auto actorPtr = adjacencyList.get(id)->getFirstNode()->item.lock()) { // Simplified for brevity
//            std::cout << actorPtr->getName() << " (ID: " << id << ") ";
//        }
//    }
//
//    std::cout << std::endl;
//}

//void Graph::displayKnownActors(int actorID) const {
//    LinkedList<std::weak_ptr<Actor>>* firstLevel = adjacencyList.get(actorID);
//
//    if (firstLevel == nullptr) {
//        std::cout << "Actor with ID " << actorID << " not found or has no connections." << std::endl;
//        return;
//    }
//
//    std::cout << "Directly knows: ";
//    for (LinkedListNode<std::weak_ptr<Actor>>* node = firstLevel->getFirstNode(); node != nullptr; node = node->next) {
//        if (auto actorPtr = node->item.lock()) {
//            std::cout << actorPtr->getName() << " (ID: " << actorPtr->getActorID() << ") ";
//        }
//    }
//
//    std::cout << "\nIndirectly knows: ";
//    for (LinkedListNode<std::weak_ptr<Actor>>* node = firstLevel->getFirstNode(); node != nullptr; node = node->next) {
//        if (auto actorPtr = node->item.lock()) {
//            LinkedList<std::weak_ptr<Actor>>* secondLevel = adjacencyList.get(actorPtr->getActorID());
//            if (secondLevel == nullptr) continue;
//
//            for (LinkedListNode<std::weak_ptr<Actor>>* secondNode = secondLevel->getFirstNode(); secondNode != nullptr; secondNode = secondNode->next) {
//                if (auto indirectActorPtr = secondNode->item.lock()) {
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
void Graph::insertActorRelationships(
    LinkedList<std::weak_ptr<Actor>>* actorList,
    std::weak_ptr<Actor> sourceActor
) {
    //std::cout << "DEBUG: insertActorRelationships() called\n";

    if (!actorList) {
        std::cerr << "ERROR: Invalid actor list reference!\n";
        return;
    }

    // Lock the sourceActor to get its ID
    auto sourceShared = sourceActor.lock();
    if (!sourceShared) {
        std::cout << "WARNING: Source actor expired.\n";
        return;
    }
    int sourceId = sourceShared->getActorID();

    // Iterate through co-actors
    for (auto node = actorList->getFirstNode(); node != nullptr; node = node->next) {
        if (auto coActor = node->item.lock()) {
            int coActorId = coActor->getActorID();

            if (coActorId != sourceId) {
                // Add edge: sourceActor -> coActor
                addEdge(sourceId, node->item);

                // For undirected graphs, add reverse edge: coActor -> sourceActor
                if (!isDirected) {
                    addEdge(coActorId, sourceActor);
                }
            }
        }
        else {
            std::cout << "WARNING: Skipping expired weak_ptr\n";
        }
    }
}

//void Graph::insertActorRelationships(LinkedList<std::weak_ptr<Actor>>* actorList, int actorId) {
//    std::cout << "DEBUG: insertActorRelationships() called for Actor " << actorId << std::endl;
//
//    if (!actorList) {
//        std::cerr << "ERROR: Invalid actor list reference!" << std::endl;
//        return;
//    }
//
//    // Print out the actors in actorList
//    std::cout << "DEBUG: Actor list contains " << actorList->getLength() << " elements.\n";
//
//    // Add edges between the actor and all other actors in the list
//    for (LinkedListNode<std::weak_ptr<Actor>>* node = actorList->getFirstNode();
//        node != nullptr;
//        node = node->next) {
//
//        std::cout << "DEBUG: Node at " << node << ", item (weak_ptr) exists: "
//            << (node->item.expired() ? "NO" : "YES") << std::endl;
//
//        if (auto coActor = node->item.lock()) {  // Convert weak_ptr to shared_ptr
//            std::cout << "DEBUG: Actor ID in list: " << coActor->getActorID() << std::endl;
//            std::cout << "DEBUG: Connecting " << actorId << " with " << coActor->getActorID() << std::endl;
//            addEdge(actorId, coActor);
//          
//        }
//        else {
//            std::cout << "WARNING: Skipping expired weak_ptr\n";
//        }
//    }
//
//}

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
