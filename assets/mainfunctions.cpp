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

    string uname, pword;

    while(!stream.eof())
    {
        getline(stream, uname);
        getline(stream, pword);


        users.push_back(User(uname, pword));
    }

    stream.close();

    return users;
}

bool PromptLogin(vector<User> list)
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

    return loggedIn;
}