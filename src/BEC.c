#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include "TDAs/arraylist/arraylist.h"
#include "TDAs/tuple/tuple.h"
#include <unistd.h>

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

//jaque and jaQUEMATE
#define CHECK 100
#define CHECKMATE 110



typedef char string[MAXCHAR];
typedef struct chessboard {
	int turn; //indicates wich player has to play
	int board[8][8];
} node;




node* createNode(int turn)
{
	node* new;
	new = malloc(sizeof(node));
	new->turn = turn;
  
	//new->anpassant = createTuple(0,0);
	//new->Wcastle = createTuple(0,0);
	//new->Bcastle = createTuple(0,0);
	
	return new;
}
tuple* findPiece(int board[8][8],int ID)
{
		for (int i=0; i < 7; i++)
			for (int j=0; j < 7; j++)
				if (board[i][j] == ID) 
					return createTuple(i,j);
	return NULL;
}


/** FUNCIONES PARA COMPROBAR **/

int comprobarRey(tuple* mov_start, tuple* mov_end, int board[8][8]){
  printf("\nComprobando REY\n");
  int startRow = mov_start->y ;
  int startCol = mov_start->x;
  int endRow = mov_end->y;
  int endCol = mov_end->x;
  int rowDiff = abs(endRow - startRow);
  int colDiff = abs(endCol - startCol);

  if(rowDiff <= 1 && colDiff <= 1){
    if(board[startRow][startCol]==1){
      if(board[endRow][endCol]>7 || board[endRow][endCol]==0)
        return 1;
    }  
    if(board[startRow][startCol]==10){
      if(board[endRow][endCol]<7 || board[endRow][endCol]==0)
        return 1;
    }
  }
  return 0;
}

int comprobarReina(tuple* mov_start, tuple* mov_end, int board[8][8]){
  int rowDiff = abs(mov_end->y - mov_start->y);
  int colDiff = abs(mov_end->x - mov_start->x);

  if(rowDiff==colDiff) return comprobarAlfil(mov_start,mov_end,board);
  if(rowDiff>0 && colDiff==0) return comprobarTorre(mov_start,mov_end,board);
  if(rowDiff==0 && colDiff>0) return comprobarTorre(mov_start,mov_end,board);
  return 0;
}

int comprobarTorre(tuple* mov_start,tuple* mov_end,int board[8][8]){
  int startRow = mov_start->y ;
  int startCol = mov_start->x;
  int endRow = mov_end->y;
  int endCol = mov_end->x;
  int rowDiff = abs(endRow - startRow);
  int colDiff = abs(endCol - startCol);
  
  if(rowDiff>0 && colDiff==0){
    if(board[startRow][startCol]==3 || board[startRow][startCol]==2){
      if(board[endRow][endCol]>7 || board[endRow][endCol]==0){
        if(rowDiff>1){
          if(startRow<endRow){
            for(int i=1;i<rowDiff;i++){
              if(board[startRow+i][startCol]!=0){
                return 0;
              }
            }
          }
          if(startRow>endRow){
            for(int i=1;i<colDiff;i++){
              if(board[startRow-i][startCol]!=0){
                return 0;
              }
            }
          }
        }
        return 1;
      }
    }
    if(board[startRow][startCol]==30 || board[startRow][startCol]==20){
      if(board[endRow][endCol]>7 || board[endRow][endCol]==0){
        if(rowDiff>1){
          if(startRow<endRow){
            for(int i=1;i<rowDiff;i++){
              if(board[startRow+i][startCol]!=0){
                return 0;
              }
            }
          }
          if(startRow>endRow){
            for(int i=1;i<colDiff;i++){
              if(board[startRow-i][startCol]!=0){
                return 0;
              }
            }
          }
        }
        return 1;
      }
    }
  }
  if(rowDiff==0 && colDiff>0){
    if(board[startRow][startCol]==3 || board[startRow][startCol]==2){
      if(board[endRow][endCol]>7 || board[endRow][endCol]==0){
        if(rowDiff>1){
          if(startRow<endRow){
            for(int i=1;i<rowDiff;i++){
              if(board[startRow][startCol+i]!=0){
                return 0;
              }
            }
          }
          if(startRow>endRow){
            for(int i=1;i<colDiff;i++){
              if(board[startRow][startCol-i]!=0){
                return 0;
              }
            }
          }
        }
        return 1;
      }
    }
    if(board[startRow][startCol]==30 || board[startRow][startCol]==20){
      if(board[endRow][endCol]>7 || board[endRow][endCol]==0){
        if(rowDiff>1){
          if(startRow<endRow){
            for(int i=1;i<rowDiff;i++){
              if(board[startRow][startCol+i]!=0){
                return 0;
              }
            }
          }
          if(startRow>endRow){
            for(int i=1;i<colDiff;i++){
              if(board[startRow][startCol-i]!=0){
                return 0;
              }
            }
          }
        }
        return 1;
      }
    }
  }
  return 0;
}

