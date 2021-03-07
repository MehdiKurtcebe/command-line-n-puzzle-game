#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "classes.h"

using namespace std;

const int BLANK = -2;
const int MAX_DIMENSION = 9;

Board::Board()
			:xDimension(3), yDimension(3) {
	for (int i = 0; i < MAX_DIMENSION; ++i) {
		gameBoard.push_back(vector<int> (MAX_DIMENSION, -1));
	}
}

Board::Board (int xD, int yD)
			 :xDimension(xD), yDimension(yD) {
	for (int i = 0; i < MAX_DIMENSION; ++i) {
		gameBoard.push_back(vector<int> (MAX_DIMENSION, -1));
	}
}

inline void Board::print() const {
	for (int y = 0; y < yDimension; ++y) {
		for (int x = 0; x < xDimension; ++x) {
			if (gameBoard[x][y] == BLANK) {
				cout << "  ";
			} else {
				cout << setfill('0') << setw(2) << gameBoard[x][y];
			}
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Board::readFromFile (string filename) {
	ifstream puzzleFile(filename);
	int counter = 0;
	string tile;

	if(puzzleFile){
		while (getline(puzzleFile, tile)) ++counter; // to find number of rows
		yDimension = counter;

		counter = 0;
		puzzleFile.clear();
		puzzleFile.seekg(0);
		while(puzzleFile >> tile) ++counter; // to find number of columns
		xDimension = counter / yDimension;

		puzzleFile.clear();
		puzzleFile.seekg(0);
		for(int y = 0; y < yDimension; ++y){
			for(int x = 0; x < xDimension; ++x){
				puzzleFile >> tile;
				if(tile == "bb") gameBoard[x][y] = BLANK;
				else gameBoard[x][y] = str_to_int(tile);
			}
		}
	}
	puzzleFile.close();
}

void Board::writeToFile (const string filename) const {
	ofstream saveFile(filename);

	for (int y = 0; y < yDimension; ++y) {
		for (int x = 0; x < xDimension; ++x) {
			if (gameBoard[x][y] == BLANK) {
				saveFile << "bb";
			} else {
				saveFile << setfill('0') << setw(2) << gameBoard[x][y];
			}
			saveFile << " ";
		}
		saveFile << endl;
	}

	saveFile.close();
}

void Board::reset() {
	int count = 1;

	for (int y = 0; y < yDimension; ++y){
		for (int x = 0; x < xDimension; ++x){
			if (gameBoard[x][y] != 0)
				gameBoard[x][y] = count++;
		}
	}
	gameBoard[xDimension - 1][yDimension - 1] = BLANK;
}

inline void Board::setSize (const int newX, const int newY) {
	xDimension = newX;
	yDimension = newY;

	reset();
}

bool Board::move (const char playerMove) {
	int blankCoordinates[2]; // blankCoordinates[] = {x_axis, y_axis}
	int temp;

	for (int y = 0; y < yDimension; ++y){
		for (int x = 0; x < xDimension; ++x){
			if (gameBoard[x][y] == BLANK){
				blankCoordinates[0] = x;
				blankCoordinates[1] = y;
			}
		}
	} // it finds the coordinates of blank on the board

	switch (playerMove){
		case 'L':
			if (blankCoordinates[0] == 0) return false; // x = 0 is left border
			else if (gameBoard[blankCoordinates[0] - 1][blankCoordinates[1]] == 0) return false; // 00 is impossible position
			else {
				temp = gameBoard[blankCoordinates[0] - 1][blankCoordinates[1]];
				gameBoard[blankCoordinates[0] - 1][blankCoordinates[1]] = gameBoard[blankCoordinates[0]][blankCoordinates[1]];
				gameBoard[blankCoordinates[0]][blankCoordinates[1]] = temp;
				return true;
			} // swap
			break;
		case 'R':
			if (blankCoordinates[0] == xDimension - 1) return false; // x = xDimension - 1 is right border
			else if (gameBoard[blankCoordinates[0] + 1][blankCoordinates[1]] == 0) return false; // 00 is impossible position
			else {
				temp = gameBoard[blankCoordinates[0] + 1][blankCoordinates[1]];
				gameBoard[blankCoordinates[0] + 1][blankCoordinates[1]] = gameBoard[blankCoordinates[0]][blankCoordinates[1]];
				gameBoard[blankCoordinates[0]][blankCoordinates[1]] = temp;
				return true;
			} // swap
			break;
		case 'U':
			if (blankCoordinates[1] == 0) return false; // y = 0 is top border
			else if (gameBoard[blankCoordinates[0]][blankCoordinates[1] - 1] == 0) return false; // 00 is impossible position
			else {
				temp = gameBoard[blankCoordinates[0]][blankCoordinates[1] - 1];
				gameBoard[blankCoordinates[0]][blankCoordinates[1] - 1] = gameBoard[blankCoordinates[0]][blankCoordinates[1]];
				gameBoard[blankCoordinates[0]][blankCoordinates[1]] = temp;
				return true;
			} // swap
			break;
		case 'D':
			if (blankCoordinates[1] == yDimension - 1) return false; // y = yDimension - 1 is bottom border
			else if (gameBoard[blankCoordinates[0]][blankCoordinates[1] + 1] == 0) return false; // 00 is impossible position
			else {
				temp = gameBoard[blankCoordinates[0]][blankCoordinates[1] + 1];
				gameBoard[blankCoordinates[0]][blankCoordinates[1] + 1] = gameBoard[blankCoordinates[0]][blankCoordinates[1]];
				gameBoard[blankCoordinates[0]][blankCoordinates[1]] = temp;
				return true;
			} // swap
			break;
	}
}

bool Board::isSolved() const {
	int solvedPuzzle[xDimension][yDimension];
	int count = 1;

	for (int y = 0; y < yDimension; ++y){
		for (int x = 0; x < xDimension; ++x){
			if (gameBoard[x][y] == 0)
				solvedPuzzle[x][y] = 0;
			else solvedPuzzle[x][y] = count++;
		}
	}
	solvedPuzzle[xDimension - 1][yDimension - 1] = BLANK;

	for (int y = 0; y < yDimension; ++y){
		for (int x = 0; x < xDimension; ++x){
			if (solvedPuzzle[x][y] != gameBoard[x][y]) return false;
		}
	}
	return true;
}

const bool Board::operator== (const Board& other) const {
	if (xDimension != other.xDimension || yDimension != other.yDimension) return false;

	for (int x = 0; x < xDimension; ++x){
		for (int y = 0; y < yDimension; ++y){
			if (gameBoard[x][y] != other(x, y)) return false;
		}
	}

	return true;
}

ostream& operator<< (ostream& out, const Board& game) {
	for (int y = 0; y < game.getYD(); ++y) {
		for (int x = 0; x < game.getXD(); ++x) {
			if (game(x, y) == BLANK) {
				out << "  ";
			} else {
				out << setfill('0') << setw(2) << game(x, y);
			}
			out << " ";
		}
		out << endl;
	}
	out << endl;

	return out;
}

istream& operator>> (istream& in, Board& game) {
	int counter = 0;
	string tile;

	while (getline(in, tile)) ++counter; // to find number of rows
	game.yDimension = counter;

	counter = 0;
	in.clear();
	in.seekg(0);
	while(in >> tile) ++counter; // to find number of columns
	game.xDimension = counter / game.yDimension;

	in.clear();
	in.seekg(0);
	for(int y = 0; y < game.yDimension; ++y){
		for(int x = 0; x < game.xDimension; ++x){
			in >> tile;
			if(tile == "bb") game.gameBoard[x][y] = BLANK;
			else game.gameBoard[x][y] = game.str_to_int(tile);
		}
	}

	return in;
}

///////////////////////////////////////////////////////////////////////////////

NPuzzle::NPuzzle() {
	PuzzleBoard = Board(3, 3);
	resetNumOfMoves();
	setPrevMove('S');
}

NPuzzle::NPuzzle (int xD, int yD) {
	PuzzleBoard = Board(xD, yD);
	resetNumOfMoves();
	setPrevMove('S');
}

char NPuzzle::moveRandom() {
	int randMove;

	while (true){
		randMove = rand() % 4;

		switch (randMove){
			case 0:
				if(lastMove() != 'R' && move ('R')) return 'R';
			case 1:
				if(lastMove() != 'L' && move ('L')) return 'L';
			case 2:
				if(lastMove() != 'U' && move ('U')) return 'U';
			case 3:
				if(lastMove() != 'D' && move ('D')) return 'D';
		}
	}
}

bool NPuzzle::move (const char playerMove) {
	if(PuzzleBoard.move (playerMove)){
		Boards.resize(1);
		Boards[0] = PuzzleBoard;
		incrementMoveCounter();
		setPrevMove(playerMove);
		return true;
	}else return false;
}

void NPuzzle::solvePuzzle(){
	Board tempBoard;
	bool isInTheVector;
	resetNumOfMoves();
	for (int i = 0; i < Boards.size(); ++i) {
		tempBoard = Boards[i];

		if (tempBoard.move('R')) {
			isInTheVector = false;

			for (int j = 0; j < Boards.size(); ++j) {
				if (Boards[j] == tempBoard) {
					isInTheVector = true;
					break;
				}
			}

			if (!isInTheVector) {
				tempBoard.incrementMoveCounter();
				tempBoard.setPrevMove('R');
				Boards.push_back(tempBoard);
			}
			
			tempBoard = Boards[i];
		}

		if (tempBoard.move('L')) {
			isInTheVector = false;

			for (int j = 0; j < Boards.size(); ++j) {
				if (Boards[j] == tempBoard) {
					isInTheVector = true;
					break;
				}
			}

			if (!isInTheVector) {
				tempBoard.incrementMoveCounter();
				tempBoard.setPrevMove('L');
				Boards.push_back(tempBoard);
			} 

			tempBoard = Boards[i];
		}

		if (tempBoard.move('U')) {
			isInTheVector = false;

			for (int j = 0; j < Boards.size(); ++j) {
				if (Boards[j] == tempBoard) {
					isInTheVector = true;
					break;
				}
			}

			if (!isInTheVector) {
				tempBoard.incrementMoveCounter();
				tempBoard.setPrevMove('U');
				Boards.push_back(tempBoard);
			} 

			tempBoard = Boards[i];
		}

		if (tempBoard.move('D')) {
			isInTheVector = false;

			for (int j = 0; j < Boards.size(); ++j) {
				if (Boards[j] == tempBoard) {
					isInTheVector = true;
					break;
				}
			}

			if (!isInTheVector) {
				tempBoard.incrementMoveCounter();
				tempBoard.setPrevMove('D');
				Boards.push_back(tempBoard);
			} 

			tempBoard = Boards[i];
		}

		for(int j = 0; j < Boards.size(); ++j){
			if(Boards[j].isSolved()){
				tempBoard = Boards[j];
				Boards.resize(1);
				Boards[0] = PuzzleBoard = tempBoard;
				return;
			}
		}
	}
}