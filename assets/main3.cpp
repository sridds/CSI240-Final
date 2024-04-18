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

    for (int i = 0; i < userList.size(); i++)
    {
        cout << userList[i].getUsername() << " " << userList[i].getPassword() << endl;
    }

    PromptLogin(userList);
}