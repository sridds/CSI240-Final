//
// Created by basil on 4/17/2024.
//

#ifndef MYPROJECT_MAINFUNCTIONS_H
#define MYPROJECT_MAINFUNCTIONS_H

#include "store.h"

using namespace std;

const int ITEMS_IN_LIST = 10;
const int PENALTY_MULTIPLIER = 5;

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

// starts the game
void StartGame(Store *store, User user);

// returns either 0, 1, or 2, based on whether the user's shopping list has been completed
// 0 represents the user selecting to not checkout
// 1 represents the user checking out without having completed their shopping list
// 2 represents the user checking out with a completed shopping list
int Checkout(Store *store);

#endif //MYPROJECT_MAINFUNCTIONS_H
