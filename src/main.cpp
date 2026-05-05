#include "../include/logic.h"
#include "../include/presentation.h"

/*
 * Purpose: Runs the terminal inventory application.
 * Parameters: argc - argument count, argv - optional CSV path as argv[1].
 * Return value: zero on normal exit.
 */
int main(int argc, char* argv[])
{
    const char* inventoryFilePath = "resources/products.csv";

    if (argc > 1 && argv[1] != nullptr && argv[1][0] != '\0')
    {
        inventoryFilePath = argv[1];
    }

    loadInventoryFromFile(inventoryFilePath);
    renderUI(inventoryFilePath);
    saveInventoryToFile(inventoryFilePath);

    return 0;
}
