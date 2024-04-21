//
// Created by Seth Riddensdale on 4/15/24.
//

#include "food.h"
#include <sstream>
#include <fstream>

/* FOOD */

Food::Food(){
    name = "null";
    price = 0.0;
}

bool Food::operator==(const Food& other) const{
    return name == other.getName();
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
    this->isCollected = false;
}

string Food::getName() const { return name; }
double Food::getPrice() const { return price; }
bool Food::getIsCollected() const { return isCollected; }
void Food::setIsCollected(bool isCollected) { this->isCollected = isCollected; }

/* PRODUCE */

Produce::Produce(string name, double price, ProduceType type) : Food(name, price){
    this->type = type;
}

ProduceType Produce::getProduceType() { return type; }

string Produce::print() {
    stringstream stream;
    stream.setf(ios::fixed, ios::floatfield);
    stream.setf(ios::showpoint);
    stream.precision(2);

    if(isCollected) stream << "(COLLECTED)";
    else stream << name << " $" << price << " (" << PRODUCE_STRINGS[type] << ")";

    return stream.str();
}

/* DELI */

Deli::Deli(string name, double price, double pounds) : Food(name, price){
    this->pounds = pounds;
}

double Deli::getPounds(){
    return pounds;
}

string Deli::print() {
    stringstream stream;
    stream.setf(ios::fixed, ios::floatfield);
    stream.setf(ios::showpoint);
    stream.precision(2);
    stream << name + " $" << price << " (Pounds: " << pounds << ")";

    return stream.str();
}

/* DAIRY */

Dairy::Dairy(string name, double price, bool isSpoiled) : Food(name, price){
    this->isSpoiled = isSpoiled;
}

void Dairy::setIsSpoiled(bool spoiled) { isSpoiled = spoiled; }
bool Dairy::getIsSpoiled() { return isSpoiled; }

string Dairy::print() {
    stringstream stream;
    stream.setf(ios::fixed, ios::floatfield);
    stream.setf(ios::showpoint);
    stream.precision(2);

    if(isCollected) stream << "(COLLECTED)";
    else{
        stream << name << " $" << price;
        if(isSpoiled) stream << " (Spoiled)";
    }

    return stream.str();
}

/* FROZEN */

Frozen::Frozen(string name, double price, bool isGlutenFree, bool isVegan) : Food(name, price){
    this->isGlutenFree = isGlutenFree;
    this->isVegan = isVegan;
}

bool Frozen::getIsGlutenFree() { return isGlutenFree; }
bool Frozen::getIsVegan() { return isVegan; }

string Frozen::print() {
    stringstream stream;
    stream.setf(ios::fixed, ios::floatfield);
    stream.setf(ios::showpoint);
    stream.precision(2);

    if(isCollected) stream << "(COLLECTED)";
    else{
        stream << name << " $" << price;
        if(isGlutenFree) stream << " (Gluten Free)";
        if(isVegan) stream << " (Vegan)";
    }

    return stream.str();
}

//ImGui::Begin("Window");
// write in a while loop inside newFrame() before cleanup / end of loop ADTER ImGui::NewFrame
//ImGui::End();