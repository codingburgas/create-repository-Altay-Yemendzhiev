cmake_minimum_required(VERSION 3.20)

project(InventoryManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32 AND EXISTS "C:/Qt/6.11.0/mingw_64")
    list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.11.0/mingw_64")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(InventoryManager
    src/data.cpp
    src/logic.cpp
    src/presentation.cpp
    src/main.cpp
)

target_include_directories(InventoryManager PRIVATE include)

target_link_libraries(InventoryManager PRIVATE Qt6::Widgets)

add_custom_command(TARGET InventoryManager POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:InventoryManager>/resources
)

if (WIN32 AND TARGET Qt6::windeployqt)
    add_custom_command(TARGET InventoryManager POST_BUILD
        COMMAND Qt6::windeployqt
            --no-translations
            --no-system-d3d-compiler
            "$<TARGET_FILE:InventoryManager>"
    )
endif()

add_executable(InventoryTests
    tests/data_tests.cpp
    tests/logic_tests.cpp
    src/data.cpp
    src/logic.cpp
)

target_include_directories(InventoryTests PRIVATE include)

if (MSVC)
    target_compile_options(InventoryManager PRIVATE /utf-8)
    target_compile_options(InventoryTests PRIVATE /utf-8)
endif()

add_custom_command(TARGET InventoryTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:InventoryTests>/resources
)
