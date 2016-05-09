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
            for (int k = 1; k < 10; ++k) {
                domains[y][x].insert(k);
            }
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


int Sudoku::read(const std::pair<int, int>& coordinates) {
    return squares[coordinates.second][coordinates.first];
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


std::set<int> Sudoku::get_domain(const std::pair<int, int>& coordinates) {
    return domains[coordinates.second][coordinates.first];
}


void Sudoku::set_domain(const std::set<int>& domain, const std::pair<int, int>& coordinates) {
    domains[coordinates.second][coordinates.first] = domain;
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


std::pair<int, int> Sudoku::get_next_empty_square() {
    if (modified) {
        update_domains();
    }
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (domains[i][j].size() > 0) {
                return std::pair<int, int>(j, i);
            }
        }
    }

    return std::pair<int, int>(-1, -1);
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


bool solve(Sudoku& sudoku) {
    if (!sudoku.is_valid()) {
        return false;
    }
    std::stack<std::pair<Sudoku, std::pair<int, int>>> history;
    while(true) {
        sudoku.update_domains();
        if (!sudoku.is_valid()) {
            auto previous_sudoku = history.top().first;
            auto wrong_coordinates = history.top().second;
            int wrong_value = sudoku.read(wrong_coordinates);
            // std::cout << "Bad guess: " << wrong_value << " (" << wrong_coordinates.first << ',' << wrong_coordinates.second << ")\n";
            sudoku = previous_sudoku;
            auto domain = sudoku.get_domain(wrong_coordinates);
            domain.erase(wrong_value);
            sudoku.set_domain(domain, wrong_coordinates);
            history.pop();
        }
        auto coordinates = sudoku.get_next_single_domain();
        if (coordinates.first != -1) {
            // std::cout << "Found single domain: " << coordinates.first << ',' << coordinates.second << ' ';
            int first_val = *(sudoku.get_domain(coordinates).begin());
            // std::cout << "Writing " << *sudoku.get_domain(coordinates).begin() << std::endl;
            sudoku.write(first_val, coordinates.first, coordinates.second);
        } else {
            coordinates = sudoku.get_next_empty_square();
            if (coordinates.first != -1) {
                // std::cout << "Making a guess: " << coordinates.first << ',' << coordinates.second << ' ';
                history.push(std::pair<Sudoku, std::pair<int, int>>(sudoku, coordinates));
                int first_val = *(sudoku.get_domain(coordinates).begin());
                // std::cout << "Writing " << first_val << std::endl;
                sudoku.write(first_val, coordinates.first, coordinates.second);
            } else {
                break;
            }
        }
    }
    return sudoku.is_solved();
}

