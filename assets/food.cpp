//
// Created by Seth Riddensdale on 4/15/24.
//

#include "food.h"
#include <sstream>

Food::Food(string name, double price){
    this->name = name;
    this->price = price;
}

string Food::getName() { return name; }
double Food::getPrice() { return price; }

// Deli
Deli::Deli(string name, double price, double pounds) : Food(name, price){
    this->pounds = pounds;
}

double Deli::getPounds(){
    return pounds;
}

string Deli::print() {
    stringstream stream;
    stream << name + " ~ $" + to_string(price) + " ~ Pounds: " + to_string(pounds);
}