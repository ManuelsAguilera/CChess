#!bin/bash

gcc src/menu.c src/players.c src/game.c src/BEC.c src/main.c src/TDAs/hashmap/hashmap.c src/TDAs/max_heap/maxHeap.c src/TDAs/tuple/tuple.c src/TDAs/arraylist/arraylist.c -lncurses -o binary/chess.out 

printf "Compilado\n";
./binary/chess.out