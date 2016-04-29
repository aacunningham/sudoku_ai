#ifndef SUDOKU__H
#define SUDOKU__H


class Sudoku {
public:
    Sudoku ();
    Sudoku (int** input);
    Sudoku (const Sudoku& input);

    bool operator==(const Sudoku& other) const;
    bool operator!=(const Sudoku& other) const;

    int read(const int& i, const int& j);
    void write(const int& value, const int& i, const int& j);
    bool check_domain(const int& i, const int& j, const int& k);

    void get_next_n_domain(const int& n, int& x, int& y);

    void get_next_single_domain(int& x, int& y);

    void update_domains();

    bool is_valid();

    bool is_solved();

private:
    int squares[9][9];
    bool domains[9][9][9];
    bool modified;
};

#endif

