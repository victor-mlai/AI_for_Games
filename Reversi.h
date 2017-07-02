#pragma once
#include "Game.h"

/*
	X = -1
	O = 1
	None = 0
*/

struct Point { int x, y; };

/**
* Reprezinta mutarea in jocu Nim
*/
class RevMove : public Move
{
public:
	int player; /* Jucatorul care face mutarea */
	int row, col;
	vector< vector<int> > table;	// Retin starea jocului inainte de fiecare mutare sa pot da undo

	RevMove(int row, int col, int player, int n) : row(row), col(col), player(player) {
		table = vector< vector<int> >(n, vector<int>(n));
	}
	~RevMove() { table.clear(); }
};

class Reversi :
	public Game
{
private:
	int n = 6;	// table dimension
	vector< vector<int> > table;
	vector< vector<int> > heuristic;
public:
	Reversi();
	~Reversi();

	bool isOutsidePoint(Point p);

	bool isValid(RevMove mv);

	void setN(int n);

	// Initializeaza jocul
	void init();

	/**
	* Returneaza o lista cu mutarile posibile
	* care pot fi efectuate de player
	*/
	std::vector<Move*> getMoves(int player);

	// Returneaza mutarea citita
	Move* readHumanMove(int player);

	/**
	* Intoarce true daca jocul este intr-o stare finala
	*/
	bool ended();

	/**
	* Evalueaza starea jocului
	* Cu cat a fost mai buna mutarea jucatorului curent (player)
	* cu atat valoarea returnata trebuie sa fie mai mare
	* Ex: -Inf = daca player a pierdut, Inf = daca a castigat
	*/
	int eval(int player);

	/**
	* Aplica o mutarea a jucatorului asupra starii curente
	* Returneaza false daca mutarea e invalida
	*/
	bool apply_move(Move* move);

	/**
	* Aplica o mutarea inversa
	*/
	void reverse(Move* move);

	/**
	* Afiseaza starea jocului
	*/
	void print();

	int winner();

	/**
	* Afiseaza rezultatul jocului
	*/
	void showRezult(int turn);
};

