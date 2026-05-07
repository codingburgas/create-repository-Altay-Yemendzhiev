#include "../include/presentation.h"

#include "../include/logic.h"

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>

enum
{
    productsPerPage = 12,
    productNameColumnWidth = 34
};

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
 * Purpose: Clears the terminal so each screen replaces the previous one.
 * Parameters: None.
 * Return value: None.
 */
static void clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

/*
 * Purpose: Pauses the terminal until the user presses Enter.
 * Parameters: None.
 * Return value: None.
 */
static void waitForEnter()
{
    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*
 * Purpose: Prints a consistent screen title.
 * Parameters: title - title to print.
 * Return value: None.
 */
static void displayTitle(const char* title)
{
    std::cout << "Inventory Manager";

    if (title != nullptr && title[0] != '\0')
    {
        std::cout << " - " << title;
    }

    std::cout << "\n";
    std::cout << "============================================================\n";
}

/*
 * Purpose: Shows one product row in a formatted terminal table.
 * Parameters: number - one-based row number, product - product to display,
 *             highlight - whether this row should be marked.
 * Return value: None.
 */
static void displayProductRow(int number, product item, bool highlight)
{
    char displayName[productNameColumnWidth + 1] = "";
    const int nameLength = static_cast<int>(std::strlen(item.name));

    if (nameLength > productNameColumnWidth)
    {
        std::strncpy(displayName, item.name, productNameColumnWidth - 3);
        displayName[productNameColumnWidth - 3] = '.';
        displayName[productNameColumnWidth - 2] = '.';
        displayName[productNameColumnWidth - 1] = '.';
        displayName[productNameColumnWidth] = '\0';
    }
    else
    {
        std::strncpy(displayName, item.name, productNameColumnWidth);
        displayName[productNameColumnWidth] = '\0';
    }

    std::cout << std::left << std::setw(6) << number;
    std::cout << std::left << std::setw(productNameColumnWidth) << displayName;
    std::cout << std::right << std::setw(10) << std::fixed
        << std::setprecision(2) << item.price;
    std::cout << std::right << std::setw(10) << item.quantity;

    if (highlight)
    {
        std::cout << "  <- found";
    }

    std::cout << "\n";
}

/*
 * Purpose: Shows a paged product table.
 * Parameters: highlightIndex - product index to mark, or -1 for no highlight.
 * Return value: None.
 */
static void displayProducts(int highlightIndex)
{
    const int count = getProductCountForDisplay();

    if (count == 0)
    {
        clearScreen();
        displayTitle("Products");
        std::cout << "No products are loaded.\n";
        waitForEnter();
        return;
    }

    int startIndex = 0;
    bool paging = true;

    while (paging)
    {
        clearScreen();
        displayTitle("Products");

        const int endIndex = startIndex + productsPerPage < count
            ? startIndex + productsPerPage
            : count;

        std::cout << "Showing " << (startIndex + 1) << "-" << endIndex;
        std::cout << " of " << count << " products\n\n";

        std::cout << std::left << std::setw(6) << "No.";
        std::cout << std::left << std::setw(productNameColumnWidth) << "Name";
        std::cout << std::right << std::setw(10) << "Price";
        std::cout << std::right << std::setw(10) << "Quantity";
        std::cout << "\n";
        std::cout << "------------------------------------------------------------\n";

        for (int i = startIndex; i < endIndex; ++i)
        {
            product item = {};
            getProductForDisplay(i, &item);
            displayProductRow(i + 1, item, i == highlightIndex);
        }

        if (endIndex >= count)
        {
            std::cout << "\nEnd of list. Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            paging = false;
        }
        else
        {
            char command = '\0';
            std::cout << "\nEnter = next page, q = menu: ";
            std::cin.get(command);
            clearInput();

            if (command == 'q' || command == 'Q')
            {
                paging = false;
            }
            else
            {
                startIndex += productsPerPage;
            }
        }
    }
}

/*
 * Purpose: Reads a one-based product number from the terminal.
 * Parameters: prompt - prompt text shown to the user.
 * Return value: zero-based index, or -1 when invalid.
 */
static int readProductIndex(const char* prompt)
{
    int number = 0;

    std::cout << prompt;

    if (!(std::cin >> number))
    {
        clearInput();
        return -1;
    }

    clearInput();
    return number - 1;
}

/*
 * Purpose: Reads a product name, price, and quantity from the terminal.
 * Parameters: None.
 * Return value: None.
 */
static void handleAddProduct()
{
    char name[maxNameLength] = "";
    float price = 0.0f;
    int quantity = 0;

    clearScreen();
    displayTitle("Add Product");

    std::cout << "Product name: ";
    std::cin.getline(name, sizeof(name));

    std::cout << "Price: ";

    if (!(std::cin >> price))
    {
        clearInput();
        std::cout << "\nError: price must be a number.\n";
        waitForEnter();
        return;
    }

    std::cout << "Quantity: ";

    if (!(std::cin >> quantity))
    {
        clearInput();
        std::cout << "\nError: quantity must be a whole number.\n";
        waitForEnter();
        return;
    }

    clearInput();

    if (!addNewProduct(name, price, quantity))
    {
        std::cout << "\nError: empty name, negative values, or full inventory.\n";
        waitForEnter();
        return;
    }

    std::cout << "\nProduct added.\n";
    waitForEnter();
}

/*
 * Purpose: Reads a search term and displays the matching product.
 * Parameters: foundIndex - pointer to the last found product index.
 * Return value: None.
 */
static void handleSearchByName(int* foundIndex)
{
    char query[maxNameLength] = "";

    clearScreen();
    displayTitle("Search");

    std::cout << "Search by product name: ";
    std::cin.getline(query, sizeof(query));

    if (query[0] == '\0')
    {
        std::cout << "\nError: search text cannot be empty.\n";
        waitForEnter();
        return;
    }

    *foundIndex = findProductByName(query);

    if (*foundIndex < 0)
    {
        std::cout << "\nNo matching product found.\n";
        waitForEnter();
        return;
    }

    product item = {};
    getProductForDisplay(*foundIndex, &item);

    std::cout << "\nFound product:\n\n";
    std::cout << std::left << std::setw(6) << "No.";
    std::cout << std::left << std::setw(productNameColumnWidth) << "Name";
    std::cout << std::right << std::setw(10) << "Price";
    std::cout << std::right << std::setw(10) << "Quantity";
    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";
    displayProductRow(*foundIndex + 1, item, true);

    waitForEnter();
}

/*
 * Purpose: Reads an exact quantity and displays every matching product.
 * Parameters: None.
 * Return value: None.
 */
static void handleSearchByQuantity()
{
    int quantity = 0;
    int foundIndex = 0;
    int matchCount = 0;

    clearScreen();
    displayTitle("Search By Quantity");

    std::cout << "Quantity to find: ";

    if (!(std::cin >> quantity))
    {
        clearInput();
        std::cout << "\nError: quantity must be a whole number.\n";
        waitForEnter();
        return;
    }

    clearInput();

    if (quantity < 0)
    {
        std::cout << "\nError: quantity cannot be negative.\n";
        waitForEnter();
        return;
    }

    std::cout << "\nProducts with quantity " << quantity << ":\n\n";
    std::cout << std::left << std::setw(6) << "No.";
    std::cout << std::left << std::setw(productNameColumnWidth) << "Name";
    std::cout << std::right << std::setw(10) << "Price";
    std::cout << std::right << std::setw(10) << "Quantity";
    std::cout << "\n";
    std::cout << "------------------------------------------------------------\n";

    while (foundIndex >= 0)
    {
        foundIndex = findProductByQuantity(quantity, foundIndex);

        if (foundIndex >= 0)
        {
            product item = {};
            getProductForDisplay(foundIndex, &item);
            displayProductRow(foundIndex + 1, item, true);
            ++foundIndex;
            ++matchCount;
        }
    }

    if (matchCount == 0)
    {
        std::cout << "No products have that quantity.\n";
    }

    waitForEnter();
}

/*
 * Purpose: Reads the selected sort field.
 * Parameters: field - destination pointer for the selected field.
 * Return value: true when a valid field was selected.
 */
static bool readSortField(sortField* field)
{
    int choice = 0;

    std::cout << "1. Price\n";
    std::cout << "2. Quantity\n";
    std::cout << "Choose field: ";

    if (!(std::cin >> choice))
    {
        clearInput();
        return false;
    }

    clearInput();

    if (choice == 1)
    {
        *field = sortByPrice;
        return true;
    }

    if (choice == 2)
    {
        *field = sortByQuantity;
        return true;
    }

    return false;
}

/*
 * Purpose: Reads the selected sort algorithm.
 * Parameters: algorithm - destination pointer for the selected algorithm.
 * Return value: true when a valid algorithm was selected.
 */
static bool readSortAlgorithm(sortAlgorithm* algorithm)
{
    int choice = 0;

    std::cout << "\n1. Quick Sort\n";
    std::cout << "2. Bogo Sort (joke, only works with 8 or fewer products)\n";
    std::cout << "Choose algorithm: ";

    if (!(std::cin >> choice))
    {
        clearInput();
        return false;
    }

    clearInput();

    if (choice == 1)
    {
        *algorithm = quickSortAlgorithm;
        return true;
    }

    if (choice == 2)
    {
        *algorithm = bogoSortAlgorithm;
        return true;
    }

    return false;
}

/*
 * Purpose: Handles the complete sorting menu.
 * Parameters: None.
 * Return value: true when sorting changed the inventory order.
 */
static bool handleSort()
{
    sortField field = sortByPrice;
    sortAlgorithm algorithm = quickSortAlgorithm;

    clearScreen();
    displayTitle("Sort Products");

    if (!readSortField(&field) || !readSortAlgorithm(&algorithm))
    {
        std::cout << "\nError: invalid sort choice.\n";
        waitForEnter();
        return false;
    }

    if (!sortInventory(field, algorithm))
    {
        std::cout << "\nBogo Sort was not started because the inventory has ";
        std::cout << "more than 8 products.\n";
        std::cout << "Use Quick Sort for the full inventory.\n";
        waitForEnter();
        return false;
    }

    std::cout << "\nProducts sorted with ";
    std::cout << (algorithm == quickSortAlgorithm ? "Quick Sort" : "Bogo Sort");
    std::cout << " by ";
    std::cout << (field == sortByPrice ? "price" : "quantity") << ".\n";
    waitForEnter();
    return true;
}

/*
 * Purpose: Updates a product quantity by its visible row number.
 * Parameters: None.
 * Return value: None.
 */
static void handleUpdateQuantity()
{
    clearScreen();
    displayTitle("Update Quantity");

    const int index = readProductIndex("Product number: ");
    int quantity = 0;

    std::cout << "New quantity: ";

    if (!(std::cin >> quantity))
    {
        clearInput();
        std::cout << "\nError: quantity must be a whole number.\n";
        waitForEnter();
        return;
    }

    clearInput();

    if (!updateProductQuantity(index, quantity))
    {
        std::cout << "\nError: invalid product number or negative quantity.\n";
        waitForEnter();
        return;
    }

    std::cout << "\nQuantity updated.\n";
    waitForEnter();
}

/*
 * Purpose: Deletes a product by its visible row number.
 * Parameters: None.
 * Return value: None.
 */
static void handleDeleteProduct()
{
    clearScreen();
    displayTitle("Delete Product");

    const int index = readProductIndex("Product number: ");
    product item = {};

    if (!getProductForDisplay(index, &item))
    {
        std::cout << "\nError: invalid product number.\n";
        waitForEnter();
        return;
    }

    if (!deleteProductByIndex(index))
    {
        std::cout << "\nError: product could not be deleted.\n";
        waitForEnter();
        return;
    }

    std::cout << "\nDeleted: " << item.name << "\n";
    waitForEnter();
}

/*
 * Purpose: Displays the recursive total inventory value.
 * Parameters: None.
 * Return value: None.
 */
static void displayTotalValue()
{
    clearScreen();
    displayTitle("Total Value");

    const float totalValue = calculateInventoryTotalValue();

    std::cout << "Total inventory value: ";
    std::cout << std::fixed << std::setprecision(2) << totalValue << "\n";
    waitForEnter();
}

/*
 * Purpose: Displays a short status message.
 * Parameters: title - screen title, message - message to show.
 * Return value: None.
 */
static void displayMessage(const char* title, const char* message)
{
    clearScreen();
    displayTitle(title);
    std::cout << message << "\n";
    waitForEnter();
}

/*
 * Purpose: Displays the terminal menu choices.
 * Parameters: inventoryFilePath - CSV path used by load and save actions.
 * Return value: None.
 */
static void displayMenu(const char* inventoryFilePath)
{
    displayTitle("Main Menu");
    std::cout << "Data file: " << inventoryFilePath << "\n";
    std::cout << "Loaded products: " << getProductCountForDisplay() << "\n\n";
    std::cout << "View\n";
    std::cout << "  1. Show products\n";
    std::cout << "  2. Search by name\n";
    std::cout << "  3. Search by quantity\n";
    std::cout << "  4. Show total inventory value\n\n";
    std::cout << "Edit\n";
    std::cout << "  5. Add product\n";
    std::cout << "  6. Update product quantity\n";
    std::cout << "  7. Delete product\n\n";
    std::cout << "Tools\n";
    std::cout << "  8. Sort products\n";
    std::cout << "  9. Save\n";
    std::cout << " 10. Reload from file\n";
    std::cout << "0. Save and exit\n\n";
    std::cout << "Choose: ";
}

/*
 * Purpose: Renders and runs the complete terminal inventory interface.
 * Parameters: inventoryFilePath - CSV path used by load and save actions.
 * Return value: None.
 */
void renderUI(const char* inventoryFilePath)
{
    bool running = true;
    int foundIndex = -1;

    while (running)
    {
        int choice = -1;
        clearScreen();
        displayMenu(inventoryFilePath);

        if (!(std::cin >> choice))
        {
            if (std::cin.eof())
            {
                running = false;
                continue;
            }

            clearInput();
            displayMessage("Input Error", "Enter a valid menu number.");
            continue;
        }

        clearInput();

        switch (choice)
        {
        case 1:
            displayProducts(foundIndex);
            break;
        case 2:
            handleSearchByName(&foundIndex);
            break;
        case 3:
            handleSearchByQuantity();
            break;
        case 4:
            displayTotalValue();
            break;
        case 5:
            handleAddProduct();
            foundIndex = -1;
            break;
        case 6:
            handleUpdateQuantity();
            foundIndex = -1;
            break;
        case 7:
            handleDeleteProduct();
            foundIndex = -1;
            break;
        case 8:
            if (handleSort())
            {
                foundIndex = -1;
            }
            break;
        case 9:
            displayMessage(
                "Save",
                saveInventoryToFile(inventoryFilePath) ? "Saved." : "Save failed."
            );
            break;
        case 10:
            displayMessage(
                "Reload",
                loadInventoryFromFile(inventoryFilePath) ? "Reloaded." : "Load failed."
            );
            foundIndex = -1;
            break;
        case 0:
            running = false;
            break;
        default:
            displayMessage("Input Error", "Unknown menu option.");
            break;
        }
    }
}
