#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

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

class Easy_Sudoku_3 {
public:
    Easy_Sudoku_3() {
        input = new int*[9];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[EASY_3]", 0) != std::string::npos) {
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
    ~Easy_Sudoku_3() {
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

class Size_4_Sudoku_1 {
public:
    Size_4_Sudoku_1() {
        input = new int*[4];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[SIZE_4_1]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 3; i >= 0; --i) {
                int* temp = new int[4];
                for (int j = 0; j < 4; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~Size_4_Sudoku_1() {
        for (int i = 0; i < 4; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Size_16_Sudoku_1 {
public:
    Size_16_Sudoku_1() {
        input = new int*[16];
        std::ifstream fixture_data ("tests/test_fixture_data.txt", std::ios::in);
        if (fixture_data.is_open()) {
            std::string str;
            while (std::getline(fixture_data, str)) {
                if (str.find("[SIZE_16_1]", 0) != std::string::npos) {
                    break;
                }
            }
            for (int i = 15; i >= 0; --i) {
                int* temp = new int[16];
                for (int j = 0; j < 16; ++j) {
                    fixture_data >> temp[j];
                }
                input[i] = temp;
            }
        }
    }
    ~Size_16_Sudoku_1() {
        for (int i = 0; i < 16; ++i) {
            delete[] input[i];
        }
        delete[] input;
    }

    int** input;
};

class Tiered_All_Sudoku {
public:
    Tiered_All_Sudoku() {
        inputs.resize(5);
        for (int z = 0; z < 5; ++z) {
            std::ifstream fixture_data;
            std::ostringstream file_name;
            file_name << "tests/" << z << "_sudoku.txt";
            std::cout << "Opening " << file_name.str() << '\n';
            fixture_data.open(file_name.str(), std::ios::in);
            if (fixture_data.is_open()) {
                std::cout << "Opened " << file_name.str() << '\n';
                for (int x = 0; x < 20 ; ++x) {
                    int** input = new int*[9];
                    for (int i = 8; i >= 0; --i) {
                        input[i] = new int[9];
                        for (int j = 0; j < 9; ++j) {
                            fixture_data >> input[i][j];
                        }
                    }
                    inputs[z].push_back(input);
                }
            }
            fixture_data.close();
        }
    }
    ~Tiered_All_Sudoku() {
        for (auto m : inputs) {
            for (int** n : m) {
                for (int i = 0; i < 9; ++i) {
                    delete[] n[i];
                }
                delete[] n;
            }
        }
    }

    std::vector<std::vector<int**>> inputs;
};

