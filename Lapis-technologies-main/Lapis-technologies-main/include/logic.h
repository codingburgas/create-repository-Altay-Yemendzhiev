#pragma once

/*
 * logic.h
 * Logic layer for validating, searching, sorting, and totaling inventory data.
 */

#include "data.h"

enum sortField
{
    sortByPrice,
    sortByQuantity
};

enum sortAlgorithm
{
    quickSortAlgorithm,
    bogoSortAlgorithm
};

/*
 * Purpose: Sorts products in ascending order by price using Quick Sort.
 * Parameters: products - product array to sort, count - number of products.
 * Return value: None.
 */
void quickSortByPrice(product products[], int count);

/*
 * Purpose: Sorts products in ascending order by quantity using Quick Sort.
 * Parameters: products - product array to sort, count - number of products.
 * Return value: None.
 */
void quickSortByQuantity(product products[], int count);

/*
 * Purpose: Sorts a small product array using Bogo Sort.
 * Parameters: products - product array to sort, count - number of products,
 *             field - product field used for comparison.
 * Return value: true when sorted, otherwise false after the attempt limit.
 */
bool bogoSortProducts(product products[], int count, sortField field);

/*
 * Purpose: Finds a product by name using a linear search.
 * Parameters: products - product array to search, count - number of products,
 *             query - name or partial name to find.
 * Return value: Matching index when found, otherwise -1.
 */
int linearSearchByName(product products[], int count, const char* query);

/*
 * Purpose: Finds a product by quantity using a linear search.
 * Parameters: products - product array to search, count - number of products,
 *             quantity - exact quantity to find, startIndex - first index to check.
 * Return value: Matching index when found, otherwise -1.
 */
int linearSearchByQuantity(
    product products[],
    int count,
    int quantity,
    int startIndex
);

/*
 * Purpose: Recursively calculates the total inventory value.
 * Parameters: products - product array to total, count - number of products.
 * Return value: Sum of price multiplied by quantity for all products.
 */
float calculateTotalValueRecursive(product products[], int count);

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
 * Purpose: Sorts the stored inventory.
 * Parameters: field - field used for comparison,
 *             algorithm - selected sorting algorithm.
 * Return value: true when sorting succeeds, otherwise false.
 */
bool sortInventory(sortField field, sortAlgorithm algorithm);

/*
 * Purpose: Searches the stored inventory by exact quantity.
 * Parameters: quantity - quantity to find, startIndex - first index to check.
 * Return value: Matching index when found, otherwise -1.
 */
int findProductByQuantity(int quantity, int startIndex);

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
bool getProductForDisplay(int index, product* item);

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
