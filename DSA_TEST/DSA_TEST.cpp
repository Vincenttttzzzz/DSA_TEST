// DSA_TEST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "HashTable.h"
#include "Actor.h"
#include "Movie.h"
#include "BinaryTree.h"
#include "LinkedList.h"
#include "List.h"
#include "Graph.h"
#include "RatingSystem.h"

void readCSV(const std::string& csvName, HashTable<std::shared_ptr<Actor>>& table, BST& tree);
void readCSV(const std::string& csvName, HashTable<std::shared_ptr<Movie>>& table, BST& tree);
void readCSV(const std::string& csvName, HashTable<std::shared_ptr<Movie>>& movieTable, HashTable<std::shared_ptr<Actor>>& actor, HashTable<LinkedList<std::weak_ptr<Movie>>*>& table, Graph& actorGraph);

void insertActor(HashTable<std::shared_ptr<Actor>>& actor, BST& tree, int id, string name, int year);
void insertMovie(HashTable<std::shared_ptr<Movie>>& movie, BST& tree, int id, string title, string plot, int year);
void insertActorToMovie(HashTable<std::shared_ptr<Movie>>& movie, HashTable<std::shared_ptr<Actor>>& actor, HashTable<LinkedList<std::weak_ptr<Movie>>*>& actorToMovie, int actorId, int movieId, Graph& actorGraph);

void addNewActor(HashTable<std::shared_ptr<Actor>>& table, BST& tree);
void addNewMovie(HashTable<std::shared_ptr<Movie>>& table, BST& tree);
void addActorToMovie(HashTable<std::shared_ptr<Movie>>& movieTable, HashTable<std::shared_ptr<Actor>>& actorTable, HashTable<LinkedList<std::weak_ptr<Movie>>*>& actorToMovieTable, Graph& actorGraph);
void updateActor(HashTable<std::shared_ptr<Actor>>& actorTable);
void updateMovie(HashTable<std::shared_ptr<Movie>>& movieTable);

void displayMenu();

void displayActorByYear(const BST& actorTree, const HashTable<std::shared_ptr<Actor>>& table);
void displayMovieByYear(const BST& movieTree, const HashTable<std::shared_ptr<Movie>>& table);
void displayMoviesForActor(const HashTable<LinkedList<std::weak_ptr<Movie>>*>& table, const HashTable<std::shared_ptr<Movie>>& movieTable);
void displayActorsForMovie(const HashTable<std::shared_ptr<Movie>>& movieTable, const HashTable<std::shared_ptr<Actor>>& actorTable);


template <typename T, typename Compare>
int partition(std::shared_ptr<T>* arr, int low, int high, Compare comp);
// Template quicksort function
template <typename T, typename Compare>
void quickSort(std::shared_ptr<T>* arr, int low, int high, Compare comp);

void displayActorRelationship(Graph& actorGraph);

