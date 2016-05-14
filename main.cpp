#include <iostream>
#include <string>
#include "Sudoku_AIConfig.h"
#include "SudokuClass/sudoku.h"

int main (){
    std::cout << "Sudoku AI, version " << Sudoku_AI_VERSION_MAJOR << "." << Sudoku_AI_VERSION_MINOR << std::endl;
    std::cout << "Written by Aaron Cunningham\n" << std::endl;

    std::cout << "Type 'help' for commands\n\n" << std::endl;

    std::string input;
    while (true) {
        std::cout << ">> ";
        std::getline (std::cin, input);

        if (input == "help") {
            std::cout << "List of commands:\n"
                << "  create sudoku\n"
                << "  solve sudoku\n"
                << "  help\n"
                << "  exit\n" << std::endl;
        } else if (input == "create sudoku") {
            int diff;
            int size;
            while (true) {
                std::cout << "What difficulty (1-5): ";
                std::cin >> diff;
                if (diff > 0 && diff < 6) {
                    break;
                }
            }
            while (true) {
                std::cout << "What size (4, 9, 16): ";
                std::cin >> size;
                if (size == 4 || size == 9 || size == 16) {
                    break;
                }
            }

            int removed;
            std::cout << "About to call create sudoku function...\n";
            Sudoku new_puzzle = create_sudoku(size, diff - 1, removed);
            for (int i = size-1; i >= 0; --i) {
                for (int j = 0; j < size; ++j) {
                    std::cout << new_puzzle.read(j, i) << " ";
                }
                std::cout << std::endl;
            }
        } else if (input == "solve sudoku") {
            int size;
            while (true) {
                std::cout << "What size (4, 9, 16): ";
                std::cin >> size;
                if (size == 4 || size == 9 || size == 16) {
                    break;
                }
            }
            std::cout << "Enter the values separated with white space, with empty squares being 0 and anything larger than 9\nwritten as numbers (A = 10):\n";
            std::cout << "4x4 example:\n1 0 0 4\n2 0 0 3\n3 0 0 2\n4 0 0 1\n\n";
            std::cout << "Your grid:\n";
            int** input = new int*[size];
            for (int i = size - 1; i >= 0; --i) {
                input[i] = new int[size];
                for (int j = 0; j < size; ++j) {
                    std::cin >> input[i][j];
                }
            }
            Sudoku new_puzzle = Sudoku(input, size);
            solve(new_puzzle);

            std::cout << "\nSolved puzzle:\n";
            for (int i = size -1; i >= 0; --i) {
                for (int j = 0; j < size; ++j) {
                    std::cout << new_puzzle.read(j, i) << ' ';
                }
                std::cout << '\n';
            }
            for (int i = 0; i < size; ++i) {
                delete[] input[i];
            }
            delete[] input;
        } else if (input == "exit") {
            break;
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}

