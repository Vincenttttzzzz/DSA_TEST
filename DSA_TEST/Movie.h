#pragma once
#include <string>
#include <iostream>
#include "vector.h"         // Your custom vector implementation (vectorClass)
#include "Actor.h"
#include "Rating.h"
#include "RatingSystem.h"
#include "LinkedList.h"

using namespace std;

class Movie {

private:
    int movieID;
    string title;
    string plot;
    int year;
    // Use vectorClass to store a dynamic array of weak pointers to Actor
    vectorClass<std::weak_ptr<Actor>> listOfActors;

public:
    // Default Constructor
    Movie();

    Movie(int, string, string, int);

    // Getters
    int getMovieID() const;
    string getTitle() const;
    string getPlot() const;
    int getYear() const;
    // Return reference to the vectorClass of weak pointers
    vectorClass<std::weak_ptr<Actor>>& getListOfActors();

    // Setters
    void setMovieID(int newMovieID);
    void setTitle(const string& newTitle);
    void setPlot(const string& newPlot);
    void setYear(int newReleaseYear);

    void print();
    friend ostream& operator<<(ostream& os, const Movie& movie) {
        os << "MovieID: " << movie.movieID
            << ", Title: " << movie.title
            << ", Year: " << movie.year
            << ", Plot: " << movie.plot;
        return os;
    }

    // Add an actor to this movie by pushing the actor's weak pointer into the vector
    void addActor(const std::weak_ptr<Actor>& actor);

    // Delegate rating operations to RatingSystem
    void addRating(const Rating& rating, RatingSystem& ratingSystem) {
        ratingSystem.addMovieRating(movieID, rating);
    }

    double getBayesianAverage(const RatingSystem& ratingSystem) const {
        return ratingSystem.getMovieBayesianAverage(movieID);
    }

    // Assuming RatingSystem.getMovieReviews returns a vectorClass<Rating>
    const LinkedList<Rating>& getReviews(const RatingSystem& ratingSystem) const {
        return ratingSystem.getMovieReviews(movieID);
    }
};
