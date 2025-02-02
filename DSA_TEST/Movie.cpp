#include "Movie.h"
#include "Actor.h"
#include <iostream>
using namespace std;

Movie::Movie() {};

Movie::Movie(int MovieID, string Title, string Plot, int Year) {
	movieID = MovieID;
	title = Title;
	plot = Plot;
	year = Year;
	listOfActors = new LinkedList<std::weak_ptr<Actor>>();
}


// Implementation of Getters and Setters
int Movie::getMovieID() const { return movieID; }
string Movie::getTitle() const { return title; }
string Movie::getPlot() const { return plot; }
int Movie::getYear() const { return year; }
LinkedList<std::weak_ptr<Actor>>* Movie::getListOfActors() const { return listOfActors; }

void Movie::setMovieID(int newMovieID) { movieID = newMovieID; }
void Movie::setTitle(const string& newTitle) { title = newTitle; }
void Movie::setPlot(const string& newPlot) { plot = newPlot; }
void Movie::setYear(int newYear) { year = newYear; }
//void Movie::setListOfActors(LinkedList*& newListOfActors) { listOfActors = newListOfActors; }


void Movie::print() {
	cout << "Movie ID: " << movieID << endl;
	cout << "Title: " << title << endl;
	cout << "Plot: " << plot << endl;
	cout << "Year: " << year << endl;
	cout << endl;

}

//friend ostream& operator<<(ostream& os, const Movie& movie) {
//	os << "MovieID: " << movie.movieID
//		<< ", Title: " << movie.title
//		<< ", Year: " << movie.releaseYear
//		<< ", Plot: " << movie.plot;
//	return os;
//}

void Movie::addActor(const std::weak_ptr<Actor>& actor) {
	listOfActors->add(actor);
}