#ifndef REVIEWS_H
#define REVIEWS_H

#include <iostream>
#include <string>

using namespace std;

// Class Definition
class Review {
private:
  string userID;
  double rating;
  string comment;
  string hotelName;

public:
  // Default Constructor
  Review() {
    userID = "";
    rating = 0.0;
    comment = "";
    hotelName = "";
  }

  // Overloaded Constructor
  Review(string id, double r, string c, string hName) {
    userID = id;
    rating = r;
    comment = c;
    hotelName = hName;
  }

  double getRating() const { return rating; }
  string getReviewerId() const { return userID; }
  string getComment() const { return comment; }
  string getHotelName() const { return hotelName; }

  // Setter Methods for editing reviews
  void setRating(double r) { rating = r; }
  void setComment(string c) { comment = c; }
  void setHotelName(string hName) { hotelName = hName; }

  void displayReview() const {
    cout << "User [" << userID << "] rated " << rating << "/5.0: " << comment
         << endl;
  }
};

#endif