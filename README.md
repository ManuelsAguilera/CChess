# CChess o Chess.c

## Proyecto final Estructura de datos

---

## Integrantes:

- Eliseo Guarda
- Felipe Villaroel
- Manuel Aguilera

---
# Importante
El codigo fue desarrollado y probado en ubuntu linux. Probar ejecutarlo en replit o en una maquina virtual, puesto que puede que de errores.
![Icono ubuntu](https://cdn-icons-png.flaticon.com/512/5969/5969282.png)

# Que esta hecho
- MODO 2V2
- Almacenar jugadores
- Mostrar mejores jugadores
- Cargar los jugadores al principio del programa
# Que no esta hecho
- Modo Bec
- El grafo
- Detectar Jaque Mate
- Guardar datos al final del programa
- Arreglar bugs sobre la lectura
  

## Una disculpa
Lamentamos no poder realizar todo lo que quisimos en el programa, al principio logramos organizarmos bien, y avanzar bastante. Pero al final en las ultimas semanas costo mucho poder organizar a todos. Y eso terminaria estancando bastante el proyecto.

Este era un proyecto que personalmente para mi, Manuel, tenia muchas ganas  de lograr. Y me es bastante dificil aceptar que no lo logre.

# Descripcion del proyecto:

Consistira en un juego de ajedrez, con modalidad de un jugador (contra la cpu local), y de dos jugadores. Ademas guardara el registro de jugadores junto a sus victorias. Se podra revisar una pantalla de highscore, la cual mostrara a los jugadores con mayores victorias contra la cpu.

## Diseño

### Registro de jugadores:

El registro de jugadores es simple, consiste en un mapa ordenado que guarda a todos los jugadores y sus datos. Este puede ser accedido para revisar a cada jugador, revisar los jugadores con mayor puntaje, y mostrar despues de finalizar una partida.

El mapa estara implementado con un arbol binario, en el que gracias al orden podremos recorrer rapidamente.

### Jugador artificial:

Para poder generar un bot que genere movimientos, capaces de rivalizar contra el jugador. Usaremos un grafo implicito, en donde cada nodo es un tablero distinto. Y los cercanos a este son todos los tableros que provienen de un movimiento valido del anterior.

Ahora, cada tablero tiene un sistema de puntuacion. Este depende de cual es el jugador que analicemos. Luego veremos la puntuacion, en base a la cantidad de piezas de valor vulnerables, la suma de puntuacion de cada pieza.

De esta manera tendremos un metodo de calcular los movimientos optimos, al desarrollar la busqueda en profundidad junto a este sistema de puntuaciones. De forma que podemos elegir si analizar dos niveles de nodos, o mas, y elegir el nodo que tenga mayores finales de buena puntuacion.

### Desafios:

- Es importante generar un modo eficiente de calcular cada movimiento de todas las piezas validas, ya que esto es lo que escencialmente realentizara el proceso de busqueda en profundidad.
- Debemos generar una forma eficiente de calcular el puntaje de cada tablero.
- Poder transimitir la informacion de la partida, con una interfaz clara, o usando notacion de ajedrez clara.



