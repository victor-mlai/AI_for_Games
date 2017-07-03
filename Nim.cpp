#include "Nim.h"

Nim::Nim() {
	std::cout << "Win by not taking the last *\n";
	init();
}

Nim::~Nim() {}

void Nim::init() {
	heaps[0] = 3;
	heaps[1] = 5;
	heaps[2] = 7;
}

void Nim::print() {
	for (int i = 0; i < 3; i++) {
		std::cout << i << ":";
		for (int j = 0; j < heaps[i]; j++)
			std::cout << " *";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

std::vector<Move*> Nim::getMoves(int player) {
	std::vector<Move*> ret;
	for (int i = 0; i < 3; i++)
		for (int k = 1; k <= 3; k++)
			if (k <= heaps[i])
				ret.push_back(new NimMove(k, i));
	return ret;
}

Move* Nim::readHumanMove(int player) {
	int am, h;
	
	if (player == -1)
		cout << "Player 1 turn: ";
	else
		cout << "Player 2 turn: ";
	
	cout << "Press U to undo or\n";
	std::cout << "Insert amount [1, 2 or 3] and heap [0, 1 or 2]: ";

	am = _getch();
	if (am == 'u') { return new Move(true); }
	am -= '0';
	cout << am;
	cin >> h;
	
	return new NimMove(am, h);
}

bool Nim::isValid(Move* move) {
	NimMove mv = *(NimMove*)move;

	if (mv.amount > 3 || mv.amount < 1 || mv.heap > 2 || mv.heap < 0 ||
		heaps[mv.heap] - mv.amount < 0)
		return false;

	return true;
}

void Nim::apply_move(Move* mv) {
	NimMove move = *(NimMove*)mv;

	heaps[move.heap] -= move.amount;
}

void Nim::undo(Move* mv) {
	NimMove move = *(NimMove*)mv;

	heaps[move.heap] += move.amount;
}

bool Nim::ended() {
	return nrOfStarsLeft() < 1;
}

// Returns -1 if player lost, 1 if player won and 0 if no one won yet
int Nim::eval(int player) {
	if (nrOfStarsLeft() == 0)
		return 1;		// Win for the current player, next player will lose.
	else if (nrOfStarsLeft() == 1)
		return -1;	// Lose for the current player, next player will win.

	return 0;
}

int Nim::nrOfStarsLeft() {
	return heaps[0] + heaps[1] + heaps[2];
}

void Nim::showRezult(int turn) {
	if (turn == -1)
		std::cout << "Player 1 WON!" << std::endl;
	else
		std::cout << "Player 2 WON!" << std::endl;
}
