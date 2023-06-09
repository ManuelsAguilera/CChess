#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "TDAs/arraylist/arraylist.h"
#include "TDAs/tuple/tuple.h"
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
	new->anpassant = malloc(sizeof(tuple));
	new->Wcastle = malloc(sizeof(tuple));
	new->Bcastle = malloc(sizeof(tuple));
	fenToBoard(new,);
	return new;
}


void fenToBoard(node* chess, const char* fencode)
{
    char i = *fencode;
    int rank = 7; // Start from the 8th rank (0-based indexing)

    while (i != '\0' && i != '\n')
    {
        switch (i)
        {
            case 'K':
                chess->board[rank][0] = 1; // Assign KING (1) to the corresponding square in the chess matrix
                break;
            case 'Q':
                chess->board[rank][0] = 2; // Assign QUEEN (2) to the corresponding square in the chess matrix
                break;
            case 'R':
                chess->board[rank][0] = 3; // Assign ROOK (3) to the corresponding square in the chess matrix
                break;
            case 'B':
                chess->board[rank][0] = 4; // Assign BISHOP (4) to the corresponding square in the chess matrix
                break;
            case 'N':
                chess->board[rank][0] = 5; // Assign KNIGHT (5) to the corresponding square in the chess matrix
                break;
            case 'P':
                chess->board[rank][0] = 6; // Assign PAWN (6) to the corresponding square in the chess matrix
                break;
            case 'k':
                chess->board[rank][0] = 10; // Assign king (10) to the corresponding square in the chess matrix
                break;
            case 'q':
                chess->board[rank][0] = 20; // Assign queen (20) to the corresponding square in the chess matrix
                break;
            case 'r':
                chess->board[rank][0] = 30; // Assign rook (30) to the corresponding square in the chess matrix
                break;
            case 'b':
                chess->board[rank][0] = 40; // Assign bishop (40) to the corresponding square in the chess matrix
                break;
            case 'n':
                chess->board[rank][0] = 50; // Assign knight (50) to the corresponding square in the chess matrix
                break;
            case 'p':
                chess->board[rank][0] = 60; // Assign pawn (60) to the corresponding square in the chess matrix
                break;
            case '/':
                rank--; // Skip to the next rank (row) in the chess matrix
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
                    int file = 0; // Start from the first file (column)
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


void boardToFen(node*);



//Will return list with new node, where the movements were already set.
ArrayList* pawnMove(node* node,tuple* original)
{
	ArrayList* movsList = createList();
	
	//Move forward
	
	
	//Eat diagonally

	//an passant
	
	//promote
}

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


void displayBoard(node* chess)
{
	for (int i = 0; i < 8; i ++)
		{
			for (int j = 0; j < 8; j++)
				printf("%d ",chess->board[i][j]);
			printf("\n");
		}
}

int main()// temporal, para probar que todo funcione bien.
{
	printf("Hello world!\n");
	return 0;
}