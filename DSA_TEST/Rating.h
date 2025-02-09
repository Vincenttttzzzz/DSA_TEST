#pragma once
#include <ctime>
#include <string>

class Rating {
private:
    double score;         // Rating value (e.g., 1-5 stars)
    int userId;           // ID of the user submitting the rating
    std::time_t timestamp;// Timestamp of the rating

public:
    // Constructor declaration
    Rating(double score, int userId);

    // Getter declarations
    double getScore() const;
    int getUserId() const;
    std::time_t getTimestamp() const;
};
