#include "logic.h"

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>

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
static void copyProductName(char destination[maxNameLength], const char* source)
{
    std::strncpy(destination, source, maxNameLength - 1);
    destination[maxNameLength - 1] = '\0';
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
 * Purpose: Swaps two products.
 * Parameters: left - first product, right - second product.
 * Return value: None.
 */
static void swapProducts(product* left, product* right)
{
    product temp = *left;
    *left = *right;
    *right = temp;
}

/*
 * Purpose: Compares two products by the selected sort field.
 * Parameters: left - first product, right - second product,
 *             field - field used for comparison.
 * Return value: true when left should be before or equal to right.
 */
static bool comesBeforeOrEqual(product left, product right, sortField field)
{
    if (field == sortByQuantity)
    {
        return left.quantity <= right.quantity;
    }

    return left.price <= right.price;
}

/*
 * Purpose: Partitions a product array for Quick Sort.
 * Parameters: products - product array, low - first index, high - last index,
 *             field - field used for comparison.
 * Return value: Final pivot index.
 */
static int partitionProducts(product products[], int low, int high, sortField field)
{
    const product pivot = products[high];
    int smallerIndex = low - 1;

    for (int currentIndex = low; currentIndex < high; ++currentIndex)
    {
        if (comesBeforeOrEqual(products[currentIndex], pivot, field))
        {
            ++smallerIndex;
            swapProducts(&products[smallerIndex], &products[currentIndex]);
        }
    }

    swapProducts(&products[smallerIndex + 1], &products[high]);
    return smallerIndex + 1;
}

/*
 * Purpose: Recursively sorts products using Quick Sort.
 * Parameters: products - product array, low - first index, high - last index,
 *             field - field used for comparison.
 * Return value: None.
 */
static void quickSortProducts(product products[], int low, int high, sortField field)
{
    if (products == nullptr || low >= high)
    {
        return;
    }

    const int pivotIndex = partitionProducts(products, low, high, field);
    quickSortProducts(products, low, pivotIndex - 1, field);
    quickSortProducts(products, pivotIndex + 1, high, field);
}

/*
 * Purpose: Checks whether products are sorted by the selected field.
 * Parameters: products - product array, count - number of products,
 *             field - field used for comparison.
 * Return value: true when the array is sorted.
 */
static bool isSorted(product products[], int count, sortField field)
{
    for (int i = 1; i < count; ++i)
    {
        if (!comesBeforeOrEqual(products[i - 1], products[i], field))
        {
            return false;
        }
    }

    return true;
}

/*
 * Purpose: Randomly shuffles products for Bogo Sort.
 * Parameters: products - product array, count - number of products.
 * Return value: None.
 */
static void shuffleProducts(product products[], int count)
{
    static bool randomSeeded = false;

    if (!randomSeeded)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        randomSeeded = true;
    }

    for (int i = count - 1; i > 0; --i)
    {
        const int randomIndex = std::rand() % (i + 1);
        swapProducts(&products[i], &products[randomIndex]);
    }
}

/*
 * Purpose: Sorts products in ascending order by price using Quick Sort.
 * Parameters: products - product array to sort, count - number of products.
 * Return value: None.
 */
void quickSortByPrice(product products[], int count)
{
    quickSortProducts(products, 0, count - 1, sortByPrice);
}

/*
 * Purpose: Sorts products in ascending order by quantity using Quick Sort.
 * Parameters: products - product array to sort, count - number of products.
 * Return value: None.
 */
void quickSortByQuantity(product products[], int count)
{
    quickSortProducts(products, 0, count - 1, sortByQuantity);
}

/*
 * Purpose: Sorts products using Bubble Sort.
 * Parameters: products - product array to sort, count - number of products,
 *             field - product field used for comparison.
 * Return value: None.
 */
void bubbleSortProducts(product products[], int count, sortField field)
{
    if (products == nullptr || count <= 1)
    {
        return;
    }

    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (!comesBeforeOrEqual(products[j], products[j + 1], field))
            {
                swapProducts(&products[j], &products[j + 1]);
            }
        }
    }
}

/*
 * Purpose: Sorts a small product array using Bogo Sort.
 * Parameters: products - product array to sort, count - number of products,
 *             field - product field used for comparison.
 * Return value: true when sorted, otherwise false after the attempt limit.
 */
bool bogoSortProducts(product products[], int count, sortField field)
{
    const int maxBogoItems = 8;
    const int maxAttempts = 20000;

    if (products == nullptr || count <= 1)
    {
        return true;
    }

    if (count > maxBogoItems)
    {
        return false;
    }

    for (int attempt = 0; attempt < maxAttempts; ++attempt)
    {
        if (isSorted(products, count, field))
        {
            return true;
        }

        shuffleProducts(products, count);
    }

    return isSorted(products, count, field);
}

