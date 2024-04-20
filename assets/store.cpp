//
// Created by Seth Riddensdale on 4/16/24.
//

#include "store.h"
#include "food.h"
#include <fstream>
#include <cstring>

// constants
const int STORE_LENGTH = 10;
const int PRODUCE_READ_LINES = 4;

const string PRODUCE_FILE_PATH = "produce.txt";
const string DAIRY_FILE_PATH = "produce.txt";
const string DELI_FILE_PATH = "produce.txt";
const string FROZEN_FILE_PATH = "produce.txt";

int* shuffleKeysFromFile(int size, int linesToSkip, string filePath);
bool containsValue(int* arr, int value, int size);
string* getRandomLinesFromFile(string path, int linesToRead);

Produce* populateProduce();

// Defines a store with provided dimensions w and h
Store::Store() {
    // initialize arrays
    produceAisle = populateProduce();
    //dairyAisle = populateDairy();
    //deliAisle = new Deli[STORE_LENGTH];
    //frozenAisle = new Frozen[STORE_LENGTH];

    for(int i = 0; i < 10; i++){
        cout << produceAisle[i].print() << endl;
    }
}

/*
 * This is a very specific function. In summary, the function does the following:
 * - Gets a list of random keys, each key indicating the start of a new data entry in the file
 * - From that key, a loop will go through the file and match the line with the key.
 * - If there is a match, record
 */
string* getRandomLinesFromFile(string path, int linesToRead, int lineCap){
    // open file
    ifstream fileIn(path, ios::in);

    // fail check, return null
    if(fileIn.fail()) return nullptr;

    string* data = new string[lineCap * linesToRead];
    int* keys = shuffleKeysFromFile(lineCap, linesToRead + 1, path);
    int index = 0, lineCount = 0;
    string trash;

    // Populate data
    while(!fileIn.eof()){
        if(index >= lineCap) break;

        getline(fileIn, data[(index * (linesToRead))]);
        lineCount++;

        // Does the line count match a key?
        if(!containsValue(keys, lineCount, STORE_LENGTH)) continue;

        for(int i = 1; i < linesToRead; i++){
            getline(fileIn, data[(index * (linesToRead)) + i]);
        }
        // put empty seperator line in trash and iterate index
        getline(fileIn, trash);
        index++;
        lineCount += PRODUCE_READ_LINES - 1;
    }

    return data;
}

Produce* populateProduce(){
    // get random lines
    string* data = getRandomLinesFromFile(PRODUCE_FILE_PATH, PRODUCE_READ_LINES - 1, STORE_LENGTH);
    Produce* produce = new Produce[STORE_LENGTH];

    int produceIndex = 0;

    // produce data
    double cost;

    // Store the data in the produce array
    for(int i = 0; i < STORE_LENGTH * (PRODUCE_READ_LINES - 1); i += (PRODUCE_READ_LINES - 1)){

        ProduceType typeKey;
        for(int j = 0; j < sizeof(PRODUCE_STRINGS); j++){
            if(PRODUCE_STRINGS[j] == data[i + 2]){
                typeKey = (ProduceType)j;
            }
        }

        // store data. because of how the loop functions this will not break
        produce[produceIndex] = *new Produce(data[i], stod(data[i + 1]), typeKey);
        produceIndex++;
    }

    return produce;
}

/*
Produce* populateProduce(){
    Produce* produceAisle = new Produce[STORE_LENGTH];

    ifstream produceIn(PRODUCE_FILE_PATH, ios::in);
    string produceName, produceCost, produceType, trash = "";

    // ADD FAIL CHECK

    int index, lineCount = 0;
    int* keys = shuffleKeysFromFile(STORE_LENGTH, PRODUCE_READ_LINES, PRODUCE_FILE_PATH);

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
        lineCount += PRODUCE_READ_LINES - 1;
    }

    // deallocate and close file
    delete[] keys;
    produceIn.close();

    return produceAisle;
}*/

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