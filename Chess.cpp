#include "Chess.h"

Chess::Chess()
{
	init();
}

Chess::~Chess()
{
}

void Chess::init()
{
	int Mat[8][8] = {	{ 1, 2, 3, 4, 5, 3, 2, 1 },
						{ 6, 6, 6, 6, 6, 6, 6, 6 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 },
						{ 0, 0, 0, 0, 0, 0, 0, 0 },
						{-6,-6,-6,-6,-6,-6,-6,-6 },
						{-1,-2,-3,-4,-5,-3,-2,-1 }};

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->table[i][j] = Mat[i][j];
		}
	}
}

std::vector<Move*> Chess::getMoves(int player)
{
	std::vector<Move*> moves;
	ChessMove* move;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (table[i][j] * player > 0) {	// if it's player's piece
				// search where I can put it
				for (int x = 0; x < 8; x++) {
					for (int y = 0; y < 8; y++) {
						move = new ChessMove(i, j, x, y, player);
						if (isValid(move)) {
							moves.push_back(move);
						}
					}
				}
			}
		}
	}

	return moves;
}

Move * Chess::getNextMove(Move * prevMove, int player) {
	ChessMove* pmv = (ChessMove*)prevMove;

	Move * move;
	int i = pmv->from.x;
	int j = pmv->from.y;
	int x = pmv->to.x;
	int y = pmv->to.y + 1;
	for (; i < 8; i++) {
		for (; j < 8; j++) {
			if (table[i][j] * player > 0) {	// if it's player's piece
											// search where I can put it
				for (; x < 8; x++) {
					for (; y < 8; y++) {
						move = new ChessMove(i, j, x, y, player);
						if (isValid(move)) {
							return move;
						}
						delete move;
					}
					y = 0;
				}
				x = 0;
			}
		}
		j = 0;
	}

	return NULL;
}

// move used to get the first valid move
Move * Chess::getInitMove(int player) {
	return new ChessMove(0, 0, 0, 0, player);
}

Move * Chess::readHumanMove(int player)
{
	if (player == -1)
		cout << "White turn: ";
	else
		cout << "Black turn: ";

	char Arow, Acol, Brow, Bcol;	// from A to B

	cout << "Press U to undo or\n";
	cout << "Write from and where to move your piece (Format example: a3 b8)\n";

	Acol = _getch();
	if (Acol == 'u') {	return new Move(true);	}
	cout << Acol;

	Arow = _getch();
	cout << Arow;

	_getch();
	cout << " ";

	Bcol = _getch();
	cout << Bcol;

	Brow = _getch();
	cout << Brow << endl;

	return new ChessMove(Arow - '0' - 1, Acol - 'a', Brow - '0' - 1, Bcol - 'a', player);
}

// gets the absolute value of x
int abs(int x) {
	return x > 0 ? x : -x;
}

int max(int a, int b) {
	return a > b ? a : b;
}

// gets the normalized value of x
int norm(int x) {
	return x < 0 ? -1 : (x > 0 ? 1 : 0);
}

bool Chess::isValid(Move * move)
{
	ChessMove mv = *(ChessMove*)move;

	// outbound check
	if (mv.from.x < 0 || mv.from.y < 0 || mv.from.x > 7 || mv.from.y > 7)	return false;
	if (mv.to.x < 0 || mv.to.y < 0 || mv.to.x > 7 || mv.to.y > 7)	return false;
	// moving to the same cell
	if (mv.from.x == mv.to.x && mv.from.y == mv.to.y)	return false;
	// moving nothing
	if (table[mv.from.x][mv.from.y] == 0)	return false;
	// moving opponent piece
	if (table[mv.from.x][mv.from.y] * mv.player < 0)	return false;
	// taking my own piece
	if (table[mv.to.x][mv.to.y] * mv.player > 0)	return false;

	Pair c = mv.from;	// current piece position
	int x = mv.to.x - mv.from.x;
	int y = mv.to.y - mv.from.y;
	Pair d = { norm(x), norm(y) };	// direction

	// distance between the 2 positions
	x = abs(x);
	y = abs(y);

	int piece = table[mv.from.x][mv.from.y] * mv.player;

	switch (piece)
	{
	int n;
	case 1:	// tower
		if (x != 0 && y != 0)	return false;

		n = max(x, y);

		for (int i = 1; i < n; i++) {
			c.x += d.x;
			c.y += d.y; 
			if (table[c.x][c.y] != 0)
				return false;
		}
		break;
	case 2:	// knight
		if (x + y != 3 || x == 3 || y == 3)	return false;	// return (x + y == 3 && x != 3 && y != 3);
		break;
	case 3:	// bishop
		if (x != y)	return false;
		
		n = x;

		for (int i = 1; i < n; i++) {
			c.x += d.x;
			c.y += d.y;
			if (table[c.x][c.y] != 0)
				return false;
		}
		break;
	case 4:	// qween
		if ((x != 0 && y != 0) && x != y)	return false;
		
		n = max(x, y);

		for (int i = 1; i < n; i++) {
			c.x += d.x;
			c.y += d.y;
			if (table[c.x][c.y] != 0)
				return false;
		}
		break;
	case 5:	// king
		if (x > 1 || y > 1)	return false;	// return !(x > 1 || y > 1);
		break;
	case 6:	// pawn
		if ((mv.to.x - mv.from.x) * mv.player < 0)	return false;
		c.x += d.x;
		c.y += d.y; 
		if (y == 0) {
			if (table[c.x][c.y] != 0)
				return false;
			if (x > 2)
				return false;
			// moving 2 cells horizontally
			if (x == 2) {
				if ((mv.from.x == 1 && mv.player == 1) || (mv.from.x == 6 && mv.player == -1))
					if (table[c.x + d.x][c.y + d.y] == 0)
						return true;
				return false;
			}
		}
		else if (x != 1 || y != 1 || table[c.x][c.y] * mv.player >= 0)
			return false;
		break;
	default:
		break;
	}

	return true;
}

