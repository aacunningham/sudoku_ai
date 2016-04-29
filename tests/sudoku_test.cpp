#define BOOST_TEST_MODULE Sudoku_Test
#include "fixtures.h"
#include "../SudokuClass/sudoku.h"
#include <boost/test/unit_test.hpp>


bool correct_message(const std::domain_error& ex) {
    BOOST_CHECK_EQUAL(ex.what(), std::string("Sudoku may only accept values 0 through 9"));
    return true;
}


BOOST_FIXTURE_TEST_SUITE (sudoku_random, Random_Sudoku)

BOOST_AUTO_TEST_CASE (sudoku_constructors) {
    Sudoku test = Sudoku(input);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            BOOST_CHECK_MESSAGE(test.read(i, j) == (i * j) % 10, "At " << i << "," << j << ": " << test.read(i ,j) << " != " << (i * j) % 10);
        }
    }

    Sudoku test2 = Sudoku(test);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            BOOST_CHECK_MESSAGE(test2.read(i, j) == (i * j) % 10, "At " << i << "," << j << ": " << test2.read(i ,j) << " != " << (i * j) % 10);
        }
    }

    Sudoku test4 = Sudoku(input);

    input[0][0] = 100;
    BOOST_CHECK_EXCEPTION(test4 = Sudoku(input), std::domain_error, correct_message);

    BOOST_CHECK(test2 == test);
}

BOOST_AUTO_TEST_CASE (sudoku_write) {
    Sudoku test = Sudoku(input);
    Sudoku test2 = Sudoku(test);

    BOOST_CHECK(test == test2);
    test.write(8, 3, 4);
    BOOST_CHECK(test != test2);
    BOOST_CHECK_EXCEPTION(test.write(10, 3, 4), std::domain_error, correct_message);
    BOOST_CHECK_EXCEPTION(test.write(-1, 3, 4), std::domain_error, correct_message);
}

BOOST_AUTO_TEST_CASE (sudoku_domain) {
    Sudoku test = Sudoku(input);
    BOOST_REQUIRE(test.read(2, 3) == (2 * 3) % 10);
    BOOST_CHECK_MESSAGE(!(test.check_domain(2, 3, (2 * 3) % 10)), (2 * 3) % 10 );
}

BOOST_AUTO_TEST_SUITE_END ()

BOOST_FIXTURE_TEST_SUITE (sudoku_domains, Almost_Solved)

BOOST_AUTO_TEST_CASE (sudoku_next_single) {
    Sudoku test = Sudoku(input);
    test.update_domains();
    BOOST_CHECK(test.is_valid());
    int x, y;
    test.get_next_single_domain(x, y);
    BOOST_CHECK(x == 0);
    BOOST_CHECK(y == 8);
    input[0][0] = 100;
}

BOOST_AUTO_TEST_CASE (sudoku_valid) {
    Sudoku test = Sudoku();

    test.update_domains();
    test.write(5, 0, 0);

    BOOST_CHECK(test.is_valid());

    Sudoku test2 = Sudoku(input);
    BOOST_CHECK(test2.is_valid());
}

BOOST_AUTO_TEST_SUITE_END ()

