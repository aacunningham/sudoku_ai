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
