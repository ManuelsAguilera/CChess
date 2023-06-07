#ifndef players_h
#define players_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "TDAs/hashmap/hashmap.h"

typedef struct HashMap HashMap;

struct player
{
	char * name;
};

typedef struct player player;

HashMap * readPlayers();
player * createPlayer(char * name);
player * validatePlayer(HashMap * playersMap);

int showPlayer(HashMap * playersMap, char * name);
int showAllPlayers(HashMap * playersMap);
int deletePlayer(HashMap * playersMap, char * name);
int createProfile(HashMap * playersMap, char * name);
int showTopWinners(HashMap * playersMap);


#endif /* players_h */