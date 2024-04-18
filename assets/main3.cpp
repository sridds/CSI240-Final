//
// Created by basil on 4/15/2024.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "user.h"

using namespace std;

// Function to read usernames and passwords from a file and create User objects
vector<User> readUsersFromFile(const string& filename)
{
    vector<User> users;
    string user, pass;

    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error opening file: " << filename << endl;
        return users;
    }

    while(getline(file, user) && getline(file, pass))
    {

        users.emplace_back(user, pass);

        cout << "user: " << user << " " << pass << endl;

    }

    if (file.eof())
    {
        cout << "End of file reached." << endl;
    }

    return users;
}

int main() {
    std::vector<User> users = readUsersFromFile("userinfo.txt");

    // Print the usernames and passwords of the users created
    for (auto& user : users) {
        std::cout << "Username: " << user.GetUser() << ", Password: " << user.GetPass() << std::endl;
    }

    return 0;
}