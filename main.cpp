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

#include <iostream>
#include <string>
#include <vector>
#include "user.h"
#include "mainfunctions.h"
#include "store.h"

using namespace std;

int main()
{
    vector<User> userList = readUsersToVector();
    int choice, time;
    string loggedInUsername, loggedInPass;
    User loggedInUser;
    bool loggedIn = false;

    // main game loop, will not be exited unless the user chooses to quit the game on menus
    while (true)
    {
        choice = PromptMainMenuChoice(userList);
        loggedIn = false;

        // if user chooses to log in, store their name and the user object associated
        if (choice == 1)
        {
            loggedInUsername = PromptLogin(userList);
            loggedInPass = loggedInUsername;
            loggedInUsername.erase(loggedInUsername.find(' '));
            loggedInPass = loggedInPass.substr((int)loggedInUsername.length() + 1, (int)loggedInPass.length());

            for (User &p : userList)
            {
                if (p.getUsername() == loggedInUsername)
                {
                    if (p.getPassword() == loggedInPass)
                    {
                        loggedIn = true;
                        loggedInUser = p;
                    }
                }
            }
        }
        else if (choice == 2)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            User newUser = CreateNewUser(userList);
            userList.push_back(newUser);
            loggedInUser = newUser;
            loggedIn = true;
        }

        while (loggedIn)
        {
            choice = PromptLoggedInChoice();
            Store *store = new Store();;

            switch (choice)
            {
                case 1:
                    // 1. Start Game
                    StartGame(store, loggedInUser);
                    break;
                case 2:
                    // 2. View User Statistics
                    PrintUserStats(loggedInUser);
                    break;
                case 3:
                    // 3. Log Out
                    loggedIn = false;
                    break;
                case 4:
                    // 4. Quit Program
                    exit(0);
                default:
                    break;
            }
        }
    }
}