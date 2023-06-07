#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TDAs/hashmap/hashmap.h"
#include "menu.h"
#include "players.h"


int main(int argc, char* argv[])
{
	HashMap * playersMap = createMap(10);
  
	menuPrincipal(playersMap);

	return 0;
}