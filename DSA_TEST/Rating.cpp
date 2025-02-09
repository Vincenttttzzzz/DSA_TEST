#include "Rating.h"
#include <ctime>  // for std::time

// Constructor definition; initializes the timestamp to the current time.
Rating::Rating(double score, int userId)
    : score(score), userId(userId), timestamp(std::time(nullptr)) {
}

// Getter definitions
double Rating::getScore() const {
    return score;
}

int Rating::getUserId() const {
    return userId;
}

std::time_t Rating::getTimestamp() const {
    return timestamp;
}
