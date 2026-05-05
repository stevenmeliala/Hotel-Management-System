#ifndef REVIEWS_H
#define REVIEWS_H

#include <iostream>
#include <string>

using namespace std;

// Class Definition (Encapsulation and Abstraction)
class Review {
// Encapsulation: Private members hiding internal state
private:
  string userID;
  double rating;
  string comment;
  string hotelName;

// Encapsulation: Public interface
public:
  // Polymorphism (Compile-time): Constructor overloading (Default Constructor)
  Review() {
    userID = "";
    rating = 0.0;
    comment = "";
    hotelName = "";
  }

  // Polymorphism (Compile-time): Constructor overloading (Overloaded Constructor)
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