/*
 * Purpose: Finds a product by name using a linear search.
 * Parameters: products - product array to search, count - number of products,
 *             query - name or partial name to find.
 * Return value: Matching index when found, otherwise -1.
 */
int linearSearchByName(product products[], int count, const char* query)
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
)
{
    if (products == nullptr || quantity < 0 || startIndex < 0)
    {
        return -1;
    }

    for (int i = startIndex; i < count; ++i)
    {
        if (products[i].quantity == quantity)
        {
            return i;
        }
    }

    return -1;
}

/*
 * Purpose: Finds a product by price using Binary Search.
 * Parameters: products - sorted product array to search, count - number of products,
 *             targetPrice - price to find.
 * Return value: Matching index when found, otherwise -1.
 */
int binarySearchByPrice(product products[], int count, float targetPrice)
{
    if (products == nullptr)
    {
        return -1;
    }

    int low = 0;
    int high = count - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (std::abs(products[mid].price - targetPrice) < 0.001f)
        {
            return mid;
        }
        if (products[mid].price < targetPrice)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

/*
 * Purpose: Finds a product by quantity using Binary Search.
 * Parameters: products - sorted product array to search, count - number of products,
 *             targetQuantity - quantity to find.
 * Return value: Matching index when found, otherwise -1.
 */
int binarySearchByQuantity(product products[], int count, int targetQuantity)
{
    if (products == nullptr)
    {
        return -1;
    }

    int low = 0;
    int high = count - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (products[mid].quantity == targetQuantity)
        {
            return mid;
        }
        if (products[mid].quantity < targetQuantity)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

/*
 * Purpose: Recursively calculates the total inventory value.
 */
float calculateTotalValueRecursive(product products[], int count)
{
    if (products == nullptr || count <= 0)
    {
        return 0.0f;
    }

    return (products[count - 1].price * static_cast<float>(products[count - 1].quantity))
        + calculateTotalValueRecursive(products, count - 1);
}

static bool namesAreEqualIgnoreCase(const char* a, const char* b)
{
    if (a == nullptr || b == nullptr)
    {
        return a == b;
    }

    while (*a != '\0' && *b != '\0')
    {
        if (std::tolower(static_cast<unsigned char>(*a)) !=
            std::tolower(static_cast<unsigned char>(*b)))
        {
            return false;
        }
        ++a;
        ++b;
    }

    return *a == *b;
}

/*
 * Purpose: Finds duplicate product names in the inventory.
 * Parameters: duplicateIndexes - output array to store indexes of duplicates,
 *             maxDuplicates - capacity of the output array.
 * Return value: Number of duplicates found.
 */
int findDuplicateProducts(int duplicateIndexes[], int maxDuplicates)
{
    product* products = getInventory();
    const int count = getProductCount();
    int duplicateCount = 0;

    for (int i = 0; i < count; ++i)
    {
        const char* firstName = products[i].name;

        for (int j = i + 1; j < count; ++j)
        {
            const char* secondName = products[j].name;

            if (namesAreEqualIgnoreCase(firstName, secondName))
            {
                // Found a duplicate at index j.
                // Check if we already have it to avoid duplicates in the result.
                bool alreadyAdded = false;
                for (int k = 0; k < duplicateCount; ++k)
                {
                    if (duplicateIndexes[k] == j)
                    {
                        alreadyAdded = true;
                        break;
                    }
                }

                if (!alreadyAdded && duplicateCount < maxDuplicates)
                {
                    duplicateIndexes[duplicateCount] = j;
                    ++duplicateCount;
                }
            }
        }
    }

    return duplicateCount;
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

    product item = {};
    copyProductName(item.name, name);
    item.price = price;
    item.quantity = quantity;

    return addProduct(item);
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

    product item = {};

    if (!getProduct(index, &item))
    {
        return false;
    }

    item.quantity = quantity;
    return updateProduct(index, item);
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
 * Purpose: Sorts the stored inventory.
 * Parameters: field - field used for comparison,
 *             algorithm - selected sorting algorithm.
 * Return value: true when sorting succeeds, otherwise false.
 */
bool sortInventory(sortField field, sortAlgorithm algorithm)
{
    product* products = getInventory();
    const int count = getProductCount();

    if (algorithm == bogoSortAlgorithm)
    {
        return bogoSortProducts(products, count, field);
    }

    if (algorithm == bubbleSortAlgorithm)
    {
        bubbleSortProducts(products, count, field);
        return true;
    }

    quickSortProducts(products, 0, count - 1, field);
    return true;
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
 * Purpose: Searches the stored inventory by exact quantity.
 * Parameters: quantity - quantity to find, startIndex - first index to check.
 * Return value: Matching index when found, otherwise -1.
 */
int findProductByQuantity(int quantity, int startIndex)
{
    return linearSearchByQuantity(
        getInventory(),
        getProductCount(),
        quantity,
        startIndex
    );
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
bool getProductForDisplay(int index, product* item)
{
    return getProduct(index, item);
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
