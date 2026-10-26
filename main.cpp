#include "Header.h"
#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [inventory file]\n";
        return 1;
    }

    string filename = argc == 2 ? argv[1] : "inventory.txt";

    try {
        FreshBitRestaurant restaurant;
        if (!restaurant.loadInventory(filename, cerr)) {
            return 1;
        }

        vector<Items> inventory = restaurant.getItems();
        if (inventory.empty()) {
            cout << "There are no products available.\n";
            return 0;
        }

        Orders order;
        bool hasOrder = false;
        string input;
        cout << "Welcome to FreshBitRestaurant!\n";

        while (true) {
            Menu menu;
            for (const Items& item : inventory) {
                menu.addItem(item);
            }
            menu.displayMenu(cout);
            cout << "Choose a product number, or enter 0 to finish: ";
            if (!getline(cin, input)) {
                cout << "\nInput ended.\n";
                return 0;
            }

            istringstream selectionInput(input);
            int selection;
            if (!(selectionInput >> selection)) {
                cout << "Please enter a whole product number.\n";
                continue;
            }
            selectionInput >> ws;
            if (!selectionInput.eof() || selection < 0 ||
                static_cast<size_t>(selection) > inventory.size()) {
                cout << "Invalid product number.\n";
                continue;
            }
            if (selection == 0) {
                break;
            }

            cout << "Quantity: ";
            if (!getline(cin, input)) {
                cout << "\nInput ended.\n";
                return 0;
            }

            istringstream quantityInput(input);
            int quantity;
            if (!(quantityInput >> quantity)) {
                cout << "Please enter a positive whole quantity.\n";
                continue;
            }
            quantityInput >> ws;
            if (!quantityInput.eof() || quantity <= 0) {
                cout << "Please enter a positive whole quantity.\n";
                continue;
            }

            if (!order.addItems(inventory, selection - 1, quantity)) {
                cout << "Cannot add that quantity. Check the remaining stock.\n";
                continue;
            }
            restaurant.setItems(inventory);
            hasOrder = true;
            cout << "Added to your order.\n";
        }

        if (!hasOrder) {
            cout << "No items ordered.\n";
            return 0;
        }

        double amounts[2] = {0.0, 0.0};
        const string prompts[2] = {
            "Tax percentage (for example, 8 for 8%): ",
            "Tip in dollars (0 for no tip): "
        };
        for (int i = 0; i < 2; ++i) {
            while (true) {
                cout << prompts[i];
                if (!getline(cin, input)) {
                    cout << "\nInput ended.\n";
                    return 0;
                }

                istringstream amountInput(input);
                double amount;
                if (amountInput >> amount) {
                    amountInput >> ws;
                    if (amountInput.eof() && isfinite(amount) && amount >= 0) {
                        amounts[i] = amount;
                        break;
                    }
                }
                cout << "Please enter a nonnegative number.\n";
            }
        }

        // generateReceipt calls calculateTotal before saving the receipt.
        order.generateReceipt(amounts[0] / 100.0, amounts[1]);
        order.printReceipt(cout);
    } catch (const exception& error) {
        cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
