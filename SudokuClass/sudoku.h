#ifndef SUDOKU__H
#define SUDOKU__H

#include <utility>
#include <array>
#include <set>


class Sudoku {
public:
    Sudoku ();
    Sudoku (int** input);
    Sudoku (const Sudoku& input);

    bool operator==(const Sudoku& other) const;
    bool operator!=(const Sudoku& other) const;

    int read(const int& x, const int& y);
    void write(const int& value, const int& x, const int& y);
    bool check_domain(const int& val, const int& x, const int& y);

    std::set<int> get_domain(const int& x, const int& y);

    std::pair<int, int> get_next_n_domain(const unsigned int& n);

    std::pair<int, int> get_next_single_domain();

    void update_domains();

    bool is_valid();

    bool is_solved();

private:
    std::array<std::array<int, 9>, 9> squares;
    std::array<std::array<std::set<int>, 9>, 9> domains;
    bool modified;
};

#endif

