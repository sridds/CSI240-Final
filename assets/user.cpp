//
// Created by basil on 4/15/2024.
//

#include "user.h"
#include <string>

using namespace std;

User::User()
{
    username = "";
    password = "";
}

User::User(string user, string pass)
{
    username = user;
    password = pass;
}

string User::getUsername() { return username; }

string User::getPassword() { return password; }

void User::setPassword(string pass)
{
    password = pass;
}

void User::setUsername(string user)
{
    username = user;
}


