#include "Header.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <set>
#include <sstream>

using namespace std;

Items::Items(const string& name, int quantity, double price) {
    this->name = name;
    this->quantity = quantity;
    this->price = price;
}

string Items::getName() const {
    return name;
}

void FreshBitRestaurant::addItems(const Items& item) {
    inventory.push_back(item);
    size = static_cast<int>(inventory.size());
}

// Each line contains: "Product name" quantity price.
bool FreshBitRestaurant::loadInventory(const string& filename, ostream& errors) {
    ifstream file(filename);
    if (!file.is_open()) {
        errors << "Cannot open inventory file: " << filename << '\n';
        return false;
    }

    vector<Items> loadedItems;
    set<string> names;
    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        ++lineNumber;
        if (line.find_first_not_of(" \t\r") == string::npos) {
            continue;
        }

        istringstream record(line);
        string itemName;
        int itemQuantity;
        double itemPrice;

        if (!(record >> quoted(itemName) >> itemQuantity >> itemPrice)) {
            errors << "Invalid product on line " << lineNumber << '\n';
            return false;
        }

        record >> ws;
        if (!record.eof() || itemName.find_first_not_of(" \t\r\n") == string::npos ||
            itemQuantity < 0 || !isfinite(itemPrice) || itemPrice < 0) {
            errors << "Invalid product on line " << lineNumber << '\n';
            return false;
        }

        if (!names.insert(itemName).second) {
            errors << "Duplicate product on line " << lineNumber << '\n';
            return false;
        }

        if (loadedItems.size() >= static_cast<size_t>(numeric_limits<int>::max())) {
            errors << "Too many inventory products.\n";
            return false;
        }
        loadedItems.push_back(Items(itemName, itemQuantity, itemPrice));
    }

    if (file.bad()) {
        errors << "Error reading inventory file: " << filename << '\n';
        return false;
    }

    inventory = loadedItems;
    size = static_cast<int>(inventory.size());
    return true;
}
