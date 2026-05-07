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

add_custom_command(TARGET InventoryManager POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:InventoryManager>/resources
)

add_executable(InventoryTests
    tests/data_tests.cpp
    tests/logic_tests.cpp
    src/data.cpp
    src/logic.cpp
)

target_include_directories(InventoryTests PRIVATE include)

add_custom_command(TARGET InventoryTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:InventoryTests>/resources
)
