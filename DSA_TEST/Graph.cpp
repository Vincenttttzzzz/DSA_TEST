//#include "Graph.h"
//
//// Constructor
//Graph::Graph(bool directed) : isDirected(directed) {
//}
//
//// Add an edge between two actors
////
//void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
//    std::shared_ptr<Actor> lockedDest = destActor.lock(); // Declare before if statement
//
//    std::cout << "DEBUG: Adding edge from Actor " << srcID << " to ";
//    if (lockedDest) {
//        std::cout << lockedDest->getActorID() << std::endl;
//    }
//    else {
//        std::cout << "NULL (weak_ptr expired)" << std::endl;
//        return;
//    }
//
//    // Ensure srcID exists in the adjacency list
//    if (adjacencyList.get(srcID) == nullptr) {
//        std::cout << "DEBUG: No existing list for " << srcID << ", creating new linked list.\n";
//        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
//    }
//
//    // Retrieve linked list for srcID
//    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
//    if (!neighbors) {
//        std::cerr << "ERROR: Could not retrieve adjacency list for Actor " << srcID << std::endl;
//        return;
//    }
//
//    // Check if destActor already exists
//    bool exists = false;
//    for (int i = 0; i < neighbors->getLength(); ++i) {
//        if (auto existing = neighbors->get(i).lock()) {
//            if (existing->getActorID() == lockedDest->getActorID()) {
//                exists = true;
//                break;
//            }
//        }
//    }
//
//    if (!exists) {
//        std::cout << "DEBUG: Inserting Actor " << lockedDest->getActorID() << " into adjacency list of " << srcID << std::endl;
//        neighbors->add(destActor);
//    }
//    else {
//        std::cout << "DEBUG: Actor " << lockedDest->getActorID() << " already exists in adjacency list of " << srcID << std::endl;
//    }
//}
//
//
//
//// Add an edge between two actors
////void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
////    std::cout << "Adding edge from Actor " << srcID << " to Actor " << (destActor.lock() ? destActor.lock()->getActorID() : -1) << std::endl;
////    // Ensure srcID exists in the adjacency list
////    if (adjacencyList.get(srcID) == nullptr) {
////        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
////    }
////
////    // Get the linked list for srcID
////    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
////
////    // Add destActor to the adjacency list
////    if (neighbors) {
////        neighbors->add(destActor);
////        std::cout << "Added Actor " << (destActor.lock() ? destActor.lock()->getActorID() : -1) << " to adjacency list of Actor " << srcID << std::endl;
////    }
////
////    // If the graph is undirected, add the reverse edge
////    if (isDirected) {
////        if (auto strongDestActor = destActor.lock()) {
////            int destID = strongDestActor->getActorID();
////            if (adjacencyList.get(destID) == nullptr) {
////                adjacencyList.add(destID, new LinkedList<std::weak_ptr<Actor>>());
////            }
////            LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(destID);
////            if (reverseNeighbors) {
////                reverseNeighbors->add(std::weak_ptr<Actor>(strongDestActor));
////                std::cout << "Added reverse edge from Actor " << destID << " back to Actor " << srcID << std::endl;
////            }
////        }
////    }
////}
//
////void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
////    // Ensure srcID exists in the adjacency list
////    if (adjacencyList.get(srcID) == nullptr) {
////        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
////    }
////
////    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
////    if (neighbors) neighbors->add(destActor);
////
////    // Handle undirected graph with proper weak_ptr locking
////    if (!isDirected) {
////        if (auto strongDestActor = destActor.lock()) {
////            int destID = strongDestActor->getActorID();
////            if (adjacencyList.get(destID) == nullptr) {
////                adjacencyList.add(destID, new LinkedList<std::weak_ptr<Actor>>());
////            }
////            LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(destID);
////            if (reverseNeighbors) reverseNeighbors->add(std::weak_ptr<Actor>(destActor));
////        }
////    }
////}
////
//
////void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
////    if (adjacencyList.get(srcID) == nullptr) {
////        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
////    }
////
////    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
////    if (neighbors) neighbors->add(destActor);
////
////    if (!isDirected) {
////        auto strongDestActor = destActor.lock();
////        if (strongDestActor) {
////            int destID = strongDestActor->getActorID();
////            if (adjacencyList.get(destID) == nullptr) {
////                adjacencyList.add(destID, new LinkedList<std::weak_ptr<Actor>>());
////            }
////
////            LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(destID);
////            if (reverseNeighbors) reverseNeighbors->add(std::weak_ptr<Actor>(strongDestActor));
////        }
////    }
////}
//
//// Add an edge between two actors
////void Graph::addEdge(int srcID, const std::weak_ptr<Actor>& destActor) {
////    // Ensure srcID exists in the adjacency list
////    if (adjacencyList.get(srcID) == nullptr) {
////        adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
////    }
////
////    // Get the linked list for srcID
////    LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(srcID);
////
////    // Add destActor to the adjacency list
////    if (neighbors) neighbors->add(destActor);
////
////    // If the graph is undirected, add the reverse edge
////    if (!isDirected) {
////        if (auto strongDestActor = destActor.lock()) {
////            if (adjacencyList.get(strongDestActor->getActorID()) == nullptr) {
////                adjacencyList.add(strongDestActor->getActorID(), new LinkedList<std::weak_ptr<Actor>>());
////            }
////
////            LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(strongDestActor->getActorID());
////            if (reverseNeighbors) reverseNeighbors->add(destActor);
////        }
////
////        LinkedList<std::weak_ptr<Actor>>* reverseNeighbors = adjacencyList.get(destActor->getActorID());
////        if (reverseNeighbors) reverseNeighbors->add(destActor);
////    }
////}
//
//
//
//
//
//// Print the adjacency list of the graph
////void Graph::printGraph() const {
////    for (int i = 0; i < MAX_SIZE; i++) {
////        LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(i);
////        if (neighbors == nullptr) continue;
////
////        std::cout << "Actor " << i << " knows: ";
////
////        for (const auto& actorWeakPtr : neighbors->toVector()) {
////            if (auto actorPtr = actorWeakPtr.lock()) {
////                std::cout << actorPtr->getName() << " (ID: " << actorPtr->getActorID() << ") ";
////            }
////        }
////
////        std::cout << std::endl;
////    }
////}
//
//void Graph::printGraph() const {
//    for (int i = 0; i < MAX_SIZE; i++) {
//        LinkedList<std::weak_ptr<Actor>>* neighbors = adjacencyList.get(i);
//        if (neighbors == nullptr) continue;
//
//        std::cout << "Actor " << i << " knows: ";
//
//        for (LinkedListNode<std::weak_ptr<Actor>>* node = neighbors->getFirstNode(); node != nullptr; node = node->next) {
//            if (auto actorPtr = node->item.lock()) {
//                std::cout << actorPtr->getName() << " (ID: " << actorPtr->getActorID() << ") ";
//            }
//        }
//
//        std::cout << std::endl;
//    }
//}
//
//
//// Display actors that a given actor knows (direct and indirect up to 2 levels)
////void Graph::displayKnownActors(int actorID) const {
////    LinkedList<std::weak_ptr<Actor>>* firstLevel = adjacencyList.get(actorID);
////
////    if (firstLevel == nullptr) {
////        std::cout << "Actor with ID " << actorID << " not found or has no connections." << std::endl;
////        return;
////    }
////
////    std::cout << "Directly knows: ";
////    for (const auto& actorWeakPtr : firstLevel->toVector()) {
////        if (auto actorPtr = actorWeakPtr.lock()) {
////            std::cout << actorPtr->getName() << " (ID: " << actorPtr->getActorID() << ") ";
////        }
////    }
////
////    std::cout << "\nIndirectly knows: ";
////    for (const auto& actorWeakPtr : firstLevel->toVector()) {
////        if (auto actorPtr = actorWeakPtr.lock()) {
////            LinkedList<std::weak_ptr<Actor>>* secondLevel = adjacencyList.get(actorPtr->getActorID());
////            if (secondLevel == nullptr) continue;
////
////            for (const auto& indirectActorWeakPtr : secondLevel->toVector()) {
////                if (auto indirectActorPtr = indirectActorWeakPtr.lock()) {
////                    if (indirectActorPtr->getActorID() != actorID) {
////                        std::cout << indirectActorPtr->getName() << " (ID: " << indirectActorPtr->getActorID() << ") ";
////                    }
////                }
////            }
////        }
////    }
////
////    std::cout << std::endl;
////}
//
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
//
//
//// Check if the graph is empty
//bool Graph::isEmpty() const {
//    return const_cast<HashTable<LinkedList<std::weak_ptr<Actor>>*>&>(adjacencyList).getLength() == 0;
//}
//
//// Get the number of vertices in the graph
//int Graph::getVertexCount() const {
//    return const_cast<HashTable<LinkedList<std::weak_ptr<Actor>>*>&>(adjacencyList).getLength(); // Ensure method compatibility with non-const context
//}
//// Insert actor relationships from actor-movie data into the graph
//// 
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
//            if (coActor->getActorID() != actorId) {
//                std::cout << "DEBUG: Connecting " << actorId << " with " << coActor->getActorID() << std::endl;
//                addEdge(actorId, coActor);
//            }
//        }
//        else {
//            std::cout << "WARNING: Skipping expired weak_ptr\n";
//        }
//    }
//
//}
//
//// // Insert actor relationships from actor-movie data into the graph
////void Graph::insertActorRelationships(LinkedList<std::weak_ptr<Actor>>* actorList, int actorId) {
////    std::cout << "insert actor" << endl;
////    if (!actorList) {
////        std::cerr << "Invalid actor list reference!" << std::endl;
////        return;
////    }
////
////    // Add edges between the actor and all other actors in the list
////    for (LinkedListNode<std::weak_ptr<Actor>>* node = actorList->getFirstNode(); node != nullptr; node = node->next) {
////        if (auto coActor = node->item.lock()) {
////            if (coActor->getActorID() != actorId) {
////                std::cout << "Adding edge between Actor " << actorId << " and Actor " << coActor->getActorID() << std::endl;
////                addEdge(actorId, coActor);
////            }
////        }
////    }
////}
////void Graph::insertActorRelationships(const LinkedList<std::weak_ptr<Actor>>* actorList, int actorId) {
////    if (!actorList) {
////        std::cerr << "Invalid actor list reference!" << std::endl;
////        return;
////    }
////
////    // Add edges between the actor and all other actors in the list
////    for (LinkedListNode<std::weak_ptr<Actor>>* node = actorList->getFirstNode(); node != nullptr; node = node->next) {
////        if (auto coActor = node->item.lock()) {
////            if (coActor->getActorID() != actorId) {
////                std::cout << actorId << " " << coActor->getActorID() << endl;
////                addEdge(actorId, coActor);
////            }
////        }
////    }
////}

