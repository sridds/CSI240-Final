//
// Created by basil on 4/15/2024.
//

#include "user.h"
#include <string>
#include <fstream>

using namespace std;

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

bool User::updateStats(int totalGames, int totalItems, double totalMoney, int seconds)
{
    bool newBest;
    gamesPlayed += totalGames;
    itemsCollected += totalItems;
    moneySpent += totalMoney;

    if (seconds < bestTime)
    {
        bestTime = seconds;
        newBest = true;
    }

    ifstream stream("userinfo.txt");
    ofstream temp("temp.txt");

    string replace;

    bool found = false;

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

    remove("userinfo.txt");
    rename("temp.txt", "userinfo.txt");

    return newBest;
}


