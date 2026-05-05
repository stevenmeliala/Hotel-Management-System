#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

// Base Class User - demonstrates Abstraction and serves as a blueprint
class User {
// Encapsulation: Protected access modifier allows inherited classes to access members while hiding them from outside
protected:
  string id;
  string name;
  string state;
  string email;

// Encapsulation: Public access modifier provides an interface to interact with the object
public:
  // Polymorphism (Compile-time): Constructor overloading (Default Constructor)
  User() {
    id = "";
    name = "";
    state = "";
    email = "";
  }
  // Polymorphism (Compile-time): Constructor overloading (Overloaded Constructor)
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