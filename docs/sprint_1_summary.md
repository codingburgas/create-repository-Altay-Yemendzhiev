# Sprint 1 Summary

## Completed

- Cleaned the repository structure.
- Kept one root-level `src`, `include`, `tests`, `docs`, and `resources` layout.
- Improved the terminal app so each action opens a clean screen.
- Added paging for the product table.
- Added update and delete actions.
- Added around 300 inventory products to the CSV file.
- Added basic tests for data and logic behavior.

## Challenges

- The repository contained a nested copy of the project and generated Visual
  Studio/CMake build outputs.
- The old terminal interface appended each menu and result to the same screen.

## Solutions

- Promoted the active project files to the repository root.
- Added `.gitignore` rules for local build and IDE files.
- Added a screen clear helper and paged table output.
