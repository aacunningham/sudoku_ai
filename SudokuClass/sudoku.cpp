#include <set>
#include <stdexcept>
#include <iostream>
#include "sudoku.h"


Sudoku::Sudoku() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            squares[i][j] = 0;
            for (int k = 0; k < 9; ++k) {
                domains[i][j][k] = true;
            }
        }
    }
}

Sudoku::Sudoku(int** input) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (input[i][j] < 0 || input[i][j] > 9) {
                throw std::domain_error("Sudoku may only accept values 0 through 9");
            }
            squares[i][j] = input[i][j];
        }
    }
    update_domains();
}

Sudoku::Sudoku (const Sudoku& input) {
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j) {
            squares[i][j] = input.squares[i][j];
            for (int k = 0; k < 9; ++k) {
                domains[i][j][k] = input.domains[i][j][k];
            }
        }
    }
}

bool Sudoku::operator==(const Sudoku& other) const {
    bool equal = true;
    for (int i = 0; i < 9 && equal == true; ++i) {
        for (int j = 0; j < 9 && equal == true; ++j) {
            if (squares[i][j] != other.squares[i][j]) {
                equal = false;
            }
        }
    }
    return equal;
}


bool Sudoku::operator!=(const Sudoku& other) const {
    return !(*this == other);
}


int Sudoku::read(const int& i, const int& j) {
    return squares[i][j];
}


void Sudoku::write(const int& value, const int& i, const int& j) {
    if (value > 9 || value < 0)
        throw std::domain_error("Sudoku may only accept values 0 through 9");
    squares[i][j] = value;
    return;
}


bool Sudoku::check_domain(const int& i, const int& j, const int& k) {
    return domains[i][j][k - 1];
}


void Sudoku::get_next_single_domain(int& x, int& y) {
    x = -1; y = -1;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int count = 0;
            for (int k = 0; k < 9; ++k) {
                if (domains[i][j][k]) {
                    ++count;
                }
            }
            if (count == 1) {
                x = i; y = j;
                return;
            }
        }
    }

    return;
}


void Sudoku::update_domains() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int k;
            if (squares[i][j] != 0) {
                for (k = 0; k < 9; ++k) {
                    domains[i][j][k] = false;
                }
            } else {
                for (k = 0; k < 9; ++k) {
                    domains[i][j][k] = true;
                }
                for (k = 0; k < 9; ++k) {
                    if (squares[k][j] > 0 && squares[k][j] < 10) {
                        domains[i][j][(squares[k][j] - 1)] = false;
                    }
                }
                for (k = 0; k < 9; ++k) {
                    if (squares[i][k] > 0 && squares[i][k] < 10) {
                        domains[i][j][(squares[i][k] - 1)] = false;
                    }
                }
                int group_x = i / 3;
                int group_y = j / 3;
                for (int x = group_x * 3; x < (group_x + 1) * 3; ++x) {
                    for (int y = group_y * 3; y < (group_y + 1) * 3; ++y) {
                        if (squares[x][y] > 0 && squares[x][y] < 10) {
                            domains[i][j][(squares[x][y] - 1)] = false;
                        }
                    }
                }
            }
        }
    }
}


bool Sudoku::is_valid() {
    std::set<int> groups[9];
    std::set<int> rows[9];
    for (int i = 0; i < 9; ++i) {
        std::set<int> column;
        for (int j = 0; j < 9; ++j) {
            if (squares[i][j] == 0) {
                bool at_least_one = false;
                for (int k = 0; k < 9; ++k) {
                    if (domains[i][j][k] == true) {
                        at_least_one = true;
                        break;
                    }
                }
                if (!at_least_one) {
                    return false;
                }
            } else {
                if (column.count(squares[i][j]) == 1) {
                    return false;
                } else {
                    column.insert(squares[i][j]);
                }

                if (rows[j].count(squares[i][j]) == 1) {
                    return false;
                } else {
                    rows[j].insert(squares[i][j]);
                }

                int group_id = (i / 3) + (j / 3) * 3;
                if (groups[group_id].count(squares[i][j]) == 1) {
                    return false;
                } else {
                    groups[group_id].insert(squares[i][j]);
                }
            }
        }
    }

    return true;
}
