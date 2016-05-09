#include <iostream>
#include <fstream>
#include <string>

class Solved {
public:
    Solved() {
        input = new int*[9];
        input[8] = new int[9] {9,7,8,3,1,2,6,4,5};
        input[7] = new int[9] {6,4,5,9,7,8,3,1,2};
        input[6] = new int[9] {3,1,2,6,4,5,9,7,8};
        input[5] = new int[9] {8,9,7,2,3,1,5,6,4};
        input[4] = new int[9] {5,6,4,8,9,7,2,3,1};
        input[3] = new int[9] {2,3,1,5,6,4,8,9,7};
        input[2] = new int[9] {7,8,9,1,2,3,4,5,6};
        input[1] = new int[9] {4,5,6,7,8,9,1,2,3};
        input[0] = new int[9] {1,2,3,4,5,6,7,8,9};
    }
    ~Solved() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Almost_Solved {
public:
    Almost_Solved() {
        input = new int*[9];
        input[8] = new int[9] {0,7,8,3,1,2,6,4,5};
        input[7] = new int[9] {6,4,5,0,7,8,3,1,2};
        input[6] = new int[9] {3,1,2,6,4,5,0,7,8};
        input[5] = new int[9] {8,0,7,2,3,1,5,6,4};
        input[4] = new int[9] {5,6,4,8,0,7,2,3,1};
        input[3] = new int[9] {2,3,1,5,6,4,8,0,7};
        input[2] = new int[9] {7,8,0,1,2,3,4,5,6};
        input[1] = new int[9] {4,5,6,7,8,0,1,2,3};
        input[0] = new int[9] {1,2,3,4,5,6,7,8,0};
    }
    ~Almost_Solved() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Random_Sudoku {
public:
    Random_Sudoku() {
        input = new int*[9];
        for (int i = 0; i < 9; ++i) {
            input[i] = new int[9];
            for (int j = 0; j < 9; ++j) {
                input[i][j] = (i * j) % 10;
            }
        }
    }
    ~Random_Sudoku() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Easy_Sudoku_1 {
public:
    Easy_Sudoku_1() {
        input = new int*[9];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[EASY_1]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 8; i >= 0; --i) {
                int* temp = new int[9];
                for (int j = 0; j < 9; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~Easy_Sudoku_1() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Easy_Sudoku_2 {
public:
    Easy_Sudoku_2() {
        input = new int*[9];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[EASY_2]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 8; i >= 0; --i) {
                int* temp = new int[9];
                for (int j = 0; j < 9; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~Easy_Sudoku_2() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Medium_Sudoku_1 {
public:
    Medium_Sudoku_1() {
        input = new int*[9];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[MEDIUM_1]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 8; i >= 0; --i) {
                int* temp = new int[9];
                for (int j = 0; j < 9; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~Medium_Sudoku_1() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Hard_Sudoku_1 {
public:
    Hard_Sudoku_1() {
        input = new int*[9];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[HARD_1]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 8; i >= 0; --i) {
                int* temp = new int[9];
                for (int j = 0; j < 9; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~Hard_Sudoku_1() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class AI_Sudoku {
public:
    AI_Sudoku() {
        input = new int*[9];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[AI]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 8; i >= 0; --i) {
                int* temp = new int[9];
                for (int j = 0; j < 9; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~AI_Sudoku() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Multi_Solution_Sudoku_1 {
public:
    Multi_Solution_Sudoku_1() {
        input = new int*[9];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[MULTI_SOLUTION_1]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 8; i >= 0; --i) {
                int* temp = new int[9];
                for (int j = 0; j < 9; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~Multi_Solution_Sudoku_1() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Multi_Solution_Sudoku_2 {
public:
    Multi_Solution_Sudoku_2() {
        input = new int*[9];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[MULTI_SOLUTION_2]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 8; i >= 0; --i) {
                int* temp = new int[9];
                for (int j = 0; j < 9; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~Multi_Solution_Sudoku_2() {
        for (int i = 0; i < 9; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

