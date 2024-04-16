//
// Created by Seth Riddensdale on 4/16/24.
//

#ifndef MYPROJECT_AISLE_H
#define MYPROJECT_AISLE_H
#include<vector>
#include "food.h"

using namespace std;

// acts as a wrapper for the 2D vector
class Aisle {
private:
    vector<vector<Food>> myAisle;

public:
    Aisle(int rows, int cols, const string textFile);

    int getRowLength();
    int getColLength();
    Food getItem(int x, int y) const;
};

#endif //MYPROJECT_AISLE_H
