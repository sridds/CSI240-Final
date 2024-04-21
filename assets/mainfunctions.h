//
// Created by basil on 4/17/2024.
//

#ifndef MYPROJECT_MAINFUNCTIONS_H
#define MYPROJECT_MAINFUNCTIONS_H

using namespace std;

// reads the userinfo.txt file into user instances, which are put into a vector
vector<User> readUsersToVector();

// prompts the user to log in to the system, cross-checking the login info with the user list
string PromptLogin(vector<User> list);

// prompts the user to choose a choice on the main menu
int PromptMainMenuChoice(vector<User> list);

// prompts the user to choose a choice after they have logged in
int PromptLoggedInChoice();

// prompts the user for a new username and password, and adds this to userinfo.txt, as well as create a new user object
User CreateNewUser(vector<User> list);

// prints the given username's overall statistics
void PrintUserStats(User user);

#endif //MYPROJECT_MAINFUNCTIONS_H
