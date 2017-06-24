#pragma once
#include <vector>
#include <iostream>

using namespace std;

#define Inf 9999

enum cell{X = 1, Z = -1, N = 0};	// X or Z(Zero) or N(None)

struct Move {
	int row, col;	// line and columnn
	int c;	// -1 or 1 (X or 0)

	Move(int row, int col, int c) : row(row), col(col), c(c) {}
	Move(){}
};

class X0 {
private:
	vector< vector<cell> > table;
public:
	// Initializeaza jocul
	void init();

	/**
	* Returneaza o lista cu mutarile posibile
	* care pot fi efectuate de player
	*/
	std::vector<Move> getMoves(int player);

	/**
	* Intoarce true daca jocul s-a terminat
	*/
	bool ended();

	/**
	* Functia de evaluare a starii curente a jocului
	* Evaluarea se face din perspectiva jucatorului
	* aflat curent la mutare (player)
	* -1 = the player lost, 1 = the player won, 0 = no one won
	*/
	int eval(int player);

	/**
	* Aplica o mutarea a jucatorului asupra starii curente
	* Returneaza false daca mutarea e invalida
	*/
	bool apply_move(const Move &move);

	/**
	* Aplica mutarea inversa
	*/
	void reverse(const Move &move);

	/**
	* Afiseaza starea jocului
	*/
	void print();

	/**
	* Determina cine a castigat
	*/
	cell winner();

	X0();
	~X0();
};

