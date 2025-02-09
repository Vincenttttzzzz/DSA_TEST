#pragma once
#include <string>
#include <iostream>
#include "vector.h"         // Your custom vector implementation (std::vector)
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
    // Use std::vector to store a dynamic array of weak pointers to Actor
    std::vector<std::weak_ptr<Actor>> listOfActors;

public:
    // Default Constructor
    Movie();
    Movie(int movieID, const string& title, const string& plot, int year);

    // Getters
    int getMovieID() const;
    string getTitle() const;
    string getPlot() const;
    int getYear() const;
    // Provide both non-const and const versions for accessing the actor list.
    std::vector<weak_ptr<Actor>>& getListOfActors();

    const std::vector<weak_ptr<Actor>>& getListOfActors() const;

    // Setters
    void setMovieID(int newMovieID);
    void setTitle(const string& newTitle);
    void setPlot(const string& newPlot);
    void setYear(int newReleaseYear);

    void print() const;
    friend ostream& operator<<(ostream& os, const Movie& movie);

    // Add an actor to this movie
    void addActor(const std::weak_ptr<Actor>& actor);

    // Delegate rating operations to RatingSystem
    void addRating(const Rating& rating, RatingSystem& ratingSystem);
    double getBayesianAverage(const RatingSystem& ratingSystem) const;
};

// #pragma once
//#include <string>
//#include <iostream>
//#include "vector.h"         // Your custom vector implementation (std::vector)
//#include "Actor.h"
//#include "Rating.h"
//#include "RatingSystem.h"
//#include "LinkedList.h"
//
//using namespace std;
//
//class Movie {
//
//private:
//    int movieID;
//    string title;
//    string plot;
//    int year;
//    // Use std::vector to store a dynamic array of weak pointers to Actor
//    std::vector<std::weak_ptr<Actor>> listOfActors;
//
//public:
//    // Default Constructor
//    Movie();
//
//    Movie(int, string, string, int);
//
//    // Getters
//    int getMovieID() const;
//    string getTitle() const;
//    string getPlot() const;
//    int getYear() const;
//    // Return reference to the std::vector of weak pointers
//    std::vector<std::weak_ptr<Actor>>* getListOfActors();
//
//    // Setters
//    void setMovieID(int newMovieID);
//    void setTitle(const string& newTitle);
//    void setPlot(const string& newPlot);
//    void setYear(int newReleaseYear);
//
//    void print();
//    friend ostream& operator<<(ostream& os, const Movie& movie) {
//        os << "MovieID: " << movie.movieID
//            << ", Title: " << movie.title
//            << ", Year: " << movie.year
//            << ", Plot: " << movie.plot;
//        return os;
//    }
//
//    // Add an actor to this movie by pushing the actor's weak pointer into the vector
//    void addActor(const std::weak_ptr<Actor>& actor);
//
//    // Delegate rating operations to RatingSystem
//    void addRating(const Rating& rating, RatingSystem& ratingSystem) {
//        ratingSystem.addMovieRating(movieID, rating);
//    }
//
//    double getBayesianAverage(const RatingSystem& ratingSystem) const {
//        return ratingSystem.getMovieBayesianAverage(movieID);
//    }
//
//    // Assuming RatingSystem.getMovieReviews returns a std::vector<Rating>
//    const LinkedList<Rating>& getReviews(const RatingSystem& ratingSystem) const {
//        return ratingSystem.getMovieReviews(movieID);
//    }
//};
