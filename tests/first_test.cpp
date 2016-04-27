#define BOOST_TEST_MODULE MyTest
#include "../SudokuClass/sudoku.h"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE (my_test) {
    int** input = new int*[9];
    for (int i = 0; i < 9; ++i) {
        input[i] = new int[9];
        for (int j = 0; j < 9; ++j) {
            input[i][j] = i * j;
        }
    }

    Sudoku* test = new Sudoku(input);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            BOOST_CHECK_EQUAL(test->read(i, j), i * j);
        }
    }
    
    for (int i = 0; i < 9; ++i) {
        delete[] input[i];
    }
    delete[] input;
    delete test;
}

