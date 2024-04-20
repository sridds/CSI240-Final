//
// Created by Seth Riddensdale on 4/15/24.
//

#ifndef MYPROJECT_FOOD_H
#define MYPROJECT_FOOD_H
#include <iostream>

using namespace std;

enum ProduceType{ FRUIT, EXOTIC, MELON, BERRY, PEPPER, CITRUS, ROOT, GREEN, CRUCIFEROUS, FUNGUS, UNDEFINED = -1 };
const string PRODUCE_STRINGS[] = { "Fruit", "Exotic", "Melon", "Berry", "Pepper", "Citrus", "Root", "Leafy Green", "Cruciferous", "Fungus" };

class Food {
protected:
    string name;
    double price;

public:
    // constructors
    Food();
    Food(string name, double price);

    // getters
    string getName();
    double getPrice();

    // methods
    virtual string print() = 0;

    // checks equality based on name
    template <typename T>
    friend bool operator==(const T& a, const T& b){
        return a.name == b.name;
    }
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
    bool getIsSpoiled();

    // methods
    string print() override;
};

class Deli : public Food {
private:
    double pounds;

public:
    Deli();
    Deli(string name, double price, double pounds);

    double getPounds();
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
