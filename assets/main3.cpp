//
// Created by basil on 4/15/2024.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

void CreateUsers(vector<User>& list)
{
    ifstream userInfo("userinfo.txt");
    string user, pass;

    if (!userInfo)
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    while (getline(userInfo, user) && getline(userInfo, pass))
    {
        User temp(user, pass);
        //list.emplace_back(temp);
        cout << "user added: " << temp.GetUser() << " " << temp.GetPass() << endl;
        break;
    }

    if (userInfo.eof())
    {
        cout << "End of file reached." << endl;
    }
    else if (userInfo.fail())
    {
        cout << "Error reading from file." << endl;
    }

    userInfo.close();
}


int main()
{
    vector<User> userList;
    CreateUsers(userList);
    cout << userList[0].GetUser() << endl;
    cout << userList[1].GetUser() << endl;

    return 0;
}
