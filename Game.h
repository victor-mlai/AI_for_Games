#pragma once
#include <vector>
#include <iostream>

using namespace std;

#define Inf 9999

enum cell { X = 1, Z = -1, N = 0 };	// X or Z(Zero) or N(None)

struct Move {
	int row, col;	// line and columnn
	int c;	// -1 or 1 (X or 0)

	Move(int row, int col, int c) : row(row), col(col), c(c) {}
	Move() {}
};

class Game
{
public:
	// Initializeaza jocul
	void init(){}

	/**
	* Returneaza o lista cu mutarile posibile
	* care pot fi efectuate de player
	*/
	virtual std::vector<Move> getMoves(int player) = 0;

	/**
	* Intoarce true daca jocul s-a terminat
	*/
	virtual bool ended() = 0;

	/**
	* Functia de evaluare a starii curente a jocului
	* Evaluarea se face din perspectiva jucatorului
	* aflat curent la mutare (player)
	* -1 = the player lost, 1 = the player won, 0 = no one won
	*/
	virtual int eval(int player) = 0;

	/**
	* Aplica o mutarea a jucatorului asupra starii curente
	* Returneaza false daca mutarea e invalida
	*/
	virtual bool apply_move(const Move &move) = 0;

	/**
	* Aplica mutarea inversa
	*/
	virtual void reverse(const Move &move) = 0;

	/**
	* Afiseaza starea jocului
	*/
	virtual void print() = 0;

	/**
	* Determina cine a castigat
	*/
	virtual cell winner() = 0;

	Game();
	virtual ~Game();
};

