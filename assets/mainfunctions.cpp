//
// Created by basil on 4/17/2024.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
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

    string uname, pword, temp;
    int totalGames, totalItems, seconds;
    double moneySpent;

    while(!stream.eof())
    {
        getline(stream, uname);
        getline(stream, pword);
        getline(stream, temp);
        totalGames = stoi(temp);
        getline(stream, temp);
        totalItems = stoi(temp);
        getline(stream, temp);
        moneySpent = stod(temp);
        getline(stream, temp);
        seconds = stoi(temp);


        users.push_back(User(uname, pword, totalGames, totalItems, moneySpent, seconds));
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
                    cout << "You have successfully logged in!\n" << endl;
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
        cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

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

        cout << "1. Start Game" << endl << "2. View User Statistics" << endl << "3. Log Out" << endl << "4. Quit Program" << endl;

        cin >> choice;

        if (!(!cin.fail() && choice > 0 && choice < 5))
        {
            choice = 0;
            cout << "That was not a valid option, please pick a valid option between 1, 2, and 3." << endl;
        }
    }

    return choice;
}

User CreateNewUser(vector<User> list)
{
    bool choice = false, userTaken = false;
    char yOrN;
    string username, password;

    while (!choice)
    {
        cout << "\nPlease enter the username you wish to use: " << endl;
        getline(cin, username);
        cout << username << endl;

        for (User &p : list)
        {
            if (p.getUsername() == username)
            {
                cout << username << " " << p.getUsername() << endl;
                userTaken = true;
            }
        }

        if (!userTaken)
        {
            cout << "\nPlease enter the password you wish to use: " << endl;
            getline(cin, password);

            cout << "You have chosen username: " << username << " and password: " << password << endl;
            cout << "Is this correct? (y/n)" << endl;
            cin >> yOrN;
            cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');

            if (yOrN == 'y')
                choice = true;
        }
        else
        {
            cout << "The username you have chosen is already in use. Please try another.\n" << endl;
            userTaken = false;
        }
    }

    ofstream stream("userinfo.txt", ios::app);

    stream << endl << username << endl << password << endl << "0" << endl << "0"
    << endl << "0" << endl << "99999";

    User newUser = User(username, password, 0, 0, 0, 99999);

    return newUser;
}

void PrintUserStats(User user) {
    // default set time is 99999, which works out to 1666:39
    const string DEFAULT_TIME = "1666:39";

    cout << "Statistics for user " << user.getUsername() << ".\n" << endl;
    cout << "Total Games Played: " << user.getGamesPlayed() << endl;
    cout << "Total Items Grabbed: " << user.getItemsCollected() << endl;
    cout << "Total Amount of Money Spent: " << user.getMoneySpent() << endl;

    if (user.getBestTime() == DEFAULT_TIME) {
        cout << "No time has been set by the user.\n" << endl;
    }
    else
    {
        cout << "Best Time Overall: " << user.getBestTime() << "\n" << endl;
    }

    system("pause");
}
