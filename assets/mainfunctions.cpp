//
// Created by basil on 4/17/2024.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include "stdlib.h"
#include "user.h"
#include "mainfunctions.h"

vector<User> readUsersToVector(string filename)
{
    ifstream stream;
    vector<User> users;

    stream.open("userinfo.txt", ios::in);

    if (stream.fail())
    {
        cout << "Failed to open user file!";

        // ensure the stream is closed
        stream.close();
    }

    string uname, pword, trash;

    while(!stream.eof())
    {
        getline(stream, uname);
        getline(stream, pword);
        // trashing stats variables
        for (int i = 0; i < 4; i++)
        {
            getline(stream, trash);
        }

        users.push_back(User(uname, pword));
    }

    stream.close();

    return users;
}

string PromptLogin(vector<User> list)
{
    string user, pass;
    bool loggedIn = false;

    while (!loggedIn)
    {
        cout << "Enter your username: " << endl;
        cin >> user;
        cout << "Enter your password: " << endl;
        cin >> pass;

        for (int i = 0; i < list.size(); i++)
        {
            if (user == list[i].getUsername())
            {
                if (pass == list[i].getPassword())
                {
                    loggedIn = true;
                    cout << "You have successfully logged in!" << endl;
                }
            }
        }

        if (!loggedIn)
        {
            cout << "You have entered an incorrect username and/or password. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return user;
}

int PromptMainMenuChoice(vector<User> list)
{
    int choice = 0;
    cout << "Welcome to the Grocery Game!" << endl;

    while (choice == 0)
    {
        cout << "Pick a number of what you'd like to do!\n" << endl;

        cout << "1. Log In" << endl << "2. Create New Account" << endl << "3. Quit Program" << endl;

        cin >> choice;

        if (!(!cin.fail() && choice > 0 && choice < 4))
        {
            choice = 0;
            cout << "That was not a valid option, please pick a valid option between 1, 2, and 3." << endl;
        }
    }

    if (choice == 3)
    {
        exit(0);
    }

    return choice;
}


int PromptLoggedInChoice()
{
    int choice = 0;
    cout << "Welcome to the Grocery Game!" << endl;

    while (choice == 0)
    {
        cout << "Pick a number of what you'd like to do!\n" << endl;

        cout << "1. Start Game" << endl << "2. View User Statistics" << endl << "3. Log Out" << endl;

        cin >> choice;

        if (!(!cin.fail() && choice > 0 && choice < 4))
        {
            choice = 0;
            cout << "That was not a valid option, please pick a valid option between 1, 2, and 3." << endl;
        }
    }

    return choice;
}

void PrintUserStats(string username)
{
    ifstream stream;
    // incomplete
}
