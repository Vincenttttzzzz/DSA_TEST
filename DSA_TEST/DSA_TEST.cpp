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
#include "Graph.h"
#include "RatingSystem.h"
#include "AVLTree.h"

void readActorCSV(const std::string& csvName, Graph& actorMovieGraph, AVLTree<std::weak_ptr<Actor>>& tree);
void readMovieCSV(const std::string& csvName, Graph& actorMovieGraph, AVLTree<std::weak_ptr<Movie>>& tree);
void readCastCSV(const std::string& csvName, Graph& actorMovieGraph);

bool insertActor(Graph& actorMovieGraph, AVLTree<std::weak_ptr<Actor>>& tree, int id, string name, int year);
bool insertMovie(Graph& actorMovieGraph, AVLTree<std::weak_ptr<Movie>>& tree, int id, string title, string plot, int year);
bool insertActorToMovie(Graph& actorMovieGraph, int actorId, int movieId);

void addNewActor(Graph& actorMovieGraph, AVLTree<std::weak_ptr<Actor>>& tree);
void addNewMovie(Graph& actorMovieGraph, AVLTree<std::weak_ptr<Movie>>& tree);
void addActorToMovie(Graph& actorMovieGraph);
void updateActor(Graph& actorMovieGraph);
void updateMovie(Graph& actorMovieGraph);

void displayMenu();

void displayActorByYear(const AVLTree<std::weak_ptr<Actor>>& actorTree, const Graph& actorMovieGraph);
void displayMovieByYear(const AVLTree<std::weak_ptr<Movie>>& movieTree, const Graph& actorMovieGraph);
void displayMoviesForActor(const Graph& actorMovieGraph);
void displayActorsForMovie(const Graph& actorMovieGraph);


template <typename T, typename Compare>
int partition(std::shared_ptr<T>* arr, int low, int high, Compare comp);
// Template quicksort function
template <typename T, typename Compare>
void quickSort(std::shared_ptr<T>* arr, int low, int high, Compare comp);

void displayActorRelationship(Graph& actorGraph);
void giveRating(RatingSystem& ratingSystem, Graph& actorMovieGraph);
void displayActorOrMovie(RatingSystem& ratingSystem, Graph& actorMovieGraph);

template <typename T, typename Comparator>
void merge(T arr[], int left, int mid, int right, Comparator comp);
template <typename T, typename Comparator>
void mergeSort(T arr[], int left, int right, Comparator comp);

vector<string> splitLines(const string& str) {
    vector<string> lines;
    stringstream ss(str);
    string line;
    while (getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

void displayArtAndTitle() {
    string asciiArt = R"(
@@@@@@@@@@@@@@@@@@@@@@@@@#-+**+-*@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@%-#++..++#=*@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@%-::+@@=%+..:...+%=@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@-=:..:=++#..:.....++#@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@%--....=-=%+..:...+%=@@@@@@@@@@%@@@@@
@@@@@@@@@@@@@*..:...::::.*%#:.#%#.::+@@@@@@=.=@@@@@
@@@@@@@@@@@*+-.:::..::::::.:--:.:::::-----.::=@@@@@
@@@@@@@@@@@=...:::::::::::::::::::::......:::=@@@@@
@@@@@@@@@@@=...:::::::::::::::::::::......:::=@@@@@
@@@@@@@@@@@=...:::::::::::::::::::::.::::.:::=@@@@@
@@@@@@@@@@@*+-.:::::::::::::::::::::+@@@@@%-.=@@@@@
@@@@@@@@@@@@@*......................+@@@@@@@@#@@@@@
@@@@@@@@@@@@@@@@@@@+=:===-:+*@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@=###+*@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@++**=@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@-....*@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@#:.....%@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@..*:.+:-@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@=.+@:.@:.*@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@#::@@: @@..@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@:.#@@:.@@*.-@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@-.+@@@:.@@@-.#@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@#:-@@@@::@@@@..@@@@@@@@@@@@@@@@@@@@
    )";

    string title = R"(




 ___ __  __ ____  ____  
|_ _|  \/  | __ )| __ ) 
 | || |\/| |  _ \|  _ \ 
 | || |  | | |_) | |_) |
