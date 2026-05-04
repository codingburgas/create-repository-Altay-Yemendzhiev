#include "../include/presentation.h"

#include "../include/logic.h"

#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

/*
 * Purpose: Clears invalid input from the terminal input stream.
 * Parameters: None.
 * Return value: None.
 */
static void clearInput()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
 * Purpose: Pauses the terminal until the user presses Enter.
 * Parameters: None.
 * Return value: None.
 */
static void waitForEnter()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
 * Purpose: Shows all products in a formatted terminal table.
 * Parameters: highlightIndex - product index to mark, or -1 for no highlight.
 * Return value: None.
 */
static void displayProducts(int highlightIndex)
{
    Product* products = getInventoryForDisplay();
    const int count = getProductCountForDisplay();

    std::cout << "\nInventory\n";
    std::cout << "------------------------------------------------------------\n";
    std::cout << std::left << std::setw(5) << "No.";
    std::cout << std::left << std::setw(28) << "Name";
    std::cout << std::right << std::setw(12) << "Price";
    std::cout << std::right << std::setw(12) << "Quantity";
    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";

    if (count == 0)
    {
        std::cout << "No products available.\n";
        return;
    }

    for (int i = 0; i < count; ++i)
    {
        std::cout << std::left << std::setw(5) << (i + 1);
        std::cout << std::left << std::setw(28) << products[i].name;
        std::cout << std::right << std::setw(12) << std::fixed << std::setprecision(2);
        std::cout << products[i].price;
        std::cout << std::right << std::setw(12) << products[i].quantity;

        if (i == highlightIndex)
        {
            std::cout << "  <- found";
        }

        std::cout << "\n";
    }
}

/*
 * Purpose: Reads a product name, price, and quantity from the terminal.
 * Parameters: None.
 * Return value: None.
 */
static void handleAddProduct()
{
    char name[MAX_NAME_LENGTH] = "";
    float price = 0.0f;
    int quantity = 0;

    std::cout << "\nProduct name: ";
    std::cin.getline(name, sizeof(name));

    std::cout << "Price: ";

    if (!(std::cin >> price))
    {
        clearInput();
        std::cout << "Error: price must be a number.\n";
        return;
    }

    std::cout << "Quantity: ";

    if (!(std::cin >> quantity))
    {
        clearInput();
        std::cout << "Error: quantity must be a whole number.\n";
        return;
    }

    clearInput();

    if (!addNewProduct(name, price, quantity))
    {
        std::cout << "Error: empty name, negative values, or full inventory.\n";
        return;
    }

    std::cout << "Product added.\n";
}

/*
 * Purpose: Reads a search term and displays the matching product.
 * Parameters: foundIndex - pointer to the last found product index.
 * Return value: None.
 */
static void handleSearch(int* foundIndex)
{
    char query[MAX_NAME_LENGTH] = "";
    Product* products = getInventoryForDisplay();
    const int count = getProductCountForDisplay();

    std::cout << "\nSearch name: ";
    std::cin.getline(query, sizeof(query));

    if (query[0] == '\0')
    {
        std::cout << "Error: search text cannot be empty.\n";
        return;
    }

    *foundIndex = linearSearchByName(products, count, query);

    if (*foundIndex < 0)
    {
        std::cout << "No matching product found.\n";
        return;
    }

    std::cout << "Found: " << products[*foundIndex].name << "\n";
}

/*
 * Purpose: Displays the recursive total inventory value.
 * Parameters: None.
 * Return value: None.
 */
static void displayTotalValue()
{
    Product* products = getInventoryForDisplay();
    const int count = getProductCountForDisplay();
    const float totalValue = calculateTotalValueRecursive(products, count);

    std::cout << "\nTotal Inventory Value: ";
    std::cout << std::fixed << std::setprecision(2) << totalValue << "\n";
}

/*
 * Purpose: Displays the terminal menu choices.
 * Parameters: None.
 * Return value: None.
 */
static void displayMenu()
{
    std::cout << "\nInventory Manager\n";
    std::cout << "1. Show products\n";
    std::cout << "2. Add product\n";
    std::cout << "3. Sort by price\n";
    std::cout << "4. Sort by quantity\n";
    std::cout << "5. Search by name\n";
    std::cout << "6. Show total inventory value\n";
    std::cout << "7. Save\n";
    std::cout << "8. Load\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose: ";
}

/*
 * Purpose: Renders and runs the complete terminal inventory interface.
 * Parameters: None.
 * Return value: None.
 */
void renderUI()
{
    const char* INVENTORY_FILE = "inventory.csv";
    bool running = true;
    int foundIndex = -1;

    while (running)
    {
        int choice = -1;
        displayMenu();

        if (!(std::cin >> choice))
        {
            clearInput();
            std::cout << "Error: enter a menu number.\n";
            continue;
        }

        clearInput();

        Product* products = getInventoryForDisplay();
        const int count = getProductCountForDisplay();

        switch (choice)
        {
        case 1:
            displayProducts(foundIndex);
            waitForEnter();
            break;
        case 2:
            handleAddProduct();
            foundIndex = -1;
            waitForEnter();
            break;
        case 3:
            bubbleSortByPrice(products, count);
            foundIndex = -1;
            std::cout << "Sorted by price.\n";
            waitForEnter();
            break;
        case 4:
            bubbleSortByQuantity(products, count);
            foundIndex = -1;
            std::cout << "Sorted by quantity.\n";
            waitForEnter();
            break;
        case 5:
            handleSearch(&foundIndex);
            displayProducts(foundIndex);
            waitForEnter();
            break;
        case 6:
            displayTotalValue();
            waitForEnter();
            break;
        case 7:
            std::cout << (saveInventoryToFile(INVENTORY_FILE) ? "Saved.\n" : "Save failed.\n");
            waitForEnter();
            break;
        case 8:
            std::cout << (loadInventoryFromFile(INVENTORY_FILE) ? "Loaded.\n" : "Load failed.\n");
            foundIndex = -1;
            waitForEnter();
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Error: unknown menu option.\n";
            waitForEnter();
            break;
        }
    }
}
