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

#include "store.h"
#include "food.h"
#include <fstream>
#include <sstream>
#include "exceptions.h"

/* The following code is responsible for generating a shopping list from a provided store reference
 * ~ store: A constant reference that will be used to select items from
 * ~ listLength: A variable that will determine how long the shopping list will be
 * Since Food is an abstract class, a double pointer is returned */
Food** Store::setupGroceryList(int listLength){
    Food** list = new Food*[listLength];

    // Create the shopping list
    for(int i = 0; i < listLength; i++){
        Food* item;
        // Continue until unique item found
        do{
            // Select a random file
            int randFile = rand()%(FILES_TO_READ);
            int val = (rand() % STORE_LENGTH);

            // Switch on random value and get a value from the corresponding file
            switch(randFile){
                case 0:
                    item = &getProduceAisle()[val];
                    break;
                case 1:
                    item = &getFrozenAisle()[val];
                    break;
                case 2:
                    item = &getDeliAisle()[val];
                    break;
                case 3:
                    item = &getDairyAisle()[val];
                    break;
            }
        } while(containsValue(list, item, STORE_LENGTH));

        // Set the value after verified to be a unique file
        list[i] = item;
    }

    return list;
}

/* This is a helper method that checks if all items on the grocery list have been found. */
bool Store::isGroceryListComplete() const {
    // loop through the store, if any are not collected, return false
    for(int i = 0; i < STORE_LENGTH; i++){
        if(groceryList[i]->getIsCollected() == false) return false;
    }

    return true;
}

/* This function is responsible for getting all items collected on the list and returning the total price of all items */
double Store::getPriceOfCollected() const{
    double price = 0.0;

    for(int i = 0; i < STORE_LENGTH; i++){
        if(groceryList[i]->getIsCollected()){
            price += groceryList[i]->getPrice();
        }
    }

    return price;
}

/* This function attempts to collect a grocery item and mark it as collected */
bool Store::tryCollectGroceryItem(Food* item) {
    // loop through array and compare if the items match
    for(int i = 0; i < STORE_LENGTH; i++){
        if(*item == *groceryList[i]){
            // set the item as collected
            groceryList[i]->setIsCollected(true);
            return true;
        }
    }
    return false;
}

// This constructor is responsible for initalizing the aisle pointer arrays
Store::Store() {
    // Populate all aisles with data and setup the list
    produceAisle = populateProduce();
    dairyAisle = populateDairy();
    deliAisle = populateDeli();
    frozenAisle = populateFrozen();
    groceryList = setupGroceryList(STORE_LENGTH);
}

/* This is a very specific function. In summary, the function does the following:
 * - Gets a list of random keys, each key indicating the start of a new data entry in the file
 * - From that key, a loop will go through the file and match the line with the key.
 * - If there is a match, record */
