# Lapis Technologies

Dear ImGui version of a C++ inventory management project for 9th grade.
The project follows the required three-layer architecture.

## Features

- Load and save products from `resources/products.csv`
- Show products in a Dear ImGui table
- Add products
- Update product quantities
- Delete products
- Sort products by price or quantity with Quick Sort
- Try Bogo Sort as a small joke/demo option
- Search products by name with Linear Search
- Search products by exact quantity with Linear Search
- Calculate total inventory value with recursion
- Softer theme presets using the project color palette
- Language selector for Bulgarian, Spanish, French, German, English, Turkish,
  Russian, and Hebrew
- Top navigation with pop-up panels for settings, add, edit, sort, and file actions

## Project Structure

```text
project-root/
|-- CMakeLists.txt
|-- README.md
|-- include/
|   |-- data.h
|   |-- logic.h
|   `-- presentation.h
|-- src/
|   |-- data.cpp
|   |-- logic.cpp
|   |-- presentation.cpp
|   `-- main.cpp
|-- tests/
|   |-- data_tests.cpp
|   `-- logic_tests.cpp
|-- docs/
|   |-- architecture_diagram.drawio
|   |-- backend_integration.md
|   |-- flowchart.drawio
|   |-- sprint_1_summary.md
|   |-- sprint_plan.md
|   `-- user_guide.md
`-- resources/
    `-- products.csv
```

The repository intentionally has fewer than 18 `.cpp` and `.h` files. Build
folders, Visual Studio files, executables, and large dependency source drops are
ignored. Dear ImGui is downloaded by CMake FetchContent into the ignored build
folder, so the full ImGui source is not copied into normal commits.

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
- Front-End Developer: Dear ImGui interface
