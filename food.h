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

#ifndef MYPROJECT_FOOD_H
#define MYPROJECT_FOOD_H
#include <iostream>

using namespace std;

// An enum for the produce type and the corresponding strings for each value
enum ProduceType{ FRUIT, EXOTIC, MELON, BERRY, PEPPER, CITRUS, ROOT, GREEN, CRUCIFEROUS, FUNGUS, UNDEFINED = -1 };
const string PRODUCE_STRINGS[] = { "Fruit", "Exotic", "Melon", "Berry", "Pepper", "Citrus", "Root", "Leafy Green", "Cruciferous", "Fungus" };

class Food {
protected:
    string name;
    double price;
    bool isCollected;

public:
    // constructors
    Food();
    Food(string name, double price);

    // deconstructor
    virtual ~Food(){};

    // getters
    string getName() const;
    double getPrice() const;
    bool getIsCollected() const;

    // setters
    void setIsCollected(bool isCollected);

    // methods
    virtual string print() = 0;

    bool operator==(const Food& other) const;
};

class Produce : public Food {
private:
    ProduceType type;

public:
    // constructors
    Produce();
    Produce(string name, double price, ProduceType type);

    // getters
    ProduceType getProduceType();

    // methods
    string print() override;
};

class Dairy : public Food {
private:
    bool isSpoiled;

public:
    // constructors
    Dairy();
    Dairy(string name, double price, bool isSpoiled = false);

    // getters / setters
    void setIsSpoiled(bool spoiled);
    bool getIsSpoiled() const;

    // methods
    string print() override;
};

class Deli : public Food {
private:
    double pounds;

public:
    Deli();
    Deli(string name, double price, double pounds);

    double getPounds() const;
    string print() override;
};

class Frozen : public Food {
private:
    bool isGlutenFree;
    bool isVegan;

public:
    // constructors
    Frozen();
    Frozen(string name, double price, bool isGlutenFree = false, bool isVegan = false);

    // getters
    bool getIsGlutenFree();
    bool getIsVegan();

    // methods
    string print() override;
};

#endif //MYPROJECT_FOOD_H
