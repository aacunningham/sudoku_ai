#include "sudoku.h"


Sudoku::Sudoku(int** input) {
    squares = new int*[9];
    domain = new bool**[9];
    for (int i = 0; i < 9; ++i) {
        squares[i] = new int[9];
        domain[i] = new bool*[9];
        for (int j = 0; j < 9; ++j) {
            squares[i][j] = input[i][j];
            domain[i][j] = new bool[9];
            for (int k = 0; k < 9; ++k) {
                domain[i][j][k] = false;
            }
        }
    }
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
    }
    delete[] squares;
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


int Sudoku::read(const int &i, const int &j) {
    return squares[i][j];
}


void Sudoku::write(const int &value, const int &i, const int &j) {
    squares[i][j] = value;
    return;
}


bool Sudoku::check_domain(const int &i, const int &j, const int &k) {
    return domain[i][j][k];
}
