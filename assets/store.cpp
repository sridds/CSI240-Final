//
// Created by Seth Riddensdale on 4/16/24.
//

#include "store.h"
#include "food.h"
#include <fstream>
#include <cstring>

const int STORE_LENGTH = 10;
const int PRODUCE_SKIP_LINES = 4;

const string PRODUCE_FILE_PATH = "produce.txt";
const string DAIRY_FILE_PATH = "produce.txt";
const string DELI_FILE_PATH = "produce.txt";
const string FROZEN_FILE_PATH = "produce.txt";

int* shuffleKeysFromFile(int size, int linesToSkip, string filePath);
bool containsValue(int* arr, int value, int size);

// Defines a store with provided dimensions w and h
Store::Store() {
    // initialize arrays
    produceAisle = new Produce[STORE_LENGTH];
    dairyAisle = new Dairy[STORE_LENGTH];
    deliAisle = new Deli[STORE_LENGTH];
    frozenAisle = new Frozen[STORE_LENGTH];

    ifstream produceIn("produce.txt", ios::in);
    string produceName, produceCost, produceType, trash = "";

    // ADD FAIL CHECK

    int index = 0;
    int lineCount = 0;
    int* keys = shuffleKeysFromFile(STORE_LENGTH, PRODUCE_SKIP_LINES, PRODUCE_FILE_PATH);

    // POPULATE PRODUCE
    while(!produceIn.eof()){
        // ensure index does not surpass array const length
        if(index >= STORE_LENGTH) break;

        // get name, cost, and type from file
        getline(produceIn, produceName);
        lineCount++;

        // Does the line count match a key?
        if(!containsValue(keys, lineCount, STORE_LENGTH)) continue;

        getline(produceIn, produceCost);
        getline(produceIn, produceType);

        ProduceType produceTypeKey;
        // match produce type. replace with a try catch statement later
        for(int i = 0; i < sizeof(PRODUCE_STRINGS); i++){
            if(PRODUCE_STRINGS[i] == produceType){
                produceTypeKey = (ProduceType)i;
            }
        }
        // create new food
        produceAisle[index] = *new Produce(produceName, stod(produceCost), produceTypeKey);

        // put empty seperator line in trash and iterate index
        getline(produceIn, trash);
        index++;
        lineCount += PRODUCE_SKIP_LINES - 1;
    }

    delete[] keys;

    for(int i = 0; i < 10; i++){
        cout << produceAisle[i].print() << endl;
    }

    produceIn.close();
}

Store::~Store() {
    // deallocate arrays
    delete[] produceAisle;
    delete[] dairyAisle;
    delete[] deliAisle;
    delete[] frozenAisle;
}

// helper function that checks the array to match values
bool containsValue(int* arr, int value, int size){
    for(int i = 0; i < size; i++){
        if(arr[i] == value){
            return true;
        }
    }

    return false;
}

/*
 * While the files have roughly 30 elements, the program only selects 10. Because of this, we must shuffle the file around.
 * Rather than shuffling the entire file around, the following function returns a pointer containing all the line keys.
 * param - linesToSkip indicates the amount of lines to skip each iteration. This is because some files have more data per item than others
 * param - filePath indicates which file to look through
 */
int* shuffleKeysFromFile(int size, int linesToSkip, string filePath){
    // get file
    ifstream fileIn(filePath, ios::in);

    // fail check
    if(fileIn.fail()){
        fileIn.close();
        return nullptr;
    }

    string line;
    int count = 0;

    // Get line count
    while(!fileIn.eof()){
        getline(fileIn, line);
        count++;
    }

    srand(time(NULL));

    int* keys = new int[size];
    for(int i = 0; i < size; i++){
        int val = 0;
        do{
            // get a random value that is within 4 units from each and ranges from 0 to count - 1
            val = (1 + linesToSkip * (rand() % (count - 1) + 1)) % count;

            // do not duplicate values. all must be unique
        } while(containsValue(keys, val, size));

        keys[i] = val;
    }

    fileIn.close();
    return keys;
}