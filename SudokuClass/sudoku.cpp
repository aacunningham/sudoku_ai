#include <iostream>
#include "sudoku.h"


Sudoku::Sudoku() {
    squares = new int*[9];
    domain = new bool**[9];
    for (int i = 0; i < 9; ++i) {
        squares[i] = new int[9];
        domain[i] = new bool*[9];
        for (int j = 0; j < 9; ++j) {
            squares[i][j] = 0;
            domain[i][j] = new bool[9];
            for (int k = 0; k < 9; ++k) {
                domain[i][j][k] = true;
            }
        }
    }
}

Sudoku::Sudoku(int** input) {
    squares = new int*[9];
    domain = new bool**[9];
    for (int i = 0; i < 9; ++i) {
        squares[i] = new int[9];
        domain[i] = new bool*[9];
        for (int j = 0; j < 9; ++j) {
            squares[i][j] = input[i][j];
            domain[i][j] = new bool[9];
        }
    }
    update_domains();
}

Sudoku::Sudoku (const Sudoku &input) {
    squares = new int*[9];
    domain = new bool**[9];
    for (int i = 0; i < 9; ++i){
        squares[i] = new int[9];
        domain[i] = new bool*[9];
        for (int j = 0; j < 9; ++j) {
            squares[i][j] = input.squares[i][j];
            domain[i][j] = new bool[9];
            for (int k = 0; k < 9; ++k) {
                domain[i][j][k] = input.domain[i][j][k];
            }
        }
    }
}

Sudoku::~Sudoku () {
    for (int i = 0; i < 9; ++i) {
        delete[] squares[i];
        for (int j = 0; j < 9; ++j) {
            delete[] domain[i][j];
        }
        delete[] domain[i];
    }
    delete[] squares;
    delete[] domain;

}


bool Sudoku::operator==(const Sudoku &other) const {
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


bool Sudoku::operator!=(const Sudoku &other) const {
    return !(*this == other);
}


int Sudoku::read(const int &i, const int &j) {
    return squares[i][j];
}


void Sudoku::write(const int &value, const int &i, const int &j) {
    squares[i][j] = value;
    return;
}


bool Sudoku::check_domain(const int &i, const int &j, const int &k) {
    return domain[i][j][k - 1];
}


void Sudoku::get_next_single_domain(int &x, int &y) {
    x = -1; y = -1;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int count = 0;
            for (int k = 0; k < 9; ++k) {
                if (domain[i][j][k]) {
                    ++count;
                }
            }
            if (count == 1) {
                x = i; y = j;
                break;
            }
        }
        if (x != -1) {
            break;
        }
    }

    return;
}


void Sudoku::update_domains() {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int k;
            for (k = 0; k < 9; ++k) {
                domain[i][j][k] = true;
            }
            for (k = 0; k < 9; ++k) {
                if (squares[k][j] > 0 && squares[k][j] < 10) {
                    domain[i][j][(squares[k][j] - 1)] = false;
                }
            }
            for (k = 0; k < 9; ++k) {
                if (squares[i][k] > 0 && squares[i][k] < 10) {
                    domain[i][j][(squares[i][k] - 1)] = false;
                }
            }
            int group_x = i / 3;
            int group_y = j / 3;
            for (int x = group_x * 3; x < (group_x + 1) * 3; ++x) {
                for (int y = group_y * 3; y < (group_y + 1) * 3; ++y) {
                    if (squares[x][y] > 0 && squares[x][y] < 10) {
                        domain[i][j][(squares[x][y] - 1)] = false;
                    }
                }
            }
        }
    }
}
