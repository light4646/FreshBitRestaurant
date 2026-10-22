#ifndef FRESHBIT_RESTAURANT_H
#define FRESHBIT_RESTAURANT_H

#include <iosfwd>
#include <string>
#include <vector>

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

class Menu {
private:
    string menuName = "FreshBit Menu";
    vector<Items> menuItems;

public:
    string getMenuName() const;
    vector<Items> getMenuItems() const;

    void setMenuName(const string& value);
    void setMenuItems(const vector<Items>& value);

    void addItem(const Items& item);
    void displayMenu(ostream& out) const;
};

#endif
