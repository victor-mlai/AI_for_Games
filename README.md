# AI-for-Games-alpha-beta-pruning
Play Chess, X & 0, Reversi and Nim where the AI is implemented using alpha-beta-pruning

It goes through every possible outcome and chooses only the best one,
resulting in either a draw or a Win from the AI player.

If you accidentaly write a move you don't want to be executed,
simply write an invalid move ( Ex: add more letters to the move ).
or you can undo it by pressing U after applying it.

Undoing:
every move is pushed in a stack after being applied.
when undoing, it pulls the the first 2 moves from the top
and undoes them.

To do:

	1. Choose randomly from the best moves
	
	2. 
