#include "serviceLayer/logic.h"
#include "presentationLayer/presentation.h"

#include <fstream>

/*
 * Purpose: Checks whether a file can be opened for reading.
 * Parameters: filePath - path to inspect.
 * Return value: true when the file exists and can be read.
 */
static bool canReadFile(const char* filePath)
{
    std::ifstream file(filePath);
    return file.good();
}

/*
 * Purpose: Finds the default product CSV from common run locations.
 * Parameters: None.
 * Return value: Path to the first readable default CSV.
 */
static const char* findDefaultInventoryFile()
{
    static const char* paths[] = {
        "assets/products.csv",
        "../assets/products.csv",
        "../../assets/products.csv",
        "../../../assets/products.csv"
    };

    for (const char* path : paths)
    {
        if (canReadFile(path))
        {
            return path;
        }
    }

    return paths[0];
}

/*
 * Purpose: Runs the inventory management application.
 * Parameters: argc - argument count, argv - optional CSV path as argv[1].
 * Return value: zero on normal exit.
 */
int main(int argc, char* argv[])
{
    const char* inventoryFilePath = findDefaultInventoryFile();

    if (argc > 1 && argv[1] != nullptr && argv[1][0] != '\0')
    {
        inventoryFilePath = argv[1];
    }

    loadInventoryFromFile(inventoryFilePath);
    renderUI(inventoryFilePath);
    saveInventoryToFile(inventoryFilePath);

    return 0;
}
