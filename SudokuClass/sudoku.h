#ifndef SUDOKU__H
#define SUDOKU__H

class Sudoku {
public:
    Sudoku (int** input);

    Sudoku (const Sudoku &input);

    ~Sudoku ();

    bool operator==(const Sudoku &other) const;

    int read(const int &i, const int &j);
    void write(const int &value, const int &i, const int &j);
    bool check_domain(const int &i, const int &j, const int &k);

private:
    int** squares;
    bool*** domain;
};


#endif

