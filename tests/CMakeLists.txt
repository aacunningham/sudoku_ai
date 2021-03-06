find_package(Boost COMPONENTS system unit_test_framework REQUIRED)

include_directories (
    ${TEST_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
)

file (GLOB test_files
    "*.h"
    "*.cpp"
)

file (COPY
    ${CMAKE_CURRENT_SOURCE_DIR}/test_fixture_data.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/
)

add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test ${test_files})
target_compile_features(Test PRIVATE cxx_uniform_initialization)
target_link_libraries (
    Test
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    Sudoku
)
