#ifndef SUDOKU__H
#define SUDOKU__H

#include <utility>
#include <vector>
#include <chrono>
#include <set>


class Sudoku {
public:
    Sudoku (int size = 9);
    Sudoku (int** input, int size = 9);
    Sudoku (const Sudoku& input);

    bool operator==(const Sudoku& other) const;
    bool operator!=(const Sudoku& other) const;

    int get_dimension() const { return dimension;}

    int read(const int& x, const int& y);
    int read(const std::pair<int, int>& coordinates);
    void write(const int& value, const int& x, const int& y);
    bool check_domain(const int& val, const int& x, const int& y);

    std::set<int> get_domain(const int& x, const int& y);
    std::set<int> get_domain(const std::pair<int, int>& coordinates);

    void set_domain(const std::set<int>& domain, const std::pair<int, int>& coordinates);

    std::pair<int, int> get_next_n_domain(const unsigned int& n);
    std::pair<int, int> get_next_single_domain();
    std::pair<int, int> get_next_empty_square();

    void update_domains();
    void reset_domains();

    bool is_valid();

    bool is_solved();

private:
    int dimension;
    std::vector<std::vector<int>> squares;
    std::vector<std::vector<std::set<int>>> domains;
    bool modified;
};


bool solve(Sudoku& sudoku, int& backtracksOUT, std::chrono::duration<double>& timeOUT);
bool solve(Sudoku& sudoku);
int find_all_solutions(Sudoku sudoku, bool stop_if_extra_found = false);

Sudoku create_sudoku(const int& size, const int& difficulty, int& removedOUT);

#endif

