#pragma once

/*
 * logic.h
 * Logic layer for validating, searching, sorting, and totaling inventory data.
 */

#include "data.h"

/*
 * Purpose: Sorts products in ascending order by price using Bubble Sort.
 * Parameters: products - product array to sort, count - number of products.
 * Return value: None.
 */
void bubbleSortByPrice(Product products[], int count);

/*
 * Purpose: Sorts products in ascending order by quantity using Bubble Sort.
 * Parameters: products - product array to sort, count - number of products.
 * Return value: None.
 */
void bubbleSortByQuantity(Product products[], int count);

/*
 * Purpose: Finds a product by name using a linear search.
 * Parameters: products - product array to search, count - number of products,
 *             query - name or partial name to find.
 * Return value: Matching index when found, otherwise -1.
 */
int linearSearchByName(Product products[], int count, const char* query);

/*
 * Purpose: Recursively calculates the total inventory value.
 * Parameters: products - product array to total, count - number of products.
 * Return value: Sum of price multiplied by quantity for all products.
 */
float calculateTotalValueRecursive(Product products[], int count);

/*
 * Purpose: Validates user input and adds a product through the data layer.
 * Parameters: name - product name, price - product price,
 *             quantity - product quantity.
 * Return value: true when validation and storage succeed, otherwise false.
 */
bool addNewProduct(const char* name, float price, int quantity);

/*
 * Purpose: Updates the quantity of one product through the data layer.
 * Parameters: index - zero-based product index, quantity - new quantity.
 * Return value: true when validation and storage succeed, otherwise false.
 */
bool updateProductQuantity(int index, int quantity);

/*
 * Purpose: Removes one product through the data layer.
 * Parameters: index - zero-based product index.
 * Return value: true when the product was removed, otherwise false.
 */
bool deleteProductByIndex(int index);

/*
 * Purpose: Sorts the stored inventory by price.
 * Parameters: None.
 * Return value: None.
 */
void sortInventoryByPrice();

/*
 * Purpose: Sorts the stored inventory by quantity.
 * Parameters: None.
 * Return value: None.
 */
void sortInventoryByQuantity();

/*
 * Purpose: Searches the stored inventory by name.
 * Parameters: query - name or partial name to find.
 * Return value: Matching index when found, otherwise -1.
 */
int findProductByName(const char* query);

/*
 * Purpose: Calculates the total value of the stored inventory.
 * Parameters: None.
 * Return value: Total value of all products.
 */
float calculateInventoryTotalValue();

/*
 * Purpose: Provides one product for display without exposing data functions.
 * Parameters: index - zero-based product index, product - destination pointer.
 * Return value: true when a product was copied, otherwise false.
 */
bool getProductForDisplay(int index, Product* product);

/*
 * Purpose: Provides product count access to the presentation layer.
 * Parameters: None.
 * Return value: Current product count.
 */
int getProductCountForDisplay();

/*
 * Purpose: Saves inventory through the data layer.
 * Parameters: filename - path to the file that will receive persisted products.
 * Return value: true when saving succeeds, otherwise false.
 */
bool saveInventoryToFile(const char* filename);

/*
 * Purpose: Loads inventory through the data layer.
 * Parameters: filename - path to the file that contains persisted products.
 * Return value: true when loading succeeds, otherwise false.
 */
bool loadInventoryFromFile(const char* filename);
