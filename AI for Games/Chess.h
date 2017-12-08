#pragma once
#include "Game.h"

struct Pair { int x, y; };
enum Piece {Rook = 1, Knight = 2, Bishop = 3, Queen = 4, King = 5, Pawn = 6};

class ChessMove : public Move
{
public:
	Pair from;
	Pair to;
	int player;	// -1 or 1 (White or Black)
	int pieceTaken;
	int pieceMoved;

	ChessMove(int Arow, int Acol, int Brow, int Bcol, int player) : from({ Arow, Acol }), to({ Brow, Bcol }), player(player) {}
	~ChessMove() {}
};

class Chess :
	public Game
{
private:
	int table[8][8];

	int bishop[8][8] = {{ -20, -10, -10, -10, -10, -10, -10, -20, },
						{ -10,  0,  0,  0,  0,  0,  0, -10, },
						{ -10,  0,  5, 10, 10,  5,  0, -10, },
						{ -10,  5,  5, 10, 10,  5,  5, -10, },
						{ -10,  0, 10, 10, 10, 10,  0, -10, },
						{ -10, 10, 10, 10, 10, 10, 10, -10, },
						{ -10,  5,  0,  0,  0,  0,  5, -10, },
						{ -20, -10, -10, -10, -10, -10, -10, -20, } };

	int rook[8][8] = {  { 0,  0,  0,  0,  0,  0,  0,  0 },
						{ 5, 10, 10, 10, 10, 10, 10,  5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ -5,  0,  0,  0,  0,  0,  0, -5 },
						{ 0,  0,  0,  5,  5,  0,  0,  0 } };

	int pawn[8][8] = {  { 0,  0,  0,  0,  0,  0,  0,  0 },
						{ 50, 50, 50, 50, 50, 50, 50, 50 },
						{ 10, 10, 20, 30, 30, 20, 10, 10 },
						{ 5,  5, 10, 25, 25, 10,  5,  5 },
						{ 0,  0,  0, 20, 20,  0,  0,  0 },
						{ 5, -5,-10,  0,  0,-10, -5,  5 },
						{ 5, 10, 10,-20,-20, 10, 10,  5 },
						{ 0,  0,  0,  0,  0,  0,  0,  0 } };

	int queen[8][8] = { { -20,-10,-10, -5, -5,-10,-10,-20 },
						{ -10,  0,  0,  0,  0,  0,  0,-10 },
						{ -10,  0,  5,  5,  5,  5,  0,-10 },
						{ -5,   0,  5,  5,  5,  5,  0, -5 },
						{  0,   0,  5,  5,  5,  5,  0, -5 },
						{ -10,  5,  5,  5,  5,  5,  0,-10 },
						{ -10,  0,  5,  0,  0,  0,  0,-10 },
						{ -20,-10,-10, -5, -5,-10,-10,-20 } };

	int knight[8][8] = {{ -50,-40,-30,-30,-30,-30,-40,-50 },
						{ -40,-20,  0,  0,  0,  0,-20,-40 },
						{ -30,  0, 10, 15, 15, 10,  0,-30 },
						{ -30,  5, 15, 20, 20, 15,  5,-30 },
						{ -30,  0, 15, 20, 20, 15,  0,-30 },
						{ -30,  5, 10, 15, 15, 10,  5,-30 },
						{ -40,-20,  0,  5,  5,  0,-20,-40 },
						{ -50,-40,-30,-30,-30,-30,-40,-50 } };

public:
	Chess();
	~Chess();

	// Initializeaza jocul
	void init();

	/**
	* Returneaza o lista cu mutarile posibile
	* care pot fi efectuate de player
	*/
	std::vector<Move*> getMoves(int player);

	Move * getNextMove(Move * prevMove, int player);
	/*
	used for getting the next move
	*/
	Move * getInitMove(int player);

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

	/**
	* Afiseaza rezultatul jocului
	*/
	void showRezult(int turn);
};
