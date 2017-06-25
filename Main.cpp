#include "X0.h"
#include <conio.h> // _getch()
#include <time.h> // rand()

enum Players{Human, AI, Monkey};

/**
* Implementarea de negamax cu alpha-beta pruning
* Return val: o pereche <first, second>
* first: cel mai bun scor care poate fi obtinut de jucatorul aflat la mutare,
* second: mutarea propriu-zisa
*/
std::pair<int, Move>
minimax_abeta(X0 state, int player, int depth, int alfa, int beta) {
	if (depth == 0 || state.ended()) {
		return std::pair<int, Move>(state.eval(player), Move());
	}

	Move bestMove;
	int score;
	std::pair<int, Move> p;
	std::vector<Move> moves = state.getMoves(player);
	for (Move move : moves) {
		state.apply_move(move);

		p = minimax_abeta(state, -player, depth - 1, -beta, -alfa);
		score = p.first;

		if (-score > alfa) {
			alfa = -score;
			bestMove = move;
		}

		if (alfa >= beta) {
			break;
		}

		// reverse move
		state.reverse(move);
	}

	return std::pair<int, Move>(alfa, bestMove);
}

// gets a random move from the best ones
Move getRandomMove(X0 x0, int player, int depth) {
	if (depth == 0 || x0.ended()) {
		return Move();
	}

	srand((unsigned int)time(NULL));

	int alfa = -Inf;
	int beta = Inf;
	int score;
	std::vector<Move> moves = x0.getMoves(player);
	std::vector<Move> BestMoves;
	for (Move move : moves) {
		x0.apply_move(move);

		score = minimax_abeta(x0, -player, depth - 1, -beta, -alfa).first;

		if (-score > alfa) {
			alfa = -score;
			BestMoves.clear();
			BestMoves.push_back(move);
		}
		else if (-score == alfa) {
			alfa = -score;
			BestMoves.push_back(move);
		}

		if (alfa >= beta) {
			break;
		}

		// reverse move
		x0.reverse(move);
	}

	int r = rand() % BestMoves.size();
	return BestMoves[r];
}

int main() {
	X0 x0;
	Players player1, player2;
	int depth;	// how many moves the AI can foresee

	player1 = Human;

	// Choosing player2
	do { // se asteapta decizia 1, 2 sau 3
		std::cout << "Against\n1) AI\n2) a friend\n3) a monkey\nPress 1, 2 or 3\n\n";
		switch (_getch()) {
			case '1':
				player2 = AI;
				depth = 9;	// all of them
				break;
			case '2':
				player2 = Human;
				break;
			case '3':
				player2 = Monkey;
				depth = 5;
				break;
			default:
				continue;
		}
		break;	// daca nu s-a intrat in deafault, se iese din do while
	} while (true);

	Players aux = player1;
	player1 = player2;
	player2 = aux;

	while (true) {	// while replaying
		x0.print();
		int turn = -1;	// X starts
		Players currentPlayer;
		while (!x0.ended())
		{
			if (turn == 1) {
				currentPlayer = player1;
			}
			else {
				currentPlayer = player2;
			}

			switch (currentPlayer) {
				case Human:
					// Read human move and if it's valid, apply it
					int row, col;
					do {
						std::cout << "Insert row & column (Format: row col)\n";
						std::cin >> row >> col;
					} while (!x0.apply_move(Move(row, col, turn)));
					break;
				case AI:
				case Monkey:
					x0.apply_move(minimax_abeta(x0, turn, depth, -Inf, Inf).second);
					break;
				default:
					break;
			}

			x0.print();
			turn *= -1;
		}

		if (x0.winner() == X)
			std::cout << "X WON!" << std::endl;
		else if (x0.winner() == Z)
			std::cout << "0 WON!" << std::endl;
		else
			std::cout << "Draw" << std::endl;

		std::cout << "Play again?\n y/n\n";
		if (_getch() == 'n')
			break;

		// reinit the game
		x0.init();

		//swap players
		//Players aux = player1;
		//player1 = player2;
		//player2 = aux;
	}

	return 0;
}
