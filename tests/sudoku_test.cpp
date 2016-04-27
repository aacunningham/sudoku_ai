#define BOOST_TEST_MODULE Sudoku_Test
#include "../SudokuClass/sudoku.h"
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE (sudoku_constructors) {
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
            BOOST_CHECK_MESSAGE(test->read(i, j) == i * j, "At " << i << "," << j << ": " << test->read(i ,j) << " != " << i * j);
        }
    }

    Sudoku test2 = Sudoku(*test);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            BOOST_CHECK_MESSAGE(test2.read(i, j) == i * j, "At " << i << "," << j << ": " << test2.read(i ,j) << " != " << i * j);
        }
    }

    BOOST_CHECK(test2 == *test);

    delete test;

    for (int i = 0; i < 9; ++i) {
        delete[] input[i];
    }
    delete[] input;
}

BOOST_AUTO_TEST_CASE (sudoku_write) {
    int** input = new int*[9];
    for (int i = 0; i < 9; ++i) {
        input[i] = new int[9];
        for (int j = 0; j < 9; ++j) {
            input[i][j] = i * j;
        }
    }

    Sudoku test = Sudoku(input);
    Sudoku test2 = Sudoku(test);

    BOOST_CHECK(test == test2);
    test.write(23, 3, 4);
    BOOST_CHECK(test != test2);

    for (int i = 0; i < 9; ++i) {
        delete[] input[i];
    }
    delete[] input;
}

BOOST_AUTO_TEST_CASE (sudoku_domain) {
    int** input = new int*[9];
    for (int i = 0; i < 9; ++i) {
        input[i] = new int[9];
        for (int j = 0; j < 9; ++j) {
            input[i][j] = (i * j) % 10;
        }
    }

    Sudoku test = Sudoku(input);
    BOOST_REQUIRE(test.read(2, 3) == (2 * 3) % 10);
    BOOST_CHECK_MESSAGE(!(test.check_domain(2, 3, (2 * 3) % 10)), (2 * 3) % 10 );

    for (int i = 0; i < 9; ++i) {
        delete[] input[i];
    }
    delete[] input;
}

