//
// Created by basil on 4/15/2024.
//

#include "user.h"
#include <string>

using namespace std;

User::User()
{
    user = "username";
    pass = "password";
}

User::User(string name, string key)
{
    user = name;
    pass = key;
}

void User::SetUser(string name)
{
    user = name;
}

void User::SetPass(string key)
{
    pass = key;
}

string User::GetUser()
{
    return user;
}

string User::GetPass()
{
    return pass;
}

User::~User()
{
    delete this;
}


