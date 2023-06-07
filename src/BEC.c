#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "TDAs/arraylist/arraylist.h"
/*
	Because we are using a international to name every object of the chess game.
 	We'll define everything in this file, using english.

  "8/0p/2p/5R/////"
*/



#define MAXCHAR 72
// Corresponds to how big the FEN can be
/*
	The FEN can have 7 line breaks, there are 32 pieces, plus their positions, we could have 64 characters to indicate each piece.
	In total, there would be 7 + 64 characters + 1 for the line break or \0
	total = 72
	*/

// defining int id's

//players id
#define WHITE_P -10
#define BLACK_P -1

//pieces
//White pieces are in upper cases, and black ones in lower case
#define KING 1
#define QUEEN 2
#define ROOK 3
#define BISHOP 4
#define KNIGHT 5
#define PAWN 6

#define king 10
#define queen 20
#define rook 30
#define bishop 40
#define knight 50
#define pawn 60


//no piece
#define BLANK 0

typedef char string[MAXCHAR];
typedef struct chessboard {
	int turn; //indicates wich player has to play
	string fen;
	int **board;
} node;

typedef struct position {
	int fil;
	int col;
} position;

//to translate a board into fen string and viceversa
void fenToBoard(node*);
void boardToFen(node*);



//Will return list with new node, where the movements were already set.
ArrayList* pawnMove(node*,position);
ArrayList* kingMove(node*,position);
ArrayList* queenMove(node*,position);
ArrayList* knightMove(node*,position);
ArrayList* bishopMove(node*,position);
ArrayList* rookMove(node*,position;

//will return a list of best posible moves.
ArrayList* get_adj_node(node*);

int getPieceScore(node*);
//score for how many pieces does a player have
int getDeepSearchScore(node*); 
//score for knowing how good posibilites does it has posible movements


int main()// temporal, para probar que todo funcione bien.
{
	printf("Hello world!\n");
	return 0;
}