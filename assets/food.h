//
// Created by Seth Riddensdale on 4/15/24.
//

#ifndef MYPROJECT_FOOD_H
#define MYPROJECT_FOOD_H
#include <iostream>

using namespace std;

class Food {
protected:
    string name;
    double price;

public:
    // constructors
    Food(string name, double price);

    // getters
    string getName();
    double getPrice();

    // methods
    virtual string print() = 0;
};

class Produce : Food {

    string print() override;
};

class Dairy : Food {
    string print() override;
};

class Baking : Food {
    string print() override;
};

class Spices : Food {
    string print() override;
};

class Deli : Food {
private:
    double pounds;

public:
    Deli(string name, double price, double pounds);

    double getPounds();
    string print() override;
};

class Frozen : Food {

    string print() override;
};

#endif //MYPROJECT_FOOD_H
