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

class Orders {
private:
    int orderNumber = 1;
    vector<Items> orderItems;
    vector<int> quantities;
    double total = 0.0;
    string receipt;

public:
    int getOrderNumber() const;
    vector<Items> getOrderItems() const;
    vector<int> getQuantities() const;
    double getTotal() const;
    string getReceipt() const;

    void setOrderNumber(int value);
    void setOrderItems(const vector<Items>& value);
    void setQuantities(const vector<int>& value);
    void setTotal(double value);
    void setReceipt(const string& value);

    // index starts at 0; return false for invalid input or insufficient stock.
    bool addItems(vector<Items>& inventory, int index, int quantity);
    // taxRate is a decimal (0.08 = 8%); tip is a dollar amount.
    void calculateTotal(double taxRate, double tip);
    void generateReceipt(double taxRate, double tip);
    void printReceipt(ostream& out) const;
};

class FreshBitRestaurant {
private:
    vector<Items> inventory;
    int size = 0;
    string name = "FreshBitRestaurant";

public:
    string getName() const;
    vector<Items> getItems() const;
    int getSize() const;

    void setName(const string& value);
    // Update size when replacing inventory.
    void setItems(const vector<Items>& value);
    // Only accept a size that matches the number of inventory items.
    void setSize(int value);

    void addItems(const Items& item);
    void displayInventory(ostream& out) const;
    bool loadInventory(const string& filename, ostream& errors);
};

#endif
