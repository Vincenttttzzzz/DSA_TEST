#pragma once
#include <string>
#include <iostream>
#include "LinkedList.h"
#include "Actor.h"
using namespace std;

class Movie {

private:
    int movieID;
    string title;
    string plot;
    int year;
    LinkedList<std::weak_ptr<Actor>>* listOfActors;

public:

    // Default Constructor
    Movie();

    Movie(int, string, string, int);

    // Getters
    int getMovieID() const;
    string getTitle() const;
    string getPlot() const;
    int getYear() const;
    LinkedList<std::weak_ptr<Actor>>* getListOfActors() const;

    // Setters
    void setMovieID(int newMovieID);
    void setTitle(const string& newTitle);
    void setPlot(const string& newPlot);
    void setYear(int newReleaseYear);
    void setListOfActors(const LinkedList<std::weak_ptr<Actor>>*& newListOfActors);

    void print();
    friend ostream& operator<<(ostream& os, const Movie& movie) {
        os << "MovieID: " << movie.movieID
            << ", Title: " << movie.title
            << ", Year: " << movie.year
            << ", Plot: " << movie.plot;
        return os;
    }
    void addActor(const std::weak_ptr<Actor>& actor);
};
