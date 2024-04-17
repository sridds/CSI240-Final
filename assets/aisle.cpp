//
// Created by Seth Riddensdale on 4/16/24.
//

#include "aisle.h"

Aisle::Aisle(int w, int h, const string path){
    aisle = new Food* [h];

    for(int i = 0; i < h; i++){
        aisle[i] = new Food[w];
    }
}

// food = new Food* [height];
/*
 * for(int i = 0; i < h; i++)
 *      v[i] = new Food[w];
 */
