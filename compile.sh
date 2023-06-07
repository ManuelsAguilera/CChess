#!bin/bash

gcc src/menu.c src/players.c src/main.c src/TDAs/hashmap/hashmap.c -o binary/chess.out

printf "Compilado\n";
./binary/chess.out