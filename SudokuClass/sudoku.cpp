#include <stdexcept>
#include <iostream>
#include <sstream>
#include <utility>
#include <chrono>
#include <cmath>
#include <set>
#include "sudoku.h"


Sudoku::Sudoku(int size) {
    int root = std::round(std::sqrt(size));
    if (root * root != size) {
        throw std::invalid_argument("Size of Sudoku puzzle must be a perfect square");
    } else {
        dimension = size;
    }
    squares.resize(dimension);
    domains.resize(dimension);
    for (int y = 0; y < dimension; ++y) {
        squares[y].resize(dimension);
        domains[y].resize(dimension);
        for (int x = 0; x < dimension; ++x) {
            squares[y][x] = 0;
            for (int k = 1; k <= dimension; ++k) {
                domains[y][x].insert(k);
            }
        }
    }
    modified = false;
}

Sudoku::Sudoku(int** input, int size) {
    int root = std::round(std::sqrt(size));
    if (root * root != size) {
        throw std::invalid_argument("Size of Sudoku puzzle must be a perfect square");
    } else {
        dimension = size;
    }
    squares.resize(dimension);
    domains.resize(dimension);
    for (int y = 0; y < dimension; ++y) {
        squares[y].resize(dimension);
        domains[y].resize(dimension);
        for (int x = 0; x < dimension; ++x) {
            if (input[y][x] < 0 || input[y][x] > dimension) {
                std::ostringstream ostream;
                ostream << "Sudoku may only accept values 0 through " << dimension << "; Value: " << input[y][x] << "; Location: " << x << "," << y;
                throw std::domain_error(ostream.str());
            }
            squares[y][x] = input[y][x];
            for (int k = 1; k <= dimension; ++k) {
                domains[y][x].insert(k);
            }
        }
    }
    update_domains();
}

Sudoku::Sudoku (const Sudoku& input)
    : dimension(input.dimension) {
    squares.resize(dimension);
    domains.resize(dimension);
    for (int y = 0; y < dimension; ++y){
        squares[y].resize(dimension);
        domains[y].resize(dimension);
        for (int x = 0; x < dimension; ++x) {
            squares[y][x] = input.squares[y][x];
            domains[y][x] = input.domains[y][x];
        }
    }
    modified = false;
}


