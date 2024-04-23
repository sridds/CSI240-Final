/*
Author        : Brody Silva
Class         : CSI - 240 : Advanced Programming
Assignment    : Final Project
Due Date      : 4/23/24 11:59PM

Project Description :
This project is a grocery game where the user is presented a grocery list and must collect all grocery items from the aisles.
- The grocery list, and the aisles, are randomly generated based on a file
- The users user data is stored in a text file, along with statistics for each run of the game
- The user must navigate through the aisles to find their items.
- The user's time is recorded as they shop, and they are encouraged to get the best time possible.

Certification of Authenticity :

I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/

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
