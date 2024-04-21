//
// Created by basil on 4/15/2024.
//

#include <iostream>
#include <string>
#include <vector>
#include "user.h"
#include "mainfunctions.h"
#include "store.h"

using namespace std;

int main()
{
    /*
    Store* store = new Store();
    delete store;
     */

    vector<User> userList = readUsersToVector();
    int choice;
    string loggedInUsername;
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
            loggedIn = true;
            for (User &p : userList)
            {
                if (p.getUsername() == loggedInUsername)
                {
                    loggedInUser = p;
                }
            }
        }
        else if (choice == 2)
        {
            User newUser = CreateNewUser(userList);
            userList.push_back(newUser);
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
                case 4:
                    // 4. Quit Program
                    exit(0);
                    break;
                default:
                    break;
            }
        }
    }
}