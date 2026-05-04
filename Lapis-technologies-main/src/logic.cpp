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
 * Purpose: Sorts products in ascending order by price using Bubble Sort.
 * Parameters: arr - product array to sort, n - number of products in arr.
 * Return value: None.
 */
void bubbleSortByPrice(Product arr[], int n)
{
    if (arr == nullptr || n <= 1)
    {
        return;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j].price > arr[j + 1].price)
            {
                const Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/*
 * Purpose: Sorts products in ascending order by quantity using Bubble Sort.
 * Parameters: arr - product array to sort, n - number of products in arr.
 * Return value: None.
 */
void bubbleSortByQuantity(Product arr[], int n)
{
    if (arr == nullptr || n <= 1)
    {
        return;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j].quantity > arr[j + 1].quantity)
            {
                const Product temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/*
 * Purpose: Finds a product by name using a linear search.
 * Parameters: arr - product array to search, n - number of products,
 *             query - name or partial name to find.
 * Return value: Matching index when found, otherwise -1.
 */
int linearSearchByName(Product arr[], int n, const char* query)
{
    if (arr == nullptr || query == nullptr || query[0] == '\0')
    {
        return -1;
    }

    for (int i = 0; i < n; ++i)
    {
        if (std::strstr(arr[i].name, query) != nullptr)
        {
            return i;
        }
    }

    return -1;
}

/*
 * Purpose: Recursively calculates the total inventory value.
 * Parameters: arr - product array to total, n - number of products.
 * Return value: Sum of price multiplied by quantity for all products.
 */
float calculateTotalValueRecursive(Product arr[], int n)
{
    if (arr == nullptr || n <= 0)
    {
        return 0.0f;
    }

    return (arr[n - 1].price * static_cast<float>(arr[n - 1].quantity))
        + calculateTotalValueRecursive(arr, n - 1);
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
 * Purpose: Provides inventory access to the presentation layer.
 * Parameters: None.
 * Return value: Pointer to the first product in the inventory array.
 */
Product* getInventoryForDisplay()
{
    return getInventory();
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