int comprobarAlfil(tuple* mov_start, tuple* mov_end, int board[8][8]){
  int startRow = mov_start->y;
  int startCol = mov_start->x;
  int endRow = mov_end->y;
  int endCol = mov_end->x;
  int rowDiff = abs(endRow - startRow);
  int colDiff = abs(endCol - startCol);

  if(rowDiff == colDiff){
    if(board[startRow][startCol]==4 || board[startRow][startCol]==2){
      if(board[endRow][endCol]>7 || board[endRow][endCol]==0){
        if(rowDiff>1){
          if(startCol<endCol){
            if(startRow<endRow){
              for(int i=1;i<colDiff;i++){
                if(board[startRow+i][startCol+i]!=0){
                  return 0;
                }
              }
            }
            if(startRow>endRow){
              for(int i=1;i<colDiff;i++){
                if(board[startRow-i][startCol+i]!=0){
                  return 0;
                }
              }
            }
          }
          if(startCol>endCol){
            if(startRow<endRow){
              for(int i=1;i<colDiff;i++){
                if(board[startRow+i][startCol-i]!=0){
                  return 0;
                }
              }
            }
            if(startRow>endRow){
              for(int i=1;i<colDiff;i++){
                if(board[startRow-i][startCol-i]!=0){
                  return 0;
                }
              }
            }
          }
        }
        return 1;
      }
    }
    if(board[startRow][startCol]==40 || board[startRow][startCol]==20){
      if(board[endRow][endCol]<7 || board[endRow][endCol]==0){
        if(rowDiff>1){
          if(startCol<endCol){
            if(startRow<endRow){
              for(int i=1;i<colDiff;i++){
                if(board[startRow+i][startCol+i]!=0){
                  return 0;
                }
              }
            }
            if(startRow>endRow){
              for(int i=1;i<colDiff;i++){
                if(board[startRow-i][startCol+i]!=0){
                  return 0;
                }
              }
            }
          }
          if(startCol>endCol){
            if(startRow<endRow){
              for(int i=1;i<colDiff;i++){
                if(board[startRow+i][startCol-i]!=0){
                  return 0;
                }
              }
            }
            if(startRow>endRow){
              for(int i=1;i<colDiff;i++){
                if(board[startRow-i][startCol-i]!=0){
                  return 0;
                }
              }
            }
          }
        }
        return 1;
      }
    }
  }
  return 0;
}

int comprobarCaballo(tuple* mov_start, tuple* mov_end, int board[8][8]){
  printf("\naa\n");
  int startRow = mov_start->y;
  int startCol = mov_start->x;
  int endRow = mov_end->y;
  int endCol = mov_end->x;
  int rowDiff = abs(endRow - startRow);
  int colDiff = abs(endCol - startCol);

  printf("\n%d row\n",rowDiff);
  printf("%d col\n",colDiff);
  
  if(rowDiff==2 && colDiff==1){
    if(board[startRow][startCol]==5){
      if(board[endRow][endCol]>7 || board[endRow][endCol]==0){
        return 1;
      }
    }
    if(board[startRow][startCol]==50){
      if(board[endRow][endCol]<7 || board[endRow][endCol]==0){
        return 1;
      }
    }
  }
  if(rowDiff==1 && colDiff==2){
    if(board[startRow][startCol]==5){
      if(board[endRow][endCol]>7 || board[endRow][endCol]==0){
        return 1;
      }
    }
    if(board[startRow][startCol]==50){
      if(board[endRow][endCol]<7 || board[endRow][endCol]==0){
        return 1;
      }
    }
  }
  
  return 0;
}

/*
//(2,1) (2,-1) (-2,1) (-2,-1) (1,2) (1,-2) (-1,2) (-1,-2)
int comprobarCaballo(tuple* mov_start, tuple* mov_end, int board[8][8])
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
}*/

