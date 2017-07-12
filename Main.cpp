#include "Game.h"	// Base game class
#include "X0.h"
#include "Nim.h"
#include "Reversi.h"
#include "Chess.h"
#include <time.h>	// rand()
#include <stack>	// undos

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

	int score;
	Move* bestMove = NULL;

	/* 
	gets a move, applies it, and then goes to the next one
	( more effiecient in terms of memory )
	*/
	Move* move = state->getInitMove(player);	// move used to get the first valid move
	// while move is not NULL
	while (move = state->getNextMove(move, player)) {
		state->apply_move(move);

		score = -minimax_abeta(state, -player, depth - 1, -beta, -alfa).first;

		state->undo(move);

		if (score > alfa) {
			alfa = score;
			bestMove = move;
		}

		if (alfa >= beta) {
			break;
		}
	}

	/* Gets all possible moves and iterates through them */
	//std::vector<Move*> moves = state->getMoves(player);
	//
	//for (Move* move : moves) {
	//	state->apply_move(move);
	//
	//	score = minimax_abeta(state, -player, depth - 1, -beta, -alfa).first;
	//
	//	state->undo(move);
	//
	//	if (-score > alfa) {
	//		alfa = -score;
	//		bestMove = move;
	//	}
	//
	//	if (alfa >= beta) {
	//		break;
	//	}
	//}

	return std::pair<int, Move*>(alfa, bestMove);
}

int main() {
	Players player1, player2;
	int depth;	// how many moves the AI can foresee

	while (true) {
		// Choosing Game
		Game* game;
		std::cout << "Which game?\n 1) X & 0\n 2) Nim\n 3) Reversi\n x) Chess\n Press 1, 2, 3 or 4\n\n";
		switch (_getch()) {
		case '1':
			game = new X0();
			depth = 5;
			break;
		case '2':
			game = new Nim();
			depth = 3;
			break;
		case '3':
			game = new Reversi();
			depth = 2;
			break;
		default:
			game = new Chess();
			depth = 2;
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
			depth *= 2;
			break;
		default:
			player2 = Monkey;
			break;
		}

		// while replaying
		while (true) {
			system("cls");
			game->print();
			// if turn = 1 => it's 0 or Black's turn
			int turn = -1;	// X / White starts
			Players currentPlayer;
			stack<Move*> appliedMoves;

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
					// Read human move and if it's valid, apply it
					Move* humanMove;
					while (true) {
						humanMove = game->readHumanMove(turn);
						if (humanMove && humanMove->undo) {
							if (appliedMoves.size() > 1) {
								game->undo(appliedMoves.top());
								appliedMoves.pop();

								game->undo(appliedMoves.top());
								appliedMoves.pop();

								system("cls");
								game->print();
							}
						}
						else if (game->isValid(humanMove)) {
							break;
						}
					}
					game->apply_move(humanMove);
					appliedMoves.push(humanMove);
					break;
				case AI:	// AI has depth = 2* depth of Monkey
				case Monkey:
					appliedMoves.push(minimax_abeta(game, turn, depth, -Inf, Inf).second);
					game->apply_move(appliedMoves.top());
					break;
				default:
					break;
				}

				system("cls");
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
		std::cout << "Wanna try another game?\n y/n\n";
		if (_getch() == 'n')
			break;
	}

	return 0;
}
