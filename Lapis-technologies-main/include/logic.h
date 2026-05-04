#pragma once

#include "data.h"

/*
 * Purpose: Sorts products in ascending order by price using Bubble Sort.
 * Parameters: arr - product array to sort, n - number of products in arr.
 * Return value: None.
 */
void bubbleSortByPrice(Product arr[], int n);

/*
 * Purpose: Sorts products in ascending order by quantity using Bubble Sort.
 * Parameters: arr - product array to sort, n - number of products in arr.
 * Return value: None.
 */
void bubbleSortByQuantity(Product arr[], int n);

/*
 * Purpose: Finds a product by name using a linear search.
 * Parameters: arr - product array to search, n - number of products,
 *             query - name or partial name to find.
 * Return value: Matching index when found, otherwise -1.
 */
int linearSearchByName(Product arr[], int n, const char* query);

/*
 * Purpose: Recursively calculates the total inventory value.
 * Parameters: arr - product array to total, n - number of products.
 * Return value: Sum of price multiplied by quantity for all products.
 */
float calculateTotalValueRecursive(Product arr[], int n);

/*
 * Purpose: Validates user input and adds a product through the data layer.
 * Parameters: name - product name, price - product price,
 *             quantity - product quantity.
 * Return value: true when validation and storage succeed, otherwise false.
 */
bool addNewProduct(const char* name, float price, int quantity);

/*
 * Purpose: Provides inventory access to the presentation layer.
 * Parameters: None.
 * Return value: Pointer to the first product in the inventory array.
 */
Product* getInventoryForDisplay();

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
