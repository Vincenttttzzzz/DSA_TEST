#pragma once
#include <iostream>
#include <string>
#include "Rating.h"
#include "RatingSystem.h"

using namespace std;

class Actor {

private:
    int actorID;
    string name;
    int year;

public:

    // Default Constructor
    Actor();

    Actor(int, string, int);

    // Getters
    int getActorID() const;
    string getName() const;
    int getYear() const;

    // Setters
    void setName(const string& newName);
    void setYear(int newBirth);


    void print();
    friend ostream& operator<<(ostream& os, const Actor& actor) {
        os << "ActorID: " << actor.actorID
            << ", Name: " << actor.name
            << ", Birth Year: " << actor.year;
        return os;
    }

    void addRating(const Rating& rating, RatingSystem& ratingSystem) {
        ratingSystem.addActorRating(actorID, rating);
    }

    double getBayesianAverage(const RatingSystem& ratingSystem) const {
        return ratingSystem.getActorBayesianAverage(actorID);
    }

};