|___|_|  |_|____/|____/   

 MOVIES & TV SHOWS
)";

    vector<string> artLines = splitLines(asciiArt);
    vector<string> titleLines = splitLines(title);

    // Max lines to iterate over
    size_t maxLines = max(artLines.size(), titleLines.size());

    for (size_t i = 0; i < maxLines; i++) {
        // Print art line
        if (i < artLines.size()) {
            cout << artLines[i];
        }
        else {
            cout << string(60, ' '); // Blank space if no art line
        }

        // Padding between columns
        cout << "    ";

        // Print title line
        if (i < titleLines.size()) {
            cout << titleLines[i];
        }

        cout << endl;
    }
}

int main()
{
    //HashTable<std::shared_ptr<Actor>> actorTable = HashTable<std::shared_ptr<Actor>>();

    //Graph actorToActor(false);
	Graph actorMovieGraph = Graph();

    AVLTree<std::weak_ptr<Actor>> actorAVL = AVLTree<std::weak_ptr<Actor>>();
    AVLTree<std::weak_ptr<Movie>> movieAVL = AVLTree<std::weak_ptr<Movie>>();

    RatingSystem ratingSystem;

    readActorCSV("actors.csv", actorMovieGraph, actorAVL);
    readMovieCSV("movies.csv", actorMovieGraph, movieAVL);
    readCastCSV("cast.csv", actorMovieGraph);


    //readActorCSV("people2.csv", actorMovieGraph, actorAVL);
    //readMovieCSV("movies2.csv", actorMovieGraph, movieAVL);
    //readCastCSV("cast2.csv", actorMovieGraph);

    //readActorCSV("actors3.csv", actorMovieGraph, actorAVL);
    //readMovieCSV("movies3.csv", actorMovieGraph, movieAVL);
    //readCastCSV("cast3.csv", actorMovieGraph);

    std::string opt = "";
    //displayArtAndTitle();
    while (opt != "0")
    {
        displayMenu();
        std::cout << "Enter your choice: ";
        getline(cin, opt);  // Read the entire line of input.

        if (opt == "1") {
            addNewActor(actorMovieGraph, actorAVL);
        }
        else if (opt == "2") {
            addNewMovie(actorMovieGraph, movieAVL);
        }
        else if (opt == "3") {
            addActorToMovie(actorMovieGraph);
        }
        else if (opt == "4") {
            std::string className;

            std::cout << "Choose which one to update (Actor/Movie): ";
            std::cin >> className;

            if (className == "Actor") {
                updateActor(actorMovieGraph);
            }
            else if (className == "Movie") {
                updateMovie(actorMovieGraph);
            }
            else {
                std::cout << "Invalid choice! Please choose either Actor or Movie." << std::endl;
            }
        }
        else if (opt == "5") {
            displayActorByYear(actorAVL, actorMovieGraph);
        }
        else if (opt == "6") {
            displayMovieByYear(movieAVL, actorMovieGraph);
        }
        else if (opt == "7") {
            displayMoviesForActor(actorMovieGraph);
        }
        else if (opt == "8") {
            displayActorsForMovie(actorMovieGraph);
        }
        else if (opt == "9") {
            displayActorRelationship(actorMovieGraph);
        }
        else if (opt == "10") {
            giveRating(ratingSystem, actorMovieGraph);
        }
        else if (opt == "11") {
            displayActorOrMovie(ratingSystem, actorMovieGraph);
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


std::string parseQuotedField(std::stringstream& ss);
void readActorCSV(const std::string& csvName, Graph& actorMovieGraph, AVLTree<std::weak_ptr<Actor>>& tree) {
    std::ifstream file(csvName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }
    std::cout << "Storing Actor Data..." << std::endl;
    std::string line;
    // Skip the header line
    std::getline(file, line);
    while (std::getline(file, line)) {
		//std::cout << line << std::endl;
        std::stringstream ss(line);
        std::string idStr, name, yearStr;

        // Read ID
        if (!std::getline(ss, idStr, ',')) {
            std::cerr << "Error: Malformed actor line (missing ID): " << line << std::endl;
            continue;
        }

        // Read N   ame with nested quote handling
        name = parseQuotedField(ss);

        // Read birth year (handles empty fields)
        std::getline(ss, yearStr);
        if (!yearStr.empty() && yearStr.back() == ',') {
            yearStr.pop_back(); // Remove trailing comma if present
        }

		//std::cout << idStr << name << yearStr << endl;
        try {
            int id = std::stoi(idStr);
            int birthYear = 0;  // Default value for empty birth year
            if (!yearStr.empty()) {
                birthYear = std::stoi(yearStr);
            }
            insertActor(actorMovieGraph, tree, id, name, birthYear);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: Failed to parse actor data: " << line << std::endl;
        }
    }
    std::cout << "CSV file read successfully!" << std::endl;
}

// Helper function to parse quoted fields with nested quotes
std::string parseQuotedField(std::stringstream& ss) {
    char nextChar = ss.peek();
    std::string name;

    if (nextChar == '"') {
        ss.get(); // Consume opening quote
        // Only do complex parsing if we detect an inner quote
        if (ss.str().find("\"\"", ss.tellg()) != std::string::npos) {
            std::string temp;
            bool inQuotes = true;

            while (inQuotes && std::getline(ss, temp, '"')) {
                name += temp;

                if (ss.peek() == '"') {
                    ss.get();
                    name += '"';
                }
                else {
                    inQuotes = false;
                }
            }
        }
        else {
            // Fast path for simple quoted names
            std::getline(ss, name, '"');
        }
        ss.get(); // Consume comma
    }
    else {
        std::getline(ss, name, ',');
    }

    return name;
}


void readMovieCSV(const std::string& csvName, Graph& actorMovieGraph, AVLTree<std::weak_ptr<Movie>>& tree) {
    std::ifstream file(csvName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    std::cout << "Storing Movie Data..." << endl;


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
            std::string parsedTitle;
            size_t pos = 1;  // Start after opening quote
            bool inQuotes = true;

            while (inQuotes && pos < line.length()) {
                size_t quotePos = line.find('"', pos);
                if (quotePos == std::string::npos) {
                    std::cerr << "Error: Malformed title field in line: " << line << std::endl;
                    break;
                }

                // Append text up to the quote
                parsedTitle += line.substr(pos, quotePos - pos);

                // Check for escaped quote
                if (quotePos + 1 < line.length() && line[quotePos + 1] == '"') {
                    parsedTitle += '"';
                    pos = quotePos + 2;
                }
                else {
                    title = parsedTitle;
                    // Move past closing quote and comma
                    line = line.substr(quotePos + 2);
                    inQuotes = false;
                }
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
            insertMovie(actorMovieGraph, tree, id, title, plot, releaseYear);
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


void readCastCSV(const std::string& csvName, Graph& actorMovieGraph) {
    std::ifstream file(csvName);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file!" << std::endl;
        return;
    }

    std::cout << "Storing Cast Data..." << endl;

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
            //std::cout << actorIDStr << movieIDStr << endl;

            /*auto actor = actorMovieGraph.actorTable.get(actorID);
            if (!actor) {
                std::cerr << "ERROR: Actor with ID " << actorID << " not found!" << std::endl;
                return;
            }*/

            //std::cout << actor->getName() << endl;


            int movieID = std::stoi(movieIDStr);
            // Retrieve the movie
            /*auto movie = movieTable.get(movieID);
            if (!movie) {
                std::cerr << "ERROR: Movie with ID " << movieID << " not found!" << std::endl;
                return;
            }*/

            //std::cout << movie->getTitle() << endl;
			//std::cout << actorID << movieID << std::endl;
            bool inserted = insertActorToMovie(actorMovieGraph, actorID, movieID);
			if (!inserted) {
				//std::cerr << "Failed to insert actor " << actorID << " to movie " << movieID << std::endl;
			}
        }
        catch (const std::exception& e) {
            //std::cerr << "Error: Failed to parse relationship data: " << line << std::endl;
        }
    }

    std::cout << "CSV file read successfully!" << std::endl;

}



bool insertActor(Graph& actorMovieGraph, AVLTree<std::weak_ptr<Actor>>& tree, int id, string name, int year) {
    // Actor clas
    auto newActor = std::make_shared<Actor>(id, name, year);

    bool inserted = actorMovieGraph.insertNewActor(id, newActor);
	if (!inserted) {
		std::cerr << "ERROR: Actor with ID " << id << " already exists!" << std::endl;
		return false;
	}
    //std::cout << "Insert success: " << inserted << std::endl;

    std::weak_ptr<Actor> weakActor = newActor;

    tree.insert(id, year, weakActor);

	//std::cout << "Actor " << name << " added!" << std::endl;
    return true;

}


bool insertMovie(Graph& actorMovieGraph, AVLTree<std::weak_ptr<Movie>>& tree, int id, string title, string plot, int year) {
    // Actor clas
    auto newMovie = std::make_shared<Movie>(id, title, plot, year);

    bool inserted = actorMovieGraph.insertNewMovie(id, newMovie);
	if (!inserted) {
		std::cerr << "ERROR: Movie with ID " << id << " already exists!" << std::endl;
        return false;
    }

    std::weak_ptr<Movie> weakMovie = newMovie;

    tree.insert(id, year, weakMovie);

	//std::cout << "Movie " << title << " added!" << std::endl;
    return true;

}

bool insertActorToMovie(Graph& actorMovieGraph, int actorId, int movieId) {

	bool insertion = actorMovieGraph.insertActorToMovie(actorId, movieId);

	if (!insertion) {
		//std::cerr << "ERROR: Failed to insert actor " << actorId << " to movie " << movieId << std::endl;
        return false;
    }

	//std::cout << "Actor " << actorId << " added to Movie " << movieId << std::endl;
    return true;

}

// Utility function to safely get integer input
int getIntegerInput(const std::string& prompt) {
    int value;
    bool validInput = false;

    do {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);

        // Try to convert string to integer
        try {
            // Check if the string contains only digits
            if (input.find_first_not_of("0123456789") == std::string::npos) {
                value = std::stoi(input);
                validInput = true;
            }
            else {
                std::cout << "Error: Please enter a valid number.\n";
            }
        }
        catch (const std::invalid_argument&) {
            std::cout << "Error: Please enter a valid number.\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Error: Number is too large.\n";
        }
    } while (!validInput);

    return value;
}

// Utility function to safely get string input
std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    // Clear any leftover newline characters
    std::cin.clear();
    std::getline(std::cin, input);

    // Remove leading and trailing whitespace
    while (!input.empty() && std::isspace(input.front())) {
        input.erase(0, 1);
    }
    while (!input.empty() && std::isspace(input.back())) {
        input.pop_back();
    }

    return input;
}

void addNewActor(Graph& actorMovieGraph, AVLTree<std::weak_ptr<Actor>>& tree) {
    // Get actor details with validation
    int id = getIntegerInput("Actor's ID: ");
    std::string name = getStringInput("Actor's Name: ");

    // Validate name is not empty
    while (name.empty()) {
        std::cout << "Error: Name cannot be empty.\n";
        name = getStringInput("Actor's Name: ");
    }

    int year = getIntegerInput("Actor's Birth Year: ");

    // Validate year is reasonable
    while (year < 1800 || year > 2024) {
        std::cout << "Error: Please enter a valid birth year (1800-2024).\n";
        year = getIntegerInput("Actor's Birth Year: ");
    }

    std::cout << std::endl;
    bool inserted = insertActor(actorMovieGraph, tree, id, name, year);
    if (inserted) {
        std::cout << "New Actor added!" << std::endl;
        return;
    }
	std::cout << "Failed to add Actor." << std::endl;
}

void addNewMovie(Graph& actorMovieGraph, AVLTree<std::weak_ptr<Movie>>& tree) {
    // Get movie details with validation
    int id = getIntegerInput("Movie's ID: ");
    std::string title = getStringInput("Movie's Title: ");

    // Validate title is not empty
    while (title.empty()) {
        std::cout << "Error: Title cannot be empty.\n";
        title = getStringInput("Movie's Title: ");
    }

    std::string plot = getStringInput("Movie's Plot: ");

    int year = getIntegerInput("Movie's Release Year: ");

    // Validate year is reasonable
    while (year < 1888 || year > 2024) {  // 1888 was the year of the first film
        std::cout << "Error: Please enter a valid release year (1888-2024).\n";
        year = getIntegerInput("Movie's Release Year: ");
    }

    bool inserted = insertMovie(actorMovieGraph, tree, id, title, plot, year);
    if (inserted) {
        std::cout << "New Movie added!" << std::endl;
        return;
    }
    std::cout << "Failed to add Movie." << std::endl;
}

void addActorToMovie(Graph& actorMovieGraph) {
    int actorId = getIntegerInput("Actor Id: ");

    int movieId = getIntegerInput("Movie Id: ");

    bool inserted = insertActorToMovie(actorMovieGraph, actorId, movieId);
	if (inserted) {
		std::cout << "Actor added to Movie!" << std::endl;
		return;
	}
	std::cout << "Failed to add Actor to Movie." << std::endl;
}

void updateActor(Graph& actorMovieGraph) {
    // Get actor ID using the safe integer input function.
    int actorId = getIntegerInput("Which Actor(Id) do you want to update: ");
    std::cout << std::endl;

    // Get the actor as a weak pointer from your graph.
    auto actor = actorMovieGraph.getActor(actorId);
    if (!actor) {
        std::cout << "Actor not found or has expired." << std::endl;
        return;
    }

    actor->print();
    std::cout << std::endl;

    // Get the attribute to update using the safe string input function.
    std::string attribute = getStringInput("Which attribute do you want to update: ");

    // Convert the string to lowercase.
    for (char& c : attribute) {
        c = std::tolower(c);
    }

    bool updated = false;
    if (attribute == "id") {
        std::cout << "Id can't be changed." << std::endl;
        return;
    }
    else if (attribute == "name") {
        // Get updated name safely.
        std::string name = getStringInput("Updated Name: ");
        actor->setName(name);
        updated = true;
    }
    else if (attribute == "year") {
        // Get updated birth year safely.
        int birth = getIntegerInput("Updated Birth Year: ");
        actor->setYear(birth);
        updated = true;
    }
    else {
        std::cout << "Invalid attribute." << std::endl;
    }

    if (updated) {
        std::cout << "Newly Updated Actor Class: " << std::endl;
        actor->print();
        std::cout << std::endl;
    }
}

void updateMovie(Graph& actorMovieGraph) {
    // Get movie ID using the safe integer input function.
    int movieId = getIntegerInput("Which Movie(Id) do you want to update: ");
    std::cout << std::endl;

    auto movie = actorMovieGraph.getMovie(movieId);
    if (!movie) {
        std::cout << "Movie not found or has expired." << std::endl;
        return;
    }

    movie->print();

    // Get the attribute to update using the safe string input function.
    std::string attribute = getStringInput("Which attribute do you want to update: ");

    // Convert the string to lowercase.
    for (char& c : attribute) {
        c = std::tolower(c);
    }

    bool updated = false;
    if (attribute == "id") {
        std::cout << "Id can't be changed." << std::endl;
        return;
    }
    else if (attribute == "title") {
        // Get updated title safely.
        std::string title = getStringInput("Updated Title: ");
        movie->setTitle(title);
        updated = true;
    }
    else if (attribute == "plot") {
        // Get updated plot safely.
        std::string plot = getStringInput("Updated Plot: ");
        movie->setPlot(plot);
        updated = true;
    }
    else if (attribute == "year") {
        // Get updated release year safely.
        int year = getIntegerInput("Updated Release Year: ");
        movie->setYear(year);
        updated = true;
    }
    else {
        std::cout << "Invalid attribute." << std::endl;
    }

    if (updated) {
        std::cout << "Newly Updated Movie Class: " << std::endl;
        movie->print();
        std::cout << std::endl;
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
    std::cout << "10. Rate an actor or a movie" << std::endl;
    std::cout << "11. Display an Actor/Movie" << std::endl;
    std::cout << "0. Exit" << std::endl;

}

void displayActorByYear(const AVLTree<std::weak_ptr<Actor>>& actorTree, const Graph& actorMovieGraph) {
    int year1, year2;

    std::cout << "year1: ";
    std::cin >> year1;

    std::cout << "year2: ";
    std::cin >> year2;

    // Use the callback to process actors within the range
    //actorTree.displayByRange(year1, year2, [&table](int actorId) {
    //    auto actor = table.get(actorId);
    //    if (actor) {
    //        actor->print(); // Print actor details
    //    }
    //    else {
    //        std::cout << "Actor ID " << actorId << " not found!" << std::endl;
    //    }
    //});

    actorTree.rangeQuery(year1, year2, [&](std::weak_ptr<Actor> actor) {
        if (auto a = actor.lock()) {
            std::cout << a->getName() << " (Age: " << a->getYear() << ")\n";
        }
    });

}

void displayMovieByYear(const AVLTree<std::weak_ptr<Movie>>& movieTree, const Graph& actorMovieGraph) {
    int year;

    std::cout << "year: ";
    std::cin >> year;

    // Use the callback to process actors within the range
    //movieTree.displayByRange(year - 3, year, [&table](int movieId) {
    //    auto actor = table.get(movieId);
    //    if (actor) {
    //        actor->print(); // Print actor details
    //    }
    //    else {
    //        std::cout << "Actor ID " << movieId << " not found!" << std::endl;
    //    }
    //});

    movieTree.rangeQuery(year-3, year, [&](std::weak_ptr<Movie> movie) {
        if (auto m = movie.lock()) {
            std::cout << m->getTitle() << " (Year: " << m->getYear() << ")\n";
        }
    });
}

// Function to display movies for an actor using merge sort.
void displayMoviesForActor(const Graph& actorMovieGraph) {
    int actorId;
    cout << "Enter Actor ID: ";
    cin >> actorId;

    LinkedList<std::weak_ptr<Movie>>* listOfMovies = actorMovieGraph.getMovies(actorId);
    if (!listOfMovies || listOfMovies->getLength() == 0) {
        cout << "No movies found for Actor ID: " << actorId << endl << endl;
        return;
    }

    std::vector<std::shared_ptr<Movie>> movieVector;
    movieVector.reserve(listOfMovies->getLength());

    for (int i = 0; i < listOfMovies->getLength(); ++i) {
        if (auto movie = listOfMovies->get(i).lock()) {
            movieVector.push_back(movie);
        }
    }

    if (movieVector.empty()) {
        cout << "No valid movies to display!" << endl;
        return;
    }

    mergeSort(movieVector.data(), 0, movieVector.size() - 1,
        [](const auto& a, const auto& b) { return a->getTitle() < b->getTitle(); });

    cout << "Movies for Actor ID " << actorId << " (sorted by title):" << endl;
    for (const auto& movie : movieVector) {
        movie->print();
    }
    cout << endl;
}


void displayActorsForMovie(const Graph& actorMovieGraph) {
    int movieId;
    cout << "Enter Movie ID: ";
    cin >> movieId;

    auto movie = actorMovieGraph.getMovie(movieId);
    if (!movie) {
        cout << "Movie not found!" << endl;
        return;
    }

    const vectorClass<std::weak_ptr<Actor>>& listOfActors = movie->getListOfActors();
    if (listOfActors.size() == 0) {
        cout << "No valid actors to display!" << endl;
        return;
    }

    // Build vector of valid actors
    vectorClass<std::shared_ptr<Actor>> actorVector;
    for (int i = 0; i < listOfActors.size(); ++i) {
        if (auto actor = listOfActors.get(i).lock()) {
            actorVector.push(actor);
        }
    }

    if (actorVector.size() == 0) {
        cout << "No valid actors to display!" << endl;
        return;
    }

    // Convert vector to array for quicksort
    std::shared_ptr<Actor>* actorArray = actorVector.data();
    quickSort(actorArray, 0, actorVector.size() - 1,
        [](const std::shared_ptr<Actor>& a, const std::shared_ptr<Actor>& b) {
            return a->getName() < b->getName();
        }); 

    cout << "Actors for Movie ID " << movieId << " (sorted by name):" << endl;
    for (int i = 0; i < actorVector.size(); ++i) {
        actorArray[i]->print();
    }
    cout << endl;
}



// Template partition function
template <typename T, typename Compare>
int partition(std::shared_ptr<T>* arr, int low, int high, Compare comp) {
    // Choose middle element as pivot
    int mid = low + (high - low) / 2;
    auto pivot = arr[mid];
    std::swap(arr[mid], arr[high]);

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
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

// Merge function used by mergeSort.
template <typename T, typename Comparator>
void merge(T arr[], int left, int mid, int right, Comparator comp) {
    // Calculate sizes for our temporary arrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays - note we're using T directly now
    std::vector<T> leftArr(n1);
    std::vector<T> rightArr(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // Standard merge process
    int i = 0;      // Index for left array
    int j = 0;      // Index for right array
    int k = left;   // Index for merged array

    // Compare and merge back into original array
    while (i < n1 && j < n2) {
        if (comp(leftArr[i], rightArr[j])) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements from left array, if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements from right array, if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// The mergeSort function remains the same
template <typename T, typename Comparator>
void mergeSort(T arr[], int left, int right, Comparator comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comp);
        mergeSort(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }
}

void displayActorRelationship(Graph& actorMovieGraph) {
    int actorId;
    std::cout << "Insert actor Id: ";
    std::cin >> actorId;

    auto actor = actorMovieGraph.getActor(actorId);
	if (!actor) {
		std::cout << "Actor not found or has expired." << std::endl;
		return;
	}

    actorMovieGraph.displayKnownActors(actor);
}

void giveRating(RatingSystem& ratingSystem, Graph& actorMovieGraph) {
    std::string opt;
    std::cout << "Do you want to rate Actor/Movie: ";
    std::cin >> opt;

    int id;
    std::cout << "Enter the id: ";
    std::cin >> id;

    int num;
    std::string review;

    std::cout << "Give a rating (1-5): ";
    std::cin >> num;
    

    if (opt == "Movie") {
        auto movie = actorMovieGraph.getMovie(id);

        if (!movie) {
            std::cout << "Movie not found or has expired." << std::endl;
            return;
        }

        Rating rating(num, std::time(0));
        movie->addRating(rating, ratingSystem);
    }
    else if (opt == "Actor") {
        auto actor = actorMovieGraph.getActor(id);

        if (!actor) {
            std::cout << "Actor not found or has expired." << std::endl;
            return;
        }

        Rating rating(num, std::time(0));
        actor->addRating(rating, ratingSystem);
    }
    else {
        std::cout << "Invalid input." << endl;
    }
}

void displayActorOrMovie(RatingSystem& ratingSystem, Graph& actorMovieGraph) {
    std::string opt;
    std::cout << "Do you want to display Actor/Movie: ";
    std::cin >> opt;

    int id;
    std::cout << "Enter the id: ";
    std::cin >> id;

    if (opt == "Movie") {
        auto movie = actorMovieGraph.getMovie(id);

        if (!movie) {
            std::cout << "Movie not found or has expired." << std::endl;
            return;
        }
        movie->print();
        std::cout << "Rating: " << movie->getBayesianAverage(ratingSystem) << endl;
    }
    else if (opt == "Actor") {
        auto actor = actorMovieGraph.getActor(id);
                    
        if (!actor) {
            std::cout << "Actor not found or has expired." << std::endl;
            return;
        }
        actor->print();
        std::cout << "Rating: " << actor->getBayesianAverage(ratingSystem) << endl;
    }
    else {
        std::cout << "Invalid input." << endl;
    }
}
