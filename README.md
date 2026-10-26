# FreshBitRestaurant

FreshBitRestaurant is a C++ restaurant ordering program. It loads products from an inventory file, displays a numbered menu, takes customer orders, and prints an itemized receipt.

Each product has a name, an available quantity, and a unit price. Customers select products by their menu numbers and enter the quantities they want. They can keep adding products or enter 0 to finish. Selecting the same product again adds to the quantity already ordered, and the menu updates to show the remaining stock.

The program rejects invalid selections, quantities of zero or less, and requests that exceed the available stock. It also displays an error if the inventory file cannot be opened or contains invalid product records.

At checkout, the customer enters a tax percentage and an optional tip amount. The receipt shows each purchased product’s name, combined quantity, unit price, and line total, followed by the subtotal, tax, tip, and final total. All monetary amounts are displayed with two decimal places.

## Program files

- `Header.h` contains the four classes and their function declarations.
- `functions.cpp` contains the function definitions.
- `main.cpp` handles startup, customer input, ordering, and checkout.
- `inventory.txt` contains the product names, quantities, and prices.

The four classes are `Items`, `Menu`, `Orders`, and `FreshBitRestaurant`.

## Inventory format

Each line contains a product name, quantity, and unit price. Names containing spaces are enclosed in quotation marks.

```text
"Fruit Bowl" 12 4.50
"Chicken Sandwich" 10 7.25
"Water" 20 1.50
```

## Build and run

Compile the program using C++17:

```sh
g++ -std=c++17 main.cpp functions.cpp -o FreshBitRestaurant
```

Run it with the inventory file:

```sh
./FreshBitRestaurant inventory.txt
```

If no filename is provided, the program uses `inventory.txt` from the current folder.