int main()
{
    HashTable<std::shared_ptr<Actor>> actorTable = HashTable<std::shared_ptr<Actor>>();
    HashTable<std::shared_ptr<Movie>> movieTable = HashTable<std::shared_ptr<Movie>>();
    HashTable<LinkedList<std::weak_ptr<Movie>>*> actorToMovie = HashTable<LinkedList<std::weak_ptr<Movie>>*>();
    Graph actorToActor(false);

    BST actorAVL = BST();
    BST movieAVL = BST();


    readCSV("actors.csv", actorTable, actorAVL);
    readCSV("movies.csv", movieTable, movieAVL);
    readCSV("cast.csv", movieTable, actorTable, actorToMovie, actorToActor);

    /*readCSV("people2.csv", actorTable, actorAVL);
    readCSV("movies2.csv", movieTable, movieAVL);
    readCSV("cast2.csv", movieTable, actorTable, actorToMovie, actorToActor);*/

    std::string opt = "";
    while (opt != "0") {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> opt;

        if (opt == "1") {
            addNewActor(actorTable, actorAVL);
        }
        else if (opt == "2") {
            addNewMovie(movieTable, movieAVL);
        }
        else if (opt == "3") {
            addActorToMovie(movieTable, actorTable, actorToMovie, actorToActor);
        }
        else if (opt == "4") {
            std::string className;

            std::cout << "Choose which one to update (Actor/Movie): ";
            std::cin >> className;

            if (className == "Actor") {
                updateActor(actorTable);
            }
            else if (className == "Movie") {
                updateMovie(movieTable);
            }
            else {
                std::cout << "Invalid choice! Please choose either Actor or Movie." << std::endl;
            }
        }
        else if (opt == "5") {
            displayActorByYear(actorAVL, actorTable);
        }
        else if (opt == "6") {
            displayMovieByYear(movieAVL, movieTable);
        }
        else if (opt == "7") {
            displayMoviesForActor(actorToMovie, movieTable);
        }
        else if (opt == "8") {
            displayActorsForMovie(movieTable, actorTable);
        }
        else if (opt == "9") {
            displayActorRelationship(actorToActor);
        }
        else if (opt == "0") {
            std::cout << "Exiting program..." << std::endl;
        }
        else {
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }


    return 0;

}

void readCSV(const std::string& csvName, HashTable<std::shared_ptr<Actor>>& table, BST& tree) {
    std::ifstream file(csvName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, yearStr;
        if (!std::getline(ss, idStr, ',') || !std::getline(ss, name, ',') || !std::getline(ss, yearStr, ',')) {
            std::cerr << "Error: Malformed actor line: " << line << std::endl;
            continue;
        }

        try {
            int id = std::stoi(idStr);
            int birthYear = std::stoi(yearStr);
            insertActor(table, tree, id, name, birthYear);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: Failed to parse actor data: " << line << std::endl;
        }
    }
}


void readCSV(const std::string& csvName, HashTable<std::shared_ptr<Movie>>& table, BST& tree) {
    std::ifstream file(csvName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::string idStr, title, plot, yearStr;
        size_t pos = 0;

        // Extract movie ID (before first comma)
        pos = line.find(',');
        if (pos == std::string::npos) continue;
        idStr = line.substr(0, pos);
        line = line.substr(pos + 1);

        // Extract movie title (handling cases where it's enclosed in quotes)
        if (!line.empty() && line[0] == '"') {
            size_t quoteEnd = line.find('"', 1); // Find closing quote
            if (quoteEnd == std::string::npos) {
                std::cerr << "Error: Malformed title field in line: " << line << std::endl;
                continue;
            }
            title = line.substr(1, quoteEnd - 1); // Extract title (remove quotes)
            line = line.substr(quoteEnd + 1); // Move past the closing quote

            // Check if a comma immediately follows (indicating a proper CSV structure)
            if (!line.empty() && line[0] == ',') {
                line = line.substr(1); // Remove the leading comma
            }
        }
        else {
            // Extract title normally (for cases without quotes)
            pos = line.find(',');
            if (pos == std::string::npos) continue;
            title = line.substr(0, pos);
            line = line.substr(pos + 1);
        }

        // Trim any trailing commas from the extracted title
        while (!title.empty() && title.back() == ',') {
            title.pop_back();
        }

        // Handle plots enclosed in quotes
        if (!line.empty() && line[0] == '"') {
            size_t quoteStart = 1; // Skip opening quote
            size_t quoteEnd = quoteStart;

            std::ostringstream plotStream;
            bool insideQuotes = true;
            while (insideQuotes && quoteEnd < line.size()) {
                quoteEnd = line.find('"', quoteEnd);

                if (quoteEnd == std::string::npos) {
                    std::cerr << "Error: Malformed plot field in line: " << line << std::endl;
                    continue;
                }

                // Check if the quote is escaped (if followed by another quote)
                if (quoteEnd + 1 < line.size() && line[quoteEnd + 1] == '"') {
                    plotStream << line.substr(quoteStart, quoteEnd - quoteStart + 1);  // Include one quote
                    quoteStart = quoteEnd + 2;  // Move past escaped quote
                    quoteEnd += 2;  // Skip the escaped quote
                }
                else {
                    plotStream << line.substr(quoteStart, quoteEnd - quoteStart);  // Normal quote
                    insideQuotes = false;
                    quoteStart = quoteEnd + 1;  // Skip the closing quote
                }
            }

            plot = plotStream.str();
            line = line.substr(quoteStart + 1);  // Skip comma after closing quote
        }
        else {
            // Handle plots without quotes
            pos = line.rfind(','); // Find the last comma (before the year)
            if (pos == std::string::npos) {
                std::cerr << "Error: Malformed CSV - missing year in line: " << line << std::endl;
                continue;
            }
            plot = line.substr(0, pos);
            line = line.substr(pos + 1);
        }

        // Remove leading comma before extracting year
        if (!line.empty() && line[0] == ',') {
            line = line.substr(1);
        }

        // If yearStr was not extracted, take it from line
        if (yearStr.empty()) {
            yearStr = line;
        }

        // Trim whitespace
        idStr.erase(0, idStr.find_first_not_of(" \t\r\n"));
        idStr.erase(idStr.find_last_not_of(" \t\r\n") + 1);

        title.erase(0, title.find_first_not_of(" \t\r\n"));
        title.erase(title.find_last_not_of(" \t\r\n") + 1);

        plot.erase(0, plot.find_first_not_of(" \t\r\n"));
        plot.erase(plot.find_last_not_of(" \t\r\n") + 1);

        yearStr.erase(0, yearStr.find_first_not_of(" \t\r\n"));
        yearStr.erase(yearStr.find_last_not_of(" \t\r\n") + 1);

        // Convert ID and year to integers with error handling
        try {
            int id = std::stoi(idStr);
            int releaseYear = std::stoi(yearStr);

            // Insert into hash table
            insertMovie(table, tree, id, title, plot, releaseYear);
        }
        catch (const std::invalid_argument&) {
            std::cerr << "Error: Invalid number format in line: " << line << std::endl;
            continue;
        }
        catch (const std::out_of_range&) {
            std::cerr << "Error: Number out of range in line: " << line << std::endl;
            continue;
        }
    }

    std::cout << "CSV file read successfully!" << std::endl;
}


//void readCSV(const std::string& csvName, HashTable<std::shared_ptr<Movie>>& table, BST& tree) {
//    std::ifstream file(csvName);
//    if (!file.is_open()) {
//        std::cerr << "Error: Could not open file!" << std::endl;
//        return;
//    }
//
//    std::string line;
//
//    // Skip the header line
//    std::getline(file, line);
//
//    std::cout << line << endl;
//    while (std::getline(file, line)) {
//        std::string idStr, title, plot, yearStr;
//        size_t pos = 0;
//
//        //std::cout << "Processing line: " << line << std::endl;
//
//        // Extract movie ID (before first comma)
//        pos = line.find(',');
//        if (pos == std::string::npos) continue;
//        idStr = line.substr(0, pos);
//        line = line.substr(pos + 1);
//
//        // Extract movie title (before next comma)
//        pos = line.find(',');
//        if (pos == std::string::npos) continue;
//        title = line.substr(0, pos);
//        line = line.substr(pos + 1);
//
//
//        std::cout << "idstr" << idStr << endl;
//        std::cout << "title" << title << endl;
//
//        std::cout << "LINE PLS" << line << endl;
//        // Handle plot enclosed in quotes while considering escaped quotes
//
//        if (!line.empty() && line[0] == '"') {
//            size_t quoteStart = 1; // Skip opening quote
//            size_t quoteEnd = quoteStart;
//
//            std::ostringstream plotStream;
//
//            bool insideQuotes = true;
//            while (insideQuotes && quoteEnd < line.size()) {
//                quoteEnd = line.find('"', quoteEnd);
//                std::cout << quoteEnd;
//
//                if (quoteEnd == std::string::npos) {
//                    std::cerr << "Error: Malformed plot field in line: " << line << std::endl;
//                    break;
//                    continue;
//                }
//
//                // Check if the quote is escaped (if followed by another quote)
//                if (quoteEnd + 1 < line.size() && line[quoteEnd + 1] == '"') {
//                    plotStream << line.substr(quoteStart, quoteEnd - quoteStart + 1);  // Include one quote
//                    quoteStart = quoteEnd + 2;  // Move past escaped quote
//                    quoteEnd += 2;  // Skip the escaped quote
//                }
//                else {
//                    plotStream << line.substr(quoteStart, quoteEnd - quoteStart);  // Normal quote
//                    insideQuotes = false;
//                    quoteStart = quoteEnd + 1;  // Skip the closing quote
//                }
//            }
//
//            plot = plotStream.str();
//            line = line.substr(quoteStart + 1);  // Skip comma after closing quote
//
//            std::cout << "Line in if" << line << endl;
//        }
//        else {
//            // Handle plots without quotes
//            pos = line.rfind(','); // Find the last comma (before the year)
//            if (pos == std::string::npos) {
//                std::cerr << "Error: Malformed CSV - missing year in line: " << line << std::endl;
//                break;
//                continue;
//            }
//            std::cout << "PLOT1::: " << pos << endl;
//     
//
//            plot = line.substr(0, pos);
//            yearStr = line.substr(pos + 1);
//
//            std::cout << "PLOT2::: " << plot << endl;
//            std::cout << "PLOT3::: " << yearStr << endl;
//            //line.clear();
//        }
//        //else {
//        //    std::cerr << "Error: Malformed CSV - missing quotes around plot in line: " << line << std::endl;
//        //    break;
//        //    //continue;
//        //}
//
//        // Remove leading comma before extracting year
//        if (!line.empty() && line[0] == ',') {
//            line = line.substr(1);
//        }
//
//        // If yearStr was not extracted, take it from line
//        if (yearStr.empty()) {
//            yearStr = line;
//        }
//
//        // Trim whitespace (optional but helpful)
//        idStr.erase(0, idStr.find_first_not_of(" \t\r\n"));
//        idStr.erase(idStr.find_last_not_of(" \t\r\n") + 1);
//
//        plot.erase(0, plot.find_first_not_of(" \t\r\n"));
//        plot.erase(plot.find_last_not_of(" \t\r\n") + 1);
//
//        yearStr.erase(0, yearStr.find_first_not_of(" \t\r\n"));
//        yearStr.erase(yearStr.find_last_not_of(" \t\r\n") + 1);
//
//        // Convert ID and year to integers with error handling
//        std::cout << "idstr" << idStr << endl;
//        std::cout << "title" << title << endl;
//        std::cout << "plot" << plot << endl;
//        std::cout << "year" << yearStr << endl;
//
//        try {
//            int id = std::stoi(idStr);
//            int releaseYear = std::stoi(yearStr);
//
//            
//
//            // Insert into hash table
//            insertMovie(table, tree, id, title, plot, releaseYear);
//        }
//        catch (const std::invalid_argument&) {
//            std::cerr << "Error: Invalid number format in line: " << line << std::endl;
//            break;
//            continue;
//        }
//        catch (const std::out_of_range&) {
//            std::cerr << "Error: Number out of range in line: " << line << std::endl;
//            continue;
//        }
//    }
//
//    std::cout << "CSV file read successfully!" << std::endl;
//}


void readCSV(const std::string& csvName, HashTable<std::shared_ptr<Movie>>& movieTable, HashTable<std::shared_ptr<Actor>>& actorTable, HashTable<LinkedList<std::weak_ptr<Movie>>*>& table, Graph& actorGraph) {
    std::ifstream file(csvName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        //std::cout << line << endl;
        std::stringstream ss(line);
        std::string actorIDStr, movieIDStr;
        if (!std::getline(ss, actorIDStr, ',') || !std::getline(ss, movieIDStr, ',')) {
            std::cerr << "Error: Malformed relationship line: " << line << std::endl;
            continue;
        }

        try {
            int actorID = std::stoi(actorIDStr);
            int movieID = std::stoi(movieIDStr);
            insertActorToMovie(movieTable, actorTable, table, actorID, movieID, actorGraph);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: Failed to parse relationship data: " << line << std::endl;
        }
    }
}




void insertActor(HashTable<std::shared_ptr<Actor>>& actor, BST& tree, int id, string name, int year) {
    // Actor clas
    auto newActor = std::make_shared<Actor>(id, name, year);

    bool inserted = actor.add(id, newActor);
    //std::cout << "Insert success: " << inserted << std::endl;

    auto testActor = actor.get(id);
    if (testActor) {
        //std::cout << "DEBUG: Retrieved " << testActor->getName() << " after insert." << std::endl;
    }
    else {
        //std::cout << "ERROR: Could not retrieve actor after insert!" << std::endl;
    }
    //std::cout << inserted;
    tree.insert(id, year);
}


void insertMovie(HashTable<std::shared_ptr<Movie>>& movie, BST& tree, int id, string title, string plot, int year) {
    // Actor clas
    auto newMovie = std::make_shared<Movie>(id, title, plot, year);

    bool inserted = movie.add(id, newMovie);
    tree.insert(id, year);
}

void insertActorToMovie(HashTable<std::shared_ptr<Movie>>& movieTable, HashTable<std::shared_ptr<Actor>>& actorTable,
    HashTable<LinkedList<std::weak_ptr<Movie>>*>& actorToMovie, int actorId, int movieId, Graph& actorGraph) {

    //std::cout << "DEBUG: insertActorToMovie() called for Actor " << actorId << " and Movie " << movieId << std::endl;

    auto actor = actorTable.get(actorId);
    if (!actor) {
        //std::cerr << "ERROR: Actor with ID " << actorId << " not found!" << std::endl;
        return;
    }

    // Retrieve or create list of movies for actor
    LinkedList<std::weak_ptr<Movie>>* listOfMovies = actorToMovie.get(actorId);
    if (!listOfMovies) {
        //std::cout << "DEBUG: Creating new movie list for Actor " << actorId << std::endl;
        listOfMovies = new LinkedList<std::weak_ptr<Movie>>();
        actorToMovie.add(actorId, listOfMovies);
    }

    // Retrieve the movie
    auto movie = movieTable.get(movieId);
    if (!movie) {
        //std::cerr << "ERROR:    Movie with ID " << movieId << " not found!" << std::endl;
        return;
    }

    // Add movie to actor's list
    listOfMovies->add(movie);
    //std::cout << "DEBUG: Added Movie ID: " << movie->getMovieID() << " to Actor ID: " << actorId << std::endl;
    //std::cout << "DEBUG: Current list size after adding: " << listOfMovies->getLength() << std::endl;

    // Add actor to movie
    movie->addActor(actor);

    // Insert to graph
    LinkedList<std::weak_ptr<Actor>>* listOfActors = movie->getListOfActors();
    actorGraph.insertActorRelationships(listOfActors, actor);
}

//void insertActorToMovie(HashTable<std::shared_ptr<Movie>>& movieTable, HashTable<std::shared_ptr<Actor>>& actorTable, HashTable<LinkedList<std::weak_ptr<Movie>>*>& actorToMovie, int actorId, int movieId, Graph& actorGraph) {
//
//    //// Retrieve the list of movies for the actor
//    //LinkedList<std::weak_ptr<Actor>>* movies = actorToMovie.get(actorId);
//
//    //// If no list exists for the actor, create a new list
//    //if (movies == nullptr) {
//    //    movies = new LinkedList<std::weak_ptr<Actor>>();
//    //    actorToMovie.add(actorId, movies);
//    //}
//
//    //// Add the movieId to the actor's list of movies
//    //movies->add(movieId);
//
//
//    //// add to the list of actors in the movie class
//    //Movie* movie = movieTable.get(movieId);
//    //movie->addActor(actorId);
//
//
//    auto actor = actorTable.get(actorId); //Actor pointer
//    //std::cout << "DEBUG: actorTable.get(" << actorId << ") returned: " << (actor ? "FOUND" : "NULL") << std::endl;
//
//    if (!actor) {
//        //std::cout << "Actor with ID " << actorId << " not found!" << std::endl;
//        return;
//    }
//
//    // Retrieve the list of movies for the actor
//    LinkedList<std::weak_ptr<Movie>>* listOfMovies = actorToMovie.get(actorId);
//
//    // If no list exists for the actor, create a new list
//    if (listOfMovies == nullptr) {
//        listOfMovies = new LinkedList<std::weak_ptr<Movie>>();
//        actorToMovie.add(actorId, listOfMovies); 
//    }
//
//    // Retrieve the movie from the movie table
//    auto movie = movieTable.get(movieId);
//    if (!movie) {
//        //std::cout << "Movie with ID " << movieId << " not found!" << std::endl;
//        return;
//    }
//
//    // Add the movie to the actor's list of movies
//    listOfMovies->add(movie);
//    //listOfMovies.print();
//    // Add the actor to the movie's list of actors
//    movie->addActor(actor);
//    std::cout << "Adding Movie ID: " << movie->getMovieID() << " to Actor ID: " << actorId << std::endl;
//    std::cout << "Current list size after adding: " << listOfMovies->getLength() << std::endl;
//
//
//    // Insert to the graph (movie is a weak pointer)
//    LinkedList<std::weak_ptr<Actor>>* listOfActors = movie->getListOfActors();
//    actorGraph.insertActorRelationships(listOfActors, actorId);
//    /*for (int i = 0; i < listOfActors->getLength(); ++i) {
//        actorGraph.addEdge(actorId, actor);
//    }*/
//    
//}


 
void addNewActor(HashTable<std::shared_ptr<Actor>>& table, BST& tree) {
    std::string name;
    int id, year;

    std::cout << endl;
    std::cout << "Actor's Id: ";
    std::cin >> id;

    std::cout << "Actor's Name: ";
    std::cin >> name;

    std::cout << "Actor's Birth Year: ";
    std::cin >> year;
    std::cout << endl;

    insertActor(table, tree, id, name, year);
    std::cout << "New Actor added!" << endl;
    table.print();
}

void addNewMovie(HashTable<std::shared_ptr<Movie>>& table, BST& tree) {
    std::string title, plot;
    int id, year;

    std::cout << "Movie's Id: ";
    std::cin >> id;

    std::cout << "Movie's Title: ";
    std::cin >> title;

    std::cout << "Movie's Plot: ";
    std::cin >> plot;

    std::cout << "Movie's Release Year: ";
    std::cin >> year;

    insertMovie(table, tree, id, title, plot, year);
    std::cout << "New Movie added!" << endl;
    table.print();
}

void addActorToMovie(HashTable<std::shared_ptr<Movie>>& movieTable, HashTable<std::shared_ptr<Actor>>& actorTable, HashTable<LinkedList<std::weak_ptr<Movie>>*>& actorToMovieTable, Graph& actorGraph) {
    int actorId, movieId;
    std::cout << "Actor Id: ";
    std::cin >> actorId;

    std::cout << "Movie Id: ";
    std::cin >> movieId;

    // Insert into Actor (Key) to Movie(Value) Hashtable
    insertActorToMovie(movieTable, actorTable, actorToMovieTable, actorId, movieId, actorGraph);
    
    // Insert into LinkedList of Actors (value) in Movie (key) class
    auto movie = movieTable.get(movieId);
    /*auto actor = actorTable.get(actorId);
    movie->addActor(actor);*/

    std::cout << "Actor " << actorId << " added to Movie " << movieId << endl;

    const LinkedList<std::weak_ptr<Actor>>* listOfActors = movie->getListOfActors();
    listOfActors->print();
}

void updateActor(HashTable<std::shared_ptr<Actor>>& actorTable) {
    int actorId;

    std::cout << "Which Actor(Id) do you want to update: ";
    std::cin >> actorId;
    std::cout << endl;

    auto actor = actorTable.get(actorId);
    actor->print();

    string attribute;
    bool updated = false;

    std::cout << endl;
    std::cout << "Which attribute do you want to update: ";
    std::cin >> attribute;

    // Convert the string to lowercase
    for (char& c : attribute) {
        c = std::tolower(c);
    }

    if (attribute == "name") {
        std::string name;
        std::cout << "Updated Name: ";
        std::cin.ignore(); // Ignore any leftover newline in the input buffer
        std::getline(std::cin, name);

        actor->setName(name);
        updated = true;
    }
    else if (attribute == "birth year") {
        int birth;
        std::cout << "Updated Birth Year: ";
        std::cin >> birth;

        actor->setYear(birth);
        updated = true;
    }
    else {
        std::cout << "Invalid attribute." << endl;
    }

    if (updated) {
        std::cout << "Newly Updated Actor Class: " << endl;
        actor->print();
        std::cout << endl;
    }
}

 
void updateMovie(HashTable<std::shared_ptr<Movie>>& movieTable) {
    int movieId;

    std::cout << "Which Movie(Id) do you want to update: ";
    std::cin >> movieId;
    std::cout << endl;

    auto movie = movieTable.get(movieId);
    movie->print();

    string attribute;
    bool updated;

    std::cout << "Which attribute do you want to update: ";
    std::cin >> attribute;

    // Convert the string to lowercase
    for (char& c : attribute) {
        c = std::tolower(c);
    }

    if (attribute == "title") {
        std::string name;
        std::cout << "Updated Title: ";
        std::cin.ignore(); // Ignore any leftover newline in the input buffer
        std::getline(std::cin, name);

        movie->setTitle(name);
        updated = true;
    }
    else if (attribute == "plot") {
        std::string plot;
        std::cout << "Updated Plot: ";
        std::cin.ignore(); // Ignore any leftover newline in the input buffer
        std::getline(std::cin, plot);

        movie->setPlot(plot);
        updated = true;
    }
    else if (attribute == "year") {
        int year;
        std::cout << "Updated Release Year: ";
        std::cin >> year;

        movie->setYear(year);
        updated = true;
    }
    else {
        std::cout << "Invalid attribute." << endl;
    }

    if (updated) {
        std::cout << "Newly Updated Movie Class: " << endl;
        movie->print();
        std::cout << endl;
    }
}

void displayMenu() {
    std::cout << "IMBB: Movies & TV Shows" << endl;
    std::cout << "--------------------------------" << endl;
    std::cout << "Administrator Functions" << endl;
    std::cout << "1. Add New Actor" << endl;
    std::cout << "2. Add New Movie" << endl;
    std::cout << "3. Add New Actor to a Movie" << endl;
    std::cout << "4. Update Actor/Movie Details" << endl;
    std::cout << "--------------------------------" << endl;
    std::cout << "User Functions" << endl;
    std::cout << "5. Display the actors (in ascending order of age)" << endl;
    std::cout << "6. Display movies made within the past 3 years (in ascending order of year)" << endl;
    std::cout << "7. Display all movies an actor starred in (in alphabetical order)" << endl;
    std::cout << "8. Display all the actors in a particular movie (in alphabetical order)" << endl;
    std::cout << "9. Display a list of all actors that a particular actor knows" << std::endl;
    std::cout << "0. Exit" << std::endl;

}

void displayActorByYear(const BST& actorTree, const HashTable<std::shared_ptr<Actor>>& table) {
    int year1, year2;

    std::cout << "year1: ";
    std::cin >> year1;

    std::cout << "year2: ";
    std::cin >> year2;

    // Use the callback to process actors within the range
    actorTree.displayByRange(year1, year2, [&table](int actorId) {
        auto actor = table.get(actorId);
        if (actor) {
            actor->print(); // Print actor details
        }
        else {
            std::cout << "Actor ID " << actorId << " not found!" << std::endl;
        }
    });
}

void displayMovieByYear(const BST& movieTree, const HashTable<std::shared_ptr<Movie>>& table) {
    int year;

    std::cout << "year: ";
    std::cin >> year;

    // Use the callback to process actors within the range
    movieTree.displayByRange(year - 3, year, [&table](int movieId) {
        auto actor = table.get(movieId);
        if (actor) {
            actor->print(); // Print actor details
        }
        else {
            std::cout << "Actor ID " << movieId << " not found!" << std::endl;
        }
    });
}

void displayMoviesForActor(const HashTable<LinkedList<std::weak_ptr<Movie>>*>& table, const HashTable<std::shared_ptr<Movie>>& movieTable) {
    int actorId;
    cout << "Enter Actor ID: ";
    cin >> actorId;

    // Get the movie object from the hash table
    LinkedList<std::weak_ptr<Movie>>* listOfMovies = table.get(actorId);
    listOfMovies->print();
    if (listOfMovies == nullptr) {
        cout << "No movies found for Actor ID: " << actorId << endl;
        return;
    }
    /*if (!listOfMovies) {
        cout << "Movies not found!" << endl;
        return;
    }*/


    // Loop through listOfActors(LinkedList) and store in List (Fixed size)


    // Sort actors using quicksort based on a chosen attribute (e.g., actor name)
    // Sorting actors by name using quickSort


    // Display sorted actors




    // Implementation
    // Create a custom List to store Actor* pointers
    List<std::shared_ptr<Movie>> moviePointers(listOfMovies->getLength());
    for (int i = 0; i < listOfMovies->getLength(); ++i) {
        auto weakMovie = listOfMovies->get(i);
        if (auto movie = weakMovie.lock()) { // Lock weak_ptr to get shared_ptr
            moviePointers.add(movie);       // Add shared_ptr<Movie> to the List
        }
    }

    // Sort movies by title
    int length = moviePointers.getLength();
    if (length > 0) {
        std::shared_ptr<Movie>* movieArray = new std::shared_ptr<Movie>[length];

        // Copy items from List to the array for sorting
        for (int i = 0; i < length; ++i) {
            movieArray[i] = moviePointers.get(i);
        }

        // QuickSort using a lambda comparator
        quickSort(movieArray, 0, length - 1, [](const std::shared_ptr<Movie>& a, const std::shared_ptr<Movie>& b) {
            return a->getTitle() < b->getTitle();
            });

        // Display sorted movies
        cout << "Movies for Actor ID " << actorId << " (sorted by title):" << endl;
        for (int i = 0; i < length; ++i) {
            movieArray[i]->print();
        }

        delete[] movieArray; // Clean up the dynamic array
    }
    else {
        cout << "No valid movies to display!" << endl;
    }

}

void displayActorsForMovie(const HashTable<std::shared_ptr<Movie>>& movieTable, const HashTable<std::shared_ptr<Actor>>& actorTable) {
    int movieId;
    cout << "Enter Movie ID: ";
    cin >> movieId;

    // Get the movie object from the hash table
    auto movie = movieTable.get(movieId);
    if (!movie) {
        cout << "Movie not found!" << endl;
        return;
    }

    // Get the list of actor IDs for the movie
    const LinkedList<std::weak_ptr<Actor>>* listOfActors = movie->getListOfActors();


    // Loop through listOfActors(LinkedList) and store in List (Fixed size)

 
    // Sort actors using quicksort based on a chosen attribute (e.g., actor name)
    // Sorting actors by name using quickSort
 

    // Display sorted actors

    

    
    // Implementation
    // Create a custom List to store Actor* pointers
    List<std::shared_ptr<Actor>> actorPointers(listOfActors->getLength());
    for (int i = 0; i < listOfActors->getLength(); ++i) {
        auto weakActor = listOfActors->get(i);
        if (auto actor = weakActor.lock()) { // Lock weak_ptr to get shared_ptr
            actorPointers.add(actor);       // Add shared_ptr<Movie> to the List
        }
    }

    // Sort movies by title
    int length = actorPointers.getLength();
    if (length > 0) {
        std::shared_ptr<Actor>* actorArray = new std::shared_ptr<Actor>[length];

        // Copy items from List to the array for sorting
        for (int i = 0; i < length; ++i) {
            actorArray[i] = actorPointers.get(i);
        }

        // QuickSort using a lambda comparator
        quickSort(actorArray, 0, length - 1, [](const std::shared_ptr<Actor>& a, const std::shared_ptr<Actor>& b) {
            return a->getName() < b->getName();
            });

        // Display sorted movies
        cout << "Actors for Movie ID " << movieId << " (sorted by name):" << endl;
        for (int i = 0; i < length; ++i) {
            actorArray[i]->print();
        }

        delete[] actorArray; // Clean up the dynamic array
    }
    else {
        cout << "No valid actors to display!" << endl;
    }
  
}


// Template partition function
template <typename T, typename Compare>
int partition(std::shared_ptr<T>* arr, int low, int high, Compare comp) {
    auto pivot = arr[high]; // Choose the last element as the pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (comp(arr[j], pivot)) { // Use the comparator to compare elements
            i++;
            std::swap(arr[i], arr[j]); // Swap elements if needed
        }
    }
    std::swap(arr[i + 1], arr[high]); // Place the pivot in its correct position
    return i + 1;
}



// Template quicksort function
template <typename T, typename Compare>
void quickSort(std::shared_ptr<T>* arr, int low, int high, Compare comp) {
    if (low < high) {
        int pi = partition(arr, low, high, comp); // Partition the array

        quickSort(arr, low, pi - 1, comp);  // Sort the elements to the left of the pivot
        quickSort(arr, pi + 1, high, comp); // Sort the elements to the right of the pivot
    }
}



void displayActorRelationship(Graph& actorGraph) {
    int actorId;    
    std::cout << "Insert actor Id: ";
    std::cin >> actorId;

    actorGraph.displayKnownActors(actorId);
}


//void giveRating()