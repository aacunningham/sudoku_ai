#define BOOST_TEST_MODULE Sudoku_Test
#include <boost/test/unit_test.hpp>
#include "fixtures.h"
#include "../SudokuClass/sudoku.h"
#include <iostream>


bool wrong_size(const std::invalid_argument& ex) {
    BOOST_CHECK_EQUAL(ex.what(), std::string("Size of Sudoku puzzle must be a perfect square"));
    return true;
}


BOOST_FIXTURE_TEST_SUITE (sudoku_random, Random_Sudoku);

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

    Sudoku test3 = Sudoku(input);

    BOOST_CHECK(test2 == test);

    Sudoku test4;
    Sudoku test5(9);
    BOOST_CHECK(test4 == test5);

    test4 = Sudoku(16);

    Sudoku test6;
    BOOST_CHECK_EXCEPTION(test6 = Sudoku(12), std::invalid_argument, wrong_size);
}

BOOST_AUTO_TEST_CASE (sudoku_write) {
    Sudoku test = Sudoku(input);
    Sudoku test2 = Sudoku(test);

    BOOST_CHECK(test == test2);
    test.write(8, 3, 4);
    BOOST_CHECK(test != test2);
}

BOOST_AUTO_TEST_CASE (sudoku_domain) {
    Sudoku test = Sudoku(input);
    BOOST_REQUIRE(test.read(2, 3) == (2 * 3) % 10);
    BOOST_CHECK_MESSAGE(!(test.check_domain(2, 3, (2 * 3) % 10)), (2 * 3) % 10 );
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_domains, Almost_Solved);

BOOST_AUTO_TEST_CASE (sudoku_next_single) {
    Sudoku test = Sudoku(input);
    test.update_domains();
    BOOST_CHECK(test.is_valid());
    auto coordinates = test.get_next_single_domain();
    BOOST_CHECK_EQUAL(coordinates.first, 8);
    BOOST_CHECK_EQUAL(coordinates.second, 0);
}

BOOST_AUTO_TEST_CASE (sudoku_valid) {
    Sudoku test = Sudoku();

    test.update_domains();
    test.write(5, 0, 0);

    BOOST_CHECK(test.is_valid());

    Sudoku test2 = Sudoku(input);
    BOOST_CHECK(test2.is_valid());
}

BOOST_AUTO_TEST_SUITE_END ();


BOOST_FIXTURE_TEST_SUITE (sudoku_domain_solved, Solved);

BOOST_AUTO_TEST_CASE (sudoku_next_domain_solved) {
    Sudoku test = Sudoku(input);
    BOOST_CHECK(test.is_valid());
    auto coordinates = test.get_next_single_domain();
    BOOST_CHECK_EQUAL(coordinates.first, -1);
    BOOST_CHECK_EQUAL(coordinates.second, -1);
}

BOOST_AUTO_TEST_CASE (sudoku_is_solved) {
    Sudoku test = Sudoku(input);
    BOOST_CHECK(test.is_solved());

    test.write(2,0,0);
    BOOST_CHECK(!test.is_solved());

    test.write(0,0,0);
    BOOST_CHECK(!test.is_solved());

    test.write(1,0,0);
    BOOST_CHECK(test.is_solved());
}

BOOST_AUTO_TEST_CASE (sudoku_solve) {
    Sudoku test = Sudoku(input);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Almost Solved Sudoku: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_SUITE_END ();


BOOST_FIXTURE_TEST_SUITE (sudoku_easy_1, Easy_Sudoku_1);

BOOST_AUTO_TEST_CASE (sudoku_domain_easy_1) {
    Sudoku test = Sudoku(input);
    BOOST_CHECK(test.check_domain(5, 1, 0));
    BOOST_CHECK(test.check_domain(7, 1, 0));
    BOOST_CHECK(test.check_domain(1, 2, 1));
    BOOST_CHECK(test.check_domain(2, 2, 1));
    BOOST_CHECK(test.check_domain(5, 2, 1));
    BOOST_CHECK(test.check_domain(8, 2, 1));
    BOOST_CHECK(test.check_domain(9, 2, 1));
}

BOOST_AUTO_TEST_CASE (sudoku_next_domain_easy_1) {
    Sudoku test = Sudoku(input);
    BOOST_CHECK(test.is_valid());
    auto coordinates = test.get_next_single_domain();
    BOOST_CHECK_EQUAL(coordinates.first, 6);
    BOOST_CHECK_EQUAL(coordinates.second, 4);

    coordinates = test.get_next_n_domain(2);
    BOOST_CHECK_EQUAL(coordinates.first, 1);
    BOOST_CHECK_EQUAL(coordinates.second, 0);

    coordinates = test.get_next_n_domain(3);
    BOOST_CHECK_EQUAL(coordinates.first, 0);
    BOOST_CHECK_EQUAL(coordinates.second, 1);

    coordinates = test.get_next_n_domain(4);
    BOOST_CHECK_EQUAL(coordinates.first, 1);
    BOOST_CHECK_EQUAL(coordinates.second, 2);
}

BOOST_AUTO_TEST_CASE (sudoku_get_domain_easy_1) {
    Sudoku test = Sudoku(input);
    auto domain = test.get_domain(2, 6);
    BOOST_CHECK_EQUAL(domain.count(1), 1);
    BOOST_CHECK_EQUAL(domain.count(2), 1);
    BOOST_CHECK_EQUAL(domain.count(3), 1);
    BOOST_CHECK_EQUAL(domain.count(9), 1);
}

BOOST_AUTO_TEST_CASE (sudoku_solve_easy_1) {
    Sudoku test = Sudoku(input);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Easy Sudoku: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_easy_2, Easy_Sudoku_2);

BOOST_AUTO_TEST_CASE (sudoku_solve_easy_2) {
    Sudoku test = Sudoku(input);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Easy_2 Sudoku: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_easy_3, Easy_Sudoku_3);

BOOST_AUTO_TEST_CASE (sudoku_solve_easy_3) {
    Sudoku test = Sudoku(input);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Easy_3 Sudoku: " << time.count() << "s, " << backtracks << " backtracks\n";

    for (int i = 8; i >= 0; --i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << test.read(j, i) << ' ';
        }
        std::cout << '\n';
    }
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_medium_1, Medium_Sudoku_1);