#include "Graph.h"

// Modified addEdge with O(1) complexity
//void Graph::addEdge(const std::weak_ptr<Actor>& srcActor, const std::weak_ptr<Actor>& destActor) {
//    // Lock source actor to ensure it exists
//    if (auto lockedSrc = srcActor.lock()) {
//        int srcID = lockedSrc->getActorID();
//
//        // Ensure source vertex has an adjacency list
//        if (!adjacencyList.get(srcID)) {
//            adjacencyList.add(srcID, new LinkedList<std::weak_ptr<Actor>>());
//        }
//
//        // Add destination actor to source's adjacency list
//        adjacencyList.get(srcID)->add(destActor);
//
//        // For undirected graph, add reverse edge
//        if (!isDirected && destActor.lock()) {
//            int destID = destActor.lock()->getActorID();
//            if (!adjacencyList.get(destID)) {
//                adjacencyList.add(destID, new LinkedList<std::weak_ptr<Actor>>());
//            }
//            adjacencyList.get(destID)->add(srcActor);
//        }
//    }
//}

Graph::Graph(bool directed) : isDirected(directed) {
}

void Graph::addEdge(
    const std::weak_ptr<Actor>& srcActor,
    const std::weak_ptr<Actor>& destActor
) {
    auto src = srcActor.lock();
    auto dest = destActor.lock();
    if (!src || !dest) return;

    // Add dest to src's adjacency list
    LinkedList<std::weak_ptr<Actor>>* srcList = adjacencyList.get(src->getActorID());
    if (!srcList) {
        srcList = new LinkedList<std::weak_ptr<Actor>>();
        adjacencyList.add(src->getActorID(), srcList);
    }
    srcList->add(destActor);

    // If undirected, add the reverse edge
    if (!isDirected) {
        LinkedList<std::weak_ptr<Actor>>* destList = adjacencyList.get(dest->getActorID());
        if (!destList) {
            destList = new LinkedList<std::weak_ptr<Actor>>();
            adjacencyList.add(dest->getActorID(), destList);
        }
        destList->add(srcActor);
    }
}

