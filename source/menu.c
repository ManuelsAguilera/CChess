#include <stdio.h>

#define SEP printf("\n**********************************\n")

char * validarUsuario(void)
{
	menuPrincipal(usuario);
}

void menuPrincipal(char * ususario)
{
	int opcion;
	puts("Bienvenid@ al menu principal, por favor, selecciona una de las siguientes opciones:");
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
				puts("to do");
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