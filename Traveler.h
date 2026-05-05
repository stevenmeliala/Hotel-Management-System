#ifndef TRAVELER_H
#define TRAVELER_H

#include "User.h"
#include <iostream>
#include <string>

using namespace std;

// Derived Class from User Class (Inheritance)
class Traveler : public User {
private:
  string membershipLevel;
  int points;

public:
  // Default Constructor
  Traveler() : User() {
    membershipLevel = "";
    points = 0;
  }
  // Paramaterized Constructor
  Traveler(string u_id, string u_name, string u_state, string u_email,
           string t_tier, int t_points)
      : User(u_id, u_name, u_state, u_email) {
    membershipLevel = t_tier;
    points = t_points;
  }
  // Getter Methods
  string getMembershipLevel() { return membershipLevel; }
  int getPoints() { return points; }
  void displayProfile() {
    cout << "========= Traveler Profile =========" << endl;
    cout << "ID: " << id << endl;
    cout << "Name: " << name << endl;
    cout << "Location: " << state << endl;
    cout << "Contact: " << email << endl;
    cout << "Tier: " << membershipLevel << endl;
    cout << "Loyalty Points: " << points << endl;
    cout << "===================================" << endl;
  }
  // Destructor
  ~Traveler() {}

  // SETTER METHODS
  void setMembershipLevel(string tier) { membershipLevel = tier; }
  void setPoints(int p) { points = p; }
};
#endif