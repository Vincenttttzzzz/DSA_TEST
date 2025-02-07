#include "Movie.h"
#include "Actor.h"
#include <iostream>
using namespace std;

Movie::Movie() : movieID(0), title(""), plot(""), year(0) {
    // listOfActors is default constructed automatically
}

Movie::Movie(int MovieID, string Title, string Plot, int Year) {
    movieID = MovieID;
    title = Title;
    plot = Plot;
    year = Year;
    // listOfActors is default constructed
}

// Getters
int Movie::getMovieID() const { return movieID; }
string Movie::getTitle() const { return title; }
string Movie::getPlot() const { return plot; }
int Movie::getYear() const { return year; }
vectorClass<std::weak_ptr<Actor>>& Movie::getListOfActors() {
    return listOfActors;
}

// Setters
void Movie::setMovieID(int newMovieID) { movieID = newMovieID; }
void Movie::setTitle(const string& newTitle) { title = newTitle; }
void Movie::setPlot(const string& newPlot) { plot = newPlot; }
void Movie::setYear(int newReleaseYear) { year = newReleaseYear; }

void Movie::print() {
    cout << "Movie ID: " << movieID << endl;
    cout << "Title: " << title << endl;
    cout << "Plot: " << plot << endl;
    cout << "Year: " << year << endl;
    cout << endl;
}

// Add an actor: simply push the weak pointer into the vector
void Movie::addActor(const std::weak_ptr<Actor>& actor) {
    listOfActors.push(actor);
}
