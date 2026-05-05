#ifndef HOTEL_H
#define HOTEL_H

#include "Reviews.h"
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

#include "Traveler.h"

class Hotel {
private:
  // private attribute declaration
  string hotelId;
  string hotelName;

  // COMPOSITION: Hotel owns the reviews
  Review reviews[50];
  int reviewCount;
  static const int MAX_REVIEWS = 50; // fixed size array for composition

public:
  // default constructor
  Hotel() {
    hotelId = "";
    hotelName = "";
    reviewCount = 0;
  }

  // overloaded constructor
  Hotel(string h_id, string h_name) {
    hotelId = h_id;
    hotelName = h_name;
    reviewCount = 0;
  }

  // getter methods
  string getHotelId() const { return hotelId; }
  string getHotelName() const { return hotelName; }
  int getReviewCount() const { return reviewCount; }
  const Review &getReview(int idx) const { return reviews[idx]; }

  // add review method
  bool addReview(const Review &newReview) {
    if (reviewCount >= MAX_REVIEWS) {
      cout << "Error: Review capacity reached for " << hotelName << endl;
      return false;
    }
    reviews[reviewCount] = newReview;
    reviewCount++;
    return true;
  }

  double calculateAverageRating() const {
    if (reviewCount == 0)
      return 0.0;
    double total = 0.0;
    for (int i = 0; i < reviewCount; i++) {
      total += reviews[i].getRating();
    }
    return total / reviewCount;
  }

  void showAllReviews() const {
    cout << "\n\n\n=========================================================="
         << endl;
    cout << "  REVIEWS FOR: " << left << setw(39) << hotelName << "" << endl;
    cout << "=========================================================="
         << endl;
    if (reviewCount == 0) {
      cout << "  No reviews yet.                                    " << endl;
    } else {
      for (int i = 0; i < reviewCount; i++) {
        cout << "  Review #" << (i + 1) << endl;
        reviews[i].displayReview();
        if (i < reviewCount - 1) {
          cout << "  ─────────────────────────────────────────────────" << endl;
        }
      }
    }
    cout << "=========================================================="
         << endl;
    cout << "  Average Rating: " << fixed << setprecision(2)
         << calculateAverageRating() << "/5.0 (" << reviewCount << " reviews)"
         << endl;
    cout << "=========================================================="
         << endl;
  }

  void displayHotelSummary() const {
    cout << "  " << left << setw(37) << hotelName << "" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "  Rating:   " << setw(28) << calculateAverageRating() << ""
         << endl;
    cout << "  Reviews:  " << setw(28) << reviewCount << "" << endl;
    cout << "---------------------------------------------" << endl;
  }

  // NEW METHOD FOR SUB-MENU: Display reviews by a specific traveler
  void displayReviewsByTraveler(string t_id) const {
    for (int i = 0; i < reviewCount; i++) {
      if (reviews[i].getReviewerId() == t_id) {
        cout << "   -> " << hotelName << ": ";
        reviews[i].displayReview();
      }
    }
  }

  // Edit a review by a specific traveler using a sub-menu.
  // Returns the index of the edited review, or -1 if none found.
  // Sets hotelChanged to true if the hotel name was modified.
  int editReviewByTraveler(string t_id, bool &hotelChanged) {
    // Collect indices of reviews belonging to this traveler
    int matchIndices[50];
    int matchCount = 0;
    for (int i = 0; i < reviewCount; i++) {
      if (reviews[i].getReviewerId() == t_id) {
        matchIndices[matchCount++] = i;
      }
    }
    if (matchCount == 0)
      return -1; // No reviews by this traveler in this hotel

    // List the matching reviews
    cout << "\n--- Reviews in " << hotelName << " ---" << endl;
    for (int m = 0; m < matchCount; m++) {
      int idx = matchIndices[m];
      cout << "  [" << (m + 1) << "] ";
      reviews[idx].displayReview();
    }

    // Ask which review to edit
    int pick;
    cout << "Select a review to edit (1-" << matchCount << "): ";
    if (!(cin >> pick) || pick < 1 || pick > matchCount) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid selection." << endl;
      return -1;
    }
    cin.ignore();

