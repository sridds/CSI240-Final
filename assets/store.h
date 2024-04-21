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
    // aisle references
    Produce* produceAisle;
    Dairy* dairyAisle;
    Deli* deliAisle;
    Frozen* frozenAisle;

    int* shuffleKeysFromFile(int size, int linesToSkip, string filePath);
    string* getRandomLinesFromFile(string path, int linesToRead, int lineCap);

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

    Produce* getProduceAisle() const;
    Dairy* getDairyAisle() const;
    Deli* getDeliAisle() const;
    Frozen* getFrozenAisle() const;
};

#endif //MYPROJECT_STORE_H
