#ifndef FRESHBIT_RESTAURANT_H
#define FRESHBIT_RESTAURANT_H

#include <string>

using namespace std;

class Items {
private:
    string name;
    int quantity = 0;
    double price = 0.0;

public:
    Items(const string& name, int quantity, double price);

    string getName() const;
    int getQuantity() const;
    double getPrice() const;

    void setName(const string& value);
    void setQuantity(int value);
    void setPrice(double value);
};

#endif
