#include "Nim.h"

Nim::Nim() {
	init();
}

Nim::~Nim() {}

void Nim::init() {
	heaps[0] = 3;
	heaps[1] = 4;
	heaps[2] = 5;
}

/**
* Afiseaza starea jocului
*/
void Nim::print() {
	for (int i = 0; i < 3; i++) {
		std::cout << i << ":";
		for (int j = 0; j < heaps[i]; j++)
			std::cout << " *";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/**
* Returneaza o lista cu mutarile posibile
* care pot fi efectuate de player
*/
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
	std::cout << "Insert amount [1, 2 or 3] and heap [0, 1 or 2]: ";
	std::cin >> am >> h;

	return new NimMove(am, h);
}

/**
* Aplica o mutarea a jucatorului asupra starii curente
* Returneaza false daca mutarea e invalida
*/
bool Nim::apply_move(Move* mv) {
	NimMove move = *(NimMove*)mv;

	if (move.amount > 3 ||
		move.amount < 1 ||
		move.heap > 2 ||
		move.heap < 0 ||
		heaps[move.heap] - move.amount < 0)
		return false;

	heaps[move.heap] -= move.amount;
	return true;
}

/**
* Aplica mutarea inversa
*/
void Nim::reverse(Move* mv) {
	NimMove move = *(NimMove*)mv;

	heaps[move.heap] += move.amount;
}

/**
* Intoarce true daca jocul este intr-o stare finala
*/
bool Nim::ended() {
	return winner() < 1;
}

// Returns -1 if player lost, 1 if player 1 and 0 if no one won yet
int Nim::eval(int player) {
	if (winner() == 0)
		return Inf;		// Win for the current player, next player will lose.
	else if (winner() == 1)
		return -Inf;	// Lose for the current player, next player will win.

	return 0;
}

int Nim::winner() {
	return heaps[0] + heaps[1] + heaps[2];
}

void Nim::showRezult(int turn) {
	if (turn == 1)
		std::cout << "Player 1 WON!" << std::endl;
	else
		std::cout << "Player 1 LOST!" << std::endl;
}
