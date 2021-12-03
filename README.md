# AI-for-Games-alpha-beta-pruning
Play Chess, X & 0, Reversi and Nim where the AI is implemented using alpha-beta-pruning

### Using the program
If you accidentaly write a move you don't want to be executed, simply write an invalid move ( Ex: add more letters to the move ).
Or you can undo it by pressing U after applying it.

### Algorithms
#### Minimax
It goes through every possible outcome and only chooses the best one, resulting in either a draw or a win for the AI player.

#### Undoing:
Every move is pushed in a stack after being applied. After pressing U, it pulls the the first 2 moves from the top and undoes them.

### To do:
```
	1. Choose randomly from the best moves
	2. 
```
