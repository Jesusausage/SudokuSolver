#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

    char board[9][9];
    long counter;
    /* A counter is declared and passed through the solver function by reference
       to count how many attempted values each puzzle took. */

    /* This section illustrates the use of the pre-supplied helper functions. */
    cout << "============= Pre-supplied functions =============" << endl << endl;

    cout << "Calling load_board():" << endl;
    load_board("easy.dat", board);

    cout << endl << "Displaying Sudoku board with display_board():" << endl;
    display_board(board);
    cout << "Done!" << endl << endl;

    cout << "=================== Question 1 ===================" << endl << endl;

    load_board("easy.dat", board);
    cout << "Board is ";
    if (!is_complete(board))
	cout << "NOT ";
    cout << "complete." << endl << endl;

    load_board("easy-solution.dat", board);
    cout << "Board is ";
    if (!is_complete(board))
	cout << "NOT ";
    cout << "complete." << endl << endl;

    cout << "=================== Question 2 ===================" << endl << endl;

    load_board("easy.dat", board);

    // Should be OK
    cout << "Putting '1' into I8 is ";
    if (!make_move("I8", '1', board)) 
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

    // Testing value out of bounds invalidity
    cout << "Putting '0' into I8 is ";
    if (!make_move("I7", '2', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

    // Testing value out of bounds invalidity
    cout << "Putting '10' into I8 is ";
    if (!make_move("I7", '2', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

    // Testing block invalidity
    cout << "Putting '9' into E5 is ";
    if (!make_move("E5", '9', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

    // Testing row invalidity
    cout << "Putting '1' into A2 is ";
    if (!make_move("A2", '1', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

    // Testing column invalidity
    cout << "Putting '7' into A2 is ";
    if (!make_move("A2", '7', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);

    // Testing tile out of bounds invalidity (next 4)
    cout << "Putting '2' into I10 is ";
    if (!make_move("I10", '2', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
    
    cout << "Putting '2' into I0 is ";
    if (!make_move("I0", '2', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
    
    cout << "Putting '2' into J7 is ";
    if (!make_move("J7", '2', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
    
    cout << "Putting '2' into @7 is ";
    if (!make_move("@7", '2', board))
	cout << "NOT ";
    cout << "a valid move. The board is:" << endl;
    display_board(board);
    
    cout << "=================== Question 3 ===================" << endl << endl;

    load_board("easy.dat", board);
    if (save_board("easy-copy.dat", board))
	cout << "Save board to 'easy-copy.dat' successful." << endl;
    else
	cout << "Save board failed." << endl;
    cout << endl;

    cout << "=================== Question 4 ===================" << endl << endl;

    load_board("easy.dat", board);
    counter=0;
    // Counter reset to zero before the solver is called each time
    
    if (solve_board(board, counter)) {
	cout << "The 'easy' board has a solution computed in " << counter << " tries:\n\n";
	// Displays the counter before each solution (if a solution exists)
	display_board(board);
    } else {
	cout << "A solution cannot be found." << endl;
	display_board(board);
    }
    cout << endl;

    load_board("medium.dat", board);
    counter=0;
    
    if (solve_board(board, counter)) {
	cout << "The 'medium' board has a solution computed in " << counter << " tries:\n\n";
	display_board(board);
    } else 
	cout << "A solution cannot be found." << endl;
    cout << endl;	

    cout << "=================== Question 5 ===================" << endl << endl;

    load_board("mystery1.dat", board);
    counter=0;
    
    if (solve_board(board, counter)) {
	cout << "The 'mystery1' board has a solution computed in " << counter << " tries:\n\n";
	display_board(board);
    } else 
	cout << "A solution cannot be found." << endl;
    cout << endl;

    load_board("mystery2.dat", board);
    counter=0;
    
    if (solve_board(board, counter)) {
	cout << "The 'mystery2' board has a solution computed in " << counter << " tries:\n\n";
	display_board(board);
    } else 
	cout << "A solution cannot be found." << endl;
    cout << endl;

    load_board("mystery3.dat", board);
    counter=0;
    if (solve_board(board, counter)) {
	cout << "The 'mystery3' board has a solution computed in " << counter << " tries:\n\n";
	display_board(board);
    } else 
	cout << "A solution cannot be found." << endl;
    cout << endl;
    
    return 0;
}
