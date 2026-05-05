#include "../include/data.h"

#include <cstdio>
#include <cstring>

static Product inventory[MAX_PRODUCTS];
static int productCount = 0;

/*
 * Purpose: Trims trailing line endings from a C string.
 * Parameters: text - string to modify in place.
 * Return value: None.
 */
static void trimLineEnd(char text[])
{
    const int length = static_cast<int>(std::strlen(text));

    for (int i = length - 1; i >= 0; --i)
    {
        if (text[i] == '\n' || text[i] == '\r')
        {
            text[i] = '\0';
        }
        else
        {
            break;
        }
    }
}

/*
 * Purpose: Loads product records from a CSV file into the inventory.
 * Parameters: filename - path to the file that contains persisted products.
 * Return value: true when the file was opened and parsed, otherwise false.
 */
bool loadFromFile(const char* filename)
{
    if (filename == nullptr || filename[0] == '\0')
    {
        return false;
    }

    FILE* file = std::fopen(filename, "r");

    if (file == nullptr)
    {
        return false;
    }

    productCount = 0;
    char line[256];

    while (std::fgets(line, sizeof(line), file) != nullptr
        && productCount < MAX_PRODUCTS)
    {
        trimLineEnd(line);

        Product product = {};
        const int scanned = std::sscanf(
            line,
            "%99[^,],%f,%d",
            product.name,
            &product.price,
            &product.quantity
        );

        if (scanned == 3 && product.price >= 0.0f && product.quantity >= 0)
        {
            inventory[productCount] = product;
            ++productCount;
        }
    }

    std::fclose(file);
    return true;
}

/*
 * Purpose: Saves all current product records to a CSV file.
 * Parameters: filename - path to the file that will receive persisted products.
 * Return value: true when the file was opened and written, otherwise false.
 */
bool saveToFile(const char* filename)
{
    if (filename == nullptr || filename[0] == '\0')
    {
        return false;
    }

    FILE* file = std::fopen(filename, "w");

    if (file == nullptr)
    {
        return false;
    }

    for (int i = 0; i < productCount; ++i)
    {
        std::fprintf(
            file,
            "%s,%.2f,%d\n",
            inventory[i].name,
            inventory[i].price,
            inventory[i].quantity
        );
    }

    std::fclose(file);
    return true;
}

/*
 * Purpose: Adds one product to the fixed-size inventory array.
 * Parameters: product - product value to append to the inventory.
 * Return value: true when the product was added, otherwise false when full.
 */
bool addProduct(Product product)
{
    if (productCount >= MAX_PRODUCTS)
    {
        return false;
    }

    inventory[productCount] = product;
    ++productCount;
    return true;
}

/*
 * Purpose: Replaces one product at a valid inventory index.
 * Parameters: index - zero-based product index, product - new product data.
 * Return value: true when the product was replaced, otherwise false.
 */
bool updateProduct(int index, Product product)
{
    if (index < 0 || index >= productCount)
    {
        return false;
    }

    inventory[index] = product;
    return true;
}

/*
 * Purpose: Removes one product from the inventory.
 * Parameters: index - zero-based product index to remove.
 * Return value: true when a product was removed, otherwise false.
 */
bool removeProduct(int index)
{
    if (index < 0 || index >= productCount)
    {
        return false;
    }

    for (int i = index; i < productCount - 1; ++i)
    {
        inventory[i] = inventory[i + 1];
    }

    --productCount;
    return true;
}

/*
 * Purpose: Copies one product into an output parameter.
 * Parameters: index - zero-based product index, product - destination pointer.
 * Return value: true when a product was copied, otherwise false.
 */
bool getProduct(int index, Product* product)
{
    if (product == nullptr || index < 0 || index >= productCount)
    {
        return false;
    }

    *product = inventory[index];
    return true;
}

/*
 * Purpose: Provides access to the inventory array for the logic layer.
 * Parameters: None.
 * Return value: Pointer to the first product in the inventory array.
 */
Product* getInventory()
{
    return inventory;
}

/*
 * Purpose: Provides the number of products currently stored.
 * Parameters: None.
 * Return value: Current product count.
 */
int getProductCount()
{
    return productCount;
}
