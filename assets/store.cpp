//
// Created by Seth Riddensdale on 4/16/24.
//

#include "store.h"
#include "food.h"

Store::Store(int w, int h) {
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

    // loop through array and create new
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            // create new produce
            produceAisle[x][y] = *new Produce("name", 1, EXOTIC);
            dairyAisle[x][y] = *new Dairy("name", 1, NutritionFacts {});
            deliAisle[x][y] = *new Deli("name", 1, 1);
            frozenAisle[x][y] = *new Frozen("name", 1, NutritionFacts {});
        }
    }
}