# Shop Inventory Management System

Terminal-based C++ application for managing a fixed-size shop inventory.

## Architecture

The project uses a three-tier procedural design:

- `include/data.h` and `src/data.cpp`: inventory storage and file persistence
- `include/logic.h` and `src/logic.cpp`: validation, sorting, searching, totals
- `include/presentation.h` and `src/presentation.cpp`: terminal menu interface
- `src/main.cpp`: entry point only

Presentation calls only logic functions. Logic is the only layer that calls data.

## Simple Windows Build

Open PowerShell in the project folder and run:

```powershell
g++ -std=c++17 src/main.cpp -o InventoryManager.exe
```

Run:

```powershell
.\InventoryManager.exe
```

## Visual Studio

Open `src/main.cpp` and run it as the startup file. The file includes the other
`.cpp` files automatically when it is compiled by itself.

## CMake Build

```powershell
cmake -S . -B build
cmake --build build --config Release
```

Inventory data is loaded from `inventory.csv` on startup and saved there on exit.
