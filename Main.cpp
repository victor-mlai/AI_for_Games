#include "Game.h"	// Base game class
#include "X0.h"
#include "Nim.h"
#include "Reversi.h"
#include <conio.h> // _getch()
#include <time.h> // rand()

enum Players{Human, AI, Monkey};

/**
* Implementarea de negamax cu alpha-beta pruning
* Return val: o pereche <first, second>
*	first: cel mai bun scor care poate fi obtinut de jucatorul aflat la mutare,
*	second: mutarea propriu-zisa
*/
std::pair<int, Move*>
minimax_abeta(Game* state, int player, int depth, int alfa, int beta) {
	if (depth == 0 || state->ended()) {
		return std::pair<int, Move*>(state->eval(player), nullptr);
	}

	Move* bestMove;
	int score;
	std::pair<int, Move*> p;
	std::vector<Move*> moves = state->getMoves(player);
	for (Move* move : moves) {
		state->apply_move(move);

		p = minimax_abeta(state, -player, depth - 1, -beta, -alfa);
		score = p.first;

		state->reverse(move);

		if (-score > alfa) {
			alfa = -score;
			bestMove = move;
		}

		if (alfa >= beta) {
			break;
		}
	}

	//return std::pair<int, Move*>(alfa, bestMove);
	return std::pair<int, Move*>(alfa + player*state->eval(player), bestMove);
}

int main() {
	Players player1, player2;
	int depth;	// how many moves the AI can foresee

	// Choosing Game
	Game* game;
	std::cout << "Which game?\n1) X & 0\n2) Nim\nx) Reversi\nPress 1, 2 or 3\n\n";
	switch (_getch()) {
		case '1':
			game = new X0();
			break;
		case '2':
			game = new Nim();
			break;
		default:
			game = new Reversi();
			break;
	}

	player1 = Human;

	// Choosing Player 2
	std::cout << "Against\n1) a friend\n2) AI\nx) a monkey\nPress 1, 2 or 3\n\n";
	switch (_getch()) {
		case '1':
			player2 = Human;
			break;
		case '2':
			player2 = AI;
			depth = 9;
			break;
		default:
			player2 = Monkey;
			depth = 5;
			break;
	}

	// while replaying
	while (true) {
		game->print();
		int turn = -1;
		Players currentPlayer;

		while (!game->ended())
		{
			if (turn == -1) {
				currentPlayer = player1;
			}
			else {
				currentPlayer = player2;
			}

			switch (currentPlayer) {
				case Human:
					Move* humanMove;
					// Read human move and if it's valid, apply it
					do {
						humanMove = game->readHumanMove(turn);
					} while (!game->apply_move(humanMove));
					delete humanMove;
					break;
				case AI:
				case Monkey:
					game->apply_move(minimax_abeta(game, turn, depth, -Inf, Inf).second);
					break;
				default:
					break;
			}

			game->print();
			turn *= -1;
		}

		game->showRezult(turn);

		std::cout << "Play again?\n y/n\n";
		if (_getch() == 'n')
			break;

		// reinit the game
		game->init();

		// swap players so the other player can start first
		Players aux = player1;
		player1 = player2;
		player2 = aux;
	}

	return 0;
}
