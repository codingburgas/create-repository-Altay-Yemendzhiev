# Inventory Management System

Terminal version of a C++ inventory management project for 9th grade.
The project follows a three-layer architecture and is prepared so a Dear ImGui
presentation layer can be added later.

## Features

- Load and save products from `resources/products.csv`
- Show products in a paged terminal table
- Add products
- Update product quantities
- Delete products
- Sort products by price with Bubble Sort
- Sort products by quantity with Bubble Sort
- Search products by name with Linear Search
- Calculate total inventory value with recursion
- Clear terminal screens between actions so the interface does not stack text

## Project Structure

```text
project-root/
├── CMakeLists.txt
├── README.md
├── include/
│   ├── data.h
│   ├── logic.h
│   └── presentation.h
├── src/
│   ├── data.cpp
│   ├── logic.cpp
│   ├── presentation.cpp
│   └── main.cpp
├── tests/
│   ├── data_tests.cpp
│   └── logic_tests.cpp
├── docs/
│   ├── architecture_diagram.drawio
│   ├── backend_integration.md
│   ├── flowchart.drawio
│   ├── sprint_1_summary.md
│   ├── sprint_plan.md
│   └── user_guide.md
└── resources/
    └── products.csv
```

The repository intentionally has only 8 `.cpp` and `.h` files. Build folders,
Visual Studio files, executables, and large dependency source drops are ignored.
When Dear ImGui is added, use a Git submodule, package manager, or CMake download
inside the ignored build folder instead of copying the full ImGui source into a
normal commit.

## Architecture

- Presentation layer: `presentation.h` and `presentation.cpp`
- Logic layer: `logic.h` and `logic.cpp`
- Data layer: `data.h` and `data.cpp`

The presentation layer calls only logic functions. The logic layer calls the
data layer for storage and file access.

## Build and Run

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\Debug\InventoryManager.exe
```

You can also pass another CSV path:

```powershell
.\build\Debug\InventoryManager.exe resources\products.csv
```

## Tests

```powershell
cmake --build build --config Debug --target InventoryTests
.\build\Debug\InventoryTests.exe
```

## Team Roles

- Scrum Master: project tracking, documentation, GitHub project board
- Back-End Developer 1: data layer and file handling
- Back-End Developer 2: sorting, searching, recursion, validation
- Front-End Developer: terminal UI now, Dear ImGui UI later
