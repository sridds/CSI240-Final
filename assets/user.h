//
// Created by basil on 4/15/2024.
//
#include <string>

using namespace std;

#ifndef MYPROJECT_USER_H
#define MYPROJECT_USER_H

class User {
private:
    // member variables
    string username;
    string password;

public:
    // getters
    string getUsername();
    string getPassword();

    // setters
    void setUsername(string user);
    void setPassword(string pass);


    // default constructor
    User();

    // alternate constructor
    User(string user, string pass);
};


#endif //MYPROJECT_USER_H
