//
// Created by Seth Riddensdale on 4/16/24.
//

#include "store.h"
#include "food.h"
#include <fstream>

// Defines a store with provided dimensions w and h
Store::Store(int w, int h) {
    // initialize arrays
    produceAisle = new Produce*[w];
    dairyAisle = new Dairy*[w];
    deliAisle = new Deli*[w];
    frozenAisle = new Frozen*[w];

    for(int i = 0; i < w; i++){
        produceAisle[i] = new Produce[h];
        dairyAisle[i] = new Dairy[h];
        deliAisle[i] = new Deli[h];
        frozenAisle[i] = new Frozen[h];
    }

    ifstream produceIn("produce.txt", ios::in);

    string produceLine = "";
    while(!produceIn.eof()){
        getline(produceIn, produceLine);

        cout << produceIn << endl;
    }

    // loop through array and create new
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            // create new produce
            produceAisle[x][y] = *new Produce("name", 1, EXOTIC);
            dairyAisle[x][y] = *new Dairy("name", 1);
            deliAisle[x][y] = *new Deli("name", 1, 1);
            frozenAisle[x][y] = *new Frozen("name", 1);
        }
    }
}