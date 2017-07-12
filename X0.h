#pragma once
#include "Game.h"

/*
	X = -1
	0 = 1
	None = 0
*/

// Reprezinta mutarea in jocu X & 0
class X0Move : public Move
{
public:
	int row, col;	// line and columnn
	int c;	// -1 or 1 (X or 0)

	X0Move(int row, int col, int c) : row(row), col(col), c(c) {}
	~X0Move(){}
};

class X0 : public Game
{
private:
	vector< vector<int> > table;
public:
	X0();
	~X0();
	
	// Initializeaza jocul
	void init();

	/**
	* Returneaza o lista cu mutarile posibile
	* care pot fi efectuate de player
	*/
	std::vector<Move*> getMoves(int player);

	/*
	Returns the next move to be made by the AI using the last move applied
	*/
	Move * getNextMove(Move * prevMove, int player);

	/*
	used for getting the next move
	*/
	Move * getInitMove(int player);

	// Returneaza mutarea citita
	Move* readHumanMove(int player);

	/**
	* Intoarce true daca jocul s-a terminat
	*/
	bool ended();

	/**
	* Cu cat e mai buna mutarea pentru jucatorul curent (player)
	* cu atat valoarea returnata trebuie sa fie mai mare
	* Ex: -Inf = the player lost, Inf = the player won
	*/
	int eval(int player);

	/**
	* Returneaza false daca mutarea e invalida
	*/
	bool isValid(Move* move);

	/*
	* Aplica o mutarea a jucatorului asupra starii curente
	*/
	void apply_move(Move* move);

	/**
	* Aplica mutarea inversa
	*/
	void undo(Move* move);

	/**
	* Afiseaza starea jocului
	*/
	void print();

	/**
	* Determina cine a castigat
	*/
	int winner();

	/**
	* Afiseaza rezultatul jocului
	*/
	void showRezult(int turn);
};

