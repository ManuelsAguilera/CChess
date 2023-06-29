#ifndef GAME_h
#define	GAME_h

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


int twoPlayersGame();

node* changePos(node* tablero,tuple* original,tuple* mov);
void displayBoardW(node* chess);
void displayBoardB(node* chess);
void printTurno(node* chess);
tuple* readTuple();
tuple* readChessCoords();



#endif