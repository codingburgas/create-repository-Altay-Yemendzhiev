#include "../include/logic.h"
#include "../include/presentation.h"

#ifndef INVENTORY_MANAGER_SEPARATE_BUILD
#include "data.cpp"
#include "logic.cpp"
#include "presentation.cpp"
#endif

/*
 * Purpose: Runs the terminal inventory application.
 * Parameters: argc - argument count, argv - argument values.
 * Return value: zero on normal exit.
 */
int main(int argc, char* argv[])
{
    const char* INVENTORY_FILE_PATH = "inventory.csv";

    (void)argc;
    (void)argv;

    loadInventoryFromFile(INVENTORY_FILE_PATH);
    renderUI();
    saveInventoryToFile(INVENTORY_FILE_PATH);

    return 0;
}
