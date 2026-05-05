#pragma once

/*
 * data.h
 * Data layer for storing and loading inventory product records.
 */

enum
{
    MAX_PRODUCTS = 500,
    MAX_NAME_LENGTH = 100
};

struct Product
{
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
};

/*
 * Purpose: Loads product records from a CSV file into the inventory.
 * Parameters: filename - path to the file that contains persisted products.
 * Return value: true when the file was opened and parsed, otherwise false.
 */
bool loadFromFile(const char* filename);

/*
 * Purpose: Saves all current product records to a CSV file.
 * Parameters: filename - path to the file that will receive persisted products.
 * Return value: true when the file was opened and written, otherwise false.
 */
bool saveToFile(const char* filename);

/*
 * Purpose: Adds one product to the fixed-size inventory array.
 * Parameters: product - product value to append to the inventory.
 * Return value: true when the product was added, otherwise false when full.
 */
bool addProduct(Product product);

/*
 * Purpose: Replaces one product at a valid inventory index.
 * Parameters: index - zero-based product index, product - new product data.
 * Return value: true when the product was replaced, otherwise false.
 */
bool updateProduct(int index, Product product);

/*
 * Purpose: Removes one product from the inventory.
 * Parameters: index - zero-based product index to remove.
 * Return value: true when a product was removed, otherwise false.
 */
bool removeProduct(int index);

/*
 * Purpose: Copies one product into an output parameter.
 * Parameters: index - zero-based product index, product - destination pointer.
 * Return value: true when a product was copied, otherwise false.
 */
bool getProduct(int index, Product* product);

/*
 * Purpose: Provides access to the inventory array for the logic layer.
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