BOOST_AUTO_TEST_CASE (sudoku_solve_medium_1) {
    Sudoku test = Sudoku(input);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Medium Sudoku: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_hard_1, Hard_Sudoku_1);

BOOST_AUTO_TEST_CASE (sudoku_solve_hard_1) {
    Sudoku test = Sudoku(input);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Hard Sudoku: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_CASE (sudoku_find_all_solutions) {
    Sudoku test = Sudoku(input);
    int solutions = find_all_solutions(test);
    std::cout << "Hard Sudoku: " << solutions << " solutions\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_ai, AI_Sudoku);

BOOST_AUTO_TEST_CASE (sudoku_solve_ai) {
    Sudoku test = Sudoku(input);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "AI Sudoku: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_multi_solution_1, Multi_Solution_Sudoku_1);

BOOST_AUTO_TEST_CASE (sudoku_find_all_solutions_multi_1) {
    Sudoku test = Sudoku(input);
    int solutions = find_all_solutions(test);
    std::cout << "Multi Sudoku: " << solutions << " solutions\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_multi_solution_2, Multi_Solution_Sudoku_2);

BOOST_AUTO_TEST_CASE (sudoku_find_all_solutions_multi_2) {
    Sudoku test = Sudoku(input);
    int solutions = find_all_solutions(test);
    std::cout << "Multi Sudoku: " << solutions << " solutions\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_size_4_1, Size_4_Sudoku_1);

BOOST_AUTO_TEST_CASE (sudoku_size_4_solve) {
    Sudoku test = Sudoku(input, 4);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Size 4 Sudoku 1: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_FIXTURE_TEST_SUITE (sudoku_size_16_1, Size_16_Sudoku_1);

BOOST_AUTO_TEST_CASE (sudoku_size_16_solve) {
    Sudoku test = Sudoku(input, 16);
    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Size 16 Sudoku 1: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_SUITE_END ();

BOOST_AUTO_TEST_CASE (sudoku_create) {
    int removed;
    Sudoku test = create_sudoku(9, 10, removed);
    for (int i = 8; i >= 0; --i) {
        for (int j = 0; j < 9; ++j) {
            std::cout << test.read(j, i) << ' ';
        }
        std::cout << std::endl;
    }

    std::chrono::duration<double> time;
    int backtracks;
    BOOST_CHECK(solve(test, backtracks, time));

    std::cout << "Custom Sudoku: " << time.count() << "s, " << backtracks << " backtracks\n";
}

BOOST_AUTO_TEST_CASE (sudoku_create_difficulty) {
    float averages[5] = {0.0};
    int temp;
    for (int i = 0; i < 50; ++i) {
        std::cout << "Creating sudoku " << i << '\n';
        create_sudoku(9, (i / 10) + 1, temp);
        std::cout << "Number removed for " << i << ": " << temp << '\n';
        averages[i/10] += temp;
    }
    for (int i = 0; i < 5; ++i) {
        averages[i] /= 10;
        std::cout << "Avg. left for difficulty of " << i << ": " << 81.0 - averages[i] << "\n";
    }
}

BOOST_FIXTURE_TEST_SUITE (sudoku_tiered_all, Tiered_All_Sudoku);

BOOST_AUTO_TEST_CASE (sudoku_tiered_all_solve) {
    int counter = 0;
    for (auto m : inputs) {
        std::cout << "Starting difficulty " << counter << '\n';
        int backtracks_sum = 0;
        std::chrono::duration<double> time_sum(0);
        for (int** input : m) {
            std::cout << "Starting puzzle\n";
            Sudoku test = Sudoku(input);
            std::chrono::duration<double> time;
            int backtracks;
            BOOST_CHECK(solve(test, backtracks, time));
            
            backtracks_sum += backtracks;
            time_sum += time;
        }
        float backtracks_avg = backtracks_sum / m.size();
        std::chrono::duration<double> time_avg = time_sum / m.size();

        std::cout << "Ran " << m.size() << " Tests; Difficulty: " << counter << '\n'
            << "Total Backtracks: " << backtracks_sum << '\n'
            << "Avg. Backtracks: " << backtracks_avg << '\n'
            << "Total Time: " << time_sum.count() << '\n'
            << "Avg. Time: " << time_avg.count() << "s\n\n";
        ++counter;
    }
}

BOOST_AUTO_TEST_SUITE_END ();
