#include "Reversi.h"

Reversi::Reversi()
{
	init();
}

Reversi::~Reversi() {}

void Reversi::setN(int n)
{
	this->n = n;
}

void Reversi::init()
{
	table = vector< vector<int> >(n, vector<int>(n));
	table[n / 2 - 1][n / 2 - 1] = table[n / 2][n / 2] = 1;
	table[n / 2 - 1][n / 2] = table[n / 2][n / 2 - 1] = -1;
}

std::vector<Move*> Reversi::getMoves(int player)
{
	return std::vector<Move*>();
}

Move* Reversi::readHumanMove(int player)
{
	int x, y;
	std::cout << "Insert position [0..n - 1], [0..n - 1] ";
	std::cin >> x >> y;

	return new RevMove(x, y, player);
}

bool Reversi::ended()
{
	return false;
}

int Reversi::eval(int player)
{
	return 0;
}

bool Reversi::apply_move(Move * mv)
{
	RevMove move = *(RevMove*)mv;
	if (move.row == -1 && move.col == -1)	// daca am mutarea nula
		return true;

	if (table[move.row][move.col] != 0)
		return false;

	bool ok = false;

	for (int x_dir = -1; x_dir <= 1; x_dir++) {
		for (int y_dir = -1; y_dir <= 1; y_dir++) {
			if (x_dir == 0 && y_dir == 0)
				continue;

			int i = move.row + x_dir, j = move.col + y_dir;
			for (; i >= 0 && j >= 0 && i < n && j < n && table[i][j] == -move.player; i += x_dir, j += y_dir);
			if (i >= 0 && j >= 0 && i < n && j < n && table[i][j] == move.player && (abs(move.row - i) > 1 || abs(move.col - j) > 1))
			{
				ok = true;
				for (i = move.row + x_dir, j = move.col + y_dir; i >= 0 && j >= 0 && i < n && j < n && table[i][j] == -move.player; i += x_dir, j += y_dir)
					table[i][j] = move.player;
			}
		}
	}

	if (!ok)
		return false;

	table[move.row][move.col] = move.player;

	return true;
}

void Reversi::reverse(Move * mv)
{
	RevMove move = *(RevMove*)mv;
	table[move.row][move.col] = 0;
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

int Reversi::winner()
{
	return 0;
}

void Reversi::showRezult(int turn)
{
}
