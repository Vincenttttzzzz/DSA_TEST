#include "Movie.h"
#include "Actor.h"
#include <iostream>

Movie::Movie() : movieID(0), title(""), plot(""), year(0) {
	// listOfActors is default constructed automatically
}

Movie::Movie(int MovieID, const string& Title, const string& Plot, int Year)
    : movieID(MovieID), title(Title), plot(Plot), year(Year) {
	// listOfActors is default constructed automatically
}

// Getters
int Movie::getMovieID() const { return movieID; }
string Movie::getTitle() const { return title; }
string Movie::getPlot() const { return plot; }
int Movie::getYear() const { return year; }

// Provide both non-const and const versions for accessing the actor list.
std::vector<weak_ptr<Actor>>& Movie::getListOfActors() {
    return listOfActors;
}
const std::vector<weak_ptr<Actor>>& Movie::getListOfActors() const {
    return listOfActors;
}
// Setters
void Movie::setMovieID(int newMovieID) { movieID = newMovieID; }
void Movie::setTitle(const string& newTitle) { title = newTitle; }
void Movie::setPlot(const string& newPlot) { plot = newPlot; }
void Movie::setYear(int newReleaseYear) { year = newReleaseYear; }

void Movie::print() const {
    cout << "Movie ID: " << movieID << endl;
    cout << "Title: " << title << endl;
    cout << "Plot: " << plot << endl;
    cout << "Year: " << year << endl;
    cout << endl;
}

ostream& operator<<(ostream& os, const Movie& movie) {
    os << "MovieID: " << movie.movieID
       << ", Title: " << movie.title
       << ", Year: " << movie.year
       << ", Plot: " << movie.plot;
    return os;
}

// Add an actor: simply push the weak pointer into the vector
void Movie::addActor(const std::weak_ptr<Actor>& actor) {
    listOfActors.push_back(actor);
}

// Delegate rating operations to RatingSystem
void Movie::addRating(const Rating& rating, RatingSystem& ratingSystem) {
    ratingSystem.addMovieRating(movieID, rating);
}

double Movie::getBayesianAverage(const RatingSystem& ratingSystem) const {
    return ratingSystem.getMovieBayesianAverage(movieID);
}

