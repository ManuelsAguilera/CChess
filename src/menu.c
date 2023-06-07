#include <stdio.h>
#include <stdlib.h>
#include "players.h"

#define SEP printf("\n**********************************\n")

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
		puts("0) Salir");
		
		printf(">");
		if (!scanf("%d", &opcion))	continue;
		getchar();
		
		switch	(opcion) 
		{
			case 1:
				puts("to do");
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
				puts("Hasta la próxima...");
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

	
	int opcion;

	SEP;
	printf("Bienvenid@ al menu principal, por favor, selecciona una de las siguientes opciones:");
	SEP;
	
	while (1)
	{
		puts("1) Menu de juego");
		puts("2) Menu de jugadores");
		puts("0) Salir");
		
		printf(">");
		if (!scanf("%d", &opcion))	continue;
		getchar();
		
		switch	(opcion) 
		{
			case 1:
				puts("to do");
				break;
			case 2:
				menuJugadores(playersMap);
				break;
			case 0:
				puts("Hasta la próxima...");
				return;
			default:
				puts("Opción inválida");
				SEP;
				break;
		}
	}
	
	
}