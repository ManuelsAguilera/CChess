#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include "TDAs/arraylist/arraylist.h"
#include "TDAs/tuple/tuple.h"
#include <unistd.h>
/*
	Because we are using a international to name every object of the chess game.
 	We'll define everything in this file, using english.

  "8/0p/2p/5R/////"
*/


//The following are for colors to display

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
//defines the value of a tuple component as null

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




node* createNode()
{
	node* new;
	new = malloc(sizeof(node));
	new->turn = WHITE_P;
	
	new->anpassant = createTuple(0,0);
	new->Wcastle = createTuple(0,0);
	new->Bcastle = createTuple(0,0);
	
	return new;
}

void fenToBoard(node* chess, const char* fencode)
{
    char i = *fencode;
    int rank = 7; // Start from the 8th rank (0-based indexing)
    int file = 0; // Start from the first file (column)

    while (i != '\0' && i != '\n')
    {
        switch (i)
        {
            case 'K':
                chess->board[rank][file++] = KING;
                break;
            case 'Q':
                chess->board[rank][file++] = QUEEN;
                break;
            case 'R':
                chess->board[rank][file++] = ROOK;
                break;
            case 'B':
                chess->board[rank][file++] = BISHOP;
                break;
            case 'N':
                chess->board[rank][file++] = KNIGHT;
                break;
            case 'P':
                chess->board[rank][file++] = PAWN;
                break;
            case 'k':
                chess->board[rank][file++] = king;
                break;
            case 'q':
                chess->board[rank][file++] = queen;
                break;
            case 'r':
                chess->board[rank][file++] = rook;
                break;
            case 'b':
                chess->board[rank][file++] = bishop;
                break;
            case 'n':
                chess->board[rank][file++] = knight;
                break;
            case 'p':
                chess->board[rank][file++] = pawn;
                break;
            case '/':
                rank--; // Skip to the next rank (row) in the chess matrix
                file = 0; // Reset the file (column) count to 0
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                {
                    int numEmptySquares = i - '0';
                    for (int j = 0; j < numEmptySquares; j++)
                    {
                        chess->board[rank][file++] = 0; // Assign empty square (0) to the corresponding square in the chess matrix
                    }
                }
                break;
            default:
                // Handle any other characters (error or unsupported characters)
                break;
        }
        
        i = *(++fencode);
    }
}


/*ArrayList* pawnMove(node* node,tuple* original)
{
	ArrayList* movsList = createList();
	
	//Move forward
	
	
	//Eat diagonally

	//an passant
	
	//promote
}*/

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


