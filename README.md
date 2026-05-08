# Lapis Technologies

Qt Widgets version of a C++ inventory management project for 9th grade.
The project follows the required three-layer architecture.

## Features

- Load and save products from `resources/products.csv`
- Show products in a professional Qt table
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
- Top navigation with panels for settings, add, edit, sort, and file actions

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
folders, Visual Studio files, executables, Qt deployment files, and large
dependency source drops are ignored. Qt is used as an installed framework, not
copied into the repository.

## Architecture

- Presentation layer: `presentation.h` and `presentation.cpp`
- Logic layer: `logic.h` and `logic.cpp`
- Data layer: `data.h` and `data.cpp`

The presentation layer calls only logic functions. The logic layer calls the
data layer for storage and file access.

## Build and Run

```powershell
$env:PATH="C:\Qt\Tools\mingw1310_64\bin;C:\Qt\Tools\Ninja;C:\Qt\Tools\CMake_64\bin;C:\Qt\6.11.0\mingw_64\bin;$env:PATH"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/Qt/6.11.0/mingw_64
cmake --build build
.\build\InventoryManager.exe
```

You can also pass another CSV path:

```powershell
.\build\InventoryManager.exe resources\products.csv
```

## Tests

```powershell
cmake --build build --target InventoryTests
.\build\InventoryTests.exe
```

## Team Roles

- Scrum Master: project tracking, documentation, GitHub project board
- Back-End Developer 1: data layer and file handling
- Back-End Developer 2: sorting, searching, recursion, validation
- Front-End Developer: Qt Widgets interface
