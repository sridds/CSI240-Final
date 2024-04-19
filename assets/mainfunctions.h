//
// Created by basil on 4/17/2024.
//

#ifndef MYPROJECT_MAINFUNCTIONS_H
#define MYPROJECT_MAINFUNCTIONS_H

using namespace std;

// reads the userinfo.txt file into user instances, which are put into a vector
vector<User> readUsersToVector(string filename);

// prompts the user to log in to the system, cross checking the login info with the user list
bool PromptLogin(vector<User> list);

#endif //MYPROJECT_MAINFUNCTIONS_H
