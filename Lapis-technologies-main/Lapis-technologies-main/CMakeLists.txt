cmake_minimum_required(VERSION 3.20)

project(InventoryManager LANGUAGES CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.91.9b
)

FetchContent_MakeAvailable(imgui)

add_executable(InventoryManager
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
    src/data.cpp
    src/logic.cpp
    src/presentation.cpp
    src/main.cpp
)

target_include_directories(InventoryManager PRIVATE
    include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(InventoryManager PRIVATE
    d3d11
    d3dcompiler
    dxgi
)

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

if (MSVC)
    target_compile_options(InventoryManager PRIVATE /utf-8)
    target_compile_options(InventoryTests PRIVATE /utf-8)
endif()

add_custom_command(TARGET InventoryTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:InventoryTests>/resources
)
