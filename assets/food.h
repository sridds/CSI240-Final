//
// Created by Seth Riddensdale on 4/15/24.
//

#ifndef MYPROJECT_FOOD_H
#define MYPROJECT_FOOD_H
#include <iostream>

using namespace std;

enum ProduceType{ EXOTIC, MELON, BERRY, PEPPER, CITRUS, ROOT, GREEN, CRUCIFEROUS, MARROW };
const string PRODUCE_STRINGS[] = { "Exotic", "Melon", "Berry", "Pepper", "Citrus", "Root", "Leafy Green", "Cruciferous", "Marrow" };

struct NutritionFacts{
    double calories;
    double totalFat;
    double sodium;
    double protein;
    double totalSugars;
};

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
private:
    ProduceType type;

public:
    // constructors
    Produce(string name, double price, ProduceType type);

    // getters
    ProduceType getProduceType();

    // methods
    string print() override;
};

class Dairy : Food {
private:
    bool isSpoiled;
    NutritionFacts nutritionFacts;

public:
    // constructors
    Dairy(string name, double price, NutritionFacts nutritionFacts, bool isSpoiled = false);

    // getters / setters
    void setIsSpoiled(bool spoiled);
    bool getIsSpoiled();
    NutritionFacts getNutritionFacts();

    // methods
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
private:
    bool isGlutenFree;
    bool isVegan;

public:
    string print() override;
};

#endif //MYPROJECT_FOOD_H
