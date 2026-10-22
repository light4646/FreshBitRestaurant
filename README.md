# FreshBitRestaurant

FreshBitRestaurant is a C++ restaurant ordering program, It uses four classes: FreshBitRestaurant, Menu, Items, and Orders.

The program loads products from an inventory file when it starts. Each product has a name, an available quantity, and a unit price. Customers can view a numbered menu, select a product, and enter how many they want. They can keep adding products until they are ready to check out. Selecting the same product again adds to the quantity already ordered.

The program checks for invalid selections, quantities of zero or less, and orders that exceed the remaining stock. After the customer finishes ordering, it prints a receipt showing the products purchased, quantities, unit prices, and line totals. The receipt also includes tax, an optional tip, and the final total, with prices shown to two decimal places.
