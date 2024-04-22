//
// Created by Seth Riddensdale on 4/16/24.
//

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