// Modified displayKnownActors with O(V + E) complexity
void Graph::displayKnownActors(const std::weak_ptr<Actor>& sourceActor) const {
    // Lock source actor to get its ID
    auto lockedSource = sourceActor.lock();
    if (!lockedSource) {
        std::cout << "Source actor no longer exists.\n";
        return;
    }

    LinkedList<std::weak_ptr<Actor>>* firstLevel = adjacencyList.get(lockedSource->getActorID());
    if (!firstLevel) {
        std::cout << "Actor " << lockedSource->getName() << " has no connections.\n";
        return;
    }

    // Create queue for BFS, storing weak_ptr to actors
    Queue<std::weak_ptr<Actor>> queue;
    // Track visited actors using their IDs
    HashTable<int> visited;  // Value stores level of connection (1 or 2)

    // Start BFS from source actor
    queue.enqueue(sourceActor);
    visited.add(lockedSource->getActorID(), 0);

    // Lists to store connections at each level
    LinkedList<std::weak_ptr<Actor>> directConnections;
    LinkedList<std::weak_ptr<Actor>> indirectConnections;

    int currentLevel = 0;
    while (!queue.isEmpty() && currentLevel < 2) {
        int size = queue.getSize();

        for (int i = 0; i < size; i++) {
            std::weak_ptr<Actor> currentActor = queue.dequeue();

            // Skip if actor no longer exists
            auto lockedCurrent = currentActor.lock();
            if (!lockedCurrent) continue;

            // Get neighbors of current actor
            LinkedList<std::weak_ptr<Actor>>* neighbors =
                adjacencyList.get(lockedCurrent->getActorID());
            if (!neighbors) continue;

            // Process each neighbor
            for (auto node = neighbors->getFirstNode(); node != nullptr; node = node->next) {
                auto lockedNeighbor = node->item.lock();
                if (!lockedNeighbor) continue;  // Skip expired actors


                // Skip the source actor and already visited actors
                if (lockedNeighbor->getActorID() == lockedSource->getActorID()) continue;
                if (visited.get(lockedNeighbor->getActorID())) continue;

                visited.add(lockedNeighbor->getActorID(), currentLevel + 1);
                queue.enqueue(node->item);

                if (currentLevel == 0) {
                    directConnections.add(node->item);
                }
                else {
                    indirectConnections.add(node->item);
                }

                // If not visited, process it
                //if (!visited.get(lockedNeighbor->getActorID())) {
                //    visited.add(lockedNeighbor->getActorID(), currentLevel + 1);
                //    queue.enqueue(node->item);

                //    // Add to appropriate connection list
                //    if (currentLevel == 0) {
                //        directConnections.add(node->item);
                //    }
                //    else {
                //        indirectConnections.add(node->item);
                //    }
                //}
            }
        }
        currentLevel++;
    }

    // Print results
    std::cout << "Directly knows: ";
    printConnections(directConnections);

    std::cout << "\nIndirectly knows: ";
    printConnections(indirectConnections);
}

void Graph::insertActorRelationships(
    LinkedList<std::weak_ptr<Actor>>* actorList,
    std::weak_ptr<Actor> actor
) {
    // Check if the actor or list is invalid
    auto lockedActor = actor.lock();
    if (!lockedActor || !actorList) return;

    // Iterate through the list of actors
    for (auto node = actorList->getFirstNode(); node != nullptr; node = node->next) {
        auto otherActor = node->item.lock();
        // Skip expired actors and self-connections
        if (otherActor && otherActor != lockedActor) {
            // Add edge from the current actor to the other actor
            addEdge(actor, node->item);
            // If undirected, add the reverse edge (handled by addEdge internally)
        }
    }
}

void Graph::printConnections(const LinkedList<std::weak_ptr<Actor>>& connections) const {
    for (auto node = connections.getFirstNode(); node != nullptr; node = node->next) {
        if (auto actor = node->item.lock()) {
            std::cout << actor->getName() << " (ID: " << actor->getActorID() << ") ";
        }
    }
    std::cout << endl;
}
