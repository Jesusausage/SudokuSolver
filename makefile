sudoku: main.o sudoku.o
	g++ main.o sudoku.o -o sudoku

main.o: main.cpp
	g++ -c -g main.cpp

sudoku.o: sudoku.cpp
	g++ -c -g sudoku.cpp
