//
// Created by Seth Riddensdale on 4/15/24.
//

#include "food.h"
#include <sstream>

/*
 * FOOD
 */

Food::Food(){
    name = "null";
    price = 0.0;
}
Produce::Produce() : Food("null", 0.0){
    type = UNDEFINED;
}
Dairy::Dairy() : Food("null", 0.0){
    isSpoiled = false;
}

Deli::Deli() : Food("null", 0.0){
    pounds = 0.0;
}
Frozen::Frozen() : Food("null", 0.0){
    isVegan = false;
    isGlutenFree = false;
}

Food::Food(string name, double price){
    this->name = name;
    this->price = price;
}

string Food::getName() { return name; }
double Food::getPrice() { return price; }

/*
 * PRODUCE
 */

Produce::Produce(string name, double price, ProduceType type) : Food(name, price){
    this->type = type;
}

ProduceType Produce::getProduceType() { return type; }

string Produce::print() {
    stringstream stream;
    stream << name + " ~ $" + to_string(price) + " ~ Type: " + PRODUCE_STRINGS[type];

    return stream.str();
}

/*
 * DELI
 */

Deli::Deli(string name, double price, double pounds) : Food(name, price){
    this->pounds = pounds;
}

double Deli::getPounds(){
    return pounds;
}

string Deli::print() {
    stringstream stream;
    stream << name + " ~ $" + to_string(price) + " ~ Pounds: " + to_string(pounds);

    return stream.str();
}

/*
 * DAIRY
 */

Dairy::Dairy(string name, double price, NutritionFacts nutritionFacts, bool isSpoiled) : Food(name, price){
    this->isSpoiled = isSpoiled;
    this->nutritionFacts = nutritionFacts;
}

void Dairy::setIsSpoiled(bool spoiled) { isSpoiled = spoiled; }
bool Dairy::getIsSpoiled() { return isSpoiled; }
NutritionFacts Dairy::getNutritionFacts() { return nutritionFacts; }

string Dairy::print() {
    stringstream stream;
    stream << name + " ~ $" + to_string(price) + " ~ Spoiled: " + to_string(isSpoiled);

    return stream.str();
}

/*
 * FROZEN
 */

Frozen::Frozen(string name, double price, NutritionFacts nutritionFacts, bool isGlutenFree, bool isVegan) : Food(name, price){
    this->isGlutenFree = isGlutenFree;
    this->isVegan = isVegan;
    this->nutritionFacts = nutritionFacts;
}

bool Frozen::getIsGlutenFree() { return isGlutenFree; }
bool Frozen::getIsVegan() { return isVegan; }
NutritionFacts Frozen::getNutritionFacts() { return nutritionFacts; }

string Frozen::print() {
    stringstream stream;
    stream << name + " ~ $" + to_string(price) + " ~ Gluten Free: " + to_string(isGlutenFree) + " ~ Vegan: " +  to_string(isVegan);

    return stream.str();
}

//ImGui::Begin("Window");
// write in a while loop inside newFrame() before cleanup / end of loop ADTER ImGui::NewFrame
//ImGui::End();