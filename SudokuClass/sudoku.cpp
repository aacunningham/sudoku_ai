#include <set>
#include <utility>
#include <stdexcept>
#include <iostream>
#include "sudoku.h"


Sudoku::Sudoku() {
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            squares[y][x] = 0;
            for (int k = 1; k < 10; ++k) {
                domains[y][x].insert(k);
            }
        }
    }
    modified = false;
}

Sudoku::Sudoku(int** input) {
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            if (input[y][x] < 0 || input[y][x] > 9) {
                throw std::domain_error("Sudoku may only accept values 0 through 9");
            }
            squares[y][x] = input[y][x];
        }
    }
    update_domains();
}

Sudoku::Sudoku (const Sudoku& input) {
    for (int y = 0; y < 9; ++y){
        for (int x = 0; x < 9; ++x) {
            squares[y][x] = input.squares[y][x];
            for (int k = 0; k < 9; ++k) {
                domains[y][x] = input.domains[y][x];
            }
        }
    }
    modified = false;
}

bool Sudoku::operator==(const Sudoku& other) const {
    bool equal = true;
    for (int y = 0; y < 9 && equal == true; ++y) {
        for (int x = 0; x < 9 && equal == true; ++x) {
            if (squares[y][x] != other.squares[y][x]) {
                equal = false;
            }
        }
    }
    return equal;
}


bool Sudoku::operator!=(const Sudoku& other) const {
    return !(*this == other);
}


int Sudoku::read(const int& x, const int& y) {
    return squares[y][x];
}


void Sudoku::write(const int& value, const int& x, const int& y) {
    if (value > 9 || value < 0)
        throw std::domain_error("Sudoku may only accept values 0 through 9");
    squares[y][x] = value;
    modified = true;
    return;
}


bool Sudoku::check_domain(const int& val, const int& x, const int& y) {
    if (modified) {
        update_domains();
    }
    return domains[y][x].count(val) == 1;
}


std::set<int> Sudoku::get_domain(const int& x, const int& y) {
    return domains[y][x];
}


std::pair<int, int> Sudoku::get_next_n_domain(const unsigned int& n) {
    if (modified) {
        update_domains();
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (domains[i][j].size() == n) {
                return std::pair<int, int>(j, i);
            }
        }
    }

    return std::pair<int, int>(-1, -1);
}


std::pair<int, int> Sudoku::get_next_single_domain() {
    return get_next_n_domain(1);
}


void Sudoku::update_domains() {
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            int k;
            if (squares[y][x] != 0) {
                for (k = 0; k < 9; ++k) {
                    domains[y][x].clear();
                }
            } else {
                for (k = 1; k < 10; ++k) {
                    domains[y][x].insert(k);
                }
                for (k = 0; k < 9; ++k) {
                    if (squares[k][x] > 0 && squares[k][x] < 10) {
                        domains[y][x].erase(squares[k][x]);
                    }
                }
                for (k = 0; k < 9; ++k) {
                    if (squares[y][k] > 0 && squares[y][k] < 10) {
                        domains[y][x].erase(squares[y][k]);
                    }
                }
                int group_x = y / 3;
                int group_y = x / 3;
                for (int gx = group_x * 3; gx < (group_x + 1) * 3; ++gx) {
                    for (int gy = group_y * 3; gy < (group_y + 1) * 3; ++gy) {
                        if (squares[gx][gy] > 0 && squares[gx][gy] < 10) {
                            domains[y][x].erase(squares[gx][gy]);
                        }
                    }
                }
            }
        }
    }

    modified = false;
}


bool Sudoku::is_valid() {
    if (modified) {
        update_domains();
    }
    std::set<int> groups[9];
    std::set<int> columns[9];
    for (int y = 0; y < 9; ++y) {
        std::set<int> row;
        for (int x = 0; x < 9; ++x) {
            if (squares[y][x] == 0) {
                bool at_least_one = false;
                for (int k = 1; k < 10; ++k) {
                    if (domains[y][x].count(k) == 1) {
                        at_least_one = true;
                        break;
                    }
                }
                if (!at_least_one) {
                    return false;
                }
            } else {
                if (row.count(squares[y][x]) == 1) {
                    return false;
                } else {
                    row.insert(squares[y][x]);
                }

                if (columns[x].count(squares[y][x]) == 1) {
                    return false;
                } else {
                    columns[x].insert(squares[y][x]);
                }

                int group_id = (y / 3) + (x / 3) * 3;
                if (groups[group_id].count(squares[y][x]) == 1) {
                    return false;
                } else {
                    groups[group_id].insert(squares[y][x]);
                }
            }
        }
    }

    return true;
}


bool Sudoku::is_solved() {
    if (is_valid()) {
        bool all_filled = true;
        for (int y = 0; y < 9; ++y) {
            for (int x = 0; x < 9; ++x) {
                if (squares[y][x] == 0) {
                    all_filled = false;
                    break;
                }
            }
            if (!all_filled) {
                break;
            }
        }
        return all_filled;
    } else {
        return false;
    }
}


bool Sudoku::solve() {
    while(true) {
        auto coordinates = get_next_single_domain();
        if (coordinates.first == -1) {
            break;
        }
        write(*domains[coordinates.second][coordinates.first].begin(), coordinates.first, coordinates.second);
    }
    return is_solved();
}