    int editIdx = matchIndices[pick - 1];
    hotelChanged = false;

    // Sub-menu loop for editing individual fields
    int editChoice = 0;
    while (editChoice != 4) {
      cout << "\n---------- Editing Review ----------" << endl;
      reviews[editIdx].displayReview();
      cout << "------------------------------------" << endl;
      cout << "  1. Edit COMMENT" << endl;
      cout << "  2. Edit RATING" << endl;
      cout << "  3. Edit HOTEL NAME" << endl;
      cout << "  4. Done Editing" << endl;
      cout << "------------------------------------" << endl;
      cout << "Enter selection: ";

      if (!(cin >> editChoice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        continue;
      }
      cin.ignore();

      switch (editChoice) {
      case 1: {
        string newComment;
        cout << "Current Comment: " << reviews[editIdx].getComment() << endl;
        cout << "Enter new Comment: ";
        getline(cin, newComment);
        if (!newComment.empty()) {
          reviews[editIdx].setComment(newComment);
          cout << "Success: Comment updated." << endl;
        } else {
          cout << "No changes made." << endl;
        }
        break;
      }
      case 2: {
        string ratingInput;
        cout << "Current Rating: " << reviews[editIdx].getRating() << "/5.0"
             << endl;
        cout << "Enter new Rating (0.0 - 5.0): ";
        getline(cin, ratingInput);
        if (!ratingInput.empty()) {
          double newRating = stod(ratingInput);
          if (newRating >= 0.0 && newRating <= 5.0) {
            reviews[editIdx].setRating(newRating);
            cout << "Success: Rating updated." << endl;
          } else {
            cout << "Rating must be between 0.0 and 5.0. No changes made."
                 << endl;
          }
        } else {
          cout << "No changes made." << endl;
        }
        break;
      }
      case 3: {
        string newHotelName;
        cout << "Current Hotel Name: " << reviews[editIdx].getHotelName()
             << endl;
        cout << "Enter new Hotel Name: ";
        getline(cin, newHotelName);
        if (!newHotelName.empty() && newHotelName != hotelName) {
          reviews[editIdx].setHotelName(newHotelName);
          hotelChanged = true;
          cout << "Success: Hotel Name updated." << endl;
        } else {
          cout << "No changes made." << endl;
        }
        break;
      }
      case 4:
        cout << "Returning to Reviews menu..." << endl;
        break;
      default:
        cout << "Invalid selection. Please enter 1-4." << endl;
      }
    }

    return editIdx;
  }

  // Remove a review at a specific index and return a copy of it
  Review removeReviewAt(int idx) {
    Review removed = reviews[idx];
    for (int i = idx; i < reviewCount - 1; i++) {
      reviews[i] = reviews[i + 1];
    }
    reviewCount--;
    return removed;
  }

  // OPERATOR OVERLOADING
  bool operator>(const Hotel &other) const {
    return this->calculateAverageRating() > other.calculateAverageRating();
  }

  // STATIC HELPER METHODS (Moved from HotelSystem.cpp)
  static void buildHotelDirectory(Review rawReviews[], int totalReviews,
                                  Hotel hotels[], int maxHotels,
                                  int &hotelCount) {
    hotelCount = 0;
    for (int i = 0; i < totalReviews; i++) {
      int idx = Hotel::findHotelIndex(hotels, hotelCount,
                                      rawReviews[i].getHotelName());

      if (idx == -1 && hotelCount < maxHotels) {
        hotels[hotelCount] =
            Hotel(rawReviews[i].getReviewerId(), rawReviews[i].getHotelName());
        hotels[hotelCount].addReview(rawReviews[i]);
        hotelCount++;
      } else if (idx != -1) {
        hotels[idx].addReview(rawReviews[i]);
      }
    }
  }

  static int findHotelIndex(Hotel hotels[], int hotelCount,
                            const string &hotelName) {
    for (int i = 0; i < hotelCount; i++) {
      if (hotels[i].getHotelName() == hotelName)
        return i;
    }
    return -1;
  }

  struct ReviewerStat {
    string id;
    string name;
    int count;
  };

  static void identifyTopReviewers(const Hotel hotels[], int hCount,
                                   Traveler travelers[], int tCount) {
    ReviewerStat *stats = new ReviewerStat[tCount];

    for (int i = 0; i < tCount; i++) {
      int personalCount = 0;
      string currentId = travelers[i].getId();
      for (int j = 0; j < hCount; j++) {
        for (int k = 0; k < hotels[j].reviewCount; k++) {
          if (hotels[j].reviews[k].getReviewerId() == currentId) {
            personalCount++;
          }
        }
      }
      stats[i] = {currentId, travelers[i].getName(), personalCount};
    }

    // Sort by review count descending
    for (int i = 0; i < tCount - 1; i++) {
      for (int j = 0; j < tCount - i - 1; j++) {
        if (stats[j].count < stats[j + 1].count) {
          ReviewerStat temp = stats[j];
          stats[j] = stats[j + 1];
          stats[j + 1] = temp;
        }
      }
    }

    cout << "\n========== TOP REVIEWERS LEADERBOARD ==========" << endl;
    cout << left << setw(15) << "Traveler ID" << setw(20) << "Name"
         << "Review Count" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = 0; i < tCount; i++) {
      if (stats[i].count > 0) {
        cout << left << setw(15) << stats[i].id << setw(20) << stats[i].name
             << stats[i].count << endl;
      }
    }
    cout << "===============================================" << endl;

    delete[] stats;
  }

  static void displayTopRatedHotel(const Hotel hotelDirectory[],
                                   int hotelCount) {
    if (hotelCount > 0) {
      int topIdx = 0;
      for (int i = 1; i < hotelCount; i++) {
        if (hotelDirectory[i] > hotelDirectory[topIdx]) {
          topIdx = i;
        }
      }
      cout << "\n-------- TOP-RATED HOTEL IDENTIFIED --------" << endl;
      hotelDirectory[topIdx].displayHotelSummary();
    } else {
      cout << "No hotel data available for ranking." << endl;
    }
  }

  static void addReviewToDirectory(Hotel hotelDirectory[], int &hotelCount,
                                   int MAX_HOTELS, Review newReview) {
    string newHName = newReview.getHotelName();
    int destIdx = findHotelIndex(hotelDirectory, hotelCount, newHName);
    if (destIdx != -1) {
      hotelDirectory[destIdx].addReview(newReview);
      cout << "Review added to existing hotel: " << newHName << endl;
    } else if (hotelCount < MAX_HOTELS) {
      hotelDirectory[hotelCount] = Hotel(newReview.getReviewerId(), newHName);
      hotelDirectory[hotelCount].addReview(newReview);
      hotelCount++;
      cout << "New hotel created and review added: " << newHName << endl;
    } else {
      cout << "Error: Hotel directory is full. Cannot create new hotel for "
              "this review."
           << endl;
    }
  }

  static void handleReviewRelocation(Hotel hotelDirectory[], int &hotelCount,
                                     int MAX_HOTELS, int hIdx, int editedIdx) {
    Review movedReview = hotelDirectory[hIdx].removeReviewAt(editedIdx);
    string newHName = movedReview.getHotelName();

    int destIdx = findHotelIndex(hotelDirectory, hotelCount, newHName);
    if (destIdx != -1) {
      hotelDirectory[destIdx].addReview(movedReview);
      cout << "Review relocated to existing hotel: " << newHName << endl;
    } else if (hotelCount < MAX_HOTELS) {
      hotelDirectory[hotelCount] = Hotel(movedReview.getReviewerId(), newHName);
      hotelDirectory[hotelCount].addReview(movedReview);
      hotelCount++;
      cout << "New hotel created and review moved to: " << newHName << endl;
    } else {
      // Revert the removal if capacity reached
      hotelDirectory[hIdx].addReview(movedReview);
      cout << "Error: Hotel capacity reached. Review not moved." << endl;
    }
  }
};
#endif