#ifndef BEC_h
#define BEC_h

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include "TDAs/arraylist/arraylist.h"
#include "TDAs/tuple/tuple.h"
#include <unistd.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAXCHAR 72

#define WHITE_P -10
#define BLACK_P 10

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
	int board[8][8];
	tuple *anpassant;
	//en passant tells us if in that position the condition 
	//meets for en passant to be applied, else it will be 
	//NULL_TUPLE
	tuple *Wcastle; // includes ints for Short and long castle
	tuple *Bcastle;
} node;




node* createNode();

void fenToBoard(node* chess, const char* fencode);

//Move value of a position to another

node* changePos(node* tablero,tuple* original,tuple* mov);


ArrayList* kingMove(node*,tuple);
ArrayList* queenMove(node*,tuple);
ArrayList* knightMove(node*,tuple);
ArrayList* bishopMove(node*,tuple);
ArrayList* rookMove(node*,tuple);

//will return a list of best posible moves.
ArrayList* get_adj_node(node*);

int getPieceScore(node*);
//score for how many pieces does a player have
int getDeepSearchScore(node*); 
//score for knowing how good posibilites does it has posible movements




#endif /* BEC_h */