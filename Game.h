#pragma once
#include <vector>
#include <iostream>

using namespace std;

#define Inf 999999

class Move {};

class Game
{
public:
	Game();
	virtual ~Game();
	
	// Initializeaza jocul
	virtual void init() = 0;

	/**
	* Returneaza un vector cu mutarile posibile
	* care pot fi efectuate de player
	*/
	virtual std::vector<Move*> getMoves(int player) = 0;

	// Returneaza false daca mutarea este invalida
	virtual Move* readHumanMove(int player) = 0;

	/**
	* Intoarce true daca jocul s-a terminat
	*/
	virtual bool ended() = 0;

	/**
	* Cu cat e mai buna mutarea pentru jucatorul curent (player)
	* cu atat valoarea returnata trebuie sa fie mai mare
	* Ex: -Inf = the player lost, Inf = the player won, 0 = nothing happened
	*/
	virtual int eval(int player) = 0;

	/**
	* Aplica mutarea jucatorului asupra starii curente
	* Returneaza false daca mutarea e invalida
	*/
	virtual bool apply_move(Move* move) = 0;

	/**
	* Aplica mutarea inversa
	*/
	virtual void reverse(Move* move) = 0;

	/**
	* Afiseaza starea jocului
	*/
	virtual void print() = 0;

	/**
	* Determina cine a castigat
	*/
	virtual int winner() = 0;

	/**
	* Afiseaza rezultatul jocului
	*/
	virtual void showRezult(int turn) = 0;
};

