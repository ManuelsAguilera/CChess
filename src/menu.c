#include <stdio.h>
#include <stdlib.h>
#include "players.h"
#include "game.h"
#include <ncurses.h>

#define SEP printf("\n**********************************\n\n")

// Función estética

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

// Funciones menú

void menuJugadores(HashMap * playersMap)
{
	int opcion;
	char name[11];

	puts("Menú de jugadores");
	
	while (1)
	{
		SEP;
		puts("1) Top 10 Winners");
		puts("2) Mostrar perfil de un jugador");
		puts("3) Mostrar todos los jugadores registrados");
		puts("4) Crear perfil");
		puts("5) Eliminar un jugador del sistema");
		puts("0) Volver al menú principal");
		
		printf("> ");
		if (!scanf("%d", &opcion))	continue;
		getchar();
		
		switch(opcion) 
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
				puts("\nIngrese el nombre");
				printf("> ");

				if (!scanf("%10[^\n]s",name)) break;
				getchar();
				
				if (showPlayer(playersMap,name) != 0)
				{
					puts("\nEl nombre de jugador ingresado no se encuentra en el sistema");
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
				puts("\nIngrese el nombre");
				printf("> ");

				if (!scanf("%10[^\n]s", name))	break;
				getchar();
				
				if (createProfile(playersMap, name) != 0)
				{
					puts("\nEl jugador ya se encuentra en el sistema");
					break;
				}
				puts("\nPerfil creado correctamente");
				break;
			case 5:
				puts("\nIngrese el nombre");
				printf("> ");

				if (!scanf("%10[^\n]s", name))	break;
				getchar();
				
				if (deletePlayer(playersMap, name) != 0)
					puts("\nEl nombre ingresado no se encuentra en el sistema");
        
				break;
			case 0:
        SEP;
				return;
			default:
				puts("\nOpción inválida");
				break;
		}
	}
}

char* ingresarPlayer(HashMap* playersMap) {
    char response;
    char* name = (char*)malloc(sizeof(char) * 50); // Reserva memoria para el nombre
    
    while (1) {
        system("clear");
        printf("¿Quieres jugar con un usuario anterior o hacer uno nuevo? (y/n)\n");
        scanf(" %c", &response); // Corregido para leer un solo carácter
        
        if (response == 'y') {
            printf("Ingresa tu nombre: ");
            scanf("%s", name);
            
            Pair* current = searchMap(playersMap, name);
            if (current != NULL)
                return (char*)current->key;
        } else if (response == 'n') {
            printf("Deberás crear un nuevo usuario. Ingresa tu nombre:\n");
            scanf("%s", name);

            createProfile(playersMap, name);
            return name;
        }
    }
}

void menuJuego(HashMap * playersMap)
{
	int opcion;
	system("clear");
	writeLogo();
	SEP;
	puts("Menú de juego");
  SEP;
  
	while (1)
	{
		puts("1) Modo 2 jugadores");
		puts("2) Jugar contra BEC");
		puts("0) Volver al menú principal");

		printf("> ");
		if (!scanf("%d", &opcion))	continue;
		getchar();

		switch (opcion)
		{
			case 1:
        system("clear");
				char* Jugador = ingresarPlayer(playersMap);
				addWin(playersMap,Jugador,twoPlayersGame());
				
				showPlayer(playersMap,Jugador);
				break;
			case 2:
				puts("\nto do");
        SEP;
				break;
			case 0:
        SEP;
				return;
			default:
				puts("\nOpción inválida");
				SEP;
				break;
		}
	}
}

void menuPrincipal(HashMap * playersMap)
{
	char opcion = '\0';
	//system("clear");
	writeLogo();
	
	printf("\nSelecciona una de las siguientes opciones:\n\n");

	while(1)
  {
    puts("1) Menú de juego");
		puts("2) Menú de jugadores");
		puts("0) Salir");
		
    printf("> ");
    opcion = getchar();
		getchar();
    
		if(!opcion) continue;
		
		switch(opcion) 
		{
			case '1':
				SEP;
        menuJuego(playersMap);
				break;
			case '2':
        SEP;
				menuJugadores(playersMap);
				break;
			case '0':
        puts("\nHasta la próxima...\n");
				return;
			default:
				puts("\nOpción inválida");
				SEP;
				break;
		}
	}
	
	
}