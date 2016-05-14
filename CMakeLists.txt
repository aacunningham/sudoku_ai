cmake_minimum_required (VERSION 3.1)
project (Sudoku_AI)

set (Sudoku_AI_VERSION_MAJOR 1)
set (Sudoku_AI_VERSION_MINOR 0)

configure_file (
    "${PROJECT_SOURCE_DIR}/Sudoku_AIConfig.h.in"
    "${PROJECT_SOURCE_DIR}/Sudoku_AIConfig.h"
)

add_subdirectory (SudokuClass)
add_subdirectory (tests)

enable_testing ()
add_test (name MyTest command Test)

set (
    needed_features
    cxx_auto_type
    cxx_uniform_initialization
)

add_executable (Sudoku_AI main.cpp)
set_property(TARGET Sudoku_AI PROPERTY CXX_STANDARD 11)
set_property(TARGET Sudoku_AI PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries (Sudoku_AI Sudoku)
