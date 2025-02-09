#include "RatingSystem.h"
#include <iostream>
using namespace std;

// ---------- EntityRatings Member Functions ----------

void EntityRatings::addRating(const Rating& rating) {
    sumScores += rating.getScore();
    numRatings++;
    ratings.add(rating);  // Adds the rating to the LinkedList.
}

void EntityRatings::print() const {
    cout << "Sum of Scores: " << sumScores << ", Number of Ratings: " << numRatings << endl;
    cout << "Ratings: ";
}

// ---------- RatingSystem Member Functions ----------

void RatingSystem::addMovieRating(int movieId, const Rating& rating) {
    // Retrieve the ratings for the movie.
    EntityRatings* er = movieRatings.get(movieId);
    if (!er) {
        er = new EntityRatings();
        movieRatings.add(movieId, er);
    }
    er->addRating(rating);
    sumAll += rating.getScore();
    countAll++;
}

void RatingSystem::addActorRating(int actorId, const Rating& rating) {
    // Retrieve the ratings for the actor.
    EntityRatings* er = actorRatings.get(actorId);
    if (!er) {
        er = new EntityRatings();
        actorRatings.add(actorId, er);
    }
    er->addRating(rating);
    sumAll += rating.getScore();
    countAll++;
}

double RatingSystem::getMovieBayesianAverage(int movieId) const {
    const EntityRatings* er = movieRatings.get(movieId);
    if (!er || er->numRatings == 0) {
        return getGlobalAverage(); // Fallback to global average.
    }
    double R = er->sumScores / er->numRatings;
    return calculateBayesianAverage(R, er->numRatings);
}

double RatingSystem::getActorBayesianAverage(int actorId) const {
    const EntityRatings* er = actorRatings.get(actorId);
    if (!er || er->numRatings == 0) {
        return getGlobalAverage(); // Fallback to global average.
    }
    double R = er->sumScores / er->numRatings;
    return calculateBayesianAverage(R, er->numRatings);
}

void RatingSystem::setMinimumVotesThreshold(int m) {
    this->m = m;
}

double RatingSystem::getGlobalAverage() const {
    if (countAll == 0)
        return 0.0;  // Default if no ratings exist.
    return sumAll / countAll;
}

double RatingSystem::calculateBayesianAverage(double R, int v) const {
    double C = getGlobalAverage();
    return (R * v + C * m) / (v + m);
}
