cmake_minimum_required (VERSION 3.1)
project (Sudoku_AI)

set (Sudoku_AI_VERSION_MAJOR 0)
set (Sudoku_AI_VERSION_MINOR 2)

configure_file (
    "${PROJECT_SOURCE_DIR}/Sudoku_AIConfig.h.in"
    "${PROJECT_BINARY_DIR}/Sudoku_AIConfig.h"
)

add_subdirectory (SudokuClass)
add_subdirectory (tests)

enable_testing ()
add_test (name MyTest command Test)

set(needed_features
    cxx_auto_type
    cxx_uniform_initialization)

add_executable (Sudoku_AI main.cpp)
target_link_libraries (Sudoku_AI Sudoku)