bool Sudoku::operator==(const Sudoku& other) const {
    bool equal = dimension == other.dimension;
    for (int y = 0; y < dimension && equal == true; ++y) {
        for (int x = 0; x < dimension && equal == true; ++x) {
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
    if (x >= 0 && x < dimension && y >= 0 && y < dimension) {
        return squares[y][x];
    } else {
        std::ostringstream ostream;
        ostream << "Out of dimension of puzzle. Dimension: " << dimension << "; Given: " << x << "," << y;
        throw std::domain_error(ostream.str());
    }
}


int Sudoku::read(const std::pair<int, int>& coordinates) {
    if (coordinates.second >= 0 && coordinates.second < dimension &&
            coordinates.first >= 0 && coordinates.first < dimension) {
        return squares[coordinates.second][coordinates.first];
    } else {
        std::ostringstream ostream;
        ostream << "Out of dimension of puzzle. Dimension: " << dimension << "; Given: " << coordinates.first << "," << coordinates.second;
        throw std::domain_error(ostream.str());
    }
}


void Sudoku::write(const int& value, const int& x, const int& y) {
    if (value > dimension || value < 0)
        throw std::domain_error("Sudoku may only accept values 0 through 9");
    if (x >= 0 && x < dimension && y >= 0 && y < dimension) {
        squares[y][x] = value;
        modified = true;
        return;
    } else {
        std::ostringstream ostream;
        ostream << "Out of dimension of puzzle. Dimension: " << dimension << "; Given: " << x << "," << y;
        throw std::domain_error(ostream.str());
    }
}


bool Sudoku::check_domain(const int& val, const int& x, const int& y) {
    if (modified) {
        update_domains();
    }
    if (x >= 0 && x < dimension && y >= 0 && y < dimension) {
        return domains[y][x].count(val) == 1;
    } else {
        std::ostringstream ostream;
        ostream << "Out of dimension of puzzle. Dimension: " << dimension << "; Given: " << x << "," << y;
        throw std::domain_error(ostream.str());
    }
}


std::set<int> Sudoku::get_domain(const int& x, const int& y) {
    if (x >= 0 && x < dimension && y >= 0 && y < dimension) {
        return domains[y][x];
    } else {
        std::ostringstream ostream;
        ostream << "Out of dimension of puzzle. Dimension: " << dimension << "; Given: " << x << "," << y;
        throw std::domain_error(ostream.str());
    }
}


std::set<int> Sudoku::get_domain(const std::pair<int, int>& coordinates) {
    if (coordinates.second >= 0 && coordinates.second < dimension &&
            coordinates.first >= 0 && coordinates.first < dimension) {
        return domains[coordinates.second][coordinates.first];
    } else {
        std::ostringstream ostream;
        ostream << "Out of dimension of puzzle. Dimension: " << dimension << "; Given: " << coordinates.first << "," << coordinates.second;
        throw std::domain_error(ostream.str());
    }
}


void Sudoku::set_domain(const std::set<int>& domain, const std::pair<int, int>& coordinates) {
    if (coordinates.second >= 0 && coordinates.second < dimension &&
            coordinates.first >= 0 && coordinates.first < dimension) {
        domains[coordinates.second][coordinates.first] = domain;
    } else {
        std::ostringstream ostream;
        ostream << "Out of dimension of puzzle. Dimension: " << dimension << "; Given: " << coordinates.first << "," << coordinates.second;
        throw std::domain_error(ostream.str());
    }
}


std::pair<int, int> Sudoku::get_next_n_domain(const unsigned int& n) {
    if (modified) {
        update_domains();
    }
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
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
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < dimension; ++j) {
            if (domains[i][j].size() > 0) {
                return std::pair<int, int>(j, i);
            }
        }
    }

    return std::pair<int, int>(-1, -1);
}


