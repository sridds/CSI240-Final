/*
Author        : Seth Riddensdale
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

#ifndef MYPROJECT_STORE_H
#define MYPROJECT_STORE_H
#include <iostream>
#include "food.h"

using namespace std;

// constants
const int STORE_LENGTH = 10;
const int FILES_TO_READ = 4;

class Store {
private:
    Food** groceryList;

    // aisle references
    Produce* produceAisle;
    Dairy* dairyAisle;
    Deli* deliAisle;
    Frozen* frozenAisle;

    int* shuffleKeysFromFile(int size, int linesToSkip, string filePath);
    string* getRandomLinesFromFile(string path, int linesToRead, int lineCap);
    Food** setupGroceryList(int listLength);

    Produce* populateProduce();
    Dairy* populateDairy();
    Deli* populateDeli();
    Frozen* populateFrozen();

    const int PRODUCE_READ_LINES = 4;
    const int DAIRY_READ_LINES = 4;
    const int DELI_READ_LINES = 4;
    const int FROZEN_READ_LINES = 5;

    const string PRODUCE_FILE_PATH = "produce.txt";
    const string DAIRY_FILE_PATH = "dairy.txt";
    const string DELI_FILE_PATH = "deli.txt";
    const string FROZEN_FILE_PATH = "frozen.txt";

public:
    // constructors
    Store();
    ~Store();

    // getters
    Food** getGroceryList() const;
    Produce* getProduceAisle() const;
    Dairy* getDairyAisle() const;
    Deli* getDeliAisle() const;
    Frozen* getFrozenAisle() const;

    // methods
    bool isGroceryListComplete() const;
    bool tryCollectGroceryItem(Food* item);
    double getPriceOfCollected() const;

    string printProduceAisle();
    string printDairyAisle();
    string printDeliAisle();
    string printFrozenAisle();

    /* Using a friend operator, attempting to print the store in a stream will output the full shopping list */
    friend std::ostream& operator<<(std::ostream& stream, const Store& store){
        for(int i = 0; i < STORE_LENGTH; i++){
            stream << store.getGroceryList()[i]->print() << endl;
        }

        return stream;
    }
};

#endif //MYPROJECT_STORE_H
