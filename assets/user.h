//
// Created by basil on 4/15/2024.
//
#include <string>

using namespace std;

#ifndef MYPROJECT_USER_H
#define MYPROJECT_USER_H

class User
{
public:
    // default constructor
    User();

    // alt constructor
    User(string name, string key);

    // setters
    void SetUser(string name);
    void SetPass(string key);

    // getters
    string GetUser();
    string GetPass();

    // destructor
     ~User();

private:
    string user;
    string pass;
};


#endif //MYPROJECT_USER_H
