#include "Header.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <map>
#include <stdexcept>
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

void FreshBitRestaurant::displayInventory(ostream& out) const {
    if (inventory.empty()) {
        out << "Inventory is empty.\n";
        return;
    }

    ostringstream display;
    display << "Inventory\n" << fixed << setprecision(2);
    for (const Items& item : inventory) {
        display << item.getName()
                << " | Available: " << item.getQuantity()
                << " | Price: $" << item.getPrice() << '\n';
    }
    out << display.str();
}

void Menu::addItem(const Items& item) {
    menuItems.push_back(item);
}

void Menu::displayMenu(ostream& out) const {
    if (menuItems.empty()) {
        out << "No products on the menu.\n";
        return;
    }

    ostringstream display;
    display << menuName << '\n' << fixed << setprecision(2);
    for (size_t i = 0; i < menuItems.size(); ++i) {
        display << i + 1 << ". " << menuItems[i].getName()
                << " | Price: $" << menuItems[i].getPrice()
                << " | Available: " << menuItems[i].getQuantity() << '\n';
    }
    out << display.str();
}

void Orders::generateReceipt(double taxRate, double tip) {
    if (!isfinite(taxRate) || taxRate < 0 || !isfinite(tip) || tip < 0) {
        throw invalid_argument("Tax and tip must be nonnegative numbers.");
    }
    if (orderItems.size() != quantities.size()) {
        throw invalid_argument("Order items and quantities do not match.");
    }

    // Store one price and combined quantity for each product name.
    map<string, pair<double, long long>> receiptItems;
    for (size_t i = 0; i < orderItems.size(); ++i) {
        string itemName = orderItems[i].getName();
        double itemPrice = orderItems[i].getPrice();
        if (itemName.empty() || quantities[i] <= 0 ||
            !isfinite(itemPrice) || itemPrice < 0) {
            throw invalid_argument("The order contains an invalid product.");
        }

        auto found = receiptItems.find(itemName);
        if (found == receiptItems.end()) {
            receiptItems[itemName] = make_pair(itemPrice, quantities[i]);
        } else {
            if (found->second.first != itemPrice) {
                throw invalid_argument("Repeated products must have the same unit price.");
            }
            found->second.second += quantities[i];
        }
    }

    ostringstream output;
    output << fixed << setprecision(2);
    output << "FreshBitRestaurant\nReceipt - Order #" << orderNumber << '\n';
    if (receiptItems.empty()) {
        output << "No items ordered.\n";
    }

    double subtotal = 0.0;
    for (const auto& entry : receiptItems) {
        double unitPrice = entry.second.first;
        long long quantity = entry.second.second;
        double lineTotal = unitPrice * quantity;
        output << entry.first << " | Qty: " << quantity
               << " | Unit price: $" << unitPrice
               << " | Line total: $" << lineTotal << '\n';
        subtotal += lineTotal;
    }

    double tax = subtotal * taxRate;
    if (!isfinite(subtotal) || !isfinite(tax) || !isfinite(subtotal + tax + tip)) {
        throw overflow_error("The order amount is too large.");
    }

    // Brian's function sets the final total, including tax and tip.
    calculateTotal(taxRate, tip);
    if (!isfinite(total) || total < 0) {
        throw invalid_argument("The calculated order total is invalid.");
    }
    output << "Subtotal: $" << subtotal << '\n'
           << "Tax: $" << tax << '\n'
           << "Tip: $" << tip << '\n'
           << "Total: $" << total << '\n';
    receipt = output.str();
}

void Orders::printReceipt(ostream& out) const {
    out << receipt;
}

int Items::getQuantity() const {
    return quantity;
}
