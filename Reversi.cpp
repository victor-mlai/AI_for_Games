#include "Reversi.h"

Point d[] = { { -1, 0 },{ -1, 1 },{ 0, 1 },{ 1, 1 },{ 1, 0 },{ 1, -1 },{ 0, -1 },{ -1, -1 } };

Reversi::Reversi()
{
	init();
}

Reversi::~Reversi() {}

bool Reversi::isOutsidePoint(Point p) {
	return p.x < 0 || p.y < 0 || p.x >= n || p.y >= n;
}

bool Reversi::isValid(Move* move)
{
	RevMove mv = *(RevMove*)move;

	Point n = { mv.row, mv.col };
	if (isOutsidePoint(n) || table[mv.row][mv.col] != 0)
		return false;

	for (int k = 0; k < 8; k++) {
		n = d[k];
		n.x += mv.row;
		n.y += mv.col;

		if (!isOutsidePoint(n) && table[n.x][n.y] == -mv.player) {
			while (!isOutsidePoint(n) && table[n.x][n.y] == -mv.player) {
				n.x += d[k].x;
				n.y += d[k].y;
			}
			if (!isOutsidePoint(n) && table[n.x][n.y] == mv.player) {
				return true;
			}
		}
	}

	return false;
}

void Reversi::setN(int n)
{
	this->n = n;
}

void Reversi::init()
{
	table = vector< vector<int> >(n, vector<int>(n));
	table[n / 2 - 1][n / 2 - 1] = table[n / 2][n / 2] = 1;
	table[n / 2 - 1][n / 2] = table[n / 2][n / 2 - 1] = -1;

	heuristic = vector< vector<int> >(n, vector<int>(n));
	heuristic[0][0] = heuristic[n - 1][0] = heuristic[0][n - 1] = heuristic[n - 1][n - 1] = 99;
	heuristic[1][1] = heuristic[n - 2][1] = heuristic[1][n - 2] = heuristic[n - 2][n - 2] = -24;

	heuristic[0][1] = heuristic[n - 1][1] = heuristic[1][n - 1] = heuristic[n - 2][n - 1] = -8;
	heuristic[1][0] = heuristic[n - 2][0] = heuristic[0][n - 2] = heuristic[n - 1][n - 2] = -8;

	for (int i = 2; i <= n / 2 - 1; i++) {
		heuristic[0][i] = heuristic[0][n - i - 1] = heuristic[n - 1][i] = heuristic[n - 1][n - i - 1] = (n - i) * 2;
		heuristic[i][0] = heuristic[n - i - 1][0] = heuristic[i][n - 1] = heuristic[n - i - 1][n - 1] = (n - i) * 2;
	}

	for (int i = 2; i <= n / 2 - 1; i++) {
		heuristic[1][i] = heuristic[1][n - i - 1] = heuristic[n - 2][i] = heuristic[n - 2][n - i - 1] = -(n - i);
		heuristic[i][1] = heuristic[n - i - 1][1] = heuristic[i][n - 2] = heuristic[n - i - 1][n - 2] = -(n - i);
	}

	for (int i = 2; i <= n / 2 - 1; i++) {
		for (int j = 2; j <= n / 2 - 1; j++) {
			heuristic[i][j] = heuristic[i][n - j - 1] = heuristic[n - i - 1][j] = heuristic[n - i - 1][n - j - 1] = (n*n - 4*i*j);
		}
	}
}

std::vector<Move*> Reversi::getMoves(int player)
{
	RevMove* mv;
	std::vector<Move*> moves;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mv = new RevMove(i, j, player, n);
			if (isValid(mv)) {
				moves.push_back(mv);
			}
			else {
				delete mv;
			}
		}
	}
	moves.push_back(new RevMove(-1, -1, player, n));	// add the Pas move

	return moves;
}

Move* Reversi::readHumanMove(int player)
{
	if (player == -1)
		cout << "Player 1 turn: ";
	else
		cout << "Player 2 turn: "; 
	
	cout << "Press U to undo or\n";
	cout << "Write position from:\n";
	cout << " {-1, -1} (Pas move), " << endl << " ";

	vector<Move*> moves = getMoves(player);
	for (Move* move : moves) {
		RevMove* mv = (RevMove*)move;
		cout << "{" << mv->row << ", " << mv->col << "}, ";
	}
	cout << endl;


	int i, j;
	i = _getch();
	if (i == 'u') { return new Move(true); }
	i -= '0';
	cout << i;
	cin >> j;

	return new RevMove(i, j, player, n);
}

bool Reversi::ended()
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (isValid(new RevMove(i, j, 1, n)))
				return false;
			if (isValid(new RevMove(i, j, -1, n)))
				return false;
		}

	return true;
	//return (getMoves(-1).size() + getMoves(1).size() == 0);
}

int Reversi::eval(int player)
{
	int score = 0;
	int my_tiles = 0;
	int op_tiles = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (table[i][j] == player) {
				score += heuristic[i][j];
				my_tiles++;
			}
			else if (table[i][j] == -player) {
				score -= heuristic[i][j];
				op_tiles++;
			}
		}
	}

	// Mobility
//	int m = getMoves(player).size() - getMoves(-player).size();

	return score + (my_tiles - op_tiles) * 5;// +m * 20;
}

void Reversi::apply_move(Move * mv)
{
	RevMove move = *(RevMove*)mv;
	RevMove* temp = (RevMove*)mv;
	if (move.row == -1 && move.col == -1)	// daca am mutarea nula
		return ;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp->table[i][j] = table[i][j];
		}
	}

	mv = (Move*)temp;

	Point n;
	for (int k = 0; k < 8; k++) {
		n = d[k];
		n.x += move.row;
		n.y += move.col;
		if (!isOutsidePoint(n) && table[n.x][n.y] == -move.player) {
			while (!isOutsidePoint(n) && table[n.x][n.y] == -move.player) {
				n.x += d[k].x;
				n.y += d[k].y;
			}
			if (!isOutsidePoint(n) && table[n.x][n.y] == move.player) {
				n.x -= d[k].x;
				n.y -= d[k].y;
				while (table[n.x][n.y] == -move.player) {
					table[n.x][n.y] = move.player;
					n.x -= d[k].x;
					n.y -= d[k].y;
				}
				table[n.x][n.y] = move.player;
			}
		}
	}
}

void Reversi::undo(Move * mv)
{
	RevMove move = *(RevMove*)mv;

	if (move.row == -1 && move.col == -1)	// daca am mutarea nula
		return; 
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			table[i][j] = move.table[i][j];
		}
	}
}

void Reversi::print()
{
	for (int i = 0; i < n; i++) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j< n; j++)
		{
			if (table[i][j] == 0)
				std::cout << '.';
			else if (table[i][j] == 1)
				std::cout << 'O';
			else
				std::cout << 'X';
			std::cout << " ";
		}
		std::cout << i << std::endl;
	}
	std::cout << std::endl;
}

void Reversi::showRezult(int turn)
{
	int s = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (table[i][j] == -1)
				s++;
			else if (table[i][j] == 1)
				s--;
		}
	}

	if (s > 0)
		std::cout << "X WON!" << std::endl;
	else if (s < 0)
		std::cout << "O WON!" << std::endl;
	else
		std::cout << "Draw" << std::endl;
}
