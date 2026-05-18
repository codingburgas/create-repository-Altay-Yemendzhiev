# Back-End Integration

The Qt presentation layer does not read or write the data access layer directly.
It uses functions from `serviceLayer/logic.h`.

Main flow:

1. `main.cpp` loads `assets/products.csv` through `loadInventoryFromFile`.
2. `presentationLayer/presentation.cpp` displays the Qt interface and reads
   user input.
3. `presentationLayer/presentation.cpp` calls service functions such as
   `sortInventory`,
   `findProductByName`, `findProductByQuantity`, `updateProductQuantity`, and
   `calculateInventoryTotalValue`.
4. `serviceLayer/logic.cpp` validates input and calls
   `dataAccessLayer/data.cpp` for stored product records.
5. `dataAccessLayer/data.cpp` owns the inventory array and CSV load/save
   functions.

The build copies `assets/products.csv` beside the executable, so the data
file is still found when the app is started from the build output directory.
