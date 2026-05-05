#include "../include/logic.h"

#include <cctype>
#include <cstring>

/*
 * Purpose: Checks whether a product name contains at least one visible character.
 * Parameters: name - product name to inspect.
 * Return value: true when the name is valid, otherwise false.
 */
static bool hasVisibleText(const char* name)
{
    if (name == nullptr)
    {
        return false;
    }

    for (int i = 0; name[i] != '\0'; ++i)
    {
        if (!std::isspace(static_cast<unsigned char>(name[i])))
        {
            return true;
        }
    }

    return false;
}

/*
 * Purpose: Copies text into a fixed-size product name buffer safely.
 * Parameters: destination - target buffer, source - text to copy.
 * Return value: None.
 */
static void copyProductName(char destination[MAX_NAME_LENGTH], const char* source)
{
    std::strncpy(destination, source, MAX_NAME_LENGTH - 1);
    destination[MAX_NAME_LENGTH - 1] = '\0';
}

/*
 * Purpose: Compares a character case-insensitively.
 * Parameters: left - first character, right - second character.
 * Return value: true when both characters match ignoring case.
 */
static bool sameLetterIgnoreCase(char left, char right)
{
    return std::tolower(static_cast<unsigned char>(left))
        == std::tolower(static_cast<unsigned char>(right));
}

/*
 * Purpose: Checks whether text contains query, ignoring letter case.
 * Parameters: text - source text, query - search text.
 * Return value: true when query appears inside text.
 */
static bool containsIgnoreCase(const char* text, const char* query)
{
    if (text == nullptr || query == nullptr || query[0] == '\0')
    {
        return false;
    }

    const int textLength = static_cast<int>(std::strlen(text));
    const int queryLength = static_cast<int>(std::strlen(query));

    if (queryLength > textLength)
    {
        return false;
    }

    for (int i = 0; i <= textLength - queryLength; ++i)
    {
        bool match = true;

        for (int j = 0; j < queryLength; ++j)
        {
            if (!sameLetterIgnoreCase(text[i + j], query[j]))
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            return true;
        }
    }

    return false;
}

/*
 * Purpose: Sorts products in ascending order by price using Bubble Sort.
 * Parameters: products - product array to sort, count - number of products.
 * Return value: None.
 */
void bubbleSortByPrice(Product products[], int count)
{
    if (products == nullptr || count <= 1)
    {
        return;
    }

    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (products[j].price > products[j + 1].price)
            {
                const Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

/*
 * Purpose: Sorts products in ascending order by quantity using Bubble Sort.
 * Parameters: products - product array to sort, count - number of products.
 * Return value: None.
 */
void bubbleSortByQuantity(Product products[], int count)
{
    if (products == nullptr || count <= 1)
    {
        return;
    }

    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (products[j].quantity > products[j + 1].quantity)
            {
                const Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }
}

/*
 * Purpose: Finds a product by name using a linear search.
 * Parameters: products - product array to search, count - number of products,
 *             query - name or partial name to find.
 * Return value: Matching index when found, otherwise -1.
 */
int linearSearchByName(Product products[], int count, const char* query)
{
    if (products == nullptr || query == nullptr || query[0] == '\0')
    {
        return -1;
    }

    for (int i = 0; i < count; ++i)
    {
        if (containsIgnoreCase(products[i].name, query))
        {
            return i;
        }
    }

    return -1;
}

/*
 * Purpose: Recursively calculates the total inventory value.
 * Parameters: products - product array to total, count - number of products.
 * Return value: Sum of price multiplied by quantity for all products.
 */
float calculateTotalValueRecursive(Product products[], int count)
{
    if (products == nullptr || count <= 0)
    {
        return 0.0f;
    }

    return (products[count - 1].price * static_cast<float>(products[count - 1].quantity))
        + calculateTotalValueRecursive(products, count - 1);
}

/*
 * Purpose: Validates user input and adds a product through the data layer.
 * Parameters: name - product name, price - product price,
 *             quantity - product quantity.
 * Return value: true when validation and storage succeed, otherwise false.
 */
bool addNewProduct(const char* name, float price, int quantity)
{
    if (!hasVisibleText(name) || price < 0.0f || quantity < 0)
    {
        return false;
    }

    Product product = {};
    copyProductName(product.name, name);
    product.price = price;
    product.quantity = quantity;

    return addProduct(product);
}

/*
 * Purpose: Updates the quantity of one product through the data layer.
 * Parameters: index - zero-based product index, quantity - new quantity.
 * Return value: true when validation and storage succeed, otherwise false.
 */
bool updateProductQuantity(int index, int quantity)
{
    if (quantity < 0)
    {
        return false;
    }

    Product product = {};

    if (!getProduct(index, &product))
    {
        return false;
    }

    product.quantity = quantity;
    return updateProduct(index, product);
}

/*
 * Purpose: Removes one product through the data layer.
 * Parameters: index - zero-based product index.
 * Return value: true when the product was removed, otherwise false.
 */
bool deleteProductByIndex(int index)
{
    return removeProduct(index);
}

/*
 * Purpose: Sorts the stored inventory by price.
 * Parameters: None.
 * Return value: None.
 */
void sortInventoryByPrice()
{
    bubbleSortByPrice(getInventory(), getProductCount());
}

/*
 * Purpose: Sorts the stored inventory by quantity.
 * Parameters: None.
 * Return value: None.
 */
void sortInventoryByQuantity()
{
    bubbleSortByQuantity(getInventory(), getProductCount());
}

/*
 * Purpose: Searches the stored inventory by name.
 * Parameters: query - name or partial name to find.
 * Return value: Matching index when found, otherwise -1.
 */
int findProductByName(const char* query)
{
    return linearSearchByName(getInventory(), getProductCount(), query);
}

/*
 * Purpose: Calculates the total value of the stored inventory.
 * Parameters: None.
 * Return value: Total value of all products.
 */
float calculateInventoryTotalValue()
{
    return calculateTotalValueRecursive(getInventory(), getProductCount());
}

/*
 * Purpose: Provides one product for display without exposing data functions.
 * Parameters: index - zero-based product index, product - destination pointer.
 * Return value: true when a product was copied, otherwise false.
 */
bool getProductForDisplay(int index, Product* product)
{
    return getProduct(index, product);
}

/*
 * Purpose: Provides product count access to the presentation layer.
 * Parameters: None.
 * Return value: Current product count.
 */
int getProductCountForDisplay()
{
    return getProductCount();
}

/*
 * Purpose: Saves inventory through the data layer.
 * Parameters: filename - path to the file that will receive persisted products.
 * Return value: true when saving succeeds, otherwise false.
 */
bool saveInventoryToFile(const char* filename)
{
    return saveToFile(filename);
}

/*
 * Purpose: Loads inventory through the data layer.
 * Parameters: filename - path to the file that contains persisted products.
 * Return value: true when loading succeeds, otherwise false.
 */
bool loadInventoryFromFile(const char* filename)
{
    return loadFromFile(filename);
}
