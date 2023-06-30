#include "game.h"
#include "BEC.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include "players.h"
#include "TDAs/arraylist/arraylist.h"
#include "TDAs/tuple/tuple.h"
#include <unistd.h>


node* changePos(node* tablero,tuple* original,tuple* mov)
{
	if (original == NULL || mov == NULL) return NULL;
	int piece = tablero->board[original->y][original->x];
	tablero->board[original->y][original->x] = BLANK;
	tablero->board[mov->y][mov->x] = piece;

	tablero->turn *= -1; //Esto cambia el turno
	return tablero;
	
}

void displayBoardW(node* chess)
{
	const char index_str[8] = "ABCDEFGH";
	const char index_num[8] = "12345678";
	for (int i = 7; i >= 0; i--)
		{
			printf("%c",index_num[i]);
			for (int j = 0; j < 8; j++)
				{
					if ((i+j)%2)
						printf(ANSI_COLOR_GREEN);
					else
						printf(ANSI_COLOR_YELLOW);
					printf("%3d",chess->board[i][j]);
				}
			printf("\n");
			printf(ANSI_COLOR_RESET);
		}
	printf(" ");
	for (int i = 0; i < 8; i++)
		printf("%3c",index_str[i]);
	printf("\n");
}

void displayBoardB(node* chess)
{
	const char index_str[8] = "ABCDEFGH";
	const char index_num[8] = "12345678";
	
	for (int i = 0; i < 8; i++)
		{
			printf("%c",index_num[i]);
			for (int j = 0; j < 8; j++)
				{
					if ((i+j)%2)
						printf(ANSI_COLOR_GREEN);
					else
						printf(ANSI_COLOR_YELLOW);
					printf("%3d",chess->board[i][j]);
				}
			printf("\n");
			printf(ANSI_COLOR_RESET);
		}
	printf(" ");
	for (int i = 0; i < 8; i++)
		printf("%3c",index_str[i]);
	printf("\n");
}

void printTurno(node* chess)
{
	if (chess->turn == WHITE_P)
		displayBoardW(chess);
	else if (chess->turn == BLACK_P)
		displayBoardB(chess);
	else 
		assert("ERROR IN FUNCTION printTurno(node*)\nTurn is neither white or black\n");
}

tuple* readTuple()
{
	int x;
	int y;
	if ( scanf("%d",&x) ) assert("ERROR couldn't read values tuple");
	if ( scanf("%d",&y) ) assert("ERROR couldn't read values tuple");
	tuple* ptr_tuple= createTuple(x,y);
	return ptr_tuple;
}

tuple* readChessCoords()
{
	char chessCoord[2];
  printf("> ");
	scanf("%s",chessCoord);
	getchar();
  
	const char* index_str = "ABCDEFGH";
	int x=-1; //just to initialize
	int y;

	for(int i=0; i<8; i++)
		if (index_str[i] == chessCoord[0] )
			x = i;

	
	if (x==-1) return NULL;
	if (isalnum(chessCoord[1])==0) return NULL;
	y = (int)atoi(&chessCoord[1]);

	if (y >8 || y<1) return NULL;


	return createTuple(x,y-1);
	
}



int twoPlayersGame()
{
	
	node* currentBoard = createNode(WHITE_P);
	fenToBoard(currentBoard,"rnbqkbnr/pppp1ppp/8/4p2Q/2B1P3/8/PPPP1PPP/RNB1K1NR");
	//fenToBoard(currentBoard,"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	tuple* mov_end = NULL;
	tuple* mov_start = NULL;
	int checkmate;
	while(1)
	{
		//system("clear");
		printf("----------------------\n");
		printf(" AJEDREZ MULTIJUGADOR\n");
		printf("----------------------\n");
		printTurno(currentBoard);
    
		printf("\nIngresa las coordenadas de la pieza que quieres mover:\n");
		mov_start=readChessCoords();

		printf("\nIngresa qué movimiento quieres hacer:\n");
		mov_end=readChessCoords();

 		if (cmpTuple(mov_start,mov_end)) return 1;

		while (comprobarMovimiento(mov_start, mov_end, currentBoard->board) != 1)
		{
			printf("\nEl movimiento ingresado no es válido, por favor ingresa uno que lo sea\n");
			printf("\nIngresa las coordenadas de la pieza que quieres mover:\n");
		  mov_start=readChessCoords();
      printf("\nIngresa que movimiento quieres hacer\n");
			mov_end=readChessCoords();
		}
    	checkmate = findJaqueMate(currentBoard,mov_end);
		if (checkmate == CHECKMATE)
		{
			if (currentBoard->turn == WHITE_P)
				return 1;
			else
				return 0;
		}
		
		currentBoard = changePos(currentBoard,mov_start,mov_end);
		
		
		
	}
	
	
	
	
	return 0;
}



