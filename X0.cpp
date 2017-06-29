#include "X0.h"

X0::X0() {
	init();
}

X0::~X0() {
	table.clear();
}

void X0::init() {
	table = vector< vector<int> >(3, vector<int>(3, 0));
	table[0][1] = -1;
}

void X0::print() {
	cout << "  0   1   2  \n";
	cout << "+---+---+---+\n";
	for (int row = 0; row < 3; row++) {
		cout << "| ";
		for (int col = 0; col < 3; col++) {
			switch (table[row][col]) {
				case -1: cout << "X"; break;
				case 1: cout << "0"; break;
				case 0: cout << " "; break;
				default: break;
			}
			cout << " | ";
		}
		cout << row << "\n+---+---+---+\n";
	}
}

void X0::showRezult(int turn) {
	int win = winner();
	if (win == -1)
		std::cout << "X WON!" << std::endl;
	else if (win == 1)
		std::cout << "0 WON!" << std::endl;
	else
		std::cout << "Draw" << std::endl;
}

std::vector<Move*> X0::getMoves(int player) {
	vector<Move*> moves;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (table[row][col] == 0) {
				moves.push_back(new X0Move(row, col, player));
			}
		}
	}

	return moves;
}

Move* X0::readHumanMove(int player) {
	int row, col;
	std::cout << "Insert row & column (Format: row col)\n";
	std::cin >> row >> col;

	return new X0Move(row, col, player);
}

bool X0::apply_move(Move* mv) {
	X0Move move = *(X0Move*)mv;

	if (move.row < 0 || move.row > 2 || move.col < 0 || move.col > 2 || table[move.row][move.col] != 0)
		return false;

	table[move.row][move.col] = move.c;
	return true;
}

void X0::reverse(Move* mv) {
	X0Move move = *(X0Move*)mv;

	table[move.row][move.col] = 0;
}

bool X0::ended() {
	return getMoves(0).empty() || winner() != 0;
}

// Returns -1 if player lost, 1 if player 1 and 0 if no one won yet
int X0::eval(int player) {
	return player*winner();
}

int X0::winner() {
	for (int i = 0; i < 3; i++) {
		// check rows
		if (table[0][i] == table[1][i] && table[1][i] == table[2][i] && table[0][i] != 0)
			return table[0][i];

		// check cols
		if (table[i][0] == table[i][1] && table[i][1] == table[i][2] && table[i][0] != 0)
			return table[i][0];
	}

	// check I diag
	if (table[0][0] == table[1][1] && table[1][1] == table[2][2] && table[1][1] != 0)
		return table[1][1];

	// check II diag
	if (table[0][2] == table[1][1] && table[1][1] == table[2][0] && table[1][1] != 0)
		return table[1][1];

	// no one won yet
	return 0;
}
