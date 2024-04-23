/*
Author        : Brody Silva
Class         : CSI - 240 : Advanced Programming
Assignment    : Final Project
Due Date      : 4/23/24 11:59PM

Project Description :
This project is a grocery game where the user is presented a grocery list and must collect all grocery items from the aisles.
- The grocery list, and the aisles, are randomly generated based on a file
- The users user data is stored in a text file, along with statistics for each run of the game
- The user must navigate through the aisles to find their items.
- The user's time is recorded as they shop, and they are encouraged to get the best time possible.

Certification of Authenticity :

I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/

#include <string>

using namespace std;

#ifndef MYPROJECT_USER_H
#define MYPROJECT_USER_H

const string USER_INFO_FILE = "userinfo.txt";
const string DEFAULT_TIME = "1666:39";
const string DEFAULT_STATS = "0\n0\n0\n99999\n";

class User {
private:
    // member variables
    string username;
    string password;
    // statistic variables (bestTime is in seconds)
    int gamesPlayed, itemsCollected, bestTime;
    double moneySpent;

public:
    // getters
    string getUsername();
    string getPassword();
    string getBestTime();
    int getGamesPlayed();
    int getItemsCollected();
    double getMoneySpent();

    // setters
    void setUsername(string user);
    void setPassword(string pass);
    void setBestTime(int seconds);
    void setGamesPlayed(int totalGames);
    void setItemsCollected(int totalItems);
    void setMoneySpent(double totalMoney);

    // updates the user's statistics stored in userinfo.txt
    bool updateStats(int totalGames, int totalItems, double totalMoney, int seconds);

    // default constructor
    User();

    // alternate constructor
    User(string user, string pass, int totalGames, int totalItems, double totalMoney, int seconds);
};


#endif //MYPROJECT_USER_H
