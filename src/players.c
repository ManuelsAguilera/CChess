#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>


#include "TDAs/hashmap/hashmap.h"

#define SEP printf("\n**********************************\n")
struct player
{
	char * name;
	long wins;
};
typedef struct player player;

player * createPlayer(char * name)
{
	player * new = (player *) malloc(sizeof(player));
	assert(new);

	new->name = (char *) malloc(sizeof(strlen(name)));
	assert(new->name);
	strcpy(new->name, name);

	new->wins = 0;

	return new;
}

int createProfile(HashMap * playersMap, char * name)
{
	Pair * par = searchMap(playersMap, name);
	if (par)	return 1;

	player * new = createPlayer(name);
	insertMap(playersMap, new->name, new);
	
	return 0;
	
}

player * validatePlayer(HashMap * playersMap)
{
	char usuario[11];
	int opcion;
	while (1)
	{
		SEP;
		puts("Por favor ingrese su nombre de usuario...");
		printf(">");
	
		if (!scanf("%10[^\n]s", usuario)) return NULL;
		getchar();
	
		Pair * par = searchMap(playersMap, usuario);
		if (!par)
		{
			SEP;
			printf("El usuario no existe ¿Desea crear un usuari con el nombre %s? \nIngrese 1 = Si | 2 = No\n", usuario);
			printf(">");
			if (!scanf("%d", &opcion))	return NULL;
			getchar();

			if (opcion == 1)
			{
				player * newPlayer = createPlayer(usuario);
				insertMap(playersMap, newPlayer->name, newPlayer);
				return newPlayer;
			}
			else
				continue;
		}
		else
			return par->value;
	}
	
}

HashMap* readPlayers()
{
	HashMap* map = createMap(0);

	FILE *csv = fopen("csv/players_file.csv", "r");

	char buffer[1000];
	
	while (fgets(buffer, sizeof(buffer), csv))
	{
		char *valor = strtok(buffer, "\n");
		int columna = 1;

		char name[11];
		player * current;

		while (valor != NULL) {
    		if (columna == 1){	//se guarda el nombre del jugador
        		strcpy(name, valor);
			}

			current = createPlayer(name);
			valor = strtok(NULL, " ,");
    		columna++;
    	}
		insertMap(map, current->name, current);
	}
	fclose(csv);
	return map;
}


int showPlayer(HashMap * playersMap, char * name)
{
	Pair * par = searchMap(playersMap, name);

	if (!par)	return 1;
	
	player * perfil = par->value;
	SEP;
	printf("Nombre: %s\n", perfil->name);
	printf("Victorias: %ld\n", perfil->wins);
	
	return 0;
}

int showAllPlayers(HashMap * playersMap)
{
	Pair * par = firstMap(playersMap);
	if (!par)	return 1;

	while (par)
	{
		player * current = par->value;
		showPlayer(playersMap, current->name);

		par = nextMap(playersMap);
	}

	return 0;
}

int deletePlayer(HashMap * playersMap, char * name)
{
	Pair * par = searchMap(playersMap, name);

	if (!par)	return 1;
	
	eraseMap(playersMap, name);
	
	return 0;
}