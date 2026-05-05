#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

// Base Class User
class User {
protected:
  string id;
  string name;
  string state;
  string email;

public:
  // Default Constructor
  User() {
    id = "";
    name = "";
    state = "";
    email = "";
  }
  // Overloaded Constructor
  User(string u_id, string u_name, string u_state, string u_email) {
    id = u_id;
    name = u_name;
    state = u_state;
    email = u_email;
  }
  // Destructor
  ~User() {}
  // Getter Methods
  string getId() const { return id; }
  string getName() const { return name; }
  string getState() const { return state; }
  string getEmail() const { return email; }

  // SETTER METHODS
  void setName(string n) { name = n; }
  void setState(string s) { state = s; }
  void setEmail(string e) { email = e; }
};
#endif