void Sudoku::update_domains() {
    for (int y = 0; y < dimension; ++y) {
        for (int x = 0; x < dimension; ++x) {
            int k;
            if (squares[y][x] != 0) {
                for (k = 0; k < dimension; ++k) {
                    domains[y][x].clear();
                }
            } else {
                for (k = 0; k < dimension; ++k) {
                    if (squares[k][x] > 0 && squares[k][x] <= dimension) {
                        domains[y][x].erase(squares[k][x]);
                    }
                }
                for (k = 0; k < dimension; ++k) {
                    if (squares[y][k] > 0 && squares[y][k] <= dimension) {
                        domains[y][x].erase(squares[y][k]);
                    }
                }
                int group_dimension = std::sqrt(dimension);
                int group_x = y / (group_dimension);
                int group_y = x / (group_dimension);
                for (int gx = group_x * group_dimension; gx < (group_x + 1) * group_dimension; ++gx) {
                    for (int gy = group_y * group_dimension; gy < (group_y + 1) * group_dimension; ++gy) {
                        if (squares[gx][gy] > 0 && squares[gx][gy] <= dimension) {
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
    std::set<int>* groups = new std::set<int>[dimension];
    std::set<int>* columns = new std::set<int>[dimension];
    for (int y = 0; y < dimension; ++y) {
        std::set<int> row;
        for (int x = 0; x < dimension; ++x) {
            if (squares[y][x] == 0) {
                if (domains[y][x].size() == 0) {
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

                int group_dimension = std::sqrt(dimension);
                int group_id = (y / group_dimension) + (x / group_dimension) * group_dimension;
                if (groups[group_id].count(squares[y][x]) == 1) {
                    return false;
                } else {
                    groups[group_id].insert(squares[y][x]);
                }
            }
        }
    }
    delete[] groups;
    delete[] columns;

    return true;
}


bool Sudoku::is_solved() {
    if (is_valid()) {
        bool all_filled = true;
        for (int y = 0; y < dimension; ++y) {
            for (int x = 0; x < dimension; ++x) {
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


bool solve(Sudoku& sudoku, int& backtracksOUT, std::chrono::duration<double>& timeOUT) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    backtracksOUT = 0;
    start = std::chrono::system_clock::now();
    if (!sudoku.is_valid()) {
        return false;
    }
    std::stack<std::pair<Sudoku, std::pair<int, int>>> history;
    while(true) {
        sudoku.update_domains();
        if (!sudoku.is_valid()) {
            if (history.size() > 0) {
                auto previous_sudoku = history.top().first;
                auto wrong_coordinates = history.top().second;
                int wrong_value = sudoku.read(wrong_coordinates);
                sudoku = previous_sudoku;
                auto domain = sudoku.get_domain(wrong_coordinates);
                domain.erase(wrong_value);
                sudoku.set_domain(domain, wrong_coordinates);
                history.pop();
                ++backtracksOUT;
            } else {
                break;
            }
        }
        auto coordinates = sudoku.get_next_single_domain();
        if (coordinates.first != -1) {
            int first_val = *(sudoku.get_domain(coordinates).begin());
            sudoku.write(first_val, coordinates.first, coordinates.second);
        } else {
            coordinates = sudoku.get_next_empty_square();
            if (coordinates.first != -1) {
                history.push(std::pair<Sudoku, std::pair<int, int>>(sudoku, coordinates));
                int first_val = *(sudoku.get_domain(coordinates).begin());
                sudoku.write(first_val, coordinates.first, coordinates.second);
            } else {
                break;
            }
        }
    }
    end = std::chrono::system_clock::now();
    timeOUT = end - start;
    return sudoku.is_solved();
}


int find_all_solutions(Sudoku& sudoku) {
    int number_of_solutions = 0;
    if (!sudoku.is_valid()) {
        return false;
    }
    const int dimension = sudoku.get_dimension();
    std::stack<std::pair<Sudoku, std::pair<int, int>>> history;
    while(true) {
        sudoku.update_domains();
        if (!sudoku.is_valid()) {
            if (history.size() > 0) {
                auto previous_sudoku = history.top().first;
                auto wrong_coordinates = history.top().second;
                int wrong_value = sudoku.read(wrong_coordinates);
                sudoku = previous_sudoku;
                auto domain = sudoku.get_domain(wrong_coordinates);
                domain.erase(wrong_value);
                sudoku.set_domain(domain, wrong_coordinates);
                history.pop();
            } else {
                break;
            }
        }
        auto coordinates = sudoku.get_next_single_domain();
        if (coordinates.first != -1) {
            int first_val = *(sudoku.get_domain(coordinates).begin());
            sudoku.write(first_val, coordinates.first, coordinates.second);
        } else {
            coordinates = sudoku.get_next_empty_square();
            if (coordinates.first != -1) {
                history.push(std::pair<Sudoku, std::pair<int, int>>(sudoku, coordinates));
                int first_val = *(sudoku.get_domain(coordinates).begin());
                sudoku.write(first_val, coordinates.first, coordinates.second);
            } else {
                if (sudoku.is_valid()) {
                    ++number_of_solutions;
                }
                if (history.size() > 0) {
                    auto previous_sudoku = history.top().first;
                    auto wrong_coordinates = history.top().second;
                    int wrong_value = sudoku.read(wrong_coordinates);
                    sudoku = previous_sudoku;
                    auto domain = sudoku.get_domain(wrong_coordinates);
                    domain.erase(wrong_value);
                    sudoku.set_domain(domain, wrong_coordinates);
                    history.pop();
                } else {
                    break;
                }
            }
        }
    }
    return number_of_solutions;
}

