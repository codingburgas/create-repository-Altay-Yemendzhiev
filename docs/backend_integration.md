# Back-End Integration

The Qt presentation layer does not read or write the data layer directly. It
uses functions from `logic.h`.

Main flow:

1. `main.cpp` loads `resources/products.csv` through `loadInventoryFromFile`.
2. `presentation.cpp` displays the Qt interface and reads user input.
3. `presentation.cpp` calls logic functions such as `sortInventory`,
   `findProductByName`, `findProductByQuantity`, `updateProductQuantity`, and
   `calculateInventoryTotalValue`.
4. `logic.cpp` validates input and calls `data.cpp` for stored product records.
5. `data.cpp` owns the inventory array and CSV load/save functions.

The build copies `resources/products.csv` beside the executable, so the data
file is still found when the app is started from the build output directory.