int comprobarPeon(tuple* mov_start, tuple* mov_end, int board[8][8]){
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
	if (board[mov_start->y][mov_start->x] == KING || board[mov_start->y][mov_start->x] == king)
		return comprobarRey(mov_start, mov_end, board);
	if (board[mov_start->y][mov_start->x] == QUEEN || board[mov_start->y][mov_start->x] == queen)
		return comprobarReina(mov_start, mov_end, board);
	if (board[mov_start->y][mov_start->x] == ROOK || board[mov_start->y][mov_start->x] == rook)
		return comprobarTorre(mov_start, mov_end, board);
	if (board[mov_start->y][mov_start->x] == BISHOP || board[mov_start->y][mov_start->x] == bishop)
		return comprobarAlfil(mov_start, mov_end, board);
	if (board[mov_start->y][mov_start->x] == KNIGHT || board[mov_start->y][mov_start->x] == knight)
		return comprobarCaballo(mov_start, mov_end, board);
	if (board[mov_start->y][mov_start->x] == PAWN || board[mov_start->y][mov_start->x] == pawn)
		return comprobarPeon(mov_start, mov_end, board);
}


/** Generar movimientos para el grafo **/


void fenToBoard(node* chess, const char* fencode)
{
  char i = *fencode;
  int rank = 7; // Start from the 8th rank (0-based indexing)
  int file = 0; // Start from the first file (column)
  int numEmptySquares;
  
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
        numEmptySquares = i - '0';
        for (int j = 0; j < numEmptySquares; j++)
          chess->board[rank][file++] = 0;
        break;
      case '2':
        numEmptySquares = i - '0';
        for (int j = 0; j < numEmptySquares; j++)
          chess->board[rank][file++] = 0;
        break;
      case '3':
        numEmptySquares = i - '0';
        for (int j = 0; j < numEmptySquares; j++)
          chess->board[rank][file++] = 0;
        break;
      case '4':
        numEmptySquares = i - '0';
        for (int j = 0; j < numEmptySquares; j++)
          chess->board[rank][file++] = 0;
        break;
      case '5':
        numEmptySquares = i - '0';
        for (int j = 0; j < numEmptySquares; j++)
          chess->board[rank][file++] = 0;
        break;
      case '6':
        numEmptySquares = i - '0';
        for (int j = 0; j < numEmptySquares; j++)
          chess->board[rank][file++] = 0;
        break;
      case '7':
        numEmptySquares = i - '0';
        for (int j = 0; j < numEmptySquares; j++)
          chess->board[rank][file++] = 0;
        break;
      case '8':
        numEmptySquares = i - '0';
        for (int j = 0; j < numEmptySquares; j++)
          chess->board[rank][file++] = 0;
        break;
      default:
        // Handle any other characters (error or unsupported characters)
        break;
    }
    i = *(++fencode);
  }
}

/*

void kingMove(node* chess, tuple* piece, ArrayList* storage)
{
    tuple* vectors[2];
    vectors[0] = createTuple(1, 0);
    vectors[1] = createTuple(0, 1);

    linearCombination(vectors, storage);
    // Now we have all directions

    // Add a tuple copy that adds to the initial position of the piece to check
    tuple* initialPos = createTuple(piece->x, piece->y);

    for (int i = 1; i < 5; i++) {
        tuple* newPos = sumTuple(initialPos, get(storage, i * -1));
        if (comprobarMovimiento(initialPos,newPos,chess->board) == 0)
            pop(storage, i * -1);

        // Clean up the memory
        nullifyTuple(newPos);
    }

    // Clean up the memory
    nullifyTuple(initialPos);
}

 */


/*
void kingMove(node* chess, tuple* piece,ArrayList* storage)
{
	tuple* vectors[2];
	vectors[0] = createTuple(1,0);
	vectors[0] = createTuple(0,1);

	linearCombination(vectors,storage);
	//Now we got all directions 
	
	/* Agregar un tuple cpy que se sume a la pos inicial de la pieza, para comprobar
	for (int i=1; i <5; i++)
		if (comprobarMovimiento(chess->board, get(storage,i*-1)) == 0)
			pop(storage,i*-1);
}	*/






ArrayList* rookMove(node*,tuple);
ArrayList* queenMove(node*,tuple);
ArrayList* knightMove(node*,tuple);

int findJaqueMate(node* chess, tuple* piece) //checks if a piece is checkmating or cheking
{
	if (chess->board[piece->y][piece->x] == BLANK)  return 0;

	tuple* rivalKing = (chess->turn == WHITE_P)? findPiece(chess->board,king):findPiece(chess->board,KING);

	//now we check if the move is valid, if so, then we have check

	if (comprobarMovimiento(piece,rivalKing,chess->board))
	{
		//revisar si el rey tiene movs
		ArrayList* movs = createList();
		//kingMove(chess,rivalKing,movs);
		if (get_size(movs) == 0) 
			return CHECKMATE;
		return CHECK;
	}
	return 0;
}


//will return a list of best posible moves.
ArrayList* get_adj_node(node*);

int getPieceScore(node*);
//score for how many pieces does a player have
int getDeepSearchScore(node*); 
//score for knowing how good posibilites does it has posible movements


