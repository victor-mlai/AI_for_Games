#pragma once
#include "Game.h"

/**
* Reprezinta mutarea in jocu Nim
*/
class NimMove : public Move
{
public:
	int amount; /* Cantitatea extrasa (1, 2 sau 3) */
	int heap; /* Indicile multimii din care se face extragerea */

	NimMove(int amount, int heap) : amount(amount), heap(heap) {}
	~NimMove() {}
};

class Nim : public Game
{
private:
	int heaps[3];
public:
	Nim();
	~Nim();

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
	* Returneaza false daca mutarea e invalida
	*/
	bool isValid(Move* move);

	/*
	* Aplica o mutarea a jucatorului asupra starii curente
	*/
	void apply_move(Move* move);

	/**
	* Aplica o mutarea inversa
	*/
	void undo(Move* move);

	/**
	* Afiseaza starea jocului
	*/
	void print();

	int nrOfStarsLeft();

	/**
	* Afiseaza rezultatul jocului
	*/
	void showRezult(int turn);
};
