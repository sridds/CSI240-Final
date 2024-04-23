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

#include "user.h"
#include <string>
#include <fstream>

using namespace std;

// Constructors
User::User()
{
    username = "";
    password = "";
    bestTime = 99999;
    gamesPlayed = 0;
    itemsCollected = 0;
    moneySpent = 0;
}

User::User(string user, string pass, int totalGames, int totalItems, double totalMoney, int seconds)
{
    username = user;
    password = pass;
    gamesPlayed = totalGames;
    itemsCollected = totalItems;
    moneySpent = totalMoney;
    bestTime = seconds;
}

// Getters
string User::getUsername() { return username; }

string User::getPassword() { return password; }

// returning the best time as a string formatted in minutes:seconds
string User::getBestTime()
{
    string bestTimeString;

    int minutes = bestTime / 60;
    int seconds = bestTime % 60;

    if (seconds >= 10)
        bestTimeString = to_string(minutes) + ":" + to_string(seconds);
    else
        bestTimeString = to_string(minutes) + ":0" + to_string(seconds);

    return bestTimeString;
}

int User::getGamesPlayed() { return gamesPlayed; }

int User::getItemsCollected() { return itemsCollected; }

double User::getMoneySpent() { return moneySpent; }

// Setters
void User::setPassword(string pass) { password = pass; }

void User::setUsername(string user) { username = user; }

void User::setBestTime(int seconds) { bestTime = seconds; }

void User::setGamesPlayed(int totalGames) { gamesPlayed = totalGames; }

void User::setItemsCollected(int totalItems) { itemsCollected = totalItems; }

void User::setMoneySpent(double totalMoney) { moneySpent = totalMoney; }

// update stats will update both the user instance that is signed in and the text file, after completing a game
bool User::updateStats(int totalGames, int totalItems, double totalMoney, int seconds)
{
    bool newBest;
    // update the user instance's stats
    gamesPlayed += totalGames;
    itemsCollected += totalItems;
    moneySpent += totalMoney;

    // if its a new best time
    if (seconds < bestTime)
    {
        bestTime = seconds;
        newBest = true;
    }

    ifstream stream(USER_INFO_FILE);
    // temp file will be the new file to write over to
    ofstream temp("temp.txt");

    string replace;

    bool found = false;

    // find the user in the text file, and rewrite their info with the new info
    while (stream >> replace)
    {
        if (replace == username && !found)
        {
            temp << username << endl << password << endl << gamesPlayed << endl << itemsCollected
            << endl << moneySpent << endl << bestTime << endl;
            found = true;

            for (int i = 0; i < 5; i++)
                stream >> replace;
        }
        else
        {
            temp << replace << endl;
        }
    }

    stream.close();
    temp.close();

    // remove old file and rename new file
    remove("userinfo.txt");
    rename("temp.txt", "userinfo.txt");

    return newBest;
}


