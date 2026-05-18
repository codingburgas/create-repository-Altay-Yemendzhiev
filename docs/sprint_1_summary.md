# Sprint 1 Summary

## Completed

- Cleaned the repository structure.
- Reorganized the repository into `presentationLayer`, `serviceLayer`,
  `dataAccessLayer`, `tests`, `docs`, and `assets`.
- Replaced the terminal flow with a clean Qt desktop interface.
- Added a searchable product table.
- Added update and delete actions.
- Added a focused inventory CSV with 80 products.
- Added basic tests for data and logic behavior.

## Challenges

- The repository contained a nested copy of the project and generated Visual
  Studio/CMake build outputs.
- The old terminal interface appended each menu and result to the same screen.

## Solutions

- Promoted the active project files to a layered repository structure.
- Added `.gitignore` rules for local build and IDE files.
- Added Qt table controls for filtering, sorting, editing, and selecting stock.
- Implemented Bubble Sort and Binary Search (by price and quantity) in the logic layer.
- Refactored duplicate detection into the logic layer to improve architectural separation.
