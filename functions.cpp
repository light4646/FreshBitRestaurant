#include "Header.h"

using namespace std;

Items::Items(const string& name, int quantity, double price) {
    this->name = name;
    this->quantity = quantity;
    this->price = price;
}

string Items::getName() const {
    return name;
}

