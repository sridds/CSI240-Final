//
// Created by Seth Riddensdale on 4/16/24.
//

#include "store.h"
#include "food.h"
#include <fstream>
#include <string.h>

const int STORE_LENGTH = 10;

// Defines a store with provided dimensions w and h
Store::Store() {
    // initialize arrays
    produceAisle = new Produce[STORE_LENGTH];
    dairyAisle = new Dairy[STORE_LENGTH];
    deliAisle = new Deli[STORE_LENGTH];
    frozenAisle = new Frozen[STORE_LENGTH];

    ifstream produceIn("produce.txt", ios::in);
    string produceName, produceCost, produceType, trash = "";

    // read in
    int index = 0;
    while(!produceIn.eof()){
        // ensure index does not surpass array const length
        if(index >= STORE_LENGTH) break;

        // get name, cost, and type from file
        getline(produceIn, produceName);
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
    }

    produceIn.close();
}