void Chess::apply_move(Move * move)
{
	ChessMove* mv = (ChessMove*)move;

	mv->pieceTaken = table[mv->to.x][mv->to.y];
	table[mv->to.x][mv->to.y] = table[mv->from.x][mv->from.y];
	table[mv->from.x][mv->from.y] = 0;

	move = mv;
}

void Chess::undo(Move * move)
{
	ChessMove mv = *(ChessMove*)move;

	table[mv.from.x][mv.from.y] = table[mv.to.x][mv.to.y];
	table[mv.to.x][mv.to.y] = mv.pieceTaken;
}

bool Chess::ended()
{
	int nr = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (table[i][j] == 5 || table[i][j] == -5) {	// if it's a king
				nr++;
			}
		}
	}

	return nr != 2;
}

int Chess::eval(int player)
{
	int score = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			switch (table[i][j])
			{
			case 0: break;
			case -1: score += -500 - rook[i][j];	break;
			case 1:  score +=  500 + rook[7 - i][j];		break;
			case -2: score += -320 - knight[i][j];	break;
			case 2:  score +=  320 + knight[7 - i][j];		break;
			case -3: score += -330 - bishop[i][j];	break;
			case 3:  score +=  330 + bishop[7 - i][j];		break;
			case -4: score += -900 - queen[i][j];	break;
			case 4:  score +=  900 + queen[7 - i][j];		break;
			case -5: score += -20000;	break;
			case 5:  score +=  20000;	break;
			case -6: score += -100 - pawn[i][j];	break;
			case 6:  score +=  100 + pawn[7 - i][j];		break;
			default:
				break;
			}
		}
	}

	return score * player;
}

void Chess::print()
{
	int i, j;
	char ch = 'a';

	for (j = 0; j < 8; j++)
		std::cout << "    " << ch++ << "   ";
	std::cout << endl;

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
			std::cout << "+-------";
		std::cout << "+\n";

		for (j = 0; j < 8; j++)
			switch (table[i][j])
			{
			case 0: std::cout << "|       "; break;
			case -1:
			case 1: std::cout << "| [---] "; break;
			case -2:std::cout << "|  / o| "; break;
			case 2: std::cout << "|  / o| "; break;
			case -3:std::cout << "|   o   "; break;
			case 3: std::cout << "|   x   "; break;
			case -4:
			case 4: std::cout << "|  \\^/  "; break;
			case -5:
			case 5: std::cout << "|  =|=  "; break;
			case -6:std::cout << "|  ( )  "; break;
			case 6: std::cout << "|  (X)  "; break;
			}
		cout << "|\n";

		for (j = 0; j < 8; j++)
			switch (table[i][j])
			{
			case 0: if ((i + j) % 2 == 1)	cout << "|   X   ";
					else					cout << "|       "; 
					break;
			case -1:cout << "|  | |  "; break;
			case 1: cout << "|  |X|  "; break;
			case -2:cout << "| [__ | "; break;
			case 2: cout << "| [XXX| "; break;
			case -3:cout << "|   O   "; break;
			case 3: cout << "|   X   "; break;
			case -4:cout << "|  / \\  "; break;
			case 4: cout << "|  /X\\  "; break;
			case -5:
			case 5: cout << "|   |   "; break;
			case -6:cout << "|  / \\  "; break;
			case 6: cout << "|  /X\\  "; break;
			}
		cout << "| " << i + 1 << endl;

		for (j = 0; j < 8; j++)
			switch (table[i][j])
			{
			case 0: cout << "|       "; break;
			case -1: cout << "| [___] "; break;
			case 1: cout << "| [XXX] "; break;
			case -2: cout << "|  /__| "; break;
			case 2: cout << "|  /XX| "; break;
			case -3: cout << "|  (_)  "; break;
			case 3: cout << "|  (X)  "; break;
			case -4:
			case -5:
			case -6: cout << "| (___) "; break;
			case 4:
			case 5:
			case 6: cout << "| (XXX) "; break;
			}
		cout << "|\n";
	}

	for (j = 0; j < 8; j++)
		cout << "+-------";
	cout << "+\n";
}

void Chess::showRezult(int turn)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (table[i][j] == 5) {
				cout << "Black Won!\n";
				return;
			}
			else if (table[i][j] == -5) {
				cout << "White Won!\n";
				return;
			}
		}
	}
}
