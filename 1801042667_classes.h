#ifndef CLASSES_H_
#define CLASSES_H_
#include <iostream>
#include <vector>

using namespace std;

class Board {
public:
	Board();
	Board(int xD, int yD);

	void print() const; // Print the gameBoard to the screen
	void readFromFile (const string filename);
	void writeToFile (const string filename) const;
	void reset(); // Reset board to solved state
	void setSize (const int newX, const int newY); // 2 < newX < 10, 2 < newY < 10
	bool move (const char playerMove); // Move the blank tile. 'R': right, 'L': left, 'U': up, 'D': down
	bool isSolved() const;

	int getXD() const {return xDimension;}
	int getYD() const {return yDimension;}
	int numberOfMoves() const {return numOfMoves;}
	char lastMove() const {return previousMove;}

	void incrementMoveCounter() {++numOfMoves;}
	void resetNumOfMoves() {numOfMoves = 0;}
	void setPrevMove(const char prev) {previousMove = prev;}

	const int operator()(const int x, const int y) const {return gameBoard[x][y];}
	const bool operator==(const Board& other) const;
	friend ostream& operator<<(ostream& out, const Board& game);
	friend istream& operator>>(istream& in, Board& game);
private:
	vector<vector<int> > gameBoard;
	int xDimension;
	int yDimension;
	int numOfMoves;
	char previousMove;

	int str_to_int(const string str) const {
		int num = 0;
		for(char c: str){
			if(c >= '0' && c <= '9')
				num = num * 10 + (c - '0');
		}
		return num;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

class NPuzzle {
public:
	NPuzzle(); // As default, puzzle is 3*3
	NPuzzle(int xD, int yD);

	void print() const {PuzzleBoard.print();}
	void printReport() const {cout << numberOfMoves() << " moves have been done." << endl;}
	void readFromFile (const string filename) {PuzzleBoard.readFromFile (filename);
						 					   resetNumOfMoves();
											   setPrevMove('S');
											   Boards.resize(1);
											   Boards[0] = PuzzleBoard;}
	void writeToFile (const string filename) const {PuzzleBoard.writeToFile (filename);}
	void shuffle (int NTimes) {reset();
							   for (int i = 0; i < NTimes; ++i) moveRandom();
							   resetNumOfMoves();
							   setPrevMove('S');
							   Boards.resize(1);
							   Boards[0] = PuzzleBoard;}
	void reset() {PuzzleBoard.reset();
				  resetNumOfMoves();
				  setPrevMove('S');
				  Boards.resize(0);}
	void setSize (const int newX, const int newY) {PuzzleBoard.setSize(newX, newY);
												   resetNumOfMoves();
												   setPrevMove('S');}
	char moveRandom(); // It does a random move except previous move
	bool move (const char playerMove);
	void solvePuzzle();
	bool isSolved() const {return PuzzleBoard.isSolved();}

	int getXD() const {return PuzzleBoard.getXD();}
	int getYD() const {return PuzzleBoard.getYD();}
	int numberOfMoves() const {return PuzzleBoard.numberOfMoves();}
	char lastMove() const {return PuzzleBoard.lastMove();}

	void incrementMoveCounter() {PuzzleBoard.incrementMoveCounter();}
	void resetNumOfMoves() {PuzzleBoard.resetNumOfMoves();}
	void setPrevMove(const char prev) {PuzzleBoard.setPrevMove(prev);}

	friend ostream& operator<< (ostream& out, const NPuzzle& game) {return out << game.PuzzleBoard;}
	friend istream& operator>> (istream& in, NPuzzle& game) {in >> game.PuzzleBoard;
																   game.resetNumOfMoves();
																   game.setPrevMove('S');
																   game.Boards.resize(1);
																   game.Boards[0] = game.PuzzleBoard;
																   return in;}
private:
	Board PuzzleBoard;
	vector<Board> Boards;
};

#endif