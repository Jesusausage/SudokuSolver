#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {
    cout << "Loading Sudoku board from file '" << filename << "'... ";

    ifstream in(filename);
    if (!in)
	cout << "Failed!" << endl;
    assert(in);

    char buffer[512];

    int row = 0;
    in.getline(buffer,512);
    while (in && row < 9) {
	for (int n=0; n<9; n++) {
	    assert(buffer[n] == '.' || isdigit(buffer[n]));
	    board[row][n] = buffer[n];
	}
	row++;
	in.getline(buffer,512);
    }

    cout << ((row == 9) ? "Success!" : "Failed!") << endl;
    assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
    if (!(row % 3))
	cout << "  +===========+===========+===========+" << endl;
    else
	cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
    cout << (char) ('A' + row) << " ";
    for (int i=0; i<9; i++) {
	cout << ( (i % 3) ? ':' : '|' ) << " ";
	cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
    }
    cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
    cout << "    ";
    for (int r=0; r<9; r++) 
	cout << (char) ('1'+r) << "   ";
    cout << endl;
    for (int r=0; r<9; r++) {
	print_frame(r);
	print_row(board[r],r);
    }
    print_frame(9);
}

bool is_complete(const char board[9][9]) {
    for (int rows=0; rows<9; rows++) {
	for (int columns=0; columns<9; columns++) {
	    if (board[rows][columns]<49 || board[rows][columns]>57)
		return 0;
	    /* It loops through each tile of the board array, then tests whether it contains
	       a character from 1-9 of the ASCII table.
	       If at any point a value other than 1-9 is contained, 'false' is returned. */
	}
    }
    return 1;
    // if it completes, then the board is full of numbers, so 'true' is returned.
}


bool make_move(const char position[2], char digit, char board[9][9]) {
    if (digit<49 || digit>57) return 0; // Tests whether the digit is in range,
    if (position[0]<65 || position[0]>73) return 0; // and whether it is on the board
    if (position[1]<49 || position[1]>57) return 0;
    
    int row = position[0]-65,
	col = position[1]-49; // Transforms the digit's ASCII coordinates to integers
    
    for (int n=0; n<9; n++) {
	if (digit==board[row][n] || digit==board[n][col])
	    return 0; // Tests whether the digit is already contained somewhere in its row/column
    }

    int block[2] = {row/3, col/3}; // This detects which 3x3 'block' the digit is contained in
    
    for (int blockRow=0; blockRow<3; blockRow++) {
	for (int blockCol=0; blockCol<3; blockCol++) {
	    if (digit == board[ 3*block[0] + blockRow ][ 3*block[1] + blockCol ])
		return 0; // Tests whether the digit is already contained somewhere in its 'block'
	}
    }

    board[row][col] = digit; // If the function has not yet returned 'false', the move is valid,
    return 1; // and so the board is updated and 'true' is returned
}


bool save_board(const char* filename, const char board[9][9]) {
    ofstream output;
    output.open(filename);

    for (int rows=0; rows<9; rows++) {
	for (int cols=0; cols<9; cols++) {
	    output.put(board[rows][cols]); // Loops through each row/col and prints the tile
	}
	output.put('\n');
    }

    if (output.fail()) return 0; // Returns 'false' if the output fails
    output.close(); // Otherwise the stream is closed and 'true' is returned
    return 1;
}


bool solve_board(char board[9][9], long& counter) {
    // I have added a counter passed by reference to count the total number of value tests for a
    // given puzzle solution
    
    for (int rows=0; rows<9; rows++) {
	for (int cols=0; cols<9; cols++) {
	    char rowName = (rows+65); 
	    char columnName = (cols+49);
	    // These variables store current row/col name as ASCII characters for 'make_move()'
	    
	    if (board[rows][cols]=='.') { // Only tries moves on blank tiles
		
		for (char testValue=49; testValue<=57; testValue++) { // Tries values from 1-9
		    counter++;
		    const char tile[2] = {rowName, columnName};
		    if (make_move(tile, testValue, board))
			if (solve_board(board, counter)) return 1;
		    /* If a valid move is found, the move is made and the 'solve_board()' function
		       is recursively called, now using the updated board to try the next tile */
		    
		}
		
		board[rows][cols]='.'; /* If the previous loop tries all values from 1-9 and none
					  of them work, the tile is reset to allow for recursive 
					  backtracking */
		return 0;  
		/* When the function recursively backtracks all the way to the first 
		   tile and fails, the function returns 'false' */
	    }
	    
	}
    }

    return 1;
}

/* If the function makes it all the way to the last tile on the board and completes it, 'true'
   is recursively returned through the function by line146 and finally here the first iteration
   also returns 'true' */
