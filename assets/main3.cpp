//
// Created by basil on 4/15/2024.
//

#include <iostream>
#include <string>
#include <vector>
#include "user.h"
#include "mainfunctions.h"

using namespace std;

int main()
{
    vector<User> userList = readUsersToVector("userinfo.txt");
    int choice;
    string loggedInUser;
    bool loggedIn = false;

    while (true)
    {
        choice = PromptMainMenuChoice(userList);
        loggedIn = false;

        if (choice == 1) {
            loggedInUser = PromptLogin(userList);
            loggedIn = true;
        }
        else if (choice == 2)
        {
            // call to create new user function
            loggedIn = true;
        }

        while (loggedIn)
        {
            choice = PromptLoggedInChoice();

            switch (choice)
            {
                case 1:
                    // 1. Start Game
                    // not yet implemented
                    break;
                case 2:
                    // 2. View User Statistics
                    PrintUserStats(loggedInUser);
                    break;
                case 3:
                    // 3. Log Out
                    loggedIn = false;
                    break;
                default:
                    break;
            }
        }
    }

    /*
     * prints out all usernames and passwords to console, for debugging
    for (int i = 0; i < userList.size(); i++)
    {
        cout << userList[i].getUsername() << " " << userList[i].getPassword() << endl;
    }
     */
}