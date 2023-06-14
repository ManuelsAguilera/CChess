#include <stdio.h>
#include <stdlib.h>
#include "players.h"
#include "game.h"
#include <ncurses.h>
//#include <ncurses.h>

#define SEP printf("\n**********************************\n")


//funcion estetica

void writeLogo()
{
	const char *logo[10] = {
    "   ______ __  __ ______ _____ _____                             ",
    "  / ____// / / // ____// ___// ___/                             ",
    " / /    / /_/ // __/   \\__ \\ \\__ \\                              ",
    "/ /___ / __  // /___  ___/ /___/ /                              ",
    "\\____//_/ /_//_____/ /____//____/                               ",
    "                  _  __   __                  _           ______",
    " _      __ _____ (_)/ /_ / /_ ___   ____     (_)____     / ____/",
    "| | /| / // ___// // __// __// _ \\ / __ \\   / // __ \\   / /     ",
    "| |/ |/ // /   / // /_ / /_ /  __// / / /  / // / / /  / /___   ",
    "|__/|__//_/   /_/ \\__/ \\__/ \\___//_/ /_/  /_//_/ /_/   \\____/   "
	};

	for (int i = 0; i < 10; i++)
		printf("%s\n",logo[i]);

	
}



//FUNCIONES DE MENU




void menuJugadores(HashMap * playersMap)
{
	int opcion;
	char name[11];
	SEP;
	
	puts("Menu de jugadores");
	
	while (1)
	{
		SEP;
		puts("1) Top 10 winners");
		puts("2) Mostrar perfil de un jugador");
		puts("3) Mostrar todos los jugadores registrados");
		puts("4) Crear perfil");
		puts("5) Eliminar un jugador del sistema");
		puts("0) Volver al menú principal");
		
		printf(">");
		if (!scanf("%d", &opcion))	continue;
		getchar();
		
		switch	(opcion) 
		{
			case 1:
				SEP;
				puts("Top 10 winners:");

				if (showTopWinners(playersMap) != 0)
				{
					SEP;
					puts("Hubo un problema...");
				}
				break;
			case 2:
				puts("Ingrese el nombre");
				printf(">");

				if (!scanf("%10[^\n]s", name))	break;
				getchar();
				
				if (showPlayer(playersMap, name) != 0)
				{
					SEP;
					puts("El nombre de jugador ingresado no se encuentra en el sistema");
				}
				break;
			case 3:
				if (showAllPlayers(playersMap) != 0)
				{
					SEP;
					puts("No hay jugadores registrados en el sistema");
				}
				break;
			case 4:
				puts("Ingrese el nombre");
				printf(">");

				if (!scanf("%10[^\n]s", name))	break;
				getchar();
				
				if (createProfile(playersMap, name) != 0)
				{
					SEP;
					puts("El jugador ya se encuentra en el sistema");
					break;
				}
				SEP;
				puts("Perfil creado correctamente");
				break;
			case 5:
				puts("Ingrese el nombre");
				printf(">");

				if (!scanf("%10[^\n]s", name))	break;
				getchar();
				
				if (deletePlayer(playersMap, name) != 0)
				{
					SEP;
					puts("El nombre ingresado no se encuentra en el sistema");
				}
				break;
			case 0:
				return;
			default:
				puts("Opción inválida");
				SEP;
				break;
		}
	}
}

void menuJuego(HashMap * playersMap)
{
	
	int opcion;
	system("clear");
	writeLogo();
	SEP;
	puts("Menu de juego, por favor selecciona una de las siguientes opciones:");

	while (1)
	{
		SEP;
		puts("1) Modo 2 jugadores");
		puts("2) Jugar contra BEC");
		puts("0) Volver al menu principal");

		printf(">");
		if (!scanf("%d", &opcion))	continue;
		getchar();

		switch (opcion)
		{
			case 1:
				twoPlayersGame();
				break;

			case 2:
				puts("to do");
				break;

			case 0:
				return;
			default:
				puts("Opción inválida");
				SEP;
				break;
		}
	}
}

void menuPrincipal(HashMap * playersMap)
{

	
	char opcion = '\0';
	system("clear");
	writeLogo();
	
	printf("\nSelecciona una de las siguientes opciones:\n");

	
	while (1)
	{
		puts("1) Menu de juego");
		puts("2) Menu de jugadores");
		puts("0) Salir");
		
		printf(">%c",opcion);
		opcion = getchar();
		
		if (!opcion )	continue;
		
		
		switch	(opcion) 
		{
			case '1':
				menuJuego(playersMap);
				break;
			case '2':
				menuJugadores(playersMap);
				break;
			case '0':
				puts("Hasta la próxima...");
				return;
			default:
				puts("Opción inválida");
				SEP;
				break;
		}
	}
	
	
}