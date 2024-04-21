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

// reads the user info text file, creating a user object for each user, and assigning the proper statistics
vector<User> readUsersToVector()
{
    ifstream stream;
    vector<User> users;

    stream.open(USER_INFO_FILE, ios::in);

    // file check
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
        // grab and store all values of a user
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

        // place newly created user into the vector
        users.push_back(User(uname, pword, totalGames, totalItems, moneySpent, seconds));
    }

    // close and return
    stream.close();
    return users;
}

// prompt the user with the login system, and return the username of who signed in
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // check if both the username and the password are correct and correlating to a user in the vector
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

        // retry login if failed
        if (!loggedIn)
        {
            cout << "You have entered an incorrect username and/or password. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return user;
}

// prompt the user with the main menu choices, and return which they chose
int PromptMainMenuChoice(vector<User> list)
{
    int choice = 0;
    cout << "Welcome to the Grocery Game!" << endl;

    // while they have not gotten a proper choice yet
    while (choice == 0)
    {
        cout << "Pick a number of what you'd like to do!\n" << endl;

        cout << "1. Log In" << endl << "2. Create New Account" << endl << "3. Quit Program" << endl;

        cin >> choice;

        // if the input isnt good
        if (cin.fail())
        {
            choice = 0;
            cout << "That was not a number, please pick a valid option between 1, 2, and 3." << endl;
            // reset input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (!(choice > 0 && choice < 4))
        {
            choice = 0;
            cout << "That was not a valid option, please pick a valid option between 1, 2, and 3." << endl;
            // reset input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // quit program if theyve chosen to do so
    if (choice == 3)
    {
        exit(0);
    }

    return choice;
}

// prompt the user with the options on the main menu
int PromptLoggedInChoice()
{
    int choice = 0;
    cout << "Welcome to the Grocery Game!" << endl;

    while (choice == 0)
    {
        cout << "Pick a number of what you'd like to do!\n" << endl;

        cout << "1. Start Game" << endl << "2. View User Statistics" << endl << "3. Log Out" << endl << "4. Quit Program" << endl;

        cin >> choice;

        // if the input isnt good
        if (cin.fail())
        {
            choice = 0;
            cout << "That was not a number, please pick a valid option between 1, 2, 3, and 4." << endl;
            // reset input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if (!(choice > 0 && choice < 5))
        {
            choice = 0;
            cout << "That was not a valid option, please pick a valid option between 1, 2, 3, and 4." << endl;
            // reset input
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return choice;
}

// creates a new user object, adds the user data to the text file, and returns the new user.
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

        // testing if the username is already taken or not
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

            // confirmation aspect for the user to choose if they've entered the right info
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

    // append the new user info to the end of the file
    ofstream stream(USER_INFO_FILE, ios::app);

    stream << username << endl << password << endl << DEFAULT_STATS;

    User newUser = User(username, password, 0, 0, 0, 99999);

    return newUser;
}

// print out the logged in user's statistics
void PrintUserStats(User user) {
    cout << "Statistics for user " << user.getUsername() << ".\n" << endl;
    cout << "Total Games Played: " << user.getGamesPlayed() << endl;
    cout << "Total Items Grabbed: " << user.getItemsCollected() << endl;
    cout << "Total Amount of Money Spent: " << user.getMoneySpent() << endl;

    // if the user has not yet set a time, don't display the default time stored in the text file
    if (user.getBestTime() == DEFAULT_TIME) {
        cout << "No time has been set by the user.\n" << endl;
    }
    else
    {
        cout << "Best Time Overall: " << user.getBestTime() << "\n" << endl;
    }

    cout << "Press Enter to continue." << endl;

    cin.ignore();
    cin.ignore();
}
