cmake_minimum_required(VERSION 3.20)

project(InventoryManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(InventoryManager
    src/data.cpp
    src/logic.cpp
    src/presentation.cpp
    src/main.cpp
)

target_include_directories(InventoryManager PRIVATE include)

target_compile_definitions(InventoryManager PRIVATE INVENTORY_MANAGER_SEPARATE_BUILD)