string* Store::getRandomLinesFromFile(string path, int linesToRead, int lineCap){
    // Open file. If failed, return null
    ifstream fileIn(path, ios::in);
    if(fileIn.fail()) {
        fileIn.close();
        throw FileNotFound(path);
    }

    string* data = new string[lineCap * linesToRead];
    // Generate a list of random keys use to pick random lines from the file. Each key indicates the start of a new data entry
    int* keys = shuffleKeysFromFile(lineCap, linesToRead + 1, path);
    int index = 0, lineCount = 0;
    string trash;

    // Populate data
    while(!fileIn.eof()){
        // Ensure the index does not exceed the line cap
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

    // Ensure keys is deallocated before leaving the scope of the function
    delete[] keys;
    return data;
}

/* The following function is responsible for populating the Produce aisle with a bunch of random data from the file.
 * Getting random data entries is already handled by getRandomLinesFromFile(), so this function merely determines how to interpret the data. */
Produce* Store::populateProduce(){
    // Get random lines using the helper function
    try{
        string* data = getRandomLinesFromFile(PRODUCE_FILE_PATH, PRODUCE_READ_LINES - 1, STORE_LENGTH);

        Produce* pProduce = new Produce[STORE_LENGTH];

        int produceIndex = 0;

        // Store the data in the pProduce array
        for(int i = 0; i < STORE_LENGTH * (PRODUCE_READ_LINES - 1); i += (PRODUCE_READ_LINES - 1)){

            // Converts the line to a produce type by comparing the line to every entry in PRODUCE_STRINGS
            ProduceType typeKey;
            for(int j = 0; j < sizeof(PRODUCE_STRINGS); j++){
                if(PRODUCE_STRINGS[j] == data[i + 2]){
                    typeKey = (ProduceType)j;
                }
            }

            // Store data. Because of how the loop functions this will not break
            pProduce[produceIndex] = *new Produce(data[i], stod(data[i + 1]), typeKey);
            produceIndex++;
        }

        // Deallocate data before leaving function scope
        delete[] data;
        return pProduce;
    }
    // Catch file exception
    catch(FileNotFound fileNotFound){
        cout << "Failed to open file: \"" << fileNotFound.getFilePath() << "\"!" << endl;
        exit(0);
    }
}

/* The following function is responsible for populating the Dairy aisle with a bunch of random data from the file.
 * Getting random data entries is already handled by getRandomLinesFromFile(), so this function merely determines how to interpret the data. */
Dairy* Store::populateDairy(){
    // get random lines
    try{
        string* data = getRandomLinesFromFile(DAIRY_FILE_PATH, DAIRY_READ_LINES - 1, STORE_LENGTH);
        Dairy* pDairy = new Dairy[STORE_LENGTH];

        int dairyIndex = 0;
        // Store the data in the pDairy array
        for(int i = 0; i < STORE_LENGTH * (DAIRY_READ_LINES - 1); i += (DAIRY_READ_LINES - 1)){
            // store data. because of how the loop functions this will not break
            pDairy[dairyIndex] = *new Dairy(data[i], stod(data[i + 1]), stoi(data[i + 2]));
            dairyIndex++;
        }

        // Deallocate data
        delete[] data;
        return pDairy;
    }
    // Catch file exception
    catch(FileNotFound fileNotFound){
        cout << "Failed to open file: \"" << fileNotFound.getFilePath() << "\"!" << endl;
        exit(0);
    }
}

/* The following function is responsible for populating the Deli aisle with a bunch of random data from the file.
 * Getting random data entries is already handled by getRandomLinesFromFile(), so this function merely determines how to interpret the data. */
Deli* Store::populateDeli(){
    // get random lines
    try{
        string* data = getRandomLinesFromFile(DELI_FILE_PATH, DELI_READ_LINES - 1, STORE_LENGTH);
        Deli* pDeli = new Deli[STORE_LENGTH];

        int deliIndex = 0;
        // Store the data in the pDeli array
        for(int i = 0; i < STORE_LENGTH * (DELI_READ_LINES - 1); i += (DELI_READ_LINES - 1)){
            // store data. because of how the loop functions this will not break
            pDeli[deliIndex] = *new Deli(data[i], stod(data[i + 1]), stod(data[i + 2]));
            deliIndex++;
        }

        // Ensure data is deallocated
        delete[] data;
        return pDeli;
    }
    // Catch file exception
    catch(FileNotFound fileNotFound){
        cout << "Failed to open file: \"" << fileNotFound.getFilePath() << "\"!" << endl;
        exit(0);
    }
}

/* The following function is responsible for populating the Frozen aisle with a bunch of random data from the file.
 * Getting random data entries is already handled by getRandomLinesFromFile(), so this function merely determines how to interpret the data. */
Frozen* Store::populateFrozen(){
    // get random lines
    try{
        string* data = getRandomLinesFromFile(FROZEN_FILE_PATH, FROZEN_READ_LINES - 1, STORE_LENGTH);
        Frozen* pFrozen = new Frozen[STORE_LENGTH];

        int frozenIndex = 0;
        // Store the data in the pFrozen array
        for(int i = 0; i < STORE_LENGTH * (FROZEN_READ_LINES - 1); i += (FROZEN_READ_LINES - 1)){
            // store data. because of how the loop functions this will not break
            pFrozen[frozenIndex] = *new Frozen(data[i], stod(data[i + 1]), stoi(data[i + 2]), stoi(data[i + 3]));
            frozenIndex++;
        }

        // Ensure deallocation
        delete[] data;
        return pFrozen;
    }
    // Catch file exception
    catch(FileNotFound fileNotFound){
        cout << "Failed to open file: \"" << fileNotFound.getFilePath() << "\"!" << endl;
        exit(0);
    }
}

// This destructor primarily handles the deallocation of aisles to ensure proper cleanup.
Store::~Store() {
    // deallocate grocery list
    for (int i = 0; i < STORE_LENGTH; i++)
        delete[] groceryList[i];

    delete[] groceryList;

    // deallocate aisles
    delete[] produceAisle;
    delete[] dairyAisle;
    delete[] deliAisle;
    delete[] frozenAisle;
}

// Helper function that checks if a pointer array contains a value. Works with any type
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
 * A line key refers to the start of each data entry. With a key, we can use a loop to go through the file again later and compare the current line with the key.
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

    // Randomize
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

// Getters
Food** Store::getGroceryList() const { return groceryList; }
Produce* Store::getProduceAisle() const { return produceAisle; }
Dairy* Store::getDairyAisle() const { return dairyAisle; }
Deli* Store::getDeliAisle() const { return deliAisle; }
Frozen* Store::getFrozenAisle() const { return frozenAisle; }

// The following function feeds the entire Produce aisle into a string stream and returns a string
string Store::printProduceAisle(){
    stringstream stream;
    for(int i = 0; i < STORE_LENGTH; i++){
        stream << to_string((i+1)) << ". " << produceAisle[i].print() << endl;
    }
    return stream.str();
}

// The following function feeds the entire Dairy aisle into a string stream and returns a string
string Store::printDairyAisle(){
    stringstream stream;
    for(int i = 0; i < STORE_LENGTH; i++){
        stream << to_string((i+1)) << ". " << dairyAisle[i].print() << endl;
    }
    return stream.str();
}

// The following function feeds the entire Deli aisle into a string stream and returns a string
string Store::printDeliAisle(){
    stringstream stream;
    for(int i = 0; i < STORE_LENGTH; i++){
        stream << to_string((i+1)) << ". " << deliAisle[i].print() << endl;
    }
    return stream.str();
}

// The following function feeds the entire Frozen aisle into a string stream and returns a string
string Store::printFrozenAisle(){
    stringstream stream;
    for(int i = 0; i < STORE_LENGTH; i++){
        stream << to_string((i+1)) << ". " << frozenAisle[i].print() << endl;
    }
    return stream.str();
}