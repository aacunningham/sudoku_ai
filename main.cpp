#include <iostream>
#include <stack>
#include "Sudoku_AIConfig.h"
#include "SudokuClass/sudoku.h"

int main (){
    std::cout << "Sudoku AI, version " << Sudoku_AI_VERSION_MAJOR << "." << Sudoku_AI_VERSION_MINOR << std::endl;
    std::cout << "Hello, world!" << std::endl;

    int** input = new int*[9];
    for (int i = 0; i < 9; ++i) {
        input[i] = new int[9];
        for (int j = 0; j < 9; ++j) {
            input[i][j] = i * j;
        }
    }

    Sudoku* test = new Sudoku(input);

    Sudoku test2 = Sudoku(*test);

    std::cout << "Test location: " << test << std::endl;
    std::cout << "Test2 location: " << &test2 << std::endl;

    bool result = *test == test2;
    std::cout << result << std::endl;

    test->write(4, 3, 3);
    result = *test == test2;
    std::cout << result << std::endl;

    for (int i = 0; i < 9; ++i) {
        delete[] input[i];
    }
    delete[] input;

    delete test;

    return 0;
}
