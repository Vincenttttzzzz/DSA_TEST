#pragma once
#include <ctime>
#include <string>

class Rating {
private:
    double score;         // Rating value (e.g., 1-5 stars)
    std::string review;   // Text review
    int userId;           // ID of the user submitting the rating
    std::time_t timestamp;// Timestamp of the rating

public:
    Rating(double score, const std::string& review, int userId)
        : score(score), review(review), userId(userId), timestamp(std::time(nullptr)) {}

    // Getters
    double getScore() const { return score; }
    const std::string& getReview() const { return review; }
    int getUserId() const { return userId; }
    std::time_t getTimestamp() const { return timestamp; }
};
