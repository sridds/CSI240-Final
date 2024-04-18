//
// Created by basil on 4/15/2024.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

int main()
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

    for (int i = 0; i < users.size(); i++)
    {
        cout << users[i].getUsername() << " " << users[i].getPassword() << endl;
    }

    stream.close();
}