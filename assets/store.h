//
// Created by Seth Riddensdale on 4/16/24.
//

#ifndef MYPROJECT_STORE_H
#define MYPROJECT_STORE_H
#include <iostream>
#include "food.h"

using namespace std;
class Store {
private:
    // aisle references
    Produce* produceAisle;
    Dairy* dairyAisle;
    Deli* deliAisle;
    Frozen* frozenAisle;

public:
    // constructors
    Store();
};


#endif //MYPROJECT_STORE_H
