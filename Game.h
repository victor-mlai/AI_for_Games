#pragma once
#include <vector>
#include <iostream>	// cin, cout
#include <conio.h>	// _getch()

using namespace std;

#define Inf 999999

class Move {
public :
	bool undo = false;
	Move(bool undo) : undo(undo) {}
	Move() {}
};

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
	
	/*
	*Returneaza false daca mutarea e invalida
	*/
	virtual bool isValid(Move* move) = 0;
	
	/**
	* Aplica mutarea jucatorului asupra starii curente
	*/
	virtual void apply_move(Move* move) = 0;

	/**
	* Aplica mutarea inversa
	*/
	virtual void undo(Move* move) = 0;

	/**
	* Afiseaza starea jocului
	*/
	virtual void print() = 0;

	/**
	* Afiseaza rezultatul jocului
	*/
	virtual void showRezult(int turn) = 0;
};

