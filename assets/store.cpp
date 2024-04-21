//
// Created by Seth Riddensdale on 4/16/24.
//

#include "store.h"
#include "food.h"
#include <fstream>

template<typename T>
bool containsValue(T* arr, T value, int size);

Food** getGroceryList(const Store& store, int listLength){
    Food** list = new Food*[listLength];

    for(int i = 0; i < listLength; i++){
        Food* item;

        // Continue until unique item found
        do{
            // chooses file
            int randFile = rand()%(3 + 1);
            int val = (rand() % STORE_LENGTH);

            // switch on file and select random item from file
            switch(randFile){
                case 0:
                    item = &store.getProduceAisle()[val];
                    break;
                case 1:
                    item = &store.getFrozenAisle()[val];
                    break;
                case 2:
                    item = &store.getDeliAisle()[val];
                    break;
                case 3:
                    item = &store.getDairyAisle()[val];
                    break;
            }
        } while(containsValue(list, item, STORE_LENGTH));

        list[i] = item;
    }

    return list;
}

// Defines a store with provided dimensions w and h
Store::Store() {
    // initialize arrays
    produceAisle = populateProduce();
    dairyAisle = populateDairy();
    deliAisle = populateDeli();
    frozenAisle = populateFrozen();

    Food** foods = getGroceryList(*this, STORE_LENGTH);

    for(int i = 0; i < STORE_LENGTH; i++){
        cout << foods[i]->print() << endl;
    }
}

/*
 * This is a very specific function. In summary, the function does the following:
 * - Gets a list of random keys, each key indicating the start of a new data entry in the file
 * - From that key, a loop will go through the file and match the line with the key.
 * - If there is a match, record
 */

string* Store::getRandomLinesFromFile(string path, int linesToRead, int lineCap){
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
        lineCount += linesToRead;
    }

    delete[] keys;
    return data;
}

Produce* Store::populateProduce(){
    // get random lines
    string* data = getRandomLinesFromFile(PRODUCE_FILE_PATH, PRODUCE_READ_LINES - 1, STORE_LENGTH);
    Produce* pProduce = new Produce[STORE_LENGTH];

    int produceIndex = 0;

    // Store the data in the pProduce array
    for(int i = 0; i < STORE_LENGTH * (PRODUCE_READ_LINES - 1); i += (PRODUCE_READ_LINES - 1)){

        ProduceType typeKey;
        for(int j = 0; j < sizeof(PRODUCE_STRINGS); j++){
            if(PRODUCE_STRINGS[j] == data[i + 2]){
                typeKey = (ProduceType)j;
            }
        }

        // store data. because of how the loop functions this will not break
        pProduce[produceIndex] = *new Produce(data[i], stod(data[i + 1]), typeKey);
        produceIndex++;
    }

    delete[] data;
    return pProduce;
}

Dairy* Store::populateDairy(){
    // get random lines
    string* data = getRandomLinesFromFile(DAIRY_FILE_PATH, DAIRY_READ_LINES - 1, STORE_LENGTH);
    Dairy* pDairy = new Dairy[STORE_LENGTH];

    int dairyIndex = 0;
    // Store the data in the pDairy array
    for(int i = 0; i < STORE_LENGTH * (DAIRY_READ_LINES - 1); i += (DAIRY_READ_LINES - 1)){
        // store data. because of how the loop functions this will not break
        pDairy[dairyIndex] = *new Dairy(data[i], stod(data[i + 1]), stoi(data[i + 2]));
        dairyIndex++;
    }

    delete[] data;
    return pDairy;
}

Deli* Store::populateDeli(){
    // get random lines
    string* data = getRandomLinesFromFile(DELI_FILE_PATH, DELI_READ_LINES - 1, STORE_LENGTH);
    Deli* pDeli = new Deli[STORE_LENGTH];

    int deliIndex = 0;
    // Store the data in the pDeli array
    for(int i = 0; i < STORE_LENGTH * (DELI_READ_LINES - 1); i += (DELI_READ_LINES - 1)){
        // store data. because of how the loop functions this will not break
        pDeli[deliIndex] = *new Deli(data[i], stod(data[i + 1]), stod(data[i + 2]));
        deliIndex++;
    }

    delete[] data;
    return pDeli;
}

Frozen* Store::populateFrozen(){
    // get random lines
    string* data = getRandomLinesFromFile(FROZEN_FILE_PATH, FROZEN_READ_LINES - 1, STORE_LENGTH);
    Frozen* pFrozen = new Frozen[STORE_LENGTH];

    int frozenIndex = 0;
    // Store the data in the pFrozen array
    for(int i = 0; i < STORE_LENGTH * (FROZEN_READ_LINES - 1); i += (FROZEN_READ_LINES - 1)){
        // store data. because of how the loop functions this will not break
        pFrozen[frozenIndex] = *new Frozen(data[i], stod(data[i + 1]), stoi(data[i + 2]), stoi(data[i + 3]));
        frozenIndex++;
    }

    delete[] data;
    return pFrozen;
}


Store::~Store() {
    // deallocate arrays
    delete[] produceAisle;
    delete[] dairyAisle;
    delete[] deliAisle;
    delete[] frozenAisle;
}

// helper function that checks the array to match values
template<typename T>
bool containsValue(T* arr, T value, int size){
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
int* Store::shuffleKeysFromFile(int size, int linesToSkip, string filePath){
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

Produce* Store::getProduceAisle() const { return produceAisle; }
Dairy* Store::getDairyAisle() const { return dairyAisle; }
Deli* Store::getDeliAisle() const { return deliAisle; }
Frozen* Store::getFrozenAisle() const { return frozenAisle; }