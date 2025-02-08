#pragma once
#include <ctime>
#include <string>

class Rating {
private:
    double score;         // Rating value (e.g., 1-5 stars)
    int userId;           // ID of the user submitting the rating
    std::time_t timestamp;// Timestamp of the rating

public:
    Rating(double score, int userId)
        : score(score), userId(userId), timestamp(std::time(nullptr)) {}

    // Getters
    double getScore() const { return score; }
    int getUserId() const { return userId; }
    std::time_t getTimestamp() const { return timestamp; }
};
