#ifndef SUDOKU_H
#define SUDOKU_H

// loads a sudoku board from file into a 9x9 char array
void load_board(const char* filename, char board[9][9]);

// prints a display of the board on screen in a 9x9 grid
void display_board(const char board[9][9]);

// tests whether the board is fully populated with characters from 1-9
bool is_complete(const char board[9][9]);

// tests whether a digit placement is valid on the given board
bool make_move(const char position[2], char digit, char board[9][9]);

// saves the board to a file called 'filename'
bool save_board(const char* filename, const char board[9][9]);

// recursively solves a given board and counts how many value tests it took
bool solve_board(char board[9][9], long& counter);

#endif
