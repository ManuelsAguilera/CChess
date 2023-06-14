#include "game.h"
#include "BEC.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
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
	if ( scanf("%d",&x) ) assert("ERROR couldnt read values tuple");
	if ( scanf("%d",&y) ) assert("ERROR couldnt read values tuple");
	tuple* ptr_tuple= createTuple(x,y);
	return ptr_tuple;
}

tuple* readChessCoords()
{
	char chessCoord[2];
	scanf("%s",chessCoord);
	getchar();
	const char* index_str = "ABCDEFGH";
	int x=-1;
	int y;

	
	for(int i = 0; i< 8; i++)
		if (index_str[i]==chessCoord[0])
			x = i;
	
	if (x==-1) assert("Coordenada mal introducida");
	if (isalnum(chessCoord[1])) assert("Coordenada mal introducida");
	y = (int)atoi(&chessCoord[1]);

	if (y >8 || y<1) assert("Coordenada mal introducida");

	return createTuple(x,y-1);
	
}

int comprobarTorre(tuple * mov_start, tuple * mov_end)
{
	tuple * mov1 = createTuple(1, 0);
	tuple * mov2 = createTuple(0, 1);
	tuple * mov3 = createTuple(-1, 0);
	tuple * mov4 = createTuple(0, -1);
	
	tuple * copia = createTuple(mov_start->x, mov_start->y);

	substractTuple(copia, mov_end);

	if (cmpTuple(copia, mov1) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		return 1;
	}

	if (cmpTuple(copia, mov2) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		return 1;
	}

	if (cmpTuple(copia, mov3) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		return 1;
	}

	if (cmpTuple(copia, mov4) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		return 1;
	}
	
	return 0;
}

int comprobarCaballo(tuple * mov_start, tuple * mov_end)
{
	tuple * mov1 = createTuple(2, 1);
	tuple * mov2 = createTuple(2, -1);
	tuple * mov3 = createTuple(-2, 1);
	tuple * mov4 = createTuple(-2, -1);
	tuple * mov5 = createTuple(1, 2);
	tuple * mov6 = createTuple(1, -2);
	tuple * mov7 = createTuple(-1, 2);
	tuple * mov8 = createTuple(-1, -2);
	
	tuple * copia = createTuple(mov_start->x, mov_start->y);

	substractTuple(copia, mov_end);

	if (cmpTuple(copia, mov1) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov2) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov3) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov4) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov5) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov6) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov7) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov8) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	return 0;
}

int comprobarRey(tuple * mov_start, tuple * mov_end)
{
	tuple * mov1 = createTuple(1, 0);
	tuple * mov2 = createTuple(0, 1);
	tuple * mov3 = createTuple(-1, 0);
	tuple * mov4 = createTuple(0, -1);
	tuple * mov5 = createTuple(1, 1);
	tuple * mov6 = createTuple(1, -1);
	tuple * mov7 = createTuple(-1, 1);
	tuple * mov8 = createTuple(-1, -1);
	
	tuple * copia = createTuple(mov_start->x, mov_start->y);

	substractTuple(copia, mov_end);

	if (cmpTuple(copia, mov1) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov2) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov3) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov4) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov5) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov6) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov7) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	if (cmpTuple(copia, mov8) == 1)
	{
		free(copia);
		free(mov1);
		free(mov2);
		free(mov3);
		free(mov4);
		free(mov5);
		free(mov6);
		free(mov7);
		free(mov8);
		return 1;
	}

	return 0;
}

int comprobarMovimiento(tuple * mov_start, tuple * mov_end, int board[8][8])
{
	if (board[mov_start->x][mov_start->y] == 1 || board[mov_start->x][mov_start->y] == 10)
		return comprobarRey(mov_start, mov_end);
	if (board[mov_start->x][mov_start->y] == 2 || board[mov_start->x][mov_start->y] == 20)
		return 1;
	if (board[mov_start->x][mov_start->y] == 3 || board[mov_start->x][mov_start->y] == 30)
		return comprobarTorre(mov_start, mov_end);
	if (board[mov_start->x][mov_start->y] == 4 || board[mov_start->x][mov_start->y] == 40)
		return 1;
	if (board[mov_start->x][mov_start->y] == 5 || board[mov_start->x][mov_start->y] == 50)
		return comprobarCaballo(mov_start, mov_end);
	if (board[mov_start->x][mov_start->y] == 6 || board[mov_start->x][mov_start->y] == 60)
		return 1;
}

int twoPlayersGame()
{
	node* currentBoard = createNode();
	
	fenToBoard(currentBoard,"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	tuple* mov_end = NULL;
	tuple* mov_start = NULL;
	
	while(1)
	{
		system("clear");
		printf("----------------------\n");
		printf(" AJEDREZ MULTIJUGADOR\n");
		printf("----------------------\n");
		printTurno(currentBoard);

		printf("\nIngresa las coordenadas de la pieza que quieres mover\n");
		mov_start=readChessCoords();
		printf("\nIngresa que movimiento quieres hacer\n");
		mov_end=readChessCoords();

		while (comprobarMovimiento(mov_start, mov_end, currentBoard->board) != 1)
		{
			printf("\nEl movimiento ingresado no es válido, por favor ingresa uno que lo sea\n");

			printf("\nIngresa que movimiento quieres hacer\n");
			mov_end=readChessCoords();
		}

		currentBoard = changePos(currentBoard,mov_start,mov_end);
	}
	
	
	
	
	return 0;
}



