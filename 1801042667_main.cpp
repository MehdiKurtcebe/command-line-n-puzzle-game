// N puzzle game program
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include "1801042667_classes.h"

using namespace std;

int main(int argc, char* argv[]){
	NPuzzle game;
	int problemSize;
	char playerMove;
	srand(time(NULL));

	if (argc == 1) {
		cout << "Please enter the problem size (2 < size < 10)" << endl;
		do {
			cin >> problemSize;
		} while (problemSize < 3 || problemSize > 9); // 2 < size < 10

		game = NPuzzle(problemSize, problemSize);
		game.shuffle(5 * problemSize); // initialize
	} else {
		game.readFromFile(argv[1]);
	}

	while (!game.isSolved()) {
		cout << game;

		do {
			cout << "L: Move the empty cell left" << endl;
			cout << "R: Move the empty cell right" << endl;
			cout << "U: Move the empty cell up" << endl;
			cout << "D: Move the empty cell down" << endl;
			cout << "S: Shuffle the board" << endl;
			cout << "V: I'm stuck, solve this" << endl;
			cout << "T: Report" << endl;
			cout << "E: Export the board" << endl;
			cout << "O: Import a board" << endl;
			cout << "Q: Quit" << endl;
			cout << "Your move (in capital letter): ";
			cin >> playerMove;
		} while (playerMove != 'L' && playerMove != 'R' && playerMove != 'U' 
				 && playerMove != 'D' && playerMove != 'S' && playerMove != 'Q'
				 && playerMove != 'V' && playerMove != 'T' && playerMove != 'E' && playerMove != 'O');

		if (playerMove == 'L' || playerMove == 'R' || playerMove == 'U' || playerMove == 'D') {
			game.move(playerMove);
		} else if (playerMove == 'S') {
			game.shuffle(game.getXD() * game.getYD());
		} else if (playerMove == 'V') {
			game.solvePuzzle();
			cout << game;
		} else if (playerMove == 'T') {
			game.printReport();
		} else if (playerMove == 'E') {
			string filename;

			cout << "Enter the filename: ";
			cin >> filename;
			game.writeToFile(filename);
		} else if (playerMove == 'O') {
			string filename;

			cout << "Enter the filename: ";
			cin >> filename;
			game.readFromFile(filename);
		} else if (playerMove == 'Q') {
			exit(0);
		}
	}

	cout << "Problem Solved!" << endl
		 << "Total number of moves: " << game.numberOfMoves() << endl;

	return 0;
}
