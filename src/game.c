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

int comprobarRey(tuple* mov_start, tuple* mov_end, int board[8][8]){
  printf("\nComprobando REY\n");
  int startRow = mov_start->y - '0';
  int startCol = mov_start->x - 'A';
  int endRow = mov_end->y - '0';
  int endCol = mov_end->x - 'A';
  int rowDiff = abs(endRow - startRow);
  int colDiff = abs(endCol - startCol);

  if(rowDiff <= 1 && colDiff <= 1){
    if(board[mov_start->y][mov_start->x]==1){
      if(board[mov_end->y][mov_end->x]>7 || board[mov_end->y][mov_end->x]==0)
        return 1;
    }  
    if(board[mov_start->y][mov_start->x]==10){
      if(board[mov_end->y][mov_end->x]<7 || board[mov_end->y][mov_end->x]==0)
        return 1;
    }
  }
  
  return 0;
}


int comprobarReina(tuple* mov_start, tuple* mov_end){
  printf("\nComprobando REINA\n");
	//if(comprobarTorre(mov_start,mov_end)==1 && comprobarAlfil(mov_start,mov_end)==1)
    //return 1;
  //return 0;
  return 1;
}


int comprobarTorre(tuple* mov_start,tuple* mov_end,int board[8][8])
{
	printf("ProbarTprre");
	tuple* vectorMov = createTuple(0,0);
	cpyTuple(vectorMov,mov_end);
	printf("\nv %d,%d",mov_end->x,mov_end->y);
	substractTuple(vectorMov,mov_start); //movement of piece
	//proving that a movement has form x(1,0) or x(0,1)
	if ( (vectorMov->x == 0 ^ vectorMov->y ==0) ) return 0;// xor
	
	//if vector has the form, then get wich form
	tuple* form = (vectorMov->x == 0)?createTuple(0,1): createTuple(1,0);
	//printf("\nf %d,%d\nv %d %d\n",form->x,form->y,vectorMov->x,vectorMov->y);
	//now just check it isnt jumping any pieces.
	if (vectorMov->x > 0 || vectorMov->y >0) //if is positive
		for (int i = 1; i < 7; i++)
			{
				scaleTuple(form,i);
				if ( cmpTuple(form,vectorMov)  ) //si no es el mov
					return 1;
				
				if (board[form->y][form->x]  != BLANK) 
					return 0;
	
			}
	else 
		for (int i = -1; i > 7; i--)
			{
				scaleTuple(form,i);
				if ( cmpTuple(form,vectorMov)  ) //si no es el mov
					return 1;
				
				if (board[form->y][form->x]  != BLANK) 
					return 0;
	
			}
	
	return 1;
}

int comprobarAlfil(tuple* mov_start,tuple* mov_end){
  printf("\nComprobando ALFIL\n");
  return 1;
}

int comprobarCaballo(tuple* mov_start, tuple* mov_end)
{
	printf("\nComprobando CABALLO\n");
	ArrayList* vectorMovs = createList();
	tuple * movs[2];
	movs[0] = createTuple(1,2); movs[1] = createTuple(2,1);
	linearCombination(movs, vectorMovs);
	
	tuple * copia = createTuple(mov_start->x, mov_start->y);
	substractTuple(copia, mov_end);

	for (int i = 0; i < get_size(vectorMovs); i++)
		{
			//cmp returns 0 or 1
			if (cmpTuple(copia,get(vectorMovs,i)) ) 
				return 1;
		}
	
	return 0;
}

int comprobarPeon(tuple* mov_start, tuple* mov_end){
  printf("\nComprobando PEÓN\n");
  return 1;
}

int comprobarMovimiento(tuple * mov_start, tuple * mov_end, int board[8][8])
{
 //if returns 0 then an error happened
	
	if (mov_start == NULL || mov_end ==NULL)
    	return 0;
	if (board[mov_start->y][mov_start->x] == BLANK)
		return 0;
	if (board[mov_start->y][mov_start->x] == KING || board[mov_start->x][mov_start->y] == king)
		return comprobarRey(mov_start, mov_end, board);
	if (board[mov_start->y][mov_start->x] == QUEEN || board[mov_start->x][mov_start->y] == queen)
		return comprobarReina(mov_start, mov_end);
	if (board[mov_start->y][mov_start->x] == ROOK || board[mov_start->x][mov_start->y] == rook)
		return comprobarTorre(mov_start, mov_end,board);
	if (board[mov_start->y][mov_start->x] == BISHOP || board[mov_start->x][mov_start->y] == bishop)
		return comprobarAlfil(mov_start, mov_end);
	if (board[mov_start->y][mov_start->x] == KNIGHT || board[mov_start->x][mov_start->y] == knight)
		return comprobarCaballo(mov_start, mov_end);
	if (board[mov_start->y][mov_start->x] == PAWN || board[mov_start->x][mov_start->y] == pawn)
		return comprobarPeon(mov_start, mov_end);
}

int twoPlayersGame()
{
	node* currentBoard = createNode();
	
	fenToBoard(currentBoard,"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	tuple* mov_end = NULL;
	tuple* mov_start = NULL;
	
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

    // para checkear qué hay en las posiciones seleccionadas
    printf("\ninicio %d\n",currentBoard->board[mov_start->y][mov_start->x]);
    printf("\nfinal %d\n",currentBoard->board[mov_end->y][mov_end->x]);

		while (comprobarMovimiento(mov_start, mov_end, currentBoard->board) != 1)
		{
			printf("\nEl movimiento ingresado no es válido, por favor ingresa uno que lo sea\n");
			printf("\nIngresa las coordenadas de la pieza que quieres mover:\n");
		  mov_start=readChessCoords();
      printf("\nIngresa que movimiento quieres hacer\n");
			mov_end=readChessCoords();
		}
    	
		currentBoard = changePos(currentBoard,mov_start,mov_end);
	}
	
	
	
	
	return 0;
}



