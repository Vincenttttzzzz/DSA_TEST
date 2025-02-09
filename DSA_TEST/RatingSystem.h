#ifndef RATINGSYSTEM_H
#define RATINGSYSTEM_H

#include "HashTable.h"    // Assumes HashTable is a template class for separate chaining.
#include "LinkedList.h"   // Assumes LinkedList is a singly linked list template.
#include "Rating.h"       // The Rating class definition.
#include <iostream>

struct EntityRatings {
    double sumScores = 0.0;          // Sum of all ratings for this entity.
    int numRatings = 0;              // Total number of ratings.
    LinkedList<Rating> ratings;      // List of all ratings (for reviews).

    // Add a rating to this entity.
    void addRating(const Rating& rating);

    // Print the ratings information.
    void print() const;
};

class RatingSystem {
private:
    // Hash tables mapping entity IDs to their ratings.
    HashTable<EntityRatings*> movieRatings;  // Key: Movie ID.
    HashTable<EntityRatings*> actorRatings;  // Key: Actor ID.

    double sumAll = 0.0;             // Sum of all ratings globally.
    int countAll = 0;                // Total number of ratings globally.
    int m = 1000;                    // Minimum votes threshold.

public:
    // Add a rating to a movie.
    void addMovieRating(int movieId, const Rating& rating);

    // Add a rating to an actor.
    void addActorRating(int actorId, const Rating& rating);

    // Calculate the Bayesian average for a movie.
    double getMovieBayesianAverage(int movieId) const;

    // Calculate the Bayesian average for an actor.
    double getActorBayesianAverage(int actorId) const;

    // Set the minimum votes threshold.
    void setMinimumVotesThreshold(int m);

    // Calculate the global average (C).
    double getGlobalAverage() const;

    // Calculate the Bayesian average using the formula: (R*v + C*m) / (v + m)
    double calculateBayesianAverage(double R, int v) const;
};

#endif // RATINGSYSTEM_H
