//
// Created by basil on 4/15/2024.
//
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
