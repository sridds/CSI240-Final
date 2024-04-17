//
// Created by Seth Riddensdale on 4/16/24.
//

#ifndef MYPROJECT_AISLE_H
#define MYPROJECT_AISLE_H
#include "food.h"

using namespace std;

// acts as a wrapper for the 2D vector

class Aisle {
private:
    // common
    Food** aisle;

    // preferable
    /*
     * Food *v2 = new Food[w * h]
     * for(int i = 0; i < h; i++){
     *      for(int j = 0; j < w; j++){
     *          v2[i * w + j] = 0; // matrix linearization
     *      }
     *  }
     */

public:
    // constructor takes in a path and constructs aisle based on the path data
    Aisle(int rows, int cols, const string path);

    int getRowLength();
    int getColLength();
    Food getItem(int x, int y) const;
};

#endif //MYPROJECT_AISLE_H
