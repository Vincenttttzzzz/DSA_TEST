#pragma once
#include "HashTable.h"
#include "LinkedList.h"
#include "Rating.h"

struct EntityRatings {
    double sumScores = 0.0;          // Sum of all ratings for this entity
    int numRatings = 0;              // Total number of ratings
    LinkedList<Rating> ratings;      // List of all ratings (for reviews)

    void addRating(const Rating& rating) {
        sumScores += rating.getScore();
        numRatings++;
        ratings.add(rating);
    }

	void print() const {
		std::cout << "Number of ratings: " << numRatings << std::endl;
		std::cout << "Sum of scores: " << sumScores << std::endl;
		std::cout << "Ratings: ";
		//ratings.print();
	}
};

class RatingSystem {
private:
    HashTable<EntityRatings*> movieRatings;  // Key: Movie ID
    HashTable<EntityRatings*> actorRatings;  // Key: Actor ID
    double sumAll = 0.0;             // Sum of all ratings globally
    int countAll = 0;                // Total number of ratings globally
    int m = 1000;                    // Minimum votes threshold (

public:
    // Add a rating to a movie
    void addMovieRating(int movieId, const Rating& rating) {
        EntityRatings* er = movieRatings.get(movieId);
        if (!er) {
            er = new EntityRatings();
            movieRatings.add(movieId, er);
        }
        er->addRating(rating);
        sumAll += rating.getScore();
        countAll++;
    }

    // Add a rating to an actor
    void addActorRating(int actorId, const Rating& rating) {
        EntityRatings* er = actorRatings.get(actorId);
        if (!er) {
            er = new EntityRatings();
            actorRatings.add(actorId, er);
        }
        er->addRating(rating);
        sumAll += rating.getScore();
        countAll++;
    }

    // Calculate Bayesian average for a movie
    double getMovieBayesianAverage(int movieId) const {
        const EntityRatings* er = movieRatings.get(movieId);
        if (!er || er->numRatings == 0) {
            return getGlobalAverage(); // Fallback to global average
        }
        double R = er->sumScores / er->numRatings;
        return calculateBayesianAverage(R, er->numRatings);
    }

    // Calculate Bayesian average for an actor
    double getActorBayesianAverage(int actorId) const {
        const EntityRatings* er = actorRatings.get(actorId);
        if (!er || er->numRatings == 0) {
            return getGlobalAverage(); // Fallback to global average
        }
        double R = er->sumScores / er->numRatings;
        return calculateBayesianAverage(R, er->numRatings);
    }

    // Retrieve reviews for a movie
    const LinkedList<Rating>& getMovieReviews(int movieId) const {
        const EntityRatings* er = movieRatings.get(movieId);
        static LinkedList<Rating> empty;
        return er ? er->ratings : empty;
    }

    // Set the minimum votes threshold (m)
    void setMinimumVotesThreshold(int m) { this->m = m; }

private:
    // Calculate the global average (C)
    double getGlobalAverage() const {
        if (countAll == 0) return 0.0; // Default if no ratings exist
        return sumAll / countAll;
    }

    // True Bayesian estimate formula: (R*v + C*m) / (v + m)
    double calculateBayesianAverage(double R, int v) const {
        double C = getGlobalAverage();
        return (R * v + C * m) / (v + m);
    }
};