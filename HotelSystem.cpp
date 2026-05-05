#include <fstream>
#include <iostream>
#include <string>

// Include all class header file
#include "Hotel.h"
#include "Reviews.h"
#include "Traveler.h"

using namespace std;

int loadTravelers(Traveler travelerDirectory[], int maxCapacity) {
  ifstream userFile("users.txt");
  int count = 0;
  if (!userFile)
    return 0;
  string id, name, state, email, tier, pointsStr;
  int points;
  while (count < maxCapacity && getline(userFile, id, '\t')) {
    getline(userFile, name, '\t');
    getline(userFile, state, '\t');
    getline(userFile, email, '\t');
    getline(userFile, tier, '\t');
    getline(userFile, pointsStr, '\n');
    points = stoi(pointsStr);
    travelerDirectory[count] = Traveler(id, name, state, email, tier, points);
    count++;
  }
  userFile.close();
  return count;
}

void saveTravelers(Traveler travelerDirectory[], int count) {
  ofstream outFile(
      "users.txt"); // This opens the file and wipes it clean to start fresh
  if (!outFile) {
    cout << "Error: Could not open users.txt for writing." << endl;
    return;
  }

  for (int i = 0; i < count; i++) {
    // We write the data back in the exact same TAB-separated format it came in
    outFile << travelerDirectory[i].getId() << "\t"
            << travelerDirectory[i].getName() << "\t"
            << travelerDirectory[i].getState() << "\t"
            << travelerDirectory[i].getEmail() << "\t"
            << travelerDirectory[i].getMembershipLevel() << "\t"
            << travelerDirectory[i].getPoints() << "\n";
  }
  outFile.close();
  cout << "Changes successfully saved to users.txt!" << endl;
}

// (ReviewerStat struct and identifyTopReviewers function have been moved to
// Hotel.h)

// ==========================================
// SAFE TWO-STEP FILE I/O LOGIC
// ==========================================
// findHotelIndex has been moved to Hotel.h

// Step 1: Pure Extraction (No logic allowed here)
int loadRawReviews(const string &filename, Review rawReviews[],
                   int maxCapacity) {
  ifstream reviewFile(filename);
  int count = 0;
  if (!reviewFile)
    return 0;

  string t_id, ratingStr, comment, hName;
  while (count < maxCapacity && getline(reviewFile, t_id, '\t')) {
    getline(reviewFile, ratingStr, '\t');
    getline(reviewFile, comment, '\t');
    getline(reviewFile, hName, '\n');
    double rating = stod(ratingStr);
    rawReviews[count] = Review(t_id, rating, comment, hName);
    count++;
  }
  reviewFile.close();
  return count;
}

// ==========================================
int main() {
  const int MAX_HOTELS = 20;
  const int MAX_USERS = 100;
  const int MAX_RAW_REVIEWS = 200;

  Hotel hotelDirectory[MAX_HOTELS];
  Traveler travelerDirectory[MAX_USERS];
  Review rawReviews[MAX_RAW_REVIEWS];

  int hotelCount = 0;
  int travelerCount = 0;

  cout << "System Booting..." << endl;
  travelerCount = loadTravelers(travelerDirectory, MAX_USERS);

  // Using the safe Two-Step loader to obey the rules
  int reviewsLoaded =
      loadRawReviews("reviews.txt", rawReviews, MAX_RAW_REVIEWS);
  Hotel::buildHotelDirectory(rawReviews, reviewsLoaded, hotelDirectory,
                             MAX_HOTELS, hotelCount);

  cout << "Success: " << travelerCount << " travelers and " << reviewsLoaded
       << " reviews loaded into memory." << endl;

  int choice = 0;
  string searchName;
  string currentAdminId =
      "U001"; // FIXED: Changed USR001 to U001 so it matches the text file

  while (choice != 5) {
    cout << "\n==========================================" << endl;
    cout << "   HOTEL REVIEW ADMINISTRATIVE SYSTEM     " << endl;
    cout << "==========================================" << endl;
    cout << "1. Property Deep-Dive (Search reviews)" << endl;
    cout << "2. Traveler Profile Management" << endl;
    cout << "3. Top-Pick Matcher (Ranking)" << endl;
    cout << "4. Administrative Analytics (Friend Func)" << endl;
    cout << "5. Save & Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Enter selection: ";

    if (!(cin >> choice)) {
      cin.clear();
      cin.ignore(1000, '\n');
      continue;
    }

    switch (choice) {
    case 1:
      cout << "Enter exact Hotel Name to search: ";
      cin.ignore();
      getline(cin, searchName);
      {
        int idx = Hotel::findHotelIndex(hotelDirectory, hotelCount, searchName);
        if (idx != -1) {
          hotelDirectory[idx].showAllReviews();
        } else {
          cout << "Hotel not found in current directory." << endl;
        }
      }
      break;
    case 2: { // Traveler Profile Management
      // List all registered travelers for selection
      cout << "\n========== REGISTERED TRAVELERS ==========" << endl;
      for (int i = 0; i < travelerCount; i++) {
        cout << "  [" << (i + 1) << "] " << travelerDirectory[i].getId()
             << " - " << travelerDirectory[i].getName() << endl;
      }
      cout << "==========================================" << endl;

      int travelerPick;
      cout << "Select a traveler to manage (1-" << travelerCount << "): ";
      if (!(cin >> travelerPick) || travelerPick < 1 ||
          travelerPick > travelerCount) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid selection." << endl;
        break;
      }

      int t_idx = travelerPick - 1;
      string selectedId = travelerDirectory[t_idx].getId();

      int subChoice = 0;
      while (subChoice != 8) {
        cout << "\n";
        travelerDirectory[t_idx]
            .displayProfile(); // Show profile before editing

        cout << "=================== Traveler information update "
                "==================="
             << endl;
        cout << " 1. USER NAME" << endl;
        cout << " 2. STATE" << endl;
        cout << " 3. EMAIL" << endl;
        cout << " 4. MEMBER TYPE" << endl;
        cout << " 5. POINTS" << endl;
        cout << " 6. REVIEWS BY TRAVELER" << endl;
        cout << " 7. ADD NEW REVIEW" << endl;
        cout << " 8. EXIT SUBPAGE" << endl;
        cout << "=============================================================="
                "====="
             << endl;
        cout << "Enter selection: ";

        if (!(cin >> subChoice)) {
          cin.clear();
          cin.ignore(1000, '\n');
          continue;
        }

        cin.ignore(); // Clear the newline character for getline()

        switch (subChoice) {
        case 1: {
          string newName;
          cout << "Enter new User Name: ";
          getline(cin, newName);
          travelerDirectory[t_idx].setName(newName);
          cout << "Success: Name updated." << endl;
          break;
        }
        case 2: {
          string newState;
          cout << "Enter new State: ";
          getline(cin, newState);
          travelerDirectory[t_idx].setState(newState);
          cout << "Success: State updated." << endl;
          break;
        }
        case 3: {
          string newEmail;
          cout << "Enter new Email: ";
          getline(cin, newEmail);
          travelerDirectory[t_idx].setEmail(newEmail);
          cout << "Success: Email updated." << endl;
          break;
        }
        case 4: {
          string newTier;
          cout << "Enter new Member Type (e.g., Gold, Platinum): ";
          getline(cin, newTier);
          travelerDirectory[t_idx].setMembershipLevel(newTier);
          cout << "Success: Membership Level updated." << endl;
          break;
        }
        case 5: {
          int newPoints;
          cout << "Enter new total accumulated points: ";
          if (cin >> newPoints) {
            travelerDirectory[t_idx].setPoints(newPoints);
            cout << "Success: Points updated." << endl;
          } else {
            cout << "Invalid input." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
          }
          break;
        }
        case 6: {
          // Display all reviews authored by this traveler
          cout << "\n========== AUTHORED REVIEWS ==========" << endl;
          for (int j = 0; j < hotelCount; j++) {
            hotelDirectory[j].displayReviewsByTraveler(selectedId);
          }
          cout << "======================================" << endl;

          // Ask which hotel's review to edit
          string editHotelName;
          cout << "\nEnter the Hotel Name of the review you want to edit "
               << "(or type 'cancel' to go back): ";
          getline(cin, editHotelName);

          if (editHotelName == "cancel") {
            cout << "Edit cancelled." << endl;
            break;
          }

          int hIdx =
              Hotel::findHotelIndex(hotelDirectory, hotelCount, editHotelName);
          if (hIdx == -1) {
            cout << "Hotel \"" << editHotelName << "\" not found in directory."
                 << endl;
            break;
          }

          // Call the edit sub-menu on the chosen hotel
          bool hotelNameChanged = false;
          int editedIdx = hotelDirectory[hIdx].editReviewByTraveler(
              selectedId, hotelNameChanged);

          if (editedIdx == -1) {
            cout << "No editable review found for your ID in that hotel."
                 << endl;
            break;
          }

          // If the user changed the hotel name, relocate the review
          if (hotelNameChanged) {
            Hotel::handleReviewRelocation(hotelDirectory, hotelCount,
                                          MAX_HOTELS, hIdx, editedIdx);
          }
          break;
        }
        case 7: {
          string newHName, newComment;
          int newRating;

          cout << "Enter the Hotel Name: ";
          getline(cin, newHName);

          cout << "Enter your Rating (1-5): ";
          if (!(cin >> newRating)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid rating. Must be a number." << endl;
            break;
          }
          cin.ignore(); // Clear newline

          if (newRating < 1 || newRating > 5) {
            cout << "Invalid rating. Must be between 1 and 5." << endl;
            break;
          }

          cout << "Enter your Comment: ";
          getline(cin, newComment);

          Review newReview(selectedId, newRating, newComment, newHName);
          Hotel::addReviewToDirectory(hotelDirectory, hotelCount, MAX_HOTELS,
                                      newReview);
          break;
        }
        case 8:
          cout << "Returning to Main Menu..." << endl;
          break;
        default:
          cout << "Invalid selection. Please enter 1-8." << endl;
        }
      }
      break;
    } // End of Case 2
    case 3:
      Hotel::displayTopRatedHotel(hotelDirectory, hotelCount);
      break;
    case 4:
      Hotel::identifyTopReviewers(hotelDirectory, hotelCount, travelerDirectory,
                                  travelerCount);
      break;
    case 5: // Save & Exit
      cout << "Terminating... Saving all changes to database." << endl;
      {
        // 1. Permanent Save: Update the users.txt with changes from the
        // sub-menu
        ofstream userSave("users.txt");
        if (userSave) {
          for (int i = 0; i < travelerCount; i++) {
            userSave << travelerDirectory[i].getId() << "\t"
                     << travelerDirectory[i].getName() << "\t"
                     << travelerDirectory[i].getState() << "\t"
                     << travelerDirectory[i].getEmail() << "\t"
                     << travelerDirectory[i].getMembershipLevel() << "\t"
                     << travelerDirectory[i].getPoints() << "\n";
          }
          userSave.close();
          cout << "-> User database updated successfully." << endl;
        }

        // 2. Session Summary: Keep existing report logic
        ofstream outFile("Session_Summary.txt");
        if (outFile) {
          outFile << "Hotel Review System Report\n";
          outFile << "Total Hotels in Memory: " << hotelCount << "\n";
          outFile << "Total Registered Travelers: " << travelerCount << "\n";
          outFile.close();
          cout << "-> Session summary generated." << endl;
        }

        // 3. Permanent Save: Update reviews.txt with any edited reviews
        {
          ofstream reviewSave("reviews.txt");
          if (reviewSave) {
            for (int i = 0; i < hotelCount; i++) {
              for (int j = 0; j < hotelDirectory[i].getReviewCount(); j++) {
                const Review &r = hotelDirectory[i].getReview(j);
                reviewSave << r.getReviewerId() << "\t" << r.getRating() << "\t"
                           << r.getComment() << "\t" << r.getHotelName()
                           << "\n";
              }
            }
            reviewSave.close();
            cout << "-> Review database updated successfully." << endl;
          }
        }
      }
      cout << "System shutdown complete." << endl;
      break;

    default:
      cout << "Invalid selection. Please use options 1-5." << endl;
    } // End of Switch
  } // End of While loop

  return 0;
}