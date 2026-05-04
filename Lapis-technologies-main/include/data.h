#pragma once

enum
{
    MAX_PRODUCTS = 100,
    MAX_NAME_LENGTH = 100
};

struct Product
{
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
};

/*
 * Purpose: Loads product records from a CSV-like file into the inventory.
 * Parameters: filename - path to the file that contains persisted products.
 * Return value: true when the file was opened and parsed, otherwise false.
 */
bool loadFromFile(const char* filename);

/*
 * Purpose: Saves all current product records to a CSV-like file.
 * Parameters: filename - path to the file that will receive persisted products.
 * Return value: true when the file was opened and written, otherwise false.
 */
bool saveToFile(const char* filename);

/*
 * Purpose: Adds one product to the fixed-size inventory array.
 * Parameters: p - product value to append to the inventory.
 * Return value: true when the product was added, otherwise false when full.
 */
bool addProduct(Product p);

/*
 * Purpose: Provides access to the inventory array.
 * Parameters: None.
 * Return value: Pointer to the first product in the inventory array.
 */
Product* getInventory();

/*
 * Purpose: Provides the number of products currently stored.
 * Parameters: None.
 * Return value: Current product count.
 */
int getProductCount();
