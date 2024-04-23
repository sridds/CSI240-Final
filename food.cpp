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

double Deli::getPounds() const{
    return pounds;
}

string Deli::print() {
    stringstream stream;
    stream.setf(ios::fixed, ios::floatfield);
    stream.setf(ios::showpoint);
    stream.precision(2);

    if (isCollected) stream << "(COLLECTED)";
    else{
        stream << name + " $" << price << " (Pounds: " << pounds << ")";
    }

    return stream.str();
}

/* DAIRY */

Dairy::Dairy(string name, double price, bool isSpoiled) : Food(name, price){
    this->isSpoiled = isSpoiled;
}

void Dairy::setIsSpoiled(bool spoiled) { isSpoiled = spoiled; }
bool Dairy::getIsSpoiled() const { return isSpoiled; }

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

Frozen::~Frozen() {
    cout << "Deconstructed Frozen" << endl;
}

Deli::~Deli() {
    cout << "Deconstructed Deli" << endl;
}

Produce::~Produce() {
    cout << "Deconstructed Produce" << endl;
}

Dairy::~Dairy() {
    cout << "Deconstructed Dairy" << endl